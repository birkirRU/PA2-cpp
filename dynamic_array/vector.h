template<typename T>
struct DArr {
    // Member variables 
    int size;
    int capacity;
    T* data;
    
    // Constructors 
    DArr(int init_cap = 8);           // Declaration
    DArr(const DArr& other);          // Declaration
    ~DArr();                          // Declaration
    
    // Methods 
    void push_back(const T& value);   // Declaration
    void reserve(int new_capacity);   // Declaration
    T& operator[](int index);         // Declaration
    const T& operator[](int index) const;  // Declaration
    
    // Assignment operator 
    DArr& operator=(const DArr& rhs); // Declaration
};
