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




# AVL Tree Implementation

## **AVL Tree (Self-Balancing Binary Search Tree)**

### **Overview**
An AVL Tree is a self-balancing binary search tree where the heights of the two child subtrees of any node differ by at most one. This ensures O(log n) time complexity for all major operations by maintaining tree balance through rotations.

**Implementation Notes**:
- **Self-balancing mechanism**: Automatic rebalancing after insert/erase via rotations
- **Balance factor**: Maintained within [-1, 1] for every node (height_left - height_right)
- **Rotation types**: Single rotations (left, right) and double rotations (left-right, right-left)
- **Augmented nodes**: Each node stores height and subtree size for efficient operations
- **Parent pointers**: Nodes maintain parent references for efficient traversal
- **Key-value pairs**: Stores integer keys with associated integer values

### **Time Complexities & Edge Cases**

| Operation | Time Complexity | Exceptional Cases / Behavior |
|-----------|----------------|------------------------------|
| **Constructor** | O(1) | Initializes empty tree with NULL root |
| **Constructor(key, value)** | O(1) | Creates tree with single root node |
| **Destructor** | O(n) | Recursively deletes all nodes via delete_tree |
| **Assignment Operator** | O(n) | Deep copy via copy_of_tree; Handles self-assignment |
| **insert(key, value)** | O(log n) | Returns pointer to inserted/existing node; Duplicate keys update existing node; Triggers rebalancing |
| **erase(node)** | O(log n) | Asserts node not NULL; Removes node and rebalances tree; Returns NULL |
| **find(key)** | O(log n) | Returns pointer to node with key, or NULL if not found |
| **lower_bound(key)** | O(log n) | Returns node with smallest key ≥ given key, or NULL if none exists |
| **upper_bound(key)** | O(log n) | Returns node with smallest key > given key, or NULL if none exists |
| **front()** | O(log n) | Returns leftmost (minimum) node, or NULL if tree empty |
| **back()** | O(log n) | Returns rightmost (maximum) node, or NULL if tree empty |
| **successor(node)** | O(log n) | Returns next node in sorted order, or NULL if node is maximum |
| **predecessor(node)** | O(log n) | Returns previous node in sorted order, or NULL if node is minimum |
| **rank(node)** | O(log n) | Returns 0-based index of node in sorted order; Returns 0 if node is NULL |
| **kth(k)** | O(log n) | Returns node at 0-based index k in sorted order, or NULL if k out of bounds |
| **size()** | O(1) | Returns total number of nodes in tree; Returns 0 if tree empty |

### **Memory Management**

**Allocation Strategy:**
- Each node allocated dynamically with `new` operator
- Nodes store: key, value, height, size, left, right, parent pointers
- Memory overhead: 7 integers per node (28 bytes on 32-bit, 56 bytes with pointers on 64-bit)

**Balancing Strategy:**
- After each insert/erase, updates height and size bottom-up to root
- Checks balance factor at each node along path
- Performs rotations when |balance_factor| > 1
- Four rotation cases:
  - **Left-Left (LL)**: Single right rotation
  - **Right-Right (RR)**: Single left rotation
  - **Left-Right (LR)**: Left rotation on left child, then right rotation
  - **Right-Left (RL)**: Right rotation on right child, then left rotation

**Copy Semantics:**
- **Copy Constructor**: Not explicitly implemented; uses default (shallow copy - potential issue)
- **Assignment Operator**: Deep copy via copy_of_tree; Deletes existing tree before copying

**Key Features:**
- Guaranteed O(log n) height for all operations
- Order statistics: rank() and kth() for finding positions and elements
- Range queries: lower_bound() and upper_bound() for interval searches
- Bidirectional traversal: successor() and predecessor() for in-order iteration
- Augmented data: size field enables O(log n) order statistics

### **Node Structure**

Each node contains:
- **key**: Integer search key (unique identifier)
- **value**: Associated integer value (can be updated)
- **height**: Height of subtree rooted at this node (for balancing)
- **size**: Number of nodes in subtree rooted at this node (for order statistics)
- **left**: Pointer to left child (smaller keys)
- **right**: Pointer to right child (larger keys)
- **parent**: Pointer to parent node (NULL for root)

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

