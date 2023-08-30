#include "shunting_yard.h"
Queue<Token*> conversion_to_queue_from_infix(const vectorstr& infix) {
    Queue<Token*> conversion_from_infix_to_token;
    for(int i = 0; i < infix.size(); i++) {
        if(infix[i] == "or") {
            conversion_from_infix_to_token.push(new Logical("or"));
        }
        else if(infix[i] == "and") {
            conversion_from_infix_to_token.push(new Logical("and"));
        } 
        else if(infix[i] == "=") {
            conversion_from_infix_to_token.push(new Relational("="));
        }
        else if(infix[i] == ">") {
            conversion_from_infix_to_token.push(new Relational(">"));
        }
        else if(infix[i] == "<") {
            conversion_from_infix_to_token.push(new Relational("<"));
        }
        else if(infix[i] == ">=") {
            conversion_from_infix_to_token.push(new Relational(">="));
        }
        else if(infix[i] == "<=") {
            conversion_from_infix_to_token.push(new Relational("<="));
        }
        else if(infix[i] == "("){
            conversion_from_infix_to_token.push(new LeftParenthesis());
        }
        else if(infix[i] == ")"){
            conversion_from_infix_to_token.push(new RightParenthesis());
        }
        else {
            conversion_from_infix_to_token.push(new TokenStr(infix[i]));
        }
    }
    return conversion_from_infix_to_token;
}

ShuntingYard::ShuntingYard() {
    _infix_queue = Queue<Token *>();
    postfix_answer = Queue<Token *>();
    _conversion_complete = false;
}

ShuntingYard::ShuntingYard(Queue<Token *> infix_queue) {
    _infix_queue = infix_queue;
    postfix_answer = Queue<Token *>();
    _conversion_complete = false;
}

ShuntingYard::~ShuntingYard() {

}

ShuntingYard::ShuntingYard(const ShuntingYard &copyMe) {
    _infix_queue = copyMe._infix_queue;
    postfix_answer = copyMe.postfix_answer;
    _conversion_complete = copyMe._conversion_complete;
}

ShuntingYard& ShuntingYard::operator= (const ShuntingYard& rhs) {
    if(this != &rhs) {
        _infix_queue = rhs._infix_queue;
        postfix_answer = rhs.postfix_answer;
        _conversion_complete = rhs._conversion_complete;
    }
    return *this;
}

void ShuntingYard::infix(Queue<Token *> infix_queue) {
    _infix_queue = infix_queue;
    _conversion_complete = false;
}

Queue<Token *> ShuntingYard::postfix() {
    if(!_conversion_complete) {
        postfix_answer = Queue<Token *>();
        Stack<Token *> work_stack;
        while(!(_infix_queue.empty())) {
            Token* token_entry =_infix_queue.pop();
            // cout << token_entry->token_str() << endl;
            if(token_entry -> get_type() <= TOKEN_STR) {
                postfix_answer.push(token_entry);
            }
            if((token_entry -> get_type() >= LOGIC_OR) && (token_entry -> get_type()) <= RELATIONAL) {
                while(!(work_stack.empty())
                 && (work_stack.top() -> get_type() >= token_entry -> get_type() ) 
                 && work_stack.top() -> get_type() != L_PARENTHESIS) { //might need to do something involving precedence
                    Token* something = work_stack.pop();
                    // cout <<"work stack pop: "<< something ->token_str() << endl;
                    postfix_answer.push(something);
                    Queue<Token *>::Iterator it = postfix_answer.begin();
                    for(; it != postfix_answer.end(); it++) {
                        // cout <<"postfix_answer: "<< (*it)->token_str() << endl;
                    }
                }
                work_stack.push(token_entry);
            }
            if(token_entry -> get_type() == L_PARENTHESIS) {
                work_stack.push(token_entry);
            }
            if(token_entry -> get_type() == R_PARENTHESIS) {
                while(work_stack.top() -> get_type() != L_PARENTHESIS) {
                    postfix_answer.push(work_stack.pop());
                }
                if(work_stack.top() -> get_type() == L_PARENTHESIS) {
                    work_stack.pop();
                }
            }
        }
        while(!(work_stack.empty())) {
            postfix_answer.push(work_stack.pop());
        }
        _conversion_complete = true;
    }
    return postfix_answer;
}

Queue<Token *> ShuntingYard::postfix(Queue<Token* > infix_queue) {
    _infix_queue = infix_queue;
    _conversion_complete = false;
    return postfix();
}