#include "token.h"
using namespace std;

Token::Token() {
    _token = "";
    _type = TOKEN_UNKNOWN;
}
Token::Token(string str) {
    _token = str;
    _type = TOKEN_UNKNOWN;
}
Token::Token(string str, int type) {
    _token = str;
    _type = type;
}

TOKEN_TYPE Token::get_type() const {
//virtual
}
vectorlong Token::eval(vectorlong left, vectorlong right) {
//virtual

}
vectorlong Token::eval(const map_sl& fieldMap, const vector<mmap_sl*>& index, Token* left, Token* right) {
//virtual

}
vectorlong Token::recnos() {
//virtual

}
ostream& operator <<(ostream& outs, const Token* &t) {
    outs << t -> _token;
    return outs;
}

ostream& operator <<(ostream& outs, const Token& t) {
        outs << t._token;
        return outs;
    }
int Token::type() const {
    return _type;
}
string Token::type_string() const {
    if(_type == 1) {
        return "NUMBER";
    }
    if(_type == 2) {
        return "ALPHA";
    }
    if(_type == 3) {
        return "SPACE";
    }
    if(_type == 4) {
        return "OPERATOR";
    }
    if(_type == 5) {
        return "PUNC";
    }
    if(_type == 6) {
        return "FOREIGN";
    }
    return "UNKNOWN";
    
}
string Token::token_str() const {
    return _token;
}