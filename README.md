# PA2-cpp

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