- **tests/test1.txt / tests/eout1.txt**: Basic insert and find operations
- **tests/test2.txt / tests/eout2.txt**: Front, back, and successor traversal
- **tests/test3.txt / tests/eout3.txt**: Rank and kth element operations
- **tests/test4.txt / tests/eout4.txt**: Lower bound and upper bound searches
- **tests/test5.txt / tests/eout5.txt**: Erase operations and size updates
- **tests/test6.txt / tests/eout6.txt**: Set value and get operations
- **tests/test7.txt / tests/eout7.txt**: Predecessor traversal operations
- **tests/test8.txt / tests/eout8.txt**: Multiple tree instances and assignment
- **tests/test9.txt / tests/eout9.txt**: Duplicate key insertion and complex operations
- **tests/test10.txt / tests/eout10.txt**: Comprehensive stress test with mixed operations

### **Test Input Format**

Each test file follows this format:
```
<number_of_operations>
<instance_number> <operation> [arguments...]
```

**Operations:**
- `i` key value: insert(key, value) - Insert or update key-value pair; Sets cursor to inserted/updated node
- `?` key: find(key) - Find node with given key; Sets cursor to found node or NULL
- `l` key: lower_bound(key) - Find node with smallest key ≥ given key; Sets cursor
- `u` key: upper_bound(key) - Find node with smallest key > given key; Sets cursor
- `e`: erase(cursor) - Erase node at cursor; Sets cursor to NULL
- `f`: front() - Get minimum (leftmost) node; Sets cursor
- `b`: back() - Get maximum (rightmost) node; Sets cursor
- `>`: successor(cursor) - Get next node in sorted order; Updates cursor
- `<`: predecessor(cursor) - Get previous node in sorted order; Updates cursor
- `r`: rank(cursor) - Get 0-based index of cursor node; Prints to output; Prints "-" if cursor is NULL
- `k` k: kth(k) - Get node at 0-based index k; Sets cursor
- `g`: Get value at cursor; Prints to output; Prints "-" if cursor is NULL
- `s` value: Set value at cursor to value; Does nothing if cursor is NULL
- `z`: size() - Get total number of nodes; Prints to output
- `a` other_instance: Assignment from other_instance; Sets cursor to NULL

### **Test Execution**

The test runner automatically:
1. Runs each test file (tests/test1.txt through tests/test10.txt)
2. Compares actual output with expected output (tests/eout1.txt through tests/eout10.txt)
3. Reports pass/fail status with color coding
4. Provides a summary of test results

**Expected Output:**
```
========================================
  AVL Tree Test Suite
========================================

[PASS] Test 1
[PASS] Test 2
[PASS] Test 3
[PASS] Test 4
[PASS] Test 5
[PASS] Test 6
[PASS] Test 7
[PASS] Test 8
[PASS] Test 9
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

- **avl_tree.h**: Header file with Node struct and AVLTree class declaration
- **main.cpp**: Interactive program for manual testing with multiple tree instances
- **test_avl_tree.cpp**: Automated test suite runner
- **Makefile**: Build automation with multiple targets
- **tests/test1.txt - tests/test10.txt**: Test input files
- **tests/eout1.txt - tests/eout10.txt**: Expected output files

## **Design Decisions**

1. **Parent Pointers**: Each node maintains a parent pointer for efficient traversal operations (successor, predecessor) without requiring a stack or recursion.

2. **Size Augmentation**: Each node stores its subtree size, enabling O(log n) order statistics (rank and kth) without additional overhead during updates.

3. **Duplicate Key Handling**: Inserting a duplicate key updates the value of the existing node rather than creating a new node, maintaining uniqueness of keys.

4. **Cursor-Based Interface**: The main.cpp uses a cursor system (array of node pointers) to track positions in multiple tree instances, enabling complex multi-instance operations.

5. **Rebalancing After Erase**: After erasing a node, the algorithm walks up from the parent to the root, updating heights/sizes and rebalancing at each step.

6. **NULL Handling**: Most operations gracefully handle NULL pointers, returning NULL or 0 as appropriate (e.g., rank(NULL) returns 0, find returns NULL if not found).

7. **Two-Step Insert**: The insert function uses an internal Insert helper that takes a reference parameter (new_node) to return the inserted node pointer while still returning the updated subtree root.

## **AVL Tree Operations**

### **Balancing Invariant**

The AVL tree maintains the following invariant:
```
For every node N:
  |height(N.left) - height(N.right)| ≤ 1
