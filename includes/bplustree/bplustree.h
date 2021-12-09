#ifndef BPLUSTREE_H
#define BPLUSTREE_H
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cassert>
#include <string.h>
#include "btree_array_funcs.h"

using namespace std;
template <class T>
class BPlusTree
{
public:
    class Iterator{
    public:
        friend class BPlusTree;
        Iterator(BPlusTree<T>* _it=NULL, int _key_ptr = 0):
                                                it(_it), key_ptr(_key_ptr){}

        T operator *() {
            assert(it);
                return it -> data[key_ptr];
        }

        Iterator operator++(int un_used) {
            Iterator temp(it, key_ptr);
            if(it != nullptr) {
                if(key_ptr < it -> data_count - 1)
                {
                    key_ptr++;
                }
                else if(key_ptr == it -> data_count -1) {
                    key_ptr = 0;
                    it = it -> next;
                }
            }
            return temp;
            
        }
        Iterator operator++() {
            if(it != nullptr) {
                if(key_ptr < it -> data_count - 1)
                {
                    key_ptr++;
                }
                else if(key_ptr == it -> data_count -1){
                    key_ptr = 0;
                    it = it -> next;
                }
            }
            return *this;
        }
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs) {
            if(lhs.it == NULL && rhs.it == NULL) {
                return true;
            }
            if(lhs.it != NULL && rhs.it != NULL) {
                Iterator left(lhs.it);
                Iterator right(rhs.it);
                return (*left == *right);
            }
            return false;
            
        }
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs) {
            return !(lhs == rhs);
        }
        void print_Iterator(){
            if (it){
                cout<<"iterator: ";
                print_array(it->data, it->data_count, key_ptr);
            }
            else{
                cout<<"iterator: NULL, key_ptr: "<<key_ptr<<endl;
            }
        }
        bool is_null(){return !it;}
        void info(){
            cout<<endl<<"Iterator info:"<<endl;
            cout<<"key_ptr: "<<key_ptr<<endl;
            cout<<"it: "<<*it<<endl;
        }

    private:
        BPlusTree<T>* it;
        int key_ptr;
    };

    BPlusTree(bool dups = false);
    BPlusTree(T *a, int size, bool dups = false);

    //big three:
    BPlusTree(const BPlusTree<T>& other);
    ~BPlusTree();
    BPlusTree<T>& operator =(const BPlusTree<T>& RHS);

    void copy_tree(const BPlusTree<T>& other);  //copy other into this object

    void copy_tree(const BPlusTree<T>& other, BPlusTree<T>*& s);
    void insert(const T& entry);   //insert entry into the tree
    void remove(const T& entry);   //remove entry from the tree
    void clear_tree();             //clear this object (delete all nodes etc.)

    bool contains(const T& entry) const; //true if entry can be found
    T& get(const T& entry);              //return a reference to entry
    const T& get(const T& entry)const;   //return a reference to entry
    T& get_existing(const T& entry);
    const T& get_existing(const T& entry) const;     //return a reference to entry
    Iterator find(const T& key) {
        int i = first_ge(data, data_count, key);
        if(data[i] == key && i < data_count) {
            if(is_leaf()) {
                return Iterator(this, i);
            }
            else {
                return subset[i+1] -> find(key);
            }
        }
        else {
            if(!is_leaf()) {
                return subset[i] -> find(key);
            }
        }
        return Iterator();
    }        //return an iterator to this key.
                                         //     NULL if not there.
    Iterator lower_bound(const T& key);  //return first that goes NOT BEFORE
                                         // key entry or next if does not
                                         // exist: >= entry
    Iterator upper_bound(const T& key);  //return first that goes AFTER key
                                         //exist or not, the next entry  >entry

    int size() const;                    //count the number of elements

    bool empty() const;                  //true if the tree is empty

    void print_tree(int level = 0,
                    ostream &outs=cout) const;
    friend ostream& operator<<(ostream& outs,
                               const BPlusTree<T>& print_me){
        print_me.print_tree(0, outs);
        return outs;
    }

    bool is_valid();
    bool is_valid(T& entry);
    string in_order();
    string post_order();
    string pre_order();

    Iterator begin() {
        return Iterator(get_smallest_node());
    }
    Iterator end() {
        return Iterator(NULL);
    }
    ostream& list_keys(Iterator from = NULL, Iterator to = NULL){
        if (from == NULL) from = begin();
        if (to == NULL) to = end();
        for (Iterator it = from; it != to; it++)
            cout<<*it<<" ";
        return cout;

    }

