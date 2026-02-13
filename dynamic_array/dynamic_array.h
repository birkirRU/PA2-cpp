#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H // to gaurd against circular dependancies

#include <iostream>
#include <cassert>

template<typename T>
struct DArr {
    // Member variables 
    int cap;
    int size;
    T* arr;
    
    // Constructors 
    DArr(const int init_cap = 8);      // Declaration
    DArr(const DArr& other);          // Declaration
    ~DArr();                          // Declaration
    
    // Methods 
    void push_back(const T& value);  
    void pop_back();
    void reserve(const int n);
    void resize(const int n); 
    void insert(const T& value, const int index);
    void erase(const int index);
    void print();
    
    
    // Operator overloads
    DArr& operator=(const DArr& rhs); // Declaration
    T& operator[](const int index);
};

#endif
