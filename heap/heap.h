#ifndef HEAP_H
#define HEAP_H

#include "../dynamic_array/dynamic_array.h"  

template<typename T, bool (*comp)(const T&, const T&)>
// comp is a function pointer to comparator.
struct Heap {
    DArr<T> arr;

    Heap();
    Heap(const Heap& other);
    ~Heap();

    void push(const T& data);
    T pop();
    T& peek();
    int get_size();

    void swim(const int& index);
    void sink(const int& index);

    Heap& operator=(const Heap& rhs);
};

template<typename T>
bool min(const T& rhs, const T& lhs);


#endif