```

This ensures the tree height is at most 1.44 * log₂(n), guaranteeing O(log n) operations.

### **Rotation Examples**

**Right Rotation (LL case):**
```
    y                x
   / \              / \
  x   C    →       A   y
 / \                  / \
A   B                B   C
```

**Left Rotation (RR case):**
```
  x                  y
 / \                / \
A   y      →       x   C
   / \            / \
  B   C          A   B
```

### **Order Statistics Examples**

```
Tree: [10, 20, 30, 40, 50, 60, 70]

rank(node_30) → 2        (0-based index)
kth(2) → node_30         (node at index 2)
kth(0) → node_10         (minimum)
kth(6) → node_70         (maximum)
```

### **Range Query Examples**

```
Tree: [10, 20, 30, 40, 50, 60, 70]

lower_bound(25) → node_30    (smallest key ≥ 25)
lower_bound(30) → node_30    (exact match)
upper_bound(30) → node_40    (smallest key > 30)
upper_bound(25) → node_30    (smallest key > 25)
```

### **Typical Use Cases**

- Maintaining sorted data with frequent insertions/deletions
- Order statistics queries (finding kth smallest/largest element)
- Range queries (finding all elements in a range)
- Database indexing with balanced search performance
- Finding predecessor/successor in sorted order
- Implementing sorted sets and maps with guaranteed O(log n) performance

### **AVL Tree Invariants**

- **BST Property**: For every node N: all keys in left subtree < N.key < all keys in right subtree
- **Balance Property**: For every node N: |height(left) - height(right)| ≤ 1
- **Height Property**: height(N) = 1 + max(height(left), height(right))
- **Size Property**: size(N) = 1 + size(left) + size(right)
- **Parent Property**: For every non-root node N: N.parent.left == N or N.parent.right == N
- **Root Property**: root.parent == NULL

## **Complexity Analysis**

### **Height Guarantee**

The AVL tree height h satisfies:
```
h ≤ 1.44 * log₂(n + 2) - 0.328
```

This means a tree with 1,000,000 nodes has height at most 29, ensuring fast operations.

### **Operation Breakdown**

**Insert(key, value):**
- Search for insertion point: O(log n)
- Create new node: O(1)
- Update heights/sizes up to root: O(log n)
- Perform at most 2 rotations: O(1)
- Total: O(log n)

**Erase(node):**
- Find successor (if needed): O(log n)
- Remove node: O(1)
- Update heights/sizes up to root: O(log n)
- Perform O(log n) rotations in worst case: O(log n)
- Total: O(log n)

**Rank(node):**
- Walk from node to root: O(log n)
- Accumulate left subtree sizes: O(log n)
- Total: O(log n)

**Kth(k):**
- Recursively search using subtree sizes: O(log n)
- Total: O(log n)


# Hash Table Implementation

## **Hash Table (Separate Chaining)**

### **Overview**
A hash table implementation using separate chaining for collision resolution. The hash table maps integer keys to integer values and provides average-case O(1) insertion, deletion, and lookup operations. The implementation automatically resizes when the load factor exceeds 0.7 to maintain performance.

**Implementation Notes**:
- **Collision resolution**: Separate chaining with singly-linked lists
- **Hash function**: `hash(key) = abs(key * 539) % capacity`
- **Initial capacity**: 16 buckets (configurable via constructor)
- **Load factor threshold**: 0.7 (70%)
- **Resize factor**: 2x capacity when load factor exceeded
- **Duplicate key handling**: Insert ignores duplicates; use set operation (erase + insert) to update values
- **Dynamic resizing**: Automatic doubling of capacity with full rehashing

### **Time Complexities & Edge Cases**

| Operation | Average Case | Worst Case | Exceptional Cases / Behavior |
|-----------|-------------|------------|------------------------------|
| **Constructor** | O(c) | O(c) | Initializes hash table with capacity c (default 16); Allocates bucket array |
| **Destructor** | O(n) | O(n) | Traverses all chains to delete nodes; Deallocates bucket array |
| **Copy Constructor** | O(n) | O(n) | Deep copy via insert; Creates independent copy with same capacity |
| **Assignment Operator** | O(n + m) | O(n + m) | Destroys current table (m elements), deep copies rhs (n elements); Handles self-assignment |
| **insert(key, value)** | O(1) amortized | O(n) | Ignores duplicate keys (no update); May trigger resize; Worst case when all keys hash to same bucket |
| **erase(key)** | O(1) amortized | O(n) | Removes key-value pair; Does nothing if key not found; Decrements size |
| **access(key, ret_val)** | O(1) amortized | O(n) | Returns true and sets ret_val if key found; Returns false and sets ret_val to 0 if not found |
| **get_size()** | O(1) | O(1) | Returns number of key-value pairs in table |
| **resize()** | O(n) | O(n) | Doubles capacity; Rehashes all n elements; Called automatically when load factor > 0.7 |

### **Memory Management**

**Allocation Strategy**:
- **Bucket array**: Array of `capacity` pointers to linked list heads
- **Nodes**: Dynamically allocated for each key-value pair
- **Memory per node**: 2 integers (key, value) + 1 pointer (next)
- **Load factor control**: Maintains load factor ≤ 0.7 via automatic resizing

**Hash Function**:
- **Formula**: `hash(key) = abs(key * 539) % capacity`
- **Multiplier**: 539 (a prime-like constant for distribution)
- **Modulo**: Ensures index within [0, capacity-1]
- **Absolute value**: Handles negative keys

**Collision Resolution**:
- **Method**: Separate chaining with singly-linked lists
- **Chain structure**: Each bucket points to head of linked list
- **Insertion order**: New elements added to end of chain (to check for duplicates)
- **Chain traversal**: Linear search within chain for key lookup/deletion

**Resizing Strategy**:
- **Trigger**: Load factor = (size + 1) / capacity > 0.7
- **New capacity**: 2 × old capacity
- **Rehashing**: All elements rehashed into new table (hash values change with new capacity)
- **Memory efficiency**: Temporary doubling during resize (old + new tables)

**Copy Semantics**:
- **Copy Constructor**: Deep copy via insert; Preserves capacity and all key-value pairs
- **Assignment Operator**: Destroys existing table, deep copies from source; Handles self-assignment

**Key Features**:
- Average O(1) operations for insert, delete, and lookup
- Automatic resizing maintains performance
- Separate chaining handles collisions gracefully
- No update on duplicate insert (intentional design choice)
- Set operation (erase + insert) available for value updates

### **Node Structure**

Each node in the chaining linked lists contains:
- **key**: Integer search key (unique within table)
- **value**: Associated integer value
- **next**: Pointer to next node in chain (NULL if last)

### **Hash Table Structure**

The hash table maintains:
- **table**: Array of Node* pointers (bucket heads)
- **size**: Number of key-value pairs currently in table
- **capacity**: Number of buckets in the array

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

- **tests/test1.txt / tests/eout1.txt**: Basic insert and access operations
- **tests/test2.txt / tests/eout2.txt**: Erase operations and size tracking
- **tests/test3.txt / tests/eout3.txt**: Duplicate key insertion (no update)
- **tests/test4.txt / tests/eout4.txt**: Set operation (update via erase + insert)
- **tests/test5.txt / tests/eout5.txt**: Access on non-existent keys
- **tests/test6.txt / tests/eout6.txt**: Assignment operator and independence
- **tests/test7.txt / tests/eout7.txt**: Automatic resizing behavior
- **tests/test8.txt / tests/eout8.txt**: Multiple instances with assignment
- **tests/test9.txt / tests/eout9.txt**: Complex mixed operations
- **tests/test10.txt / tests/eout10.txt**: Large-scale stress test with collisions

### **Test Input Format**

Each test file follows this format:
```
<number_of_operations>
<instance_number> <operation> [arguments...]
```

**Operations:**
- `i` key value: insert(key, value) - Insert key-value pair; Ignores if key exists
- `e` key: erase(key) - Remove key-value pair; Does nothing if key doesn't exist
- `g` key: access(key, value) - Get value for key; Prints value if found, "-" if not found
- `s` key value: Set operation - Erase key then insert key-value (updates value)
- `z`: get_size() or access size member - Get number of elements; Prints to output
- `a` other_instance: Assignment from other_instance - Deep copy from another hash table instance

### **Test Execution**

The test runner automatically:
1. Runs each test file (tests/test1.txt through tests/test10.txt)
2. Compares actual output with expected output (tests/eout1.txt through tests/eout10.txt)
3. Reports pass/fail status with color coding
4. Provides a summary of test results

**Expected Output:**
```
========================================
  Hash Table Test Suite