private:
    static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;

    bool dups_ok;                        //true if duplicate keys are allowed
    int data_count;                      //number of data elements
    T data[MAXIMUM + 1];                 //holds the keys
    int child_count;                     //number of children
    BPlusTree* subset[MAXIMUM + 2];      //subtrees
    BPlusTree* next;
    bool is_leaf() const
    {return child_count==0;}             //true if this is a leaf node

    T* find_ptr(const T& entry);         //return a pointer to this key.
                                         // NULL if not there.

    //insert element functions
    void loose_insert(const T& entry);   //allows MAXIMUM+1 data elements in
                                         //   the root
    void fix_excess(int i);              //fix excess in child i

    //remove element functions:
    void loose_remove(const T& entry);  //allows MINIMUM-1 data elements
                                        //  in the root

    BPlusTree<T>* fix_shortage(int i);  //fix shortage in child i
    // and return the smallest key in this subtree
    BPlusTree<T>* get_smallest_node();
    void get_smallest(T& entry);      //entry := leftmost leaf
    void get_biggest(T& entry);       //entry := rightmost leaf
    void remove_biggest(T& entry);    //remove the biggest child of tree->entry
    void transfer_left(int i);        //transfer one element LEFT from child i
    void transfer_right(int i);       //transfer one element RIGHT from child i
    BPlusTree<T> *merge_with_next_subset(int i); //merge subset i with  i+1

};

template <class T>
BPlusTree<T>::BPlusTree(bool dups):dups_ok(dups), data_count(0),
                                   child_count(0), next(NULL) {
    for(int i = 0; i < MAXIMUM+1; i++) {
        data[i] = T();
    }
    for(int i = 0; i < MAXIMUM+2; i++) {
        subset[i] = nullptr;
    }                                  
    //left emtpy
}
template <class T>
BPlusTree<T>::BPlusTree(T *a, int size, bool dups) {
    data_count = 0;
    child_count = 0;
    dups_ok = dups;
    next = NULL;
    for(int i = 0; i < MAXIMUM+1; i++) {
        data[i] = T();
    }
    for(int i = 0; i < MAXIMUM+2; i++) {
        subset[i] = nullptr;
    }
    for(int i = 0; i < size; i++) {
        insert(a[i]);
    }
}

//big three:
template <typename T>
BPlusTree<T>::BPlusTree(const BPlusTree<T>& other):
                        data_count(0), child_count(0){
    dups_ok = other.dups_ok;
    copy_tree(other);
}

template <class T>
BPlusTree<T>::~BPlusTree() {
    clear_tree();
}

template <class T>
BPlusTree<T>& BPlusTree<T>::operator =(const BPlusTree<T>& RHS) {
    dups_ok = RHS.dups_ok;
    next = NULL;
    if(this != &RHS) {
        clear_tree();
        copy_tree(RHS);
    }
    return *this;
}

template <class T>
void BPlusTree<T>::copy_tree(const BPlusTree<T>& other) {
    BPlusTree<T>* temp = NULL;
    copy_tree(other, temp);
}  //copy other into this object

