#include "ftokenize.h"
    FTokenizer::FTokenizer(char* fname) {
        _f.open(fname);
        _pos = 0;
        // _stk = STokenizer(new_array);
        _stk = STokenizer();

        _more = true;
        get_new_block();
        _blockPos = 0;


    }
    Token FTokenizer::next_token() {
        if(_stk.done()) {
            get_new_block();
        }
        Token t;
        _stk >> t;
        return t;
    }
    bool FTokenizer::more() {
        return _more;
        // if(_f.eof() && _stk.done()) {
        //     return false;
        // }
    }        //returns the current value of _more
    int FTokenizer::pos() {
        return _pos;
    }          //returns the value of _pos
    int FTokenizer::block_pos() {
        return _blockPos;
    }     //returns the value of _blockPos
    FTokenizer& operator >> (FTokenizer& f, Token& t) {
        t = f.next_token();
        return f;
    }
    bool FTokenizer::get_new_block() {
        // if(_f.eof())
        // {
        //     return false;
        // }
        char new_block[MAX_BUFFER];
        for(int i = 0; i < MAX_BUFFER; i++) {
            new_block[i] = '\0';
        }
        if(!_f.eof()) {
            _more = true;
            _f.read(new_block, MAX_BUFFER-1);
            _stk = STokenizer(new_block);
            _pos = _f.tellg();
            return true;
        }
        _more = false;
        return false;
    } //gets the new block from the file