========================================

[PASS] Test 1
[PASS] Test 2
[PASS] Test 3
[PASS] Test 4
[PASS] Test 5
[PASS] Test 6
[PASS] Test 7
[PASS] Test 8
[PASS] Test 9
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

- **hash_table.h**: Header file with Node struct and HashTable class
- **hash_table.cpp**: Implementation file (currently empty - all inline in header)
- **main.cpp**: Interactive program for manual testing with multiple table instances
- **test_hash_table.cpp**: Automated test suite runner
- **Makefile**: Build automation with multiple targets
- **tests/test1.txt - tests/test10.txt**: Test input files
- **tests/eout1.txt - tests/eout10.txt**: Expected output files

## **Design Decisions**

1. **Separate Chaining**: Chosen for simplicity and because it handles high load factors gracefully without clustering issues.

2. **No Update on Insert**: Duplicate key insertion is ignored rather than updating the value. This is intentional - use the set operation (erase + insert) to update values.

3. **Load Factor 0.7**: Chosen to balance memory usage and performance. At 70% capacity, resize is triggered to maintain O(1) average-case performance.

4. **2x Resize Factor**: Doubling the capacity provides amortized O(1) insertion while avoiding excessive resizing operations.

5. **Hash Function**: `hash(key) = abs(key * 539) % capacity` - The multiplier 539 is chosen for good distribution properties. Absolute value handles negative keys.

