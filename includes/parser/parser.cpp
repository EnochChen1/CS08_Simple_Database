#include "parser.h"
int Parser::adjacency_table[MAX_ROWS][MAX_COLUMNS];
Parser::Parser() {
    for(int i = 0; i < MAX_BUFFER; i++) {
        _buffer[i] = '\0';
    }
    fail_flag = false;
    input_q = Queue<Token*>();
}

Parser::Parser(const char *s) {
    build_keyword_list();
    make_table();
    set_buffer(s);
    fail_flag = false;
    set_string(_buffer);

}

mmap_ss Parser::parse_tree() {
    return ptree;
}
void Parser::make_table() {
    init_table(adjacency_table); //sets everything to -1
    //select success states
    mark_success(adjacency_table, START_SELECT + 3); //by choosing a table name you come here from state 3
    mark_success(adjacency_table, START_SELECT + 5); //if you chose a condition, you come here from stage 5
    //create success states
    mark_success(adjacency_table, START_CREATE + 4); //end of create
    //make success state
    mark_success(adjacency_table, START_MAKE + 4); //end of make
    //drop successful state
    mark_success(adjacency_table, START_DROP + 2); // end of drop
    //insert success state
    mark_success(adjacency_table, START_INSERT + 4); //end of insert

    //time to mark cells
    //SELECT
    mark_cell(0, adjacency_table, SELECT, START_SELECT); //Used for select
    mark_cell(START_SELECT, adjacency_table, SYMBOL, START_SELECT +1); //Used for Symbol, also should be some field name
    mark_cell(START_SELECT + 1, adjacency_table, SYMBOL, START_SELECT + 1); // repeat field names if necessary
    mark_cell(START_SELECT + 1, adjacency_table, FROM, START_SELECT +2); //Used for from
    mark_cell(START_SELECT + 2, adjacency_table, SYMBOL, START_SELECT + 3); //for the table name, success state reached
    mark_cell(START_SELECT + 3, adjacency_table, WHERE, START_SELECT + 4); // from where to symbols/field names
    mark_cell(START_SELECT + 4, adjacency_table, SYMBOL, START_SELECT + 5); //success state reached
    mark_cell(START_SELECT + 5, adjacency_table, SYMBOL, START_SELECT + 5); //add more field names if necessary

    //CREATE

    mark_cell(0, adjacency_table, CREATE, START_CREATE); //both create and make use the same code since all that differs is the name
    mark_cell(0, adjacency_table, MAKE, START_CREATE); //access create
    mark_cell(START_CREATE, adjacency_table, TABLE, START_CREATE+1); //choose table
    mark_cell(START_CREATE+1, adjacency_table, SYMBOL, START_CREATE+2);//get table_name
    mark_cell(START_CREATE+2, adjacency_table, FIELDS, START_CREATE+3);//choose fields
    mark_cell(START_CREATE+3, adjacency_table, SYMBOL, START_CREATE+4);//get field names
    mark_cell(START_CREATE+4, adjacency_table, SYMBOL, START_CREATE+4);//more if needed

    //DROP

    mark_cell(0, adjacency_table, DROP, START_DROP); //goes to DROP
    mark_cell(START_DROP, adjacency_table, TABLE, START_DROP + 1); //goes to table
    mark_cell(START_DROP + 1, adjacency_table, SYMBOL, START_DROP + 2); //goes to name of table
    mark_cell(START_DROP + 2, adjacency_table, SYMBOL, START_DROP + 2); //repeated if necessary

    //INSERT INTO
    mark_cell(0, adjacency_table, INSERT, START_INSERT); //goes to INSERT
    mark_cell(START_INSERT, adjacency_table, INTO, START_INSERT + 1); // goes to into
    mark_cell(START_INSERT + 1, adjacency_table, SYMBOL, START_INSERT + 2); // goes to symbol
    mark_cell(START_INSERT + 2, adjacency_table, VALUES, START_INSERT + 3); //checks values
    mark_cell(START_INSERT + 3, adjacency_table, SYMBOL, START_INSERT + 4); //gets the name of values
    mark_cell(START_INSERT + 4, adjacency_table, SYMBOL, START_INSERT + 4); //gets more symbols if necessary
    //select
    mark_success(adjacency_table, START_SELECT+3); //mark_success for select, with no where
    mark_success(adjacency_table, START_SELECT+5); //mark success for select, with where condition
    //create/make
    mark_success(adjacency_table, START_CREATE+4); //success state for create
    //insert
    mark_success(adjacency_table, START_INSERT+4); //success state for insert
    //drop
    mark_success(adjacency_table, START_DROP+2); //success state for drop
}

