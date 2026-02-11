#ifndef STACK_H
#define STACK_H

#include "../dynamic_array/dynamic_array.h"  

template<typename T>
struct Stack {
    DArr<T> arr;
    int size;
    
    Stack();
    Stack(const Stack& other);
    ~Stack();

    // Methods
    
    // Has side effects on the data structrure
    void push(const T& value);
    // Has side effects on the data structrure
    void pop();
    // returns reference to the top element (editable)
    T& top();

    // Doesnt have side effects on the data structure
    int get_size() const;

    // Operator overloads
    Stack& operator=(const Stack& rhs);


};

#endif