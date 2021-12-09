#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H
#include <iostream>
#include <iomanip>
#include <vector>
#include <cassert>
#include "../stack/MyStack.h"
#include "../queue/MyQueue.h"
#include "../token/child_tokens.h"
Queue<Token*> conversion_to_queue_from_infix(const vectorstr& infix);
using namespace std;
class ShuntingYard {
    public:
        ShuntingYard();
        ShuntingYard(Queue<Token *> infix_queue);
        ~ShuntingYard();
        ShuntingYard(const ShuntingYard &copyMe);
        ShuntingYard& operator= (const ShuntingYard& rhs);
        void infix(Queue<Token *> infix_queue);
        Queue<Token *> postfix();
        Queue<Token *> postfix(Queue<Token *> infix_queue);
    private:
        vectorstr _infix;
        Queue<Token *> _infix_queue;
        Queue<Token *> postfix_answer;
        bool _conversion_complete;

};


#endif //SHUNTING_YARD_H