template <class T>
void BPlusTree<T>::copy_tree(const BPlusTree<T>& other, BPlusTree<T>*& s) {
{
        dups_ok = other.dups_ok;
        child_count = other.child_count;
        next = NULL;
        copy_array(data, other.data, data_count, other.data_count);
        for(int i = 0; i < child_count; i++) {
            BPlusTree *copied_tree = new BPlusTree<T>;
            subset[i] = copied_tree;
            subset[i] -> copy_tree(*other.subset[i], s);
        }
        if(other.is_leaf()) {
            if(s != NULL) {
                s -> next = this;
            }
            s = this;
        }
    }
}

template <class T>
void BPlusTree<T>::insert(const T& entry) {
    loose_insert(entry);
    //fix_excess(0);
    if(data_count == MAXIMUM + 1) {
        BPlusTree<T>* new_node_copy = new BPlusTree<T>;
        new_node_copy -> data_count = data_count;
        new_node_copy -> child_count = child_count;
        for(int j = 0; j < data_count; j++) {
            new_node_copy -> data[j] = data[j];
        }
        for(int k = 0; k < child_count; k++) {
            new_node_copy -> subset[k] = subset[k];
        }
        data_count = 0;
        child_count = 1;
        subset[0] = new_node_copy;
        fix_excess(0);
    }

}   //insert entry into the tree

template <class T>
void BPlusTree<T>::remove(const T& entry) {

}   //remove entry from the tree

template <class T>
void BPlusTree<T>::clear_tree() {
    data_count = 0;
    for(int i = 0; i < child_count; i++) {
        subset[i] -> clear_tree();
        subset[i] = nullptr;
    }
    child_count = 0;
    next = NULL;
}             //clear this object (delete all nodes etc.)

template <class T>
bool BPlusTree<T>::contains(const T& entry) const {
    int i = first_ge(data, data_count, entry);
    bool found = (i<data_count && data[i] == entry);
    if(found) {
            return true;
        }
    else {
        if(!is_leaf()) {
            return subset[i] -> contains(entry);
        }
    }
    return false;
} //true if entry can be found

template <class T>
T& BPlusTree<T>::get(const T& entry) {
    const bool debug = false;
    if (!contains(entry)) {
        insert(entry);
    }
    return get_existing(entry);
}              //return a reference to entry

template <class T>
const T& BPlusTree<T>::get(const T& entry)const {
    assert(contains(entry));
    return get_existing(entry);

}   //return a reference to entry

template <class T>
T& BPlusTree<T>::get_existing(const T& entry) {
    const bool debug = false;
    int i = first_ge(data, data_count, entry);
    bool found = (i<data_count && data[i] == entry);
    //assert(contains(entry));
    // if(is_leaf()) {
    //     if(found) {
    //         return data[i];
    //     }
    //     else {
    //         if (debug) cout<<"get_existing was called with nonexistent entry"<<endl;
    //         assert(found);
    //     }
    // }
    if (is_leaf()) {
        if (found){
            return data[i];
        }
        else {
            if (debug) cout<<"get_existing was called with nonexistent entry"<<endl;
            assert(found);
        }
    }
    else {
        if (found) {//inner node
            return subset[i+1]->get(entry);
        }
            //or just return true?
        else {//not found yet...
            return subset[i]->get(entry);
        }
    }
}     //return a reference to entry

template <class T>
const T& BPlusTree<T>::get_existing(const T& entry) const{
    const bool debug = false;
    int i = first_ge(data, data_count, entry);
    bool found = (i<data_count && data[i] == entry);
    //assert(contains(entry));
    // if(is_leaf()) {
    //     if(found) {
    //         return data[i];
    //     }
    //     else {
    //         if (debug) cout<<"get_existing was called with nonexistent entry"<<endl;
    //         assert(found);
    //     }
    // }
    if (is_leaf()) {
        if (found){
            return data[i];
        }
        else {
            if (debug) cout<<"get_existing was called with nonexistent entry"<<endl;
            assert(found);
        }
    }
    else {
        if (found) {//inner node
            return subset[i+1]->get(entry);
        }
            //or just return true?
        else {//not found yet...
            return subset[i]->get(entry);
        }
    }
}     //return a reference to entry

