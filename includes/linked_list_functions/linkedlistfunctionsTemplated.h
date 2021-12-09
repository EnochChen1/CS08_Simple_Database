#ifndef LINKED_LIST_FUNCTIONS_TEMPLATED_H__
#define LINKED_LIST_FUNCTIONS_TEMPLATED_H__

#include "../node/node.h"
//...........Declarations
template <typename T>
node<T>* _insert_head(node<T>* &headptr, const T& item);

template <typename T>
void _print_list(node<T>* headptr);

//recursive fun! :)
template <typename T>
void _print_list_backwards(node<T> *head);

//return ptr to key or NULL
template <typename T>
node<T>* _search_list(node<T>* head, T key);

//insert after ptr: insert head if marker null
template <typename T>
node<T>* _insert_after(node<T>*& head,
                                node<T> *after_this,
                                T insert_this);

//insert before ptr: insert head if marker null
template <typename T>
node<T>* _insert_before(node<T>*& head,
                                node<T>* before_this,
                                T insert_this);

//ptr to previous node
template <typename T>
node<T>* _previous_node(node<T>* prev_to_this);

//delete, return item
template <typename T>
T _delete_node(node<T>*& head, node<T>* delete_this);

//duplicate the list...
template <typename T>
node<T>* _copy_list(node<T>* head);

//duplicate the list and return last node in list
template <typename T>
node<T>* _copy_list(node<T> *&dest, node<T> *src);

//delete all the nodes
template <typename T>
void _clear_list(node<T>*& head);

//_item at this position
template <typename T>
T& _at(node<T>* head, int pos);

//------ ------ ------ ------ ------ ------ ------ ------ ------ 

template <typename T>
node<T>* _insert_head(node<T>* &headptr, const T& item){
  node<T>* temp = new node<T>(item, headptr);  
  if(headptr != nullptr) {
      headptr -> _prev = temp;
  }
  headptr = temp;
  return headptr;
}

template <typename T>
void _print_list(node<T>* headptr){

  //                                                                w
  //hp->[  ]->[  ]->[  ]->[  ]->[  ]->[  ]->[  ]->[  ]->[  ]->[  ]->|||
  for(node<T>* walker = headptr;
      walker != nullptr;
      walker = walker->_next){
        
        cout<<*walker; //walker-->[ node ]
                        //*walker IS THE [node]
      }
      cout << "|||" << endl;
}

template <typename T>
void _print_list_backwards(node<T> *head) {
    if(head == nullptr) {
        return;
    }
    _print_list_backwards(head -> _next);

    cout << head -> _item << " " ;
}

//return ptr to key or NULL
template <typename T>
node<T>* _search_list(node<T>* head, T key) {
    node<T>* walker = head;
    while(walker != nullptr) {
        if(walker -> _item == key) {
            return walker;
        }
        walker = walker -> _next;
    }
    return nullptr;

}

//insert after ptr: insert head if marker null
template <typename T>
node<T>* _insert_after(node<T>*& head, node<T> *after_this, T insert_this) {
    if(after_this == nullptr || head == nullptr) {
        return _insert_head(head, insert_this);
    }
    node<T>* temp = new node<T>(insert_this, after_this -> _next, after_this);
    after_this -> _next = temp;
    return temp;
}

//insert before ptr: insert head if marker null
template <typename T>
node<T>* _insert_before(node<T>*& head, node<T>* before_this, T insert_this) {
    if(before_this == head || head == nullptr) {
        return _insert_head(head, insert_this);
    }
    return _insert_after(head, before_this->_prev, insert_this);
}

//ptr to previous node
template <typename T>
node<T>* _previous_node(node<T>* prev_to_this) {
    return prev_to_this -> _prev;
}

//delete, return item
template <typename T>
T _delete_node(node<T>*& head, node<T>* delete_this) {
    T items = delete_this -> _item;
    if(delete_this == head) {
        head = head -> _next;
        if(head != nullptr) {
            head -> _prev = nullptr;
        }
    }
    else{
        if(delete_this -> _prev != nullptr) {
            delete_this -> _prev -> _next = delete_this -> _next;
        }
        if(delete_this -> _next != nullptr) {
            delete_this -> _next -> _prev = delete_this -> _prev;
        }
    }
    delete delete_this;
    return items;
    
}

//duplicate the list...
template <typename T>
node<T>* _copy_list(node<T>* head) {
    // if(head == nullptr) {
    //     return nullptr;
    // }
    // node <T>* temp = head;
    // head = new node<T>(temp-> _item);
    // node<T>* current = head;
    // temp = temp -> _next;
    // while(temp != nullptr) {
    //     current -> _next = new node<T>();
    //     current = current -> _next;
    //     current -> _item = temp -> _item;
    //     current -> _next = nullptr;
    //     temp = temp -> _next;
    // }
    // return head;

    node<T>* walker = head;
    node<T>* copy_at_new_head = NULL;

    if (head != NULL) {
        copy_at_new_head = _insert_head(copy_at_new_head, walker->_item);
        node<T>* walker_for_copy = copy_at_new_head;
        node<T>* inserted;

        walker = walker->_next;
        while (walker != NULL) {
            inserted = _insert_after(copy_at_new_head, walker_for_copy, walker->_item);
            walker_for_copy = walker_for_copy->_next;
            walker = walker->_next;
        }
    }
    return copy_at_new_head;
}

template <typename T>
node<T>* _copy_list(node<T> *&dest, node<T> *src) {
    // if(dest == nullptr) {
    //     _clear_list(dest);
    //     dest = nullptr;
    // }
    // node<T>* temp = src;
    // node<T>* dest_walker = dest;
    // src = new node<T>(temp -> _item);
    // node<T>* current = src;
    // temp = temp -> _next;
    // while(temp != nullptr) {
    //     current -> _next = new node<T>();
    //     current = current -> _next;
    //     current -> _item = temp -> _item;
    //     current -> _next = nullptr;
    //     if(temp -> _next == nullptr) {
    //         return temp;
    //     }
    //     temp = temp -> _next;
    // }
    // return nullptr;
    if (dest != NULL) {
        _clear_list(dest);
        dest = NULL;
    }

    node<T>* walker = src;
    if (src != NULL) {
        dest = _insert_head(dest, walker->_item);
        node<T>* dest_walker = dest;
        node<T>* inserted;

        walker = walker->_next;
        while (walker != NULL) {
            inserted = _insert_after(dest, dest_walker, walker->_item);
            if (dest_walker->_next == NULL) {
                return dest_walker;
            }
            dest_walker = dest_walker->_next;
            walker = walker->_next;
        }
        return dest_walker;
    }
    return NULL;
}

//delete all the nodes
template <typename T>
void _clear_list(node<T>*& head) {
        while (head != nullptr) {
        _delete_node(head, head);
    }
    delete head;
}

//_item at this position
template <typename T>
T& _at(node<T>* head, int pos) {
    node<T>* walker = head;
    int current_pos = 0;
    while(walker != NULL) {
        if(current_pos == pos) {
            return walker -> _item;
        }
        current_pos++;
    }
}

#endif // LINKED_LIST_FUNCTIONS_TEMPLATED_H__
