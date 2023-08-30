#include "child_tokens.h" 

TokenStr::TokenStr(string token_string) : Token(token_string) {
    _type_enum = TOKEN_STR;
}

TOKEN_TYPE TokenStr::get_type() const{
    return _type_enum;
}

LeftParenthesis::LeftParenthesis() : Token("(") {
    _type_enum = L_PARENTHESIS;
}

TOKEN_TYPE LeftParenthesis::get_type() const{
    return _type_enum;
}

RightParenthesis::RightParenthesis() : Token(")") {
    _type_enum = R_PARENTHESIS;
}

TOKEN_TYPE RightParenthesis::get_type() const{
    return _type_enum;
}
ResultSet::ResultSet() : Token("") {
    _type_enum = SET;
}

ResultSet::ResultSet(vectorlong recons) : Token("") {
    _type_enum = SET;
    _recnos = recons;
}

TOKEN_TYPE ResultSet::get_type() const{
    return _type_enum;
}

vectorlong ResultSet::recnos() {
    return _recnos;
}

Relational::Relational(string s) : Token(s) {
    _type_enum = RELATIONAL;
}

TOKEN_TYPE Relational::get_type() const{
    return _type_enum;
}

vectorlong Relational::eval(const map_sl &fieldMap,const vector<mmap_sl *>& index, Token *left, Token *right) {
    vectorlong results;
    if(fieldMap.contains(left -> token_str())) {
        if(token_str() == "=") {
                results = (*index[fieldMap.at(left -> token_str())])[right -> token_str()];
        }
        else if(token_str() == "<") {
            mmap_sl::Iterator it_begins = index[fieldMap.at(left -> token_str())] -> begin();
            mmap_sl::Iterator it_ends = index[fieldMap.at(left -> token_str())] -> lower_bound(right -> token_str());
            for(; it_begins != it_ends; it_begins++) {
                for(int i = 0; i < (*it_begins).value_list.size(); i++) {
                    results.push_back((*it_begins).value_list[i]);
                }
            }
            // if((*it_begins).key <= (*it_ends).key) { //this is hackish shit that messed up my shit
            //     for(int i = 0; i < (*it_begins).value_list.size(); i++) {
            //         results.push_back((*it_begins).value_list[i]);
            //     }
            // }
        }
        else if(token_str() == ">") {
        mmap_sl::Iterator it_begins = index[fieldMap.at(left -> token_str())] -> upper_bound(right -> token_str());
        mmap_sl::Iterator it_ends = index[fieldMap.at(left -> token_str())] -> end();
            for(; it_begins != it_ends; it_begins++) {
                for(int i = 0; i < (*it_begins).value_list.size(); i++) {
                    results.push_back((*it_begins).value_list[i]);
                }
            }
        }
        else if(token_str() == "<=") {
        mmap_sl::Iterator it_begins = index[fieldMap.at(left -> token_str())] -> begin();
        mmap_sl::Iterator it_ends = index[fieldMap.at(left -> token_str())] -> upper_bound(right -> token_str());
            for(; it_begins != it_ends; it_begins++) {
                for(int i = 0; i < (*it_begins).value_list.size(); i++) {
                    results.push_back((*it_begins).value_list[i]);
                }
            }
        }
        else if(token_str() == ">=") {
        mmap_sl::Iterator it_begins = index[fieldMap.at(left -> token_str())] -> lower_bound(right -> token_str());
        mmap_sl::Iterator it_ends = index[fieldMap.at(left -> token_str())] -> end();
            for(; it_begins != it_ends; it_begins++) {
                for(int i = 0; i < (*it_begins).value_list.size(); i++) {
                    results.push_back((*it_begins).value_list[i]);
                }
            }
        }
    }
    return results;
}


Logical::Logical(string s) : Token(s) {
    if(s == "and") {
        _type_enum = LOGIC_AND;
    }
    else if(s == "or") {
        _type_enum = LOGIC_OR;
    }
}
TOKEN_TYPE Logical::get_type() const {
    return _type_enum;
}

vectorlong Logical::eval(vectorlong left, vectorlong right) {
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    vectorlong results;
    if(_type_enum == LOGIC_AND) {
        set_intersection(left.begin(), left.end(), right.begin(), right.end(), back_inserter(results));
    }
    else if (_type_enum == LOGIC_OR) {
        set_union(left.begin(), left.end(), right.begin(), right.end(), back_inserter(results));
    }
    return results;
}
