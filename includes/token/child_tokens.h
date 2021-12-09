#ifndef CHILD_TOKEN_H
#define CHILD_TOKEN_H
#include <algorithm>
#include "token.h"
class TokenStr : public Token {
    public:
        TokenStr();
        TokenStr(string token_string);
        TOKEN_TYPE get_type() const;

    private:
        TOKEN_TYPE _type_enum;
};

class LeftParenthesis : public Token {
    public:
        LeftParenthesis();
        TOKEN_TYPE get_type() const;
    private:
        TOKEN_TYPE _type_enum;
};

class RightParenthesis : public Token {
    public:
        RightParenthesis();
        TOKEN_TYPE get_type() const;
    private:
        TOKEN_TYPE _type_enum;
};
class ResultSet : public Token{
    public:
        ResultSet();
        ResultSet(vectorlong recons);
        TOKEN_TYPE get_type() const;
        vectorlong recnos();

    private:
        TOKEN_TYPE _type_enum;
        vectorlong _recnos;
};

class Relational : public Token {
    public:
        Relational(string s);
        TOKEN_TYPE get_type() const;
        vectorlong eval(const map_sl& fieldMap, const vector<mmap_sl *>& index, Token* left, Token* right);
    private:
        TOKEN_TYPE _type_enum;
};

class Logical : public Token {
    public:
        Logical(string s);
        TOKEN_TYPE get_type() const;
        vectorlong eval(vectorlong left, vectorlong right);

    private:
        TOKEN_TYPE _type_enum;
};
#endif //CHILD_TOKEN_H