template <class T>
int BPlusTree<T>::size() const {
    int size_of_tree = data_count;
    for(int i = 0; i < child_count; i++) {
        size_of_tree += subset[i] -> size();
    }
    return size_of_tree;
}                    //count the number of elements

template <class T>
bool BPlusTree<T>::empty() const {
    if(data_count == 0) {
        return true;
    }
    else {
        return false;
    }
}                  //true if the tree is empty

template <class T>
void BPlusTree<T>::print_tree(int level, ostream &outs) const {
//1. print the last child (if any)
    //2. print all the rest of the data and children
    if(data_count == 0) {
        return;
    }
    if(child_count > data_count) {
        if(subset[child_count -1] != NULL) {
            subset[child_count-1] -> print_tree(level+1);
        }
    }
    for(int i = data_count-1; i >= 0; i--) {
        if(i == data_count - 1) {
            outs << setw(8*level) << "-^-" << endl;
        }
        outs << setw(8*level) <<data[i] << endl;
        if(i == 0) {
            outs << setw(8*level) << "-v-" << endl;
        }
        if(i < child_count && subset[i] != NULL)
        {
            subset[i] -> print_tree(level+1);
        }
    }
}

template <class T>
bool BPlusTree<T>::is_valid() {
   //should check that every data[i] < data[i+1]
//    for(int i = 0; i < child_count; i++) {
//        subset[i] -> is_valid();
//        if(data[i] < data[i+1]) {
//        if (is_leaf()) {
//             return true;
//        }
//        if(data[i] > )
    
    

    //data[data_count-1] must be less than equal to 
    //  every subset[child_count-1]->data[ ]
    
    //every data[i] is greater than every subset[i]->data[ ]
    
    //B+Tree: Every data[i] is equal to subset[i+1]->smallest
    
    //Recursively validate every subset[i]

    return true;
}

template <class T>
string BPlusTree<T>::in_order() {
    string in_order = "";
    if(data_count == 0) {
        return in_order;
        }
        for(int i =0; i < data_count; i++) {
            if(subset[i] != NULL && i < child_count) {
                in_order += subset[i] -> in_order();
            }
            in_order += (to_string(data[i]) + "|");
        }
        if(child_count > data_count) {
            in_order += subset[child_count-1] -> in_order();
        }
        return in_order;
    }

template <class T>
string BPlusTree<T>::post_order() { //left, right, root
    string post_order = "";
    if(data_count == 0) {
        return post_order;
    }
    if(subset[0] != NULL && !is_leaf()) {
        post_order += subset[0] -> post_order();
    }
    for(int i = 0; i < data_count; i++) {
        if(subset[i+1] != NULL && i+1 < child_count) {
            //if(!is_leaf()) {
                post_order += subset[i+1] -> post_order();
            //}
        }
            post_order += (to_string(data[i]) + "|");
    }
    return post_order;
}

template <class T>
string BPlusTree<T>::pre_order() {  //root, left, right
    string pre_order = "";
    if(data_count == 0) {
        return pre_order;
        }
        for(int i =0; i < data_count; i++) {
            pre_order += (to_string(data[i]) + "|");
            if(subset[i] != NULL && i < child_count) {
                pre_order += subset[i] -> pre_order();
            }
        }
        if(child_count > data_count) {
            pre_order += subset[child_count-1] -> pre_order();
        }
        return pre_order;
}

template <class T>
T* BPlusTree<T>::find_ptr(const T& entry) {
    int i = first_ge(data, data_count, entry);
    bool found = (i<data_count && data[i] == entry);
    if(found && is_leaf()) {
        return &data[i];
    }
    if(found && !is_leaf()) {
        return subset[i+1] -> find_ptr(entry);
    }
    if(!found && !is_leaf()) {
        return subset[i] -> find_ptr(entry);
    }
    return NULL;
}         //return a pointer to this key.
                                        // NULL if not there.

