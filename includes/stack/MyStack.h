#ifndef MY_STACK_H
#define MY_STACK_H

#include <iostream>
#include <iomanip>
#include "../linked_list_functions/linkedlistfunctionsTemplated.h"
using namespace std;
template <typename ITEM_TYPE>
class Stack{
public:
    class Iterator{
    public:
        friend class Stack;                 //give access to list to access _ptr
        Iterator(){_ptr = NULL;}                          //default ctor
        Iterator(node<ITEM_TYPE>* p): _ptr(p)
        {

        }
                            //Point Iterator to where
                                                          //  p is pointing to
        ITEM_TYPE operator *(){
            return _ptr -> _item;
        }    //dereference operator
        bool is_null(){
            return _ptr == NULL;
        }            //true if _ptr is NULL
        friend bool operator !=(const Iterator& left,
                                const Iterator& right)  //true if left != right
        {
            return left._ptr != right._ptr;
        }

        friend bool operator ==(const Iterator& left,
                                const Iterator& right)  //true if left == right
        {
            return left._ptr == right._ptr;
        }


        Iterator& operator++(){                         //member operator:++it
         _ptr = _ptr -> _next;                                        // or ++it = new_value
         return *this;                                          
            
        }

        friend Iterator operator++(Iterator& it,
                                   int unused){    
                                            //friend operator: it++
        assert(it._ptr!=NULL);
        Iterator hold;
        hold = it;
        it._ptr = it._ptr -> _next;
        return hold;
        }
    private:
        node<ITEM_TYPE>* _ptr;    //pointer being encapsulated
    };
    Stack();
    Stack(const Stack<ITEM_TYPE>& copyMe);
    ~Stack();
    Stack<ITEM_TYPE>& operator=(const Stack<ITEM_TYPE>& RHS);
    ITEM_TYPE top();
    bool empty();
    void push(ITEM_TYPE item);
    ITEM_TYPE pop();
    template<typename T>
    friend ostream& operator<<(ostream& outs, const Stack<T>& printMe) {
        node<T>* walker = printMe._top;
        while(walker != nullptr) {
            outs << "<-[" << walker -> _item <<"]->";
            walker = walker -> _next;
        }
        outs << "|||"<<endl;
        return outs;
    }    Iterator begin() const {                   //Iterator to the head node
    return Iterator(_top);
    }
    Iterator end() const {                     //Iterator to NULL
    return Iterator();
    }
    int size() const { return _size; }
    private:
    node<ITEM_TYPE>* _top;
    int _size;
};
    template <typename ITEM_TYPE>
    Stack<ITEM_TYPE>::Stack(): _top(nullptr), _size(0)
    {

    }
    template <typename ITEM_TYPE>
    Stack<ITEM_TYPE>::Stack(const Stack<ITEM_TYPE>& copyMe) {
        _top = _copy_list(copyMe._top);
        _size = copyMe._size;
    }
    template <typename ITEM_TYPE>
    Stack<ITEM_TYPE>::~Stack() {
        _clear_list(_top);
    }
    template <typename ITEM_TYPE>
    Stack<ITEM_TYPE>& Stack<ITEM_TYPE>::operator=(const Stack<ITEM_TYPE>& RHS) {
        if(this == &RHS) {
            return *this;
        }
        _clear_list(_top);
        _top = _copy_list(RHS._top);
        _size = RHS._size;
        return *this;
    }
    template <typename ITEM_TYPE>
    ITEM_TYPE Stack<ITEM_TYPE>::top() {
        if(_top != NULL) {
            return _top -> _item;
        }
        return ITEM_TYPE();
    }
    template <typename ITEM_TYPE>
    bool Stack<ITEM_TYPE>:: empty() {
        return _top == NULL;
    }
    template <typename ITEM_TYPE>
    void Stack<ITEM_TYPE>::push(ITEM_TYPE item) {
        _top = _insert_head(_top, item);
        _size++;
    }
    template <typename ITEM_TYPE>
    ITEM_TYPE Stack<ITEM_TYPE>::pop() {
        if(_size > 0) {
        _size--;
        ITEM_TYPE theItem = _delete_node(_top, _top);
        return theItem;
        }
        return ITEM_TYPE();
    }


#endif //MY_STACK_H