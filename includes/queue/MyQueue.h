#ifndef MY_QUEUE_H
#define MY_QUEUE_H

#include <iostream>
#include <iomanip>
#include "../linked_list_functions/linkedlistfunctionsTemplated.h"
using namespace std;

template <typename T>
class Queue
{
public:
    class Iterator{
    public:
        friend class Queue;                               //give access to list to access _ptr
        Iterator(){_ptr = NULL;}                          //default ctor
        Iterator(node<T>* p){
            _ptr = p;
        }                            //Point Iterator to where
                                                          //  p is pointing to
        T operator *(){
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
        Iterator hold = Iterator(it._ptr);
        it._ptr = it._ptr -> _next;
        return hold;
        }

    private:
        node<T>* _ptr;                          //pointer being encapsulated
    };
    Queue();

    Queue(const Queue<T>& copyMe);
    ~Queue();
    Queue& operator=(const Queue<T>& RHS);

    bool empty();
    T front();
    T back();

    void push(T item);
    T pop();

    Iterator begin() const {                                     //Iterator to the head node
        return Iterator(_front);
    }
    Iterator end() const {                                       //Iterator to NULL
        return Iterator();
    }
    void print_pointers();
    int size() const { return _size; }
    template<typename TT>
    friend ostream& operator << (ostream& outs, const Queue<TT>& printMe) {
        node<T>* walker = printMe._front;
        while(walker != nullptr) {
            outs << "<-[" << walker -> _item <<"]->";
            walker = walker -> _next;
        }
        return outs; 
    }
    private:
    node<T>* _front;   
    node<T>* _rear;
    int _size;
};
    template <typename T>
    Queue<T>::Queue() {
        _front = nullptr;
        _rear = nullptr;
        _size = 0;
    }
    template <typename T>
    Queue<T>::Queue(const Queue<T>& copyMe) {
        _front = nullptr;
        _rear = _copy_list(_front, copyMe._front);
        _size = copyMe._size;
    }
    template <typename T>
    Queue<T>::~Queue() {
        _clear_list(_front);
    }
    template <typename T>
    Queue<T>& Queue<T>::operator=(const Queue<T>& RHS) {
        if(this != &RHS) {
            _clear_list(_front);
            _front = nullptr;
            _rear = _copy_list(_front, RHS._front);
            _size = RHS._size;
        }
        return *this;
    }
    template <typename T>
    bool Queue<T>::empty() {
        if(_front == nullptr) {
            return true;
        }
        return false;
    }
    template <typename T>
    T Queue<T>::front() {
        if(_front != NULL) {
            return _front -> _item;
        }
        return T();
    }
    template <typename T>
    T Queue<T>::back() {
        if(_rear != NULL) {
            return _rear -> _item;
        }
        return T();
    }
    template <typename T>
    void Queue<T>::push(T item) {
        node<T>* pushed = _insert_after(_front, _rear, item);
        _size++;
        if(_size == 1) {
            _rear = _front;
        }
        else {
            _rear = pushed;
        }
    }
    template <typename T>
    T Queue<T>::pop() {
        if(_size > 0) {
            _size--;
            if(_size == 0) {
                _rear = NULL;
            }
            else if(_size == 1) {
                _rear = _front;
            }
            return _delete_node(_front, _front);
        }
        return T();
    }

#endif //MY_QUEUE_H