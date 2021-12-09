//     #include "stokenize.h"
    
//     int STokenizer::_table[MAX_ROWS][MAX_COLUMNS];

//     STokenizer::STokenizer() {
//         for (int i = 0; i < MAX_BUFFER; i++) {
//             _buffer[i] = '\0';
//         }
//         _pos = 0;
//         make_table(_table);
//     }   
//     STokenizer::STokenizer(char str[]) {
//         for (int i = 0; i < MAX_BUFFER; i++) {
//             _buffer[i] = '\0';
//         }
//         for(int i = 0; i < strlen(str); i++) {
//             _buffer[i] = str[i];
//         }
//         _pos = 0;
//         make_table(_table);
//     }

//     bool STokenizer::done() {
//         if(_buffer[_pos] == '\0') {
//             return true;
//         }
//         return false;
//     }           //true: there are no more tokens
//     bool STokenizer::more() {
//     if (_pos <= strlen(_buffer)) {
//         return true;
//     }
//     return false;
//     }    //true: there are more tokens
//     //

//     //---------------
//     //extract one token (very similar to the way cin >> works)
//     STokenizer& operator >> (STokenizer& s, Token& t) {
//         char temp = s._buffer[s._pos];
//         string emptyString = "";
//         int startState = 0;
//         int type = -1;
//         if(isdigit(temp)) {
//             type = 1;
//             startState = START_DOUBLE;
//         }
//         if(isalpha(temp)) {
//             type = 2;
//         }
//         if(isspace(temp)) {
//             type = 3;
//         }
//         for(int i = 0; i < strlen(PUNC); i++) {
//             if(temp == (PUNC[i])) {
//                 type = 5;
//             }
//         }
//         for(int i = 0; i < strlen(OPERATORS); i++) {
//             if(temp == (OPERATORS[i])) {
//                 type = 4;
//             }
//         }
//         if (temp == '\"') {
//         type = TOKEN_ALPHA;
//     }

//         s.get_token(0, emptyString);
//         t = Token(emptyString, type);
//         return s;
//     }

//     //set a new string as the input string
//     void STokenizer::set_string(char str[]) {
//         for (int i = 0; i < MAX_BUFFER; i++) {
//             _buffer[i] = '\0';
//         }
//         for(int i = 0; i < strlen(str); i++) {
//             _buffer[i] = str[i];
//         }
//     }
// // create table for all the tokens we will recognize
// //                      (e.g. doubles, words, etc.)
// void STokenizer::make_table(int _table[][MAX_COLUMNS]) {
//     init_table(_table);

//     // DOUBLES:
//     mark_fail(_table, START_DOUBLE);                //Mark states 0 and 2 as fail states
//     mark_success(_table, 1);                        //Mark states 1 and 3 as success states
//     mark_fail(_table, 2);
//     mark_success(_table, 3);

//     mark_cells(START_DOUBLE, _table, DIGITS, 1);    //state [0] --- DIGITS ---> [1]
//     mark_cell(START_DOUBLE, _table, '.', 2);        //state [0] --- '.' ------> [2] 
//     mark_cells(1, _table, DIGITS, 1);               //state [1] --- DIGITS ---> [1]
//     mark_cell(1, _table, '.', 2);                   //state [1] --- '.' ------> [2] 
//     mark_cells(2, _table, DIGITS, 3);               //state [2] --- DIGITS ---> [3]
//     mark_cells(3, _table, DIGITS, 3);               //state [3] --- DIGITS ---> [3]


//     // SPACES:
//     mark_fail(_table, START_SPACES);
//     mark_success(_table, 5);

//     mark_cells(START_SPACES, _table, SPACES, 5);
//     mark_cells(5, _table, SPACES, 5);


//     // ALPHA:
//     mark_fail(_table, START_ALPHA);
//     mark_success(_table, 7);

//     mark_cells(START_ALPHA, _table, ALFA, 7);
//     mark_cells(7, _table, ALFA, 7);
//     mark_cells(7, _table, DIGITS, 7);
//     mark_cell(START_ALPHA, _table, '\"', 8);
//     mark_fail(_table, 8);
//     mark_cells(8, _table, ALFA, 8);
//     mark_cells(8, _table, DIGITS, 8);
//     mark_cells(8, _table, OPERATORS, 8);
//     mark_cells(8, _table, SPACES, 8);
//     mark_cells(8, _table, PUNC, 8);
//     mark_cell(8, _table, '\"', 9);
//     mark_success(_table, 9);

//     // PUNC:
//     mark_fail(_table, START_PUNC);
//     mark_success(_table, 11);