//insert element functions
template <class T>
void BPlusTree<T>::loose_insert(const T& entry) {
    int i = first_ge(data, data_count, entry);
    if(data[i] == entry && i < data_count) {
        if(is_leaf()) {
            data[i] = entry;
        }
        else if (subset[i+1] != NULL){
            subset[i+1] -> loose_insert(entry);
            fix_excess(i+1);
        }
    }
    else {
        if(is_leaf()) {
            insert_item(data, i,data_count, entry);
        }
        else if (subset[i] != NULL){
            subset[i] -> loose_insert(entry);
            fix_excess(i);
        }
    }

}   //allows MAXIMUM+1 data elements in
                                        //   the root
template <class T>                                        
void BPlusTree<T>::fix_excess(int i) {
    if(subset[i] != nullptr) {
        if(subset[i] -> data_count > MAXIMUM) {
            BPlusTree* new_child = new BPlusTree<T>;
            new_child -> data_count = 0;
            new_child -> child_count = 0;
            new_child -> dups_ok = dups_ok;
            //new_child -> next = NULL;
            T midpoint = T();
            split(subset[i] -> data, subset[i] -> data_count, new_child -> data, new_child -> data_count);
            split(subset[i] -> subset, subset[i] -> child_count, new_child -> subset, new_child -> child_count);
            //int middle_of_subset = subset[i] -> data_count;
            //new_child -> data_count - subset[i] -> data_count - (middle_of_subset + 1);
            //for(int m = 0; m < new_child -> data_count; m++) {
            //    new_child -> data[m] = subset[i] -> data[m + middle_of_subset + 1];
            //}
            //T inserted = T();
            detach_item(subset[i] -> data, subset[i] -> data_count, midpoint);
            //detach_item(subset[i]-> data, subset[i]->data_count, inserted);
            insert_item(this -> data, i, data_count, midpoint);
            insert_item(subset, i+1, child_count, new_child);
            if(subset[i] -> is_leaf()) {
                insert_item(new_child -> data, 0, new_child-> data_count, midpoint);
                new_child -> next = subset[i] -> next;
                subset[i] -> next = new_child;
            }
        }

    }
}

              //fix excess in child i

//remove element functions:
template <class T>
void BPlusTree<T>::loose_remove(const T& entry) {

}  //allows MINIMUM-1 data elements
                                    //  in the root

template <class T>
BPlusTree<T>* BPlusTree<T>::fix_shortage(int i) {

}  //fix shortage in child i
// and return the smallest key in this subtree

template <class T>
BPlusTree<T>* BPlusTree<T>::get_smallest_node() {
    if(!is_leaf()) {
        return subset[0] -> get_smallest_node();
    }
    else {
        return this;
    }
}

template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::lower_bound(const T& key) {
    for(Iterator walker = begin(); walker != end(); walker++) {
        if(*walker >= key) {
            return walker;
        }
    }
    return Iterator();
}

template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::upper_bound(const T& key) {
    for(Iterator walker = begin(); walker != end(); walker++) {
        if(*walker > key) {
            return walker;
        }
    }
    return Iterator();
}

template <class T>
void BPlusTree<T>::get_smallest(T& entry) {

}      //entry := leftmost leaf

template <class T>
void BPlusTree<T>::get_biggest(T& entry) {

}       //entry := rightmost leaf

template <class T>
void BPlusTree<T>::remove_biggest(T& entry) {

}    //remove the biggest child of tree->entry

template <class T>
void BPlusTree<T>::transfer_left(int i) {

}        //transfer one element LEFT from child i

template <class T>
void BPlusTree<T>::transfer_right(int i) {

}       //transfer one element RIGHT from child i

template <class T>
BPlusTree<T> BPlusTree<T>::*merge_with_next_subset(int i) {

} //merge subset i with  i+1
#endif //BPLUSTREE_H