6. **End-of-Chain Insertion**: New elements are added to the end of chains (after checking for duplicates) rather than the front. This requires traversing the chain but ensures duplicate detection.

7. **Destructor Helper**: Separate `desctructor()` method allows reuse in assignment operator for cleanup before copying.

8. **Size Member**: Direct access to `size` member in main.cpp (via `table[instance].size`) provides O(1) size queries without function call overhead.

## **Hash Table Operations**

### **Load Factor and Resizing**

The hash table maintains performance by controlling the load factor:

```
Load Factor = (size + 1) / capacity

If Load Factor > 0.7:
    Resize to 2 × capacity
    Rehash all elements
```

**Example**:
```
Initial capacity: 16
Insert 11 elements -> size = 11, load factor = 12/16 = 0.75 > 0.7
Resize triggered -> new capacity = 32
All 11 elements rehashed into new 32-bucket table
```

### **Collision Handling**

When multiple keys hash to the same bucket:

```
Bucket 5: key=10 -> key=49 -> key=88 -> NULL

insert(127, value):
    hash(127) = 5
    Traverse chain: 10 -> 49 -> 88
    Check each for key=127 (not found)
    Add new node at end: 10 -> 49 -> 88 -> 127
```

### **Insert vs Set**

```
Table: { 10:100, 20:200, 30:300 }

insert(20, 999):
    Key 20 exists -> ignored
    Table: { 10:100, 20:200, 30:300 }  // No change

set(20, 999):
    erase(20) -> Table: { 10:100, 30:300 }
    insert(20, 999) -> Table: { 10:100, 20:999, 30:300 }  // Updated
```

### **Typical Use Cases**

- Key-value storage with fast lookup (dictionaries, caches)
- Counting occurrences (frequency maps)
- Detecting duplicates in data sets
- Implementing sets (store keys, ignore values)
- Symbol tables in compilers/interpreters
- Database indexing for non-sequential keys
- Memoization for dynamic programming

### **Hash Table Invariants**

- **Uniqueness**: Each key appears at most once in the table
- **Bucket Invariant**: key K is in bucket `hash(K) % capacity`
- **Size Invariant**: `size` equals total number of nodes across all chains
- **Chain Structure**: Each chain is a NULL-terminated singly-linked list
- **Load Factor Control**: `size / capacity ≤ 0.7` after any operation (may temporarily exceed during insert before resize)

## **Complexity Analysis**

### **Average Case Analysis**

With good hash distribution and load factor ≤ 0.7:

**Expected chain length** = load factor ≈ 0.7

Therefore:
- **Insert**: Hash computation O(1) + chain traversal O(0.7) ≈ O(1)
- **Lookup**: Hash computation O(1) + chain traversal O(0.7) ≈ O(1)
- **Delete**: Hash computation O(1) + chain traversal O(0.7) ≈ O(1)

### **Worst Case Analysis**

When all keys hash to the same bucket:

**Chain length** = n (all elements in one chain)

