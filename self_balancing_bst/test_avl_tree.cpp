#include <iostream>
#include <cassert>

#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "avl_tree.h"
#include "../utils/file_comparer.h"

using namespace std;

// Color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"


int main() {
    cout << CYAN << "========================================" << RESET << endl;
    cout << CYAN << "  AVL Tree Test Suite" << RESET << endl;
    cout << CYAN << "========================================" << RESET << endl;
    cout << endl;
    
    // Check if main executable exists
    ifstream mainCheck("./main");
    if (!mainCheck.is_open()) {
        cout << RED << "Error: ./main executable not found!" << RESET << endl;
        cout << "Please run 'make main' first." << endl;
        return 1;
    }
    mainCheck.close();
    
    int totalTests = 10;
    int passedTests = 0;
    int failedTests = 0;
    
    const char* testDir = "tests";
    for (int i = 1; i <= totalTests; i++) {
        bool result = runTest(i, testDir);
        if (result) {
            passedTests++;
        } else {
            failedTests++;
        }
    }
    
    cout << endl;
    cout << CYAN << "========================================" << RESET << endl;
    cout << CYAN << "  Test Summary" << RESET << endl;
    cout << CYAN << "========================================" << RESET << endl;
    cout << "  Total:   " << totalTests << endl;
    cout << GREEN << "  Passed:  " << passedTests << RESET << endl;
    if (failedTests > 0) {
        cout << RED << "  Failed:  " << failedTests << RESET << endl;
    } else {
        cout << "  Failed:  " << failedTests << endl;
    }
    cout << CYAN << "========================================" << RESET << endl;
    cout << endl;
    
    if (failedTests == 0 && passedTests == totalTests) {
        cout << GREEN << "All tests passed!" << RESET << endl;
        return 0;
    } else if (failedTests > 0) {
        cout << RED << "Some tests failed!" << RESET << endl;
        return 1;
    } else {
        cout << YELLOW << "No tests were run!" << RESET << endl;
        return 1;
    }
}
