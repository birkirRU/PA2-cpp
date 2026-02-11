#include "heap.h"

template<typename T, bool (*comp)(const T&, const T&)>
Heap<T, comp>::Heap() {
   DArr<T> arr = DArr<T>(); 
}

template<typename T, bool (*comp)(const T&, const T&)>
Heap<T, comp>::~Heap() {
}

template<typename T, bool (*comp)(const T&, const T&)>
Heap<T, comp>::Heap(const Heap& rhs) {

}
template<typename T, bool (*comp)(const T&, const T&)>
void Heap<T, comp>::push(const T& data) {
    int index_to_swim = arr.size;
    arr.push_back(data);
    swim(index_to_swim);
}

template<typename T, bool (*comp)(const T&, const T&)>
void Heap<T, comp>::swim(const int& index) {
}

template<typename T>
bool smaller(const T& lhs, const T& rhs) {
    return lhs < rhs;
}


template bool smaller<int>(const int&, const int&);
template bool smaller<double>(const double&, const double&);
template bool smaller<float>(const float&, const float&);


template struct Heap<double, smaller<double>>;
template struct Heap<float, smaller<float>>;
template struct Heap<int, smaller<int>>;

