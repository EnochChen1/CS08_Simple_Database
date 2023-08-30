#include "rpn.h"

RPN::RPN() { //rpn default constructer
    _post_fix = Queue<Token*>();
    _evaluated = false;
}

RPN::RPN(const Queue<Token*>& post_fix) {   //rpn constructor that sets rpns post_fix to the post_fix given
    _post_fix = post_fix;
    _evaluated = false;
}

RPN::~RPN() {

}

RPN::RPN(const RPN& copyme) {
    _post_fix = copyme._post_fix;
    _answer = copyme._answer;
    _evaluated = copyme._evaluated;
}

RPN& RPN::operator= (const RPN& rhs) {
    if(this != &rhs) {
        _post_fix = rhs._post_fix;
        _answer = rhs._answer;
        _evaluated = rhs._evaluated;
    }
    return *this;
}

void RPN::set_input(Queue<Token*> &post_fix) {
    _evaluated = false;
    _post_fix = post_fix;
}

vectorlong RPN::eval(const map_sl& fieldMap, const vector<mmap_sl*>& index) {
    if(!_evaluated) {
        // cout << "inside RPN::eval" << endl;
        Queue<Token*> pop_this = _post_fix;
        Stack<Token*> evaluate;
        // cout << "rpn "<<  pop_this.size() << endl;
        // cout << "rpn "<<boolalpha<<pop_this.empty() << endl;
        while(!pop_this.empty()) {
            // cout << "inside pop_this not empty" << endl;
            evaluate.push(pop_this.pop());
            if(evaluate.top() -> get_type() >= LOGIC_OR && evaluate.top() -> get_type() <= LOGIC_AND) {
                Token* operators = evaluate.pop();
                vectorlong right = evaluate.pop() -> recnos();
                vectorlong left = evaluate.pop() -> recnos();
                evaluate.push(new ResultSet(operators -> eval(left, right)));
            }
            if(evaluate.top() -> get_type() == RELATIONAL) {
                // cout << "inside relational" << endl;        
                Token* operators = evaluate.pop();
                // cout <<"operators: "<< operators->token_str() << endl;
                Token* right = evaluate.pop();
                // cout <<"right: "<< right -> token_str() << endl;
                Token* left = evaluate.pop();
                // cout << "left: " << left -> token_str() << endl;
                evaluate.push(new ResultSet(operators -> eval(fieldMap, index, left, right)));
                // cout << "ending relational" << endl;
            }
        }
        _answer = evaluate.pop() -> recnos();
        _evaluated = true;
    }
    return _answer;
}