void Parser::build_keyword_list() {
    vectorstr keywords {"zero","select", "from", "where", "create", "table", "fields", "make", "drop", "insert", "into", "values", "symbol"};
    for(int i = 0; i < keywords.size(); i++) {
        keywords_map.insert(keywords[i], i);
    }
}

void Parser::set_string(char* s) {
    ptree.clear(); // ptree is cleared just in case it had something inside
    input_q = Queue<Token*>(); //input queue is cleared
    // cout << "in the set_string" << endl;
    // cout << endl;
    // cout << "before stokenizer constructor" << endl;
    STokenizer stoken(s); //stokenizer is created
    Token* token_ptr = new Token();
    stoken >> *token_ptr; //then get the token from stokenizer
    // stoken.print_buffer();
    // cout << "after stokenizer constructor" << endl;
    while(stoken.more()) {
        if(token_ptr -> type() < 3 || token_ptr -> type() == 4) { //if it is a number, alphabet, or operator, it is pushed in to input_q
            input_q.push(token_ptr);
        }
        token_ptr = new Token(); //then token is reset
        stoken >> *token_ptr; //then token is obtained from stokenizer
    }
    get_parse_tree(); //parse_tree is called
}


bool Parser::fail() {
    return fail_flag; //return the fail_flag
}
bool Parser::get_parse_tree() {
    int state = 0;
    int col = 0;
    Token* popped;
    while(state != -1 && !(input_q.empty())) { // continues as long as fail state is not reached, and input_q is not empty
        popped = input_q.pop(); //pops input_q
        if(keywords_map.contains(popped -> token_str())) {//checks the token to see if it is in the enum keywords
            col = keywords_map[popped -> token_str()]; //if yes, col is set to whatever is in enums
        }
        else {
            col = SYMBOL; //otherwise
        }
        state = adjacency_table[state][col];
        switch(state)
        {
            //SELECT
            case START_SELECT: { //steps used in make table, put into the parsetree, if select, then puts select in
                ptree.get("command").push_back(popped -> token_str());
                break;
            }
            case START_SELECT + 1:{ //gets specific field names
                ptree.get("fields").push_back(popped -> token_str());
                break;
            }
            case START_SELECT + 3: {//gets name of table
                 ptree.get("table_name").push_back(popped -> token_str());
                break;
            }
            case START_SELECT + 4:{ //checks if there will be conditions
                ptree.get("where").push_back("yes");
                break;
            }
            case START_SELECT + 5:{ //get more 
                ptree.get("condition").push_back(popped -> token_str());
                break;
            }

            //CREATE
            case START_CREATE: {
                ptree.get("command").push_back(popped -> token_str());
                break;
            }
            case START_CREATE + 2: {
                ptree.get("table_name").push_back(popped -> token_str());
                break;
            }
            case START_CREATE + 4:{
                ptree.get("fields").push_back(popped -> token_str());
                break;
            }
            
            // //MAKE
            // case START_MAKE:
            // ptree.get("command").push_back(popped -> token_str()); //if make breaks, issue here or make_table
            // break;
            // case START_MAKE + 1:
            // ptree.get("table_name").push_back(popped -> token_str());
            // break;
            // case START_MAKE + 2:
            // ptree.get("fields").push_back(popped -> token_str());
            // break;
            //Drop
            case START_DROP:{
                ptree.get("command").push_back(popped -> token_str());
                break;
            }
            case START_DROP + 2: {
                ptree.get("table_name").push_back(popped -> token_str());
                break;
            }
            //Insert
            case START_INSERT: {
                ptree.get("command").push_back(popped -> token_str());
                break;
            }
            case START_INSERT + 1: {
                ptree.get("command").push_back(popped -> token_str());
                break;
            }
            case START_INSERT + 2: {
                ptree.get("table_name").push_back(popped -> token_str());
                break;
            }
            // case START_INSERT + 3:
            // ptree.get("values").push_back(popped -> token_str());
            // break;
            case START_INSERT + 4: {
                ptree.get("values").push_back(popped -> token_str());
                break;
            }
            default: {

            }
        }
    }
    if(state != -1) {
        fail_flag = true;
        return fail_flag;
    }
    else {
        ptree.clear();
        fail_flag = false;
        return fail_flag;
    }
}

void Parser::set_buffer(const char* s) {
    for(int i = 0; i < MAX_BUFFER; i++) {
        _buffer[i] = '\0';
    }
    for(int i = 0; i < strlen(s); i++) {
        _buffer[i] = s[i];
    }
}