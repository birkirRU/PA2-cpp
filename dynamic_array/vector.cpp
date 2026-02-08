#include "vector.h"

#include <cstddef> // Required for NULL definition


template<typename T>
struct DArr {

    int cap;
    int size;
    T* arr;

    // Default Constructer of Dynamic Array
    DArr(const int init_cap = 8) : cap(init_cap), size(0) {
        arr = new T[cap];
    }
    
    // Deconsructer 
    ~DArr() {
        delete[] arr;
        arr = NULL;
        // can also
        // arr = 0;
    } 

    // Copy Constructer
    DArr(const DArr& rhs) {
        cap = rhs.cap;
        size = rhs.size;

        arr = new T[rhs.cap];

        for (int i=0; i < rhs.size; i++) {
            arr[i] = rhs.arr[i];
        }

    }

    // push_back method that MAKES changes to DArr
    void push_back(const T data) {
        if (size == cap) {

            int newCap = cap * 2;
            reserve(newCap);
            
            arr[size++] = data;
        }
        else {
            arr[size++] = data;
        }
    }

    T pop_back() {
        if (size == 0) {
            return NULL;
        }

        T lastElement = arr[size - 1];
        arr[--size] = T(); // Sets default value of T, e.x. 0 for int.

        if (size <= cap/4) {
            reserve(cap/4);
        }
        return lastElement;
    }


    void reserve(const int n) {
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

};

