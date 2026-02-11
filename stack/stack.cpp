#include "stack.h"

template <typename T>
Stack<T>::Stack() {
   DArr<T> arr = DArr<T>(); 
}

template <typename T>
Stack<T>::~Stack() {
    // arr is a member of stack, and will automatically call its destructor when stack is destructed
    // so we dont need to do anything here.
}
 
template <typename T>
void Stack<T>::push(const T& value) {
    arr.push_back(value);
}

template <typename T>
void Stack<T>::pop() {
    arr.pop_back();
}


template <typename T>
T& Stack<T>::top() {
    assert (arr.size != 0);
    return arr[arr.size-1];
}

template <typename T>
int Stack<T>::get_size() const {
    return arr.size;
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& rhs) { 
    arr = rhs.arr;
    return *this;
}

template class Stack<double>;
template class Stack<float>;
template class Stack<int>;