Therefore:
- **Insert**: O(n) to traverse chain and check for duplicates
- **Lookup**: O(n) to traverse chain
- **Delete**: O(n) to find and remove element

### **Amortized Analysis of Resizing**

**Resize cost**: O(n) to rehash all elements

**Resize frequency**: After every n/2 insertions (when load factor hits 0.7)

**Amortized cost per insert**:
```
Total cost for n insertions:
= n × O(1) for normal inserts
+ O(log n) resizes × O(n) per resize
= O(n) + O(n log n) / O(n)
= O(1) amortized per insert
```

### **Space Complexity**

- **Table array**: O(capacity) = O(n) when n elements stored
- **Nodes**: O(n) for n key-value pairs
- **Total**: O(n)
- **Overhead**: Bucket array may have empty slots; worst case 43% waste at load factor 0.7



# Doubly Linked List Implementation

## **Doubly Linked List (Circular with Sentinel)**

### **Overview**
A doubly linked list implementation using a circular structure with a sentinel node. Each node has pointers to both its predecessor and successor, enabling efficient bidirectional traversal. The sentinel node acts as a dummy node that simplifies edge cases by eliminating the need for NULL checks at the list boundaries.

**Implementation Notes**:
- **Sentinel node**: Dummy node that marks both the beginning and end of the list
- **Circular structure**: Last node's next points to sentinel; sentinel's prev points to last node
- **Bidirectional links**: Each node has both `prev` and `next` pointers
- **Iterator-like cursors**: Operations use node pointers as cursors for flexible positioning
- **Insert before cursor**: `insert(cursor, value)` inserts new node before the cursor position
- **No bounds checking**: Caller responsible for not erasing sentinel or dereferencing it

### **Time Complexities & Edge Cases**

| Operation | Time Complexity | Exceptional Cases / Behavior |
|-----------|----------------|------------------------------|
| **Constructor** | O(1) | Creates empty list with sentinel; Sentinel points to itself |
| **Destructor** | O(n) | Deletes all nodes except sentinel, then deletes sentinel |
| **Copy Constructor** | O(n) | Deep copy via copyFrom; Creates independent copy |
| **Assignment Operator** | O(n + m) | Clears current list (m elements), copies from rhs (n elements); Handles self-assignment |
| **insert(cursor, value)** | O(1) | Inserts new node before cursor; Returns pointer to new node; Works even if cursor is sentinel |
| **erase(cursor)** | O(1) | Removes node at cursor; Returns pointer to next node (successor); Caller must not erase sentinel |
| **successor(cursor)** | O(1) | Returns next node; Returns sentinel if cursor is last element |
| **predecessor(cursor)** | O(1) | Returns previous node; Returns sentinel if cursor is first element |
| **begin_node()** | O(1) | Returns first node in list (sentinel->next); Returns sentinel if list empty |
| **sentinel_end_node()** | O(1) | Returns sentinel node (marks end position) |
| **size()** | O(1) | Returns number of elements in list (excludes sentinel) |

### **Memory Management**

**Allocation Strategy**:
- **Sentinel node**: Single node allocated at construction, persists for lifetime of list
- **Data nodes**: Each element stored in dynamically allocated node
- **Memory per node**: 1 integer (data) + 2 pointers (prev, next)
- **No capacity/growth factor**: List grows one node at a time as needed

**Circular Structure**:
```
Empty list:
    sentinel <-> sentinel (points to itself)

List [10, 20, 30]:
    sentinel <-> [10] <-> [20] <-> [30] <-> sentinel
    ^_______________________________________________|
```

**Sentinel Benefits**:
- **No NULL checks**: All nodes always have valid prev/next pointers
- **Unified operations**: Insert/erase work identically at any position
- **Simple empty list**: Empty list has sentinel pointing to itself
- **Iterator end marker**: Sentinel serves as past-the-end iterator position

**Copy Semantics**:
- **Copy Constructor**: Deep copy creates new sentinel and all nodes; O(n) time
- **Assignment Operator**: Clears existing list, then deep copies from source
- **Independence**: Copied lists are completely independent (no shared nodes)

**Key Features**:
- O(1) insertion and deletion at any position (given cursor)
- O(1) bidirectional traversal (successor/predecessor)
- O(1) access to front via begin_node()
- Circular structure eliminates special cases for head/tail
- Sentinel node simplifies boundary conditions

