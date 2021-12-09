#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include "constants.h"
#include "../table/typedefs.h"
using namespace std;
enum TOKEN_TYPE {
    UNKNOWN,
    TOKEN_STR,
    SET,
    LOGIC_OR,
    LOGIC_AND,
    RELATIONAL,
    L_PARENTHESIS,
    R_PARENTHESIS,
};

class Token
{
public:
    Token();
    Token(string str);
    Token(string str, int type);
    virtual TOKEN_TYPE get_type() const;
    virtual vectorlong eval(vectorlong left, vectorlong right);
    virtual vectorlong eval(const map_sl& fieldMap, const vector<mmap_sl*>& index, Token* left, Token* right);
    virtual vectorlong recnos();
    friend ostream& operator <<(ostream& outs, const Token* &t);


    friend ostream& operator <<(ostream& outs, const Token &t);
    int type() const;
    string type_string() const;
    string token_str() const;
private:
    string _token;
    int _type;
};

#endif //TOKEN_H