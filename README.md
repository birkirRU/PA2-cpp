# PA2-cpp

# PA2-cpp - Data Structure Implementations

## Overview
A template-based collection of fundamental data structures implemented in C++98, featuring automatic memory management and comprehensive testing.

## Common Features Across All Structures
- **Template-based**: Works with any data type
- **C++98 compliant**: Uses `assert()` for precondition checking
- **Memory safe**: Automatic management with deep copy semantics
- **Tested**: Each structure has 10+ test cases with expected outputs
- **Explicit instantiation**: Pre-compiled for `int`, `float`, and `double`

## Building and Testing

### Compilation Per data structure
```bash
make          # Build all main programs
make test     # Build all test suites
make all      # Build everything
```

### Running
```bash
make run      # Run interactive main program
make run-test # Run automated test suite
```

### Memory Checking
```bash
make valgrind-main  # Check main for leaks
make valgrind-test  # Check tests for leaks
```

### Cleanup
```bash
make clean
```

---

## Test Format
All test suites use the same input format:
```
<num_operations>
<instance_id> <operation> [args...]
```

Common operations (varies by structure):
- `+ val`: Insert value
- `-`: Remove value
- `p`/`t`/`g`: Peek/top/get
- `s`: Get size
- `a id`: Assign from instance `id`



# Dynamic Array Implementation

## **Dynamic Array (DArr)**

### **Overview**
A template-based dynamically resizable array implementation in C++98. The dynamic array automatically grows and shrinks based on usage, providing efficient random access while managing memory automatically.

**Implementation Notes**:
- **Growth factor**: Doubles capacity (2x) when full
- **Shrink factor**: Reduces to 1/4 capacity when size ≤ cap/4 (minimum capacity of 8)
- **Default initial capacity**: 8 elements
- **Underlying data structure**: Raw pointer to dynamically allocated array
- **Memory management**: Manual allocation/deallocation with proper copy semantics

### **Time Complexities & Edge Cases**

| Operation | Time Complexity | Exceptional Cases / Behavior |
|-----------|----------------|------------------------------|
| **Constructor** | O(n) where n is initial capacity | Allocates array of size init_cap (default 8) |
| **Destructor** | O(1) | Frees allocated memory, sets pointer to NULL |
| **Copy Constructor** | O(n) where n is size | Deep copy of all elements |
| **Assignment Operator** | O(n) where n is size | Self-assignment protected, deep copy |
| **push_back** | O(1) amortized, O(n) worst | Doubles capacity when full (requires copying all elements) |
| **pop_back** | O(1) amortized | Asserts size != 0; Shrinks to cap/4 when size ≤ cap/4 and cap > 8 |
| **operator[]** (get) | O(1) | Asserts 0 ≤ index < size; Returns reference to element |
| **operator[]** (set) | O(1) | Asserts 0 ≤ index < size; Modifies element in place |
| **insert** | O(n) where n is size | Asserts valid index; Shifts elements right; May trigger resize |
| **erase** | O(n) where n is size | Asserts 0 ≤ index < size; Shifts elements left |
| **resize** | O(n) where n is new size | May call reserve if n ≥ cap; Initializes new elements to T() |
| **reserve** | O(n) where n is new capacity | Allocates new array, copies elements, updates capacity |
| **print** | O(n) where n is size | Outputs size and all elements |

### **Memory Management**

**Allocation Strategy:**
- Initial allocation occurs in constructor with specified capacity (default 8)
- Dynamic reallocation happens when:
  - Size reaches capacity (growth): allocates 2x current capacity
  - Size drops to ≤ cap/4 (shrink): reallocates to cap/4 (minimum 8)

**Copy Semantics:**
- **Copy Constructor**: Creates independent deep copy of source array
- **Assignment Operator**: 
  - Self-assignment guard prevents issues
  - Allocates new memory before freeing old to ensure exception safety
  - Deep copies all elements from source

**Destruction:**
- Destructor frees all allocated memory using `delete[]`
- Sets pointer to NULL to prevent dangling pointer issues