//     mark_cells(START_PUNC, _table, PUNC, 11);
//     mark_cells(11, _table, PUNC, 11);
    

//     // OPERATORS:
//     mark_fail(_table, START_OPERATOR);
//     mark_success(_table, 21);

//     mark_cells(START_OPERATOR, _table, OPERATORS, 21);
//     mark_cells(21, _table, OPERATORS, 21);
// }



//     // extract the longest string that match
//     // one of the acceptable token types
// bool STokenizer::get_token(int start_state, string& token) {
//     int success = _pos;
//     token = "";

//     for (int i = _pos; i < strlen(_buffer); i++) {
//         if (_buffer[i] < 0) {
//             start_state = _table[start_state][MAX_COLUMNS + _buffer[i]];
//         }
//         else {
//             start_state = _table[start_state][_buffer[i]];
//         }

//         if (is_success(_table, start_state)) {
//             success = i;
//         }
        
//         if (start_state == -1 || _buffer[i] == '\0') {
//             break;
//         }
//     }

//     for (int i = _pos ; i <= success; i++) {
//         if (_buffer[i] != '\"') {
//             token += _buffer[i];
//         }
//     }

//     _pos = success + 1;

//     if (token.length() == 0) {
//         return false;
//     }
//     return true;
// }
#include "stokenize.h" 

int STokenizer::_table[MAX_ROWS][MAX_COLUMNS];

STokenizer::STokenizer() { //default constructor
    for (int i = 0; i < MAX_BUFFER; i++) {
        _buffer[i] = '\0'; //sets buffer to null
    }
    _pos = 0;
    make_table(_table);
}

STokenizer::STokenizer(char str[]) {
    for (int i = 0; i < MAX_BUFFER; i++) {
        _buffer[i] = '\0';
    }
    for (int i = 0; i < strlen(str); i++) {
        _buffer[i] = str[i];        //constructor sets buffer to string
    }
    _pos = 0;
    make_table(_table);
}

bool STokenizer::done() {
    if (_buffer[_pos] == '\0') {    //if empty, returns true
        return true;
    }
    return false;
}

bool STokenizer::more() {
    if (_pos <= strlen(_buffer)) {
        return true; //if there is more, return true
    }
    return false;
}

//

//---------------
//friend, no scope resolution required
//extract one token (very similar to the way cin >> works)
STokenizer& operator >> (STokenizer& s, Token& t) {
    string some_string = "";
    int start_state = START_DOUBLE;     //changes the start state based on what type of token is obtained later, started with doubles
    int type = TOKEN_UNKNOWN;           //changes type based on what token's type is
    char check = s._buffer[s._pos]; //goes through the buffer

    for (int i = 0; i < strlen(DIGITS); i++) {
        if (check == DIGITS[i]) {
            start_state = START_DOUBLE;
            type = TOKEN_NUMBER;
        }
    }

    for (int i = 0; i < strlen(ALFA); i++) {
        if (check == ALFA[i]) {
            start_state = START_ALPHA;
            type = TOKEN_ALPHA;
        }
    }

    if (check == '\"') {
        start_state = START_ALPHA;
        type = TOKEN_ALPHA;
    }

    for (int i = 0; i < strlen(SPACES); i++) {
        if (check == SPACES[i]) {
            start_state = START_SPACES;
            type = TOKEN_SPACE;
        }
    }

    for (int i = 0; i < strlen(OPERATORS); i++) {
        if (check == OPERATORS[i]) {
            start_state = START_OPERATOR;
            type = TOKEN_OPERATOR;
        }
    }

    for (int i = 0; i < strlen(PUNC); i++) {
        if (check == PUNC[i]) {
            start_state = START_PUNC;
            type = TOKEN_PUNC;
        }
    }
    s.get_token(start_state, some_string);
    if (some_string == "í") {
        some_string = char(161);
    }
    t = Token(some_string, type);
    // cout << some_string << endl;
    return s;
}

//set a new string as the input string
void STokenizer::set_string(char str[]) {
    for (int i = 0; i < MAX_BUFFER; i++) {
        _buffer[i] = '\0';      //empties buffer so there will not be any junk left from previous inputs in buffer
    }
    for (int i = 0; i < strlen(str); i++) {
        _buffer[i] = str[i];    //then sets buffer to char string array
    }
}

