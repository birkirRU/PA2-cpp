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
    if (arr.size > 1) {  // Only sink if there are elements left
        sink(1);
    }
    return return_val;
}

template<typename T, bool (*comp)(const T&, const T&)>
void Heap<T, comp>::sink(const int& index) {
    assert(index > 0 && index < arr.size);

    int curri = index;
    
    while (true) {
        int lefti = curri * 2;
        int righti = curri * 2 + 1;
        bool exists_left = lefti < arr.size;
        bool exists_right = righti < arr.size;
        
        if (!exists_left && !exists_right) {
            // No children, we're done
            break;
        }
        
        int smallest = curri;
        
        // Find the smallest among current, left child, and right child
        if (exists_left && comp(arr[lefti], arr[smallest])) {
            smallest = lefti;
        }
        if (exists_right && comp(arr[righti], arr[smallest])) {
            smallest = righti;
        }
        
        // If current is already smallest, heap property is satisfied
        if (smallest == curri) {
            break;
        }
        
        // Swap with the smallest child and continue
        std::swap(arr[curri], arr[smallest]);
        curri = smallest;
    }
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
