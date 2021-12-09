#ifndef FTOKENIZE_H
#define FTOKENIZE_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include "../token/token.h"
#include "../token/constants.h"
#include "state_machine_functions.h"
#include "stokenize.h"

using namespace std;
class FTokenizer
{
public:
    const int MAX_BLOCK = MAX_BUFFER;
    FTokenizer(char* fname);
    Token next_token();
    bool more();        //returns the current value of _more
    int pos();          //returns the value of _pos
    int block_pos();     //returns the value of _blockPos
    friend FTokenizer& operator >> (FTokenizer& f, Token& t);
private:
    bool get_new_block(); //gets the new block from the file
    std::ifstream _f;   //file being tokenized
    STokenizer _stk;     //The STokenizer object to tokenize current block
    int _pos;           //Current position in the file
    int _blockPos;      //Current position in the current block
    bool _more;         //false if last token of the last block
                        //  has been processed and now we are at
                        //  the end of the last block.
};

#endif //FTOKENIZE_H