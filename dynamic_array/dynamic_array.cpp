#include "dynamic_array.h"

#include <cstddef> // Required for NULL definition

// Default Constructer of Dynamic Array
template<typename T>
DArr<T>::DArr(const int init_cap) : cap(init_cap), size(0) {
    arr = new T[cap];
}


// Deconsructer 
template<typename T>
DArr<T>::~DArr() {
    delete[] arr;
    arr = NULL;
    // can also
    // arr = 0;
} 

// Copy Constructer
template<typename T>
DArr<T>::DArr(const DArr& rhs) {
    cap = rhs.cap;
    size = rhs.size;

    arr = new T[rhs.cap];

    for (int i=0; i < rhs.size; i++) {
        arr[i] = rhs.arr[i];
    }

}

// push_back method that MAKES changes to DArr
template<typename T>
void DArr<T>::push_back(const T& data) {
    if (size == cap) {

        int newCap = cap * 2;
        reserve(newCap);
        
        arr[size++] = data;
    }
    else {
        arr[size++] = data;
    }
}

template<typename T>
T DArr<T>::pop_back() {
    // if (size == 0) {
    //     return NULL;
    // }
    assert(size != 0);

    T lastElement = arr[size - 1];
    arr[--size] = T(); // Sets default value of T, e.x. 0 for int.

    if (size <= cap/4) {
        reserve(cap/4);
    }
    return lastElement;
}

template<typename T>
DArr<T>& DArr<T>::operator=(const DArr& rhs) {
    if (this == &rhs) return *this; // self-assignment guard

    T* copyArr = new T[rhs.cap];

    for (int i = 0; i < rhs.size; i++) {
        copyArr[i] = rhs.arr[i];
    }

    delete[] arr;

    arr = copyArr;
    size = rhs.size;
    cap = rhs.cap;

    return *this;
}



template<typename T>
T& DArr<T>::operator[](const int index) {
    // if (index < 0 || index >= size) {
    //     return T();
    // }
    
    assert(index >= 0 && index < size);

    return arr[index];
} 

template<typename T>
void DArr<T>::resize(const int n) {
    // if (n < 0 || n >= cap) {
    //     return;
    // }
    
    assert( n >= 0 && n < cap);
    if (n < size) {
        size = n;
    }
    else if (n > size) {
        int i = size;
        size = n;
        for (; i < size; i++) {
            arr[i] = T();
        }
    }
}

template<typename T>
void DArr<T>::insert(const T& value, const int index) {
    // if (index < 0 || index >= size) {
    //     return;
    // }

    assert( index >= 0 && index < size);
    // Check if size == cap 
    // To resize first
    if (size == cap) {
        int newCap = cap * 2;
        reserve(newCap);
    }
    
    size++;
    int curr = index;
    T swap = T();
    T prev = arr[curr];
    arr[curr] = value;
    while (++curr != size) {
        swap = arr[curr]; 
        arr[curr] = prev;
        prev = swap;
    }
    // Doesnt work for when inserting at end
}

template<typename T>
void DArr<T>::erase(const int index) {
    // if (index < 0 || index >= size) {
    //     return;
    // }
    assert( index >= 0 && index < size);

    int curr = index;
    while (++curr != size) {
        arr[curr-1] = arr[curr];
    }
    size--;
    // Leaves last element undeleted, but it will be overwritten if pushing back.
}


template<typename T>
void DArr<T>::reserve(const int n) {
    // Initialize larger array size with cap = n
    T* newArr = new T[n];

    // Copy all values of current arr into the new initialized arr.
    for (int i=0; i < size; i++) {
        newArr[i] = arr[i];
    }
    
    // Delete contents what current arr pointed to.
    delete[] arr;
    
    // Let current arr point to newly initialized arr.
    arr = newArr;
    cap = n;
}

template<typename T>
void DArr<T>::print() {
    std::cout << size << '\n';
    
    for (int i=0; i < size; i++) { std::cout << arr[i] << ' '; }
    std::cout << '\n';
}

template class DArr<double>;
template class DArr<float>;
template class DArr<int>;
