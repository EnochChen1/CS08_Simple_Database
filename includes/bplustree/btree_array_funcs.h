#ifndef BTREE_ARRAY_FUNCS_H
#define BTREE_ARRAY_FUNCS_H
#include <iostream>
#include <iomanip>

using namespace std;
template <class T>
T maximal(const T& a, const T& b);                      //return the larger of the two items

template <class T>
void swap(T& a, T& b);  //swap the two items

template <class T>
int index_of_maximal(T data[ ], int n);                 //return index of the largest item in data

template <class T>
void ordered_insert(T data[ ], int& n, T entry);        //insert entry into the sorted array
                                                        //data with length n

template <class T>
int first_ge(const T data[ ], int n, const T& entry);   //return the first element in data that is
                                                        //not less than entry

template <class T>
void attach_item(T data[ ], int& n, const T& entry);    //append entry to the right of data

template <class T>
void insert_item(T data[ ], int i, int& n, T entry);    //insert entry at index i in data

template <class T>
void detach_item(T data[ ], int& n, T& entry);          //remove the last element in data and place
                                                        //it in entry

template <class T>
void delete_item(T data[ ], int i, int& n, T& entry);   //delete item at index i and place it in entry

template <class T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2);   //append data2 to the right of data1

template <class T>
void split(T data1[ ], int& n1, T data2[ ], int& n2);   //move n/2 elements from the right of data1
                                                        //and move to data2

template <class T>
void copy_array(T dest[], const T src[],
                int& dest_size, int src_size);              //copy src[] into dest[]

template <class T>
void print_array(const T data[], int n, int pos = -1);  //print array data

template <class T>
bool is_gt(const T data[], int n, const T& item);       //item > all data[i]

template <class T>
bool is_le(const T data[], int n, const T& item);       //item <= all data[i]

//-------------- Vector Extra operators: ---------------------

template <typename T>
ostream& operator <<(ostream& outs, const vector<T>& list); //print vector list

template <typename T>
vector<T>& operator +=(vector<T>& list, const T& addme); //list.push_back addme



//--------------------------------------------------------------------------------------------------------

template <class T>
T maximal(const T& a, const T& b) {
    if(a > b) {
        return a;
    }
    else {
        return b;
    }
}                      //return the larger of the two items

template <class T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}  //swap the two items

template <class T>
int index_of_maximal(T data[ ], int n) {
    T theMax = T();
    for(int i = 0; i < n; i++) {
        if(data[i] > theMax) {
            theMax = data[i];
        }
    }
    for(int i = 0; i < n; i++) {
        if(data[i] == theMax) {
            return i;
        }
    }
    return -1;
}                 //return index of the largest item in data

template <class T>
void ordered_insert(T data[ ], int& n, T entry) {
    int ge = first_ge(data, n, entry);
    insert_item(data, ge, n, entry);
}      //insert entry into the sorted array}
// 5 10 20 30  35 40 50
                                                       //data with length n

template <class T>
int first_ge(const T data[ ], int n, const T& entry) {
    for(int i = 0; i < n; i++) {
        if(data[i] >= entry) {
            return i;
        }
    }
    return n;
}   //return the first element in data that is
                                                        //not less than entry

template <class T>
void attach_item(T data[ ], int& n, const T& entry) {
    data[n] = entry;
    n++;
}    //append entry to the right of data

template <class T>
void insert_item(T data[ ], int i, int& n, T entry) {
for(int j = n; j > i; j--) { 
     data[j] = data[j-1];
    }
     data[i]= entry;
     n++;
}

      //insert entry into the sorted array}    //insert entry at index i in data

template <class T>
void detach_item(T data[ ], int& n, T& entry) {
    entry = T();
    if(n > 0) {
        n--;
        entry = data[n];
    }
}          //remove the last element in data and place
                                                        //it in entry

template <class T>
void delete_item(T data[ ], int i, int& n, T& entry) {
    // if(n == 0) {
    //     return;
    // }
    // entry = data[i];
    // for(int j = i; j + 1 < n; j++) {
    //     data[j] = data[j+1];
    // }
    // n--;
    entry = T();
    if(n > 0) {
        entry = data[i];
        for(; i < n-1; i++) {
            data[i] = data[i+1];
        }
        n--;
    }
}   //delete item at index i and place it in entry

template <class T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2) {
    for(int i = 0; i < n2; i++) {
        data1[i+n1] = data2[i];
    }
    n1 = n1 + n2;
    n2 = 0;
}   //append data2 to the right of data1

template <class T>
void split(T data1[ ], int& n1, T data2[ ], int& n2) {
    // if(n1 > 1) {
    //     n2 = n1/2;
    //     n1 = n1-n2;
    //     for(int i = 0; i < n2; i++) {
    //         data2[i] = data1[i+n1];
    //     }
    // }   
    n2 = n1/2;
    n1 = n1 - n2;
    for(int i = 0; i < n2; i++) {
        data2[i] = data1[i+n1];
    }
}   //move n/2 elements from the right of data1
                                                        //and move to data2

template <class T>
void copy_array(T dest[], const T src[], int& dest_size, int src_size) {
    dest_size = src_size;
    for(int i = 0; i < dest_size; i++) {
        dest[i] = src[i];
    }
}        //copy src[] into dest[]

template <class T>
void print_array(const T data[], int n, int pos) {
    
}  //print array data

template <class T>
bool is_gt(const T data[], int n, const T& item) {
    bool greater = true;
    for(int i = 0; i < n; i++) {
        if(data[i] >= item) {
            greater = false;
        }
    }
    return greater;
}       //item > all data[i]

template <class T>
bool is_le(const T data[], int n, const T& item) {
    bool lesser = true;
    for(int i = 0; i < n; i++) {
        if(data[i] < item) {
            lesser = false;
        }
    }
    return lesser;
}       //item <= all data[i]

//-------------- Vector Extra operators: ---------------------

template <typename T>
ostream& operator <<(ostream& outs, const vector<T>& list) {
    for(int i = 0; i < list.size(); i++) {
        outs << list[i] << " ";
    }
    return outs;
} //print vector list

template <typename T>
vector<T>& operator +=(vector<T>& list, const T& addme) {
    list.push_back(addme);
    return list;
} //list.push_back addme

#endif //BTREE_ARRAY_FUNCS