#ifndef RPN_H
#define RPN_H
#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"
#include "../token/child_tokens.h"
#include "../table/typedefs.h"
using namespace std;
class RPN { //rpn evaluates postfix and turns it into a vector<long> answer that is returned
    public:
        RPN();
        RPN(const Queue<Token*>& post_fix);
        ~RPN();
        RPN(const RPN& copyme);
        RPN& operator= (const RPN& rhs);
        void set_input(Queue<Token*> &post_fix);
        vectorlong eval(const map_sl& fieldMap, const vector<mmap_sl*>& index);
    private:
        Queue<Token*> _post_fix;
        vectorlong _answer;
        bool _evaluated;
};

#endif //RPN_H