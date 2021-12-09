#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "includes/sql/sql.h"
#include "includes/table/table.h"

using namespace std;

int main(int argv, char** argc) {
    int input = 0;
    string table_name;
    string fields;
    string condition;
    string values;
    string complete_command;
    string which;
    SQL sql;
    Table t;
    while(input != 5) {
        cout << "Enter 1 to start creating/making a table" << endl;
        cout << "Enter 2 to start inserting values into the table" << endl;
        cout << "Enter 3 to get a table of selected fields and conditions" << endl;
        cout << "Enter 4 to put in a custom command" << endl;
        cout << "Enter 5 to end the process" << endl;
        cout << "Enter one of these five numbers here: ";
        cin >> input;
            if(input == 1) {
                cout << "You have chosen to create/make a table: " << endl;
                cout << "Please enter the table name here: ";
                cin >> table_name;
                cout << "Please enter the fields here with commas in between: " ;
                cin.ignore(6,'\n');
                cin.clear();
                getline(cin, fields);
                complete_command = "create table "+ table_name + " fields "+ fields;              
                t = sql.command(complete_command);
                cout << t << endl;
            }
            if(input == 2) {
                cout << "You have chosen to insert values into the table: " << endl;
                cout << "Please enter the table name you would like to insert into: " << endl; 
                cin >> table_name;
                cout <<"Pease enter the values you would like to insert: " << endl;
                cin.ignore(6,'\n');
                cin.clear();
                getline(cin, values);
                complete_command = "insert into " + table_name + " values " + values;
                t = sql.command(complete_command);
                cout << t << endl;
            }
            if(input == 3) {
                cout << "You have chosen to obtain a table of selected fields and conditions: " << endl;
                cout << "Please enter the table you would like to open: " << endl;
                cin >> table_name;
                cout << "Please enter the field(s) you would like from the table: * can be used as replacement for all fields" << endl;
                cin.ignore(6,'\n');
                cin.clear();
                getline(cin, fields);
                cout << "Do you have conditions you would like to place? If yes: type yes" << endl;
                cin >> which;
                if(which == "yes") {
                    cout << "Here is how to do it:" << endl;
                    cout << "                    where <FIELD_NAME> <RELATIONAL_OPERATOR> <VALUE>" << endl;
                    cout << "                        [<LOGICAL_OPERATOR> " << endl;
                    cout << "                           <FIELD_NAME> <RELATIONAL_OPERATOR> <VALUE>...]" << endl;
                    cin.ignore(6, '\n');
                    cin.clear();
                    getline(cin, condition);
                    complete_command = "select "+fields+" from "+table_name + " where "+condition;
                    t = sql.command(complete_command);
                    cout << t << endl;
                }
                else {
                    complete_command = "select "+fields+" from "+table_name;
                    t = sql.command(complete_command);
                    cout << t << endl;
                }
            }
            if(input == 4) {
                cout <<"Here is how to create inputs for the database to respond to: " << endl;
                cout << "<CREATE | MAKE> : {  <create | make> table <TABLE_NAME> fields <FIELD_NAME> [, <FIELD_NAME>...]  }" << endl;
                cout << "<INSERT> : { insert <INTO> <TABLE_NAME> values <VALUE> [, <VALUE>...]      }" << endl;
                cout << "<SELECT> : {  select <* | FIELD_NAME> [, ,FIELD_NAME>...]" << endl;
                cout << "                    from <TABLE_NAME>" << endl;
                cout << "                    where <FIELD_NAME> <RELATIONAL_OPERATOR> <VALUE>" << endl;
                cout << "                        [<LOGICAL_OPERATOR> " << endl;
                cout << "                           <FIELD_NAME> <RELATIONAL_OPERATOR> <VALUE>...]" << endl;
                cout << endl;
                cout << "<VALUE>  : A string of alphanumeric characters, or a string of alphanumeric" << endl;
                cout << "           characters and spaces enclosed by double quotation marks:" << endl;
                cout << "           \"Jean Luise\", Finch, 1923" << endl;
                cout << "<RELATIONAL OPERATOR> : [ = | > | < | >= | <= ]" << endl;
                cout << "<LOGICAL OPERATOR>    : [and | or]" << endl;
                cin.ignore(6, '\n');
                cin.clear();
                getline(cin, complete_command);
                t = sql.command(complete_command);
                cout << t << endl;
        }
    cout << "Enter 1 to start creating/making a table" << endl;
    cout << "Enter 2 to start inserting values into the table" << endl;
    cout << "Enter 3 to get a table of selected fields and conditions" << endl;
    cout << "Enter 4 to put in a custom command" << endl;
    cout << "Enter 5 to end the process" << endl;
    cout << "Enter one of these five numbers here: ";
    cin.ignore(6,'\n');
    cin.clear();
    cin >> input;

    }
}
