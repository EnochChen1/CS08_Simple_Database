#include "sql.h"

SQL::SQL() {
    t = Table();
    _recnos_vector = vectorlong();
}

Table SQL::command(string line) {
    char s[300]; //create a char array
    strcpy(s, line.c_str()); //copies the string line to the char array
    Parser parser(s); //creates a Parser constructor, with the input as a command
    mmap_ss ptree; //create a mmap_ss
    ptree = parser.parse_tree(); //sets the ptree to a parse tree
    if(ptree["command"][0] == "make" || ptree["command"][0] == "create") { //this creates a table, must be 
        Table t(ptree["table_name"][0], ptree["fields"]); //gets the table_name from the command
        _recnos_vector = t.select_recnos(); //sets the recnos vector to the table's recnos list
        return t;   //returns the new table
    }
    if(ptree["command"][0] == "select") { //select
        Table t(ptree["table_name"][0]); // checks which table to be accessed
        if(ptree["fields"][0] == "*") { //if fields = star, means wants all field names
            if(ptree.contains("condition")) { // if there is a condition, this is accessed
                t.select(t.get_fields(), ptree["condition"]); // condition is sent to select function as ab infix vector string
                _recnos_vector = t.select_recnos(); //sets recnos vector to the select table's recnos list
                return t; //returns select table
            }
            else {
                t.select_all(); //returns the select_all as essentially a copy of the original table
                _recnos_vector = t.select_recnos(); // sets the recnos vector to the select table's recno list
                return t;   //return select table
            }
        }
        else {
            if(ptree.contains("condition")) {   //else if it contains a condition
                t.select(ptree["fields"], ptree["condition"]);//checks the fields ptree has obtained, and puts the condition into the select
                _recnos_vector = t.select_recnos(); //sets recnos vector to the select table's recno list
                return t; //return the select table
            }
            else {
                t.set_fields(ptree["fields"]); //sets the fields to the ptree fields for the table
                t.select_all(); // then calls select_all on those fields specificly
                _recnos_vector = t.select_recnos(); //sets recnos vector to the select table's recno list
                return t; // return the select table
            }
        }
    }
    if(ptree["command"][0] == "insert") {
        Table t(ptree["table_name"][0]);//checks the table_name to be opened
        t.insert_into(ptree["values"]); //then inserts the ptree values as a record
        _recnos_vector = t.select_recnos(); // then sets the recnos vector to the specific table's recnos list
        return t; //returns the specific table opened
    }
    if(ptree["command"][0] == "drop") {
        cout << "No clue, don't have remove for BPlusTree"; // don't know how to do this lol
    }
}

vectorlong SQL::select_recnos() {
    return _recnos_vector; //returns the recnos vector if needed outside of the class
}