### **Node Structure**

Each node contains:
- **data**: Integer value stored in the node
- **prev**: Pointer to previous node in the list
- **next**: Pointer to next node in the list

**Sentinel Node**:
- Special node that doesn't store meaningful data
- Acts as both the position before the first element and after the last element
- Always present, even in empty list
- Never erased or accessed for data

### **List Structure**

The DLL class maintains:
- **sentinel**: Pointer to the sentinel node
- **nodeCount**: Number of data nodes (excludes sentinel)

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

- **tests/test1.txt / tests/eout1.txt**: Basic insert and get operations
- **tests/test2.txt / tests/eout2.txt**: Front/back navigation and traversal
- **tests/test3.txt / tests/eout3.txt**: Erase operations and cursor movement
- **tests/test4.txt / tests/eout4.txt**: Successor and predecessor traversal
- **tests/test5.txt / tests/eout5.txt**: Set value and bidirectional iteration
- **tests/test6.txt / tests/eout6.txt**: Assignment operator and independence
- **tests/test7.txt / tests/eout7.txt**: Insert at various positions
- **tests/test8.txt / tests/eout8.txt**: Multiple instances with independent cursors
- **tests/test9.txt / tests/eout9.txt**: Complex mixed operations
- **tests/test10.txt / tests/eout10.txt**: Building and traversing larger lists

### **Test Input Format**

Each test file follows this format:
```
<number_of_operations>
<instance_number> <operation> [arguments...]
```

**Operations:**
- `i` value: insert(cursor, value) - Insert value before cursor; Sets cursor to new node
- `e`: erase(cursor) - Erase node at cursor; Sets cursor to successor (next node)
- `f`: begin_node() - Move cursor to first element (sentinel->next)
- `b`: sentinel_end_node() - Move cursor to sentinel (end position)
- `>`: successor(cursor) - Move cursor to next node
- `<`: predecessor(cursor) - Move cursor to previous node
- `g`: Get data at cursor - Prints cursor->data to output
- `s` value: Set data at cursor - Sets cursor->data = value
- `z`: size() - Get number of elements; Prints to output
- `a` other_instance: Assignment from other_instance - Deep copy from another list instance

### **Test Execution**

The test runner automatically:
1. Runs each test file (tests/test1.txt through tests/test10.txt)
2. Compares actual output with expected output (tests/eout1.txt through tests/eout10.txt)
3. Reports pass/fail status with color coding
4. Provides a summary of test results

**Expected Output:**
```
========================================
  Doubly Linked List Test Suite
========================================

[PASS] Test 1
[PASS] Test 2
[PASS] Test 3
[PASS] Test 4
[PASS] Test 5
[PASS] Test 6
[PASS] Test 7
[PASS] Test 8
[PASS] Test 9
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

- **doubly_linked_list.h**: Header file with Node struct and DLL class declaration
- **doubly_linked_list.cpp**: Implementation file with all member functions
- **main.cpp**: Interactive program for manual testing with multiple list instances
- **test_doubly_linked_list.cpp**: Automated test suite runner
- **Makefile**: Build automation with multiple targets
- **tests/test1.txt - tests/test10.txt**: Test input files
- **tests/eout1.txt - tests/eout10.txt**: Expected output files

## **Design Decisions**

1. **Sentinel Node**: Using a sentinel eliminates special cases for empty lists and boundary conditions. All operations work uniformly regardless of position.

2. **Circular Structure**: The last node's next points to sentinel, and sentinel's prev points to the last node. This creates a truly circular structure with no NULL pointers.

3. **Insert Before Cursor**: The `insert(cursor, value)` operation inserts the new node immediately before the cursor position. This allows insertion at the beginning (before begin_node()) and at the end (before sentinel).

4. **Erase Returns Successor**: After erasing a node, the cursor automatically moves to the next node (successor). This enables easy iteration with erase: `while (cursor != sentinel) { cursor = erase(cursor); }`

5. **Cursor Initialization**: All cursors are initialized to sentinel on list creation, representing an empty/end position.

6. **No Size Overhead in Operations**: Size is maintained as a member variable and updated during insert/erase, providing O(1) size queries without traversal.

7. **Separate Clear Method**: Private `clear()` method allows code reuse in destructor and assignment operator.

8. **CopyFrom Helper**: Private `copyFrom()` method handles deep copying for both copy constructor and assignment operator.

## **Doubly Linked List Operations**

### **Sentinel and Circular Structure**

The sentinel acts as a boundary marker:

```
Empty list:
    sentinel.next = sentinel
    sentinel.prev = sentinel
    
