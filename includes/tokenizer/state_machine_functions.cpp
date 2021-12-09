#include "state_machine_functions.h"

//Fill all cells of the array with -1
void init_table(int _table[][MAX_COLUMNS]) {
    for( int i = 0; i < MAX_ROWS; i++) {
        for(int j = 0; j < MAX_COLUMNS; j++) {
            _table[i][j] = -1;
        }
    }
}

//Mark this state (row) with a 1 (success)
void mark_success(int _table[][MAX_COLUMNS], int state) {
    _table[state][0] = 1;
}

//Mark this state (row) with a 0 (fail)
void mark_fail(int _table[][MAX_COLUMNS], int state) {
    _table[state][0] = 0;
}

//true if state is a success state
bool is_success(int _table[][MAX_COLUMNS], int state) {
    if(_table[state][0] == 1) {
        return true;
    }
    return false;
}

//Mark a range of cells in the array. 
void mark_cells(int row, int _table[][MAX_COLUMNS], int from, int to, int state) {
    for(int i = from; i <= to; i++) {
        _table[row][i] = state;
    }
}

//Mark columns represented by the string columns[] for this row
void mark_cells(int row, int _table[][MAX_COLUMNS], const char columns[], int state) {
    for(int i = 0; i <strlen(columns); i++) {
        _table[row][columns[i]] = state;
    }
}

//Mark this row and column
void mark_cell(int row, int table[][MAX_COLUMNS], int column, int state) {
    table[row][column] = state;
}

//This can realistically be used on a small table
void print_table(int _table[][MAX_COLUMNS]) {
    for(int row = 0; row < MAX_ROWS; row++) {
        for(int col = 0; col < MAX_COLUMNS; col++) {
            cout << _table[row][col] << " ";
        }
        cout << endl;
    }
}

//show string s and mark this position on the string:
//hello world   pos: 7
//       ^
void show_string(char s[], int _pos) {
    for( int i = 0; i < strlen(s); i++) {
        cout << s[i];
    }
    cout << endl;
    for(int i = 0; i < strlen(s); i++) {
        if(i!=_pos) {
            cout << " ";
        }
        else {
            cout << "^";
        }
    }
}