**Key Features:**
- No memory leaks when properly used
- All dynamically allocated memory is properly freed
- Copy operations create independent instances
- Template instantiation for `int`, `float`, and `double` types

## **Testing**

### **Compilation and Execution**

**To compile the main program:**
```bash
make
# or
make main
```

**To compile the test suite:**
```bash
make test
```

**To run the main program (interactive mode):**
```bash
make run
# or
./main
```

**To run the automated test suite:**

```bash
make run-test
# or
./test
```
Note: Test suite needs 'main' to compiled also. To be sure run `make all`.

**To run with memory leak detection:**
```bash
make valgrind-main    # Check main program
make valgrind-test    # Check test suite
```

**To clean build artifacts:**
```bash
make clean
```

### **Test Suite Structure**

The test suite consists of 10 test files with corresponding expected output files:

- **test1.txt / eout1.txt**: Basic push_back and get operations
- **test2.txt / eout2.txt**: Pop_back operations
- **test3.txt / eout3.txt**: Insert operations at various positions
- **test4.txt / eout4.txt**: Erase operations
- **test5.txt / eout5.txt**: Set and get operations
- **test6.txt / eout6.txt**: Resize operations (grow and shrink)
- **test7.txt / eout7.txt**: Assignment operator deep copy
- **test8.txt / eout8.txt**: Capacity growth (trigger automatic resize)
- **test9.txt / eout9.txt**: Mixed operations
- **test10.txt / eout10.txt**: Multiple instances with assignment

### **Test Input Format**

Each test file follows this format:
```
<number_of_operations>
<instance_number> <operation> [arguments...]
```

**Operations:**
- `+` value: push_back(value)
- `-`: pop_back()
- `a` other_instance: assignment from other_instance
- `i` index value: insert(value, index)
- `e` index: erase(index)
- `g` index: get element at index (prints to output)
- `s` index value: set element at index to value
- `r` size: resize(size)
- `p`: print array (prints size and all elements)

### **Test Execution**

The test runner (`test_dynamic_array.cpp`) automatically:
1. Runs each test file (test1.txt through test10.txt)
2. Compares actual output with expected output (eout1.txt through eout10.txt)
3. Reports pass/fail status with detailed error messages
4. Provides a summary of test results

**Expected Output:**
```
========================================
  Dynamic Array Test Suite
========================================

  [PASS] Test 1
  [PASS] Test 2
  ...
  [PASS] Test 10

========================================
  Test Summary
========================================
  Total:   10
  Passed:  10
  Failed:  0
========================================

All tests passed! ✓
```

## **Implementation Files**

- **dynamic_array.h**: Header file with class declaration and member function signatures
- **dynamic_array.cpp**: Implementation file with all member function definitions
- **main.cpp**: Interactive program for manual testing
- **test_dynamic_array.cpp**: Automated test suite runner
- **Makefile**: Build automation
- **test1.txt - test10.txt**: Test input files
- **eout1.txt - eout10.txt**: Expected output files

## **Design Decisions**

1. **Template Explicit Instantiation**: The implementation explicitly instantiates templates for `int`, `float`, and `double` to allow separate compilation of .h and .cpp files.

2. **Assertions vs Exceptions**: Uses `assert()` for precondition checking rather than exceptions (C++98 compatibility and clear failure points during development).

3. **Amortized Analysis**: Growth factor of 2x ensures O(1) amortized time for push_back operations. Each element is copied at most log₂(n) times.

4. **Memory Efficiency**: Shrinking strategy (cap/4 when size ≤ cap/4) prevents excessive memory usage while avoiding thrashing from repeated grow/shrink cycles.

5. **Minimum Capacity**: Maintains minimum capacity of 8 to avoid excessive reallocations for small arrays.



# PA2-cpp - Min Heap Implementation

## **Min Heap**

### **Overview**
A binary min-heap implementation using a function pointer-based comparator system. The heap maintains the min-heap property where each parent node is smaller than or equal to its children. Built on top of the Dynamic Array data structure for automatic memory management.

**Implementation Notes**:
- **Underlying data structure**: Dynamic Array (DArr)
- **Index 0 is dummy**: Actual heap starts at index 1 for simpler parent/child calculations
- **Parent index**: `i / 2`
- **Left child index**: `i * 2`
- **Right child index**: `i * 2 + 1`
- **Heap property**: For min-heap, `parent ≤ children`
- **Comparator**: Template parameter allows custom comparison functions
- **Default comparator**: `min` function for min-heap behavior

### **Time Complexities & Edge Cases**

| Operation | Time Complexity | Exceptional Cases / Behavior |
|-----------|----------------|------------------------------|
| **Constructor** | O(1) | Initializes with dummy element at index 0 |
| **Destructor** | O(1) | DArr handles memory cleanup automatically |
| **Copy Constructor** | O(n) | Deep copy via DArr copy constructor |
| **Assignment Operator** | O(n) | Deep copy via DArr assignment |
| **push** | O(log n) amortized | Adds element and swims up to maintain heap property |
| **pop** | O(log n) | Asserts heap not empty; Returns and removes min element; Sinks replacement down |
| **peek** | O(1) | Asserts heap not empty; Returns reference to minimum element (index 1) |
| **get_size** | O(1) | Returns `arr.size - 1` (excluding dummy element) |
| **swim** | O(log n) | Moves element up tree until heap property restored |
| **sink** | O(log n) | Moves element down tree, choosing smaller child |

### **Memory Management**

**Allocation Strategy:**
- Relies entirely on underlying DArr for memory management
- Dummy element at index 0 simplifies index calculations
- Actual heap size is `arr.size - 1`

**Copy Semantics:**
- **Copy Constructor**: Creates independent deep copy via DArr
- **Assignment Operator**: Deep copy with proper cleanup

**Heap Property Maintenance:**
- **Swim (bubble up)**: Used after insertion to restore heap property
- **Sink (bubble down)**: Used after deletion to restore heap property

**Key Features:**
- Template-based for type flexibility
- Comparator function pointer allows custom heap types (min-heap, max-heap, etc.)
- Efficient O(log n) insertions and deletions
- O(1) access to minimum element

## **Testing**

### **Compilation and Execution**

**To compile the main program:**
```bash
make
# or
make main
```

**To compile the test suite:**
```bash
make test
```

**To run the main program (interactive mode):**
```bash
make run
# or
./main
```

**To run the automated test suite:**
```bash
make run-test
# or
./test
```

**To run with memory leak detection:**
```bash
make valgrind-main    # Check main program
make valgrind-test    # Check test suite
```

**To clean build artifacts:**
```bash
make clean
```

### **Test Suite Structure**

The test suite consists of 10 test files with corresponding expected output files in the `tests/` directory:

- **tests/test1.txt / tests/eout1.txt**: Basic push and peek operations
- **tests/test2.txt / tests/eout2.txt**: Pop operations maintain heap property
- **tests/test3.txt / tests/eout3.txt**: Size tracking through operations
- **tests/test4.txt / tests/eout4.txt**: Ascending insertion order
- **tests/test5.txt / tests/eout5.txt**: Descending insertion order
- **tests/test6.txt / tests/eout6.txt**: Random insertion with duplicate values
- **tests/test7.txt / tests/eout7.txt**: Assignment operator independence
- **tests/test8.txt / tests/eout8.txt**: Large number of mixed operations
- **tests/test9.txt / tests/eout9.txt**: Complex operation sequences
- **tests/test10.txt / tests/eout10.txt**: Multiple instances with assignment

### **Test Input Format**

Each test file follows this format:
```
<number_of_operations>
<instance_number> <operation> [arguments...]
```

**Operations:**
- `+` value: push(value) - Insert element into heap
- `-`: pop() - Remove and return minimum element
- `p`: peek() - Get minimum element (prints to output)
- `s`: get_size() - Get current heap size (prints to output)
- `a` other_instance: assignment from other_instance

### **Test Execution**

The test runner automatically:
1. Runs each test file (tests/test1.txt through tests/test10.txt)
2. Compares actual output with expected output (tests/eout1.txt through tests/eout10.txt)
3. Reports pass/fail status
4. Provides a summary of test results

**Expected Output:**
```
========================================
  Min Heap Test Suite
========================================

[PASS] Test 1
[PASS] Test 2
...
[PASS] Test 10

========================================
  Test Summary
========================================
  Total:   10
  Passed:  10
  Failed:  0
========================================

All tests passed!
```

## **Implementation Files**

- **heap.h**: Header file with class declaration
- **heap.cpp**: Implementation file with all member functions
- **main.cpp**: Interactive program for manual testing
- **test_heap.cpp**: Automated test suite runner
- **Makefile**: Build automation
- **tests/test1.txt - tests/test10.txt**: Test input files
- **tests/eout1.txt - tests/eout10.txt**: Expected output files
- **../dynamic_array.h**: Required dependency
- **../dynamic_array.cpp**: Required dependency

## **Design Decisions**

1. **Dummy Element at Index 0**: Simplifies parent/child index calculations:
   - Parent of i: `i / 2` (instead of `(i-1) / 2`)
   - Left child of i: `i * 2` (instead of `2*i + 1`)
   - Right child of i: `i * 2 + 1` (instead of `2*i + 2`)

2. **Function Pointer Comparator**: Allows compile-time customization of heap behavior without virtual functions or runtime polymorphism.

3. **Template Explicit Instantiation**: Explicitly instantiates for `int`, `float`, and `double` with `min` comparator.

4. **Swim and Sink Operations**:
   - **Swim**: Compares with parent and swaps upward until heap property satisfied
   - **Sink**: Compares with both children, swaps with smaller child, continues downward

5. **Built on Dynamic Array**: Leverages existing tested data structure for:
   - Automatic memory management
   - Dynamic resizing
   - Copy semantics

6. **Min-Heap Property**: Default `min` comparator ensures smallest element is always at root (index 1).

## **Heap Property Invariant**

For all valid indices i where `1 ≤ i < arr.size`:
- If `2*i < arr.size`: `comp(arr[i], arr[2*i])` (parent ≤ left child)
- If `2*i+1 < arr.size`: `comp(arr[i], arr[2*i+1])` (parent ≤ right child)

This invariant is maintained by:
- **swim()** after insertions
- **sink()** after deletions


# PA2-cpp - Stack Implementation

## **Stack (LIFO)**

### **Overview**
A Last-In-First-Out (LIFO) stack implementation built on top of the Dynamic Array data structure. The stack follows the principle that the most recently added element is the first one to be removed.

**Implementation Notes**:
- **Underlying data structure**: Dynamic Array (DArr)
- **LIFO principle**: Last element pushed is first to be popped
- **Top element access**: O(1) via array indexing
- **Dynamic resizing**: Handled automatically by underlying DArr
- **Template-based**: Works with any type T

### **Time Complexities & Edge Cases**

| Operation | Time Complexity | Exceptional Cases / Behavior |
|-----------|----------------|------------------------------|
| **Constructor** | O(1) | Initializes empty stack with underlying DArr |
| **Destructor** | O(1) | DArr handles cleanup automatically |
| **Copy Constructor** | O(n) | Deep copy via DArr copy constructor |
| **Assignment Operator** | O(n) | Deep copy via DArr assignment |
| **push** | O(1) amortized | Adds element to top; May trigger DArr resize |
| **pop** | O(1) amortized | Asserts stack not empty; Removes top element; May trigger DArr shrink |
| **top** | O(1) | Asserts stack not empty; Returns reference to top element |
| **get_size** | O(1) | Returns number of elements in stack |

### **Memory Management**

**Allocation Strategy:**
- Relies entirely on underlying DArr for memory management
- Stack size equals DArr size
- No additional memory overhead beyond DArr

**Copy Semantics:**
- **Copy Constructor**: Creates independent deep copy via DArr
- **Assignment Operator**: Deep copy with proper resource management

**Key Features:**
- Template-based for type flexibility
- Automatic memory management via DArr
- O(1) access to top element
- O(1) amortized push and pop operations

## **Testing**

### **Compilation and Execution**

**To compile the main program:**
```bash
make
# or
make main
```