List [10]:
    sentinel <-> [10] <-> sentinel
    
List [10, 20, 30]:
    sentinel <-> [10] <-> [20] <-> [30] <-> sentinel
```

### **Insert Operation**

Inserting before a cursor position:

```
List: [10, 20, 30], cursor points to [20]

insert(cursor, 15):
    1. Create new node [15]
    2. [10].next = [15], [15].prev = [10]
    3. [15].next = [20], [20].prev = [15]
    Result: [10, 15, 20, 30]
```

**Special cases**:
- `insert(begin_node(), value)` - Insert at front
- `insert(sentinel, value)` - Insert at back (before sentinel = after last element)

### **Erase Operation**

Removing a node and returning successor:

```
List: [10, 20, 30], cursor points to [20]

erase(cursor):
    1. [10].next = [30]
    2. [30].prev = [10]
    3. delete [20]
    4. return [30]
    Result: [10, 30], cursor now at [30]
```

### **Traversal Examples**

**Forward traversal**:
```cpp
Node* cursor = list.begin_node();
while (cursor != list.sentinel_end_node()) {
    // Process cursor->data
    cursor = list.successor(cursor);
}
```

**Backward traversal**:
```cpp
Node* cursor = list.predecessor(list.sentinel_end_node()); // Last element
while (cursor != list.sentinel_end_node()) {
    // Process cursor->data
    cursor = list.predecessor(cursor);
}
```

### **Typical Use Cases**

- Implementing deques (double-ended queues)
- Browser history (forward/back navigation)
- Undo/redo functionality with bidirectional traversal
- Music playlists with previous/next navigation
- Text editors with cursor movement
- LRU cache implementation
- Any scenario requiring efficient insertion/deletion at arbitrary positions

### **List Invariants**

- **Sentinel invariant**: sentinel->next points to first element (or itself if empty); sentinel->prev points to last element (or itself if empty)
- **Circularity**: For any node N: N->next->prev == N and N->prev->next == N
- **Size invariant**: nodeCount equals the number of nodes reachable from sentinel (excluding sentinel itself)
- **Non-NULL invariant**: All prev and next pointers are non-NULL (point to sentinel if at boundary)
- **Sentinel exclusion**: Sentinel is never counted in size and should never be erased

## **Complexity Analysis**

### **Operation Breakdown**

**insert(cursor, value)**:
- Allocate new node: O(1)
- Update 4 pointers: O(1)
- Increment size: O(1)
- Total: O(1)

**erase(cursor)**:
- Update 2 pointers: O(1)
- Delete node: O(1)
- Decrement size: O(1)
- Total: O(1)

**Traversal operations (successor/predecessor)**:
- Follow pointer: O(1)
- Total: O(1)

**size()**:
- Return member variable: O(1)
- Total: O(1)

### **Comparison with Other Structures**

| Operation | Doubly Linked List | Dynamic Array | Singly Linked List |
|-----------|-------------------|---------------|-------------------|
| Insert at cursor | O(1) | O(n) | O(1) |
| Erase at cursor | O(1) | O(n) | O(1) forward only |
| Access by index | O(n) | O(1) | O(n) |
| Bidirectional traversal | O(1) per step | O(1) per step | Not supported |
| Memory per element | High (2 pointers) | Low (continuous) | Medium (1 pointer) |
| Cache friendliness | Poor | Excellent | Poor |

### **Space Complexity**

- **Per node overhead**: 2 pointers (16 bytes on 64-bit systems) + 1 integer (4 bytes) = 20-24 bytes per element
- **Sentinel overhead**: 1 extra node (20-24 bytes) regardless of list size
- **Total**: O(n) where n is the number of elements
- **Compared to array**: ~3-4x memory overhead due to pointer storage

### **When to Use Doubly Linked List**

**Use when**:
- Frequent insertions/deletions at arbitrary positions
- Bidirectional traversal required
- Constant-time splice operations needed
- List size varies significantly
- Cache misses acceptable

**Avoid when**:
- Random access by index is primary operation
- Memory is constrained
- Cache performance is critical
- Mostly sequential access with few modifications