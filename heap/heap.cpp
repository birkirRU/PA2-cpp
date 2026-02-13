#include "heap.h"

template<typename T, bool (*comp)(const T&, const T&)>
Heap<T, comp>::Heap() {
   arr = DArr<T>(); 
   T dummy = T();
   arr.push_back(dummy);
   // for calculating parent and child indices
   // resulting size of heap is arr.size - 1
}

template<typename T, bool (*comp)(const T&, const T&)>
Heap<T, comp>::~Heap() {
}

template<typename T, bool (*comp)(const T&, const T&)>
Heap<T, comp>::Heap(const Heap& rhs) {
    arr = rhs.arr;
}

template<typename T, bool (*comp)(const T&, const T&)>
void Heap<T, comp>::push(const T& data) {
    int index_to_swim = arr.size;
    arr.push_back(data);
    swim(index_to_swim);
}

template<typename T, bool (*comp)(const T&, const T&)>
void Heap<T, comp>::swim(const int& index) {
    assert (index > 0 && index < arr.size);

    int curri = index;
    int parent_index = curri / 2; 
    while (comp(arr[curri], arr[parent_index]) && parent_index != 0) {
        std::swap(arr[curri], arr[parent_index]);
        curri = parent_index;
        parent_index = curri / 2;
    }
    parent_index = curri;
}

template<typename T, bool (*comp)(const T&, const T&)>
T Heap<T, comp>::pop() {
    assert(arr.size > 1); // arr.size is 1 when heap is empty
    T return_val = arr[1];
    std::swap(arr[1], arr[arr.size-1]);
    arr.pop_back();
    sink(1);
    return return_val;
}

template<typename T, bool (*comp)(const T&, const T&)>
void Heap<T, comp>::sink(const int& index) {
    assert(index > 0 && index < arr.size);

    int curri = index;
    int lefti = curri * 2;
    int righti = curri * 2 + 1;
    bool exists_left = lefti < arr.size;
    bool exists_right = righti < arr.size;

    while (exists_left && exists_right) {
        bool l_smallest = comp(arr[lefti], arr[righti]);
        if (l_smallest && comp(arr[lefti], arr[curri])) {
            std::swap(arr[curri], arr[lefti]);
            curri = lefti;
        }
        else if (!l_smallest && comp(arr[righti], arr[curri])) {
            std::swap(arr[curri], arr[righti]);
            curri = righti;
        }
        lefti = curri * 2;
        righti = curri * 2 + 1;
        exists_left = lefti < arr.size;
        exists_right = righti < arr.size;
    }

    if (exists_left) {
        if (comp(arr[lefti], arr[curri])) std::swap(arr[curri], arr[lefti]);
    }
    else if (exists_right) {
        if (comp(arr[righti], arr[curri])) std::swap(arr[curri], arr[righti]);
    }
    else return;
}

template<typename T, bool (*comp)(const T&, const T&)>
T& Heap<T, comp>::peek() {
    assert( arr.size > 1 );
    return arr[1];
}

template<typename T, bool (*comp)(const T&, const T&)>
int Heap<T, comp>::get_size() {
    return arr.size - 1;
}

template<typename T, bool (*comp)(const T&, const T&)>
Heap<T, comp>& Heap<T, comp>::operator=(const Heap& rhs) {
    arr = rhs.arr;
    return *this;
}


template<typename T>
bool min(const T& lhs, const T& rhs) {
    return lhs < rhs;
}


template bool min<int>(const int&, const int&);
template bool min<double>(const double&, const double&);
template bool min<float>(const float&, const float&);


template struct Heap<double, min<double> >;
template struct Heap<float, min<float> >;
template struct Heap<int, min<int> >;