**To compile the test suite:**
```bash
make test
```

**To run the main program (interactive mode):**
```bash
make run
# or
./main
```

**To run the automated test suite:**
```bash
make run-test
# or
./test
```

**To run with memory leak detection:**
```bash
make valgrind-main    # Check main program
make valgrind-test    # Check test suite
```

**To clean build artifacts:**
```bash
make clean
```

### **Test Suite Structure**

The test suite consists of 10 test files with corresponding expected output files in the `tests/` directory:

- **tests/test1.txt / tests/eout1.txt**: Basic push and top operations
- **tests/test2.txt / tests/eout2.txt**: Pop operations (LIFO order)
- **tests/test3.txt / tests/eout3.txt**: Size tracking through operations
- **tests/test4.txt / tests/eout4.txt**: Push and pop alternating
- **tests/test5.txt / tests/eout5.txt**: Multiple push then multiple pop
- **tests/test6.txt / tests/eout6.txt**: Stack with duplicate values
- **tests/test7.txt / tests/eout7.txt**: Assignment operator independence
- **tests/test8.txt / tests/eout8.txt**: Large sequence of operations
- **tests/test9.txt / tests/eout9.txt**: Complex mixed operations
- **tests/test10.txt / tests/eout10.txt**: Multiple instances with assignment

### **Test Input Format**

Each test file follows this format:
```
<number_of_operations>
<instance_number> <operation> [arguments...]
```

**Operations:**
- `+` value: push(value) - Push element onto stack
- `-`: pop() - Remove top element from stack
- `t`: top() - Get top element (prints to output)
- `s`: get_size() - Get current stack size (prints to output)
- `a` other_instance: assignment from other_instance

### **Test Execution**

The test runner automatically:
1. Runs each test file (tests/test1.txt through tests/test10.txt)
2. Compares actual output with expected output (tests/eout1.txt through tests/eout10.txt)
3. Reports pass/fail status
4. Provides a summary of test results

**Expected Output:**
```
========================================
  Stack Test Suite
========================================

[PASS] Test 1
[PASS] Test 2
...
[PASS] Test 10

========================================
  Test Summary
========================================
  Total:   10
  Passed:  10
  Failed:  0
========================================

All tests passed!
```

## **Implementation Files**

- **stack.h**: Header file with class declaration
- **stack.cpp**: Implementation file with all member functions
- **main.cpp**: Interactive program for manual testing
- **test_stack.cpp**: Automated test suite runner
- **Makefile**: Build automation
- **tests/test1.txt - tests/test10.txt**: Test input files
- **tests/eout1.txt - tests/eout10.txt**: Expected output files
- **../dynamic_array.h**: Required dependency
- **../dynamic_array.cpp**: Required dependency

## **Design Decisions**

1. **Wrapper around Dynamic Array**: Stack is a thin wrapper that provides LIFO interface over DArr's functionality.

2. **Template Explicit Instantiation**: Explicitly instantiates for `int`, `float`, and `double` to allow separate compilation.

3. **Top returns reference**: Allows modification of top element without popping: `stack.top() = new_value;`

4. **Size member removed**: Originally had redundant `size` member; removed in favor of using `arr.size` directly.

5. **Automatic Memory Management**: DArr handles all allocation, deallocation, and resizing automatically.

6. **Assert for preconditions**: Uses `assert()` for empty stack checks (pop, top) rather than exceptions.

## **Stack Operations**

### **LIFO Principle**
Stack follows Last-In-First-Out ordering:
```
push(10)  →  [10]           top: 10
push(20)  →  [10, 20]       top: 20
push(30)  →  [10, 20, 30]   top: 30
pop()     →  [10, 20]       top: 20
pop()     →  [10]           top: 10
```

### **Typical Use Cases**
- Function call stack (activation records)
- Expression evaluation (postfix, infix)
- Undo/redo functionality
- Backtracking algorithms
- Parenthesis matching
- Depth-first search

### **Stack Invariant**
- Top element is always at index `arr.size - 1`
- Size is always equal to `arr.size`
- Only top element is accessible (no random access)