// create table for all the tokens we will recognize
//                      (e.g. doubles, words, etc.)
void STokenizer::make_table(int _table[][MAX_COLUMNS]) {
    init_table(_table);

    // Marking DOUBLES Success and Failures:
    mark_fail(_table, START_DOUBLE);                //Mark states 0 and 2 as fail states
    mark_success(_table, START_DOUBLE + 1);                        //Mark states 1 and 3 as success states
    mark_fail(_table, START_DOUBLE + 2);
    mark_success(_table, START_DOUBLE + 3);

     // Marking SPACES Success and Failures:
    mark_fail(_table, START_SPACES);
    mark_success(_table, START_SPACES + 1);

    //Marking Alphabet Success and Failures:
    mark_fail(_table, START_ALPHA);
    mark_success(_table, START_ALPHA + 1);
    //mark fail and success for quotations
    mark_fail(_table, START_ALPHA + 2);
    mark_success(_table, START_ALPHA + 3);

    //Marking Punctuation without quotations fail and success
    mark_fail(_table, START_PUNC);
    mark_success(_table, START_PUNC + 1);

    //Marking Operators fail and success
    mark_fail(_table, START_OPERATOR);
    mark_success(_table, START_OPERATOR + 1);

    //DOUBLES
    mark_cells(START_DOUBLE, _table, DIGITS, START_DOUBLE + 1);     //state [0] --- DIGITS ---> [1]
    mark_cell(START_DOUBLE, _table, '.', START_DOUBLE + 2);         //state [0] --- '.' ------> [2] 
    mark_cells(START_DOUBLE + 1, _table, DIGITS, START_DOUBLE + 1); //state [1] --- DIGITS ---> [1]
    mark_cell(START_DOUBLE + 1, _table, '.', START_DOUBLE + 2);     //state [1] --- '.' ------> [2] 
    mark_cells(START_DOUBLE + 2, _table, DIGITS, START_DOUBLE + 3); //state [2] --- DIGITS ---> [3]
    mark_cells(START_DOUBLE + 3, _table, DIGITS, START_DOUBLE + 3); //state [3] --- DIGITS ---> [3]


    //SPACES
    mark_cells(START_SPACES, _table, SPACES, START_SPACES + 1);    //goes to SPACE machine
    mark_cells(START_SPACES + 1, _table, SPACES, START_SPACES + 1);   //if spaces are repeated success state is repeated


    // ALPHA
    mark_cells(START_ALPHA, _table, ALFA, START_ALPHA + 1);   //if in the alphabet comes here
    mark_cells(START_ALPHA + 1, _table, ALFA, START_ALPHA + 1); //if repeated it stays and repeats as a success state
    mark_cells(START_ALPHA, _table, DIGITS, START_ALPHA);
    mark_cell(START_ALPHA, _table, '\"', START_ALPHA + 2); // for quotations
    mark_cells(START_ALPHA + 2, _table, ALFA, START_ALPHA + 2); // all other things can go through
    mark_cells(START_ALPHA + 2, _table, DIGITS, START_ALPHA + 2);
    mark_cells(START_ALPHA + 2, _table, OPERATORS, START_ALPHA + 2);
    mark_cells(START_ALPHA + 2, _table, SPACES, START_ALPHA + 2);
    mark_cells(START_ALPHA + 2, _table, PUNC, START_ALPHA + 2);
    mark_cell(START_ALPHA + 2, _table, '\"', START_ALPHA + 3); // becomes success state when second quotation is reached

    // PUNC:
    mark_cells(START_PUNC, _table, PUNC, START_PUNC + 1); //if punctuation besides quotations comes here
    mark_cells(START_PUNC + 1, _table, PUNC, START_PUNC + 1);   //if repeated
    

    // OPERATORS:
    mark_cells(START_OPERATOR, _table, OPERATORS, START_OPERATOR + 1);  //if operators comes here
    mark_cells(START_OPERATOR + 1, _table, OPERATORS, START_OPERATOR + 1); // if repeated
   
 }

//extract the longest string that match
//     one of the acceptable token types
bool STokenizer::get_token(int start_state, string& token) {
    int success = _pos;
    token = "";

    for (int i = _pos; i < strlen(_buffer); i++) {
        if (_buffer[i] < 0) {
            start_state = _table[start_state][MAX_COLUMNS + _buffer[i]]; //if buffer doesn't exits start state = -1
        }
        else {
            start_state = _table[start_state][_buffer[i]]; //else it goes to check the table and get the start state
        }

        if (is_success(_table, start_state)) {
            success = i;    //if it is a success state, puts last success state
        }
        
        if (start_state == -1 || _buffer[i] == '\0') {
            break;
        }
    }

    for (int i = _pos ; i <= success; i++) {
        if (_buffer[i] != '\"') {
            token += _buffer[i]; //if not quotation, token adds it
        }
    }

    _pos = success + 1;

    if (token.size() == 0) {
        return false;
    }
    return true;
}