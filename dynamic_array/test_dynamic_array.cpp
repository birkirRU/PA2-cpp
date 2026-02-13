// Dynamically Sized Array - Unit Tests
// C++98 Compatible
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;

// Color codes for output
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"


// Compare two files line by line
bool compareFiles(const char* file1, const char* file2) {
    ifstream f1(file1);
    ifstream f2(file2);
    
    if (!f1.is_open() || !f2.is_open()) {
        return false;
    }
    
    const int BUFFER = 1024;
    char line1[BUFFER];
    char line2[BUFFER];

    while (true) {
        f1.getline(line1, BUFFER);
        f2.getline(line2, BUFFER);

        bool has1 = !f1.eof() || strlen(line1) > 0;
        bool has2 = !f2.eof() || strlen(line2) > 0;

        if (!has1 && !has2) {
            break; // Both files ended
        }

        if (has1 != has2 || strcmp(line1, line2) != 0) {
            f1.close();
            f2.close();
            return false;
        }

        // Clear buffers
        line1[0] = '\0';
        line2[0] = '\0';
    }
    
    f1.close();
    f2.close();
    return true;
}

bool runTest(int testNum) {
    char testFile[64];
    char eoutFile[64];
    char actualFile[64];
    char command[256];

    sprintf(testFile, "tests/test%d.txt", testNum);
    sprintf(eoutFile, "tests/eout%d.txt", testNum);
    sprintf(actualFile, "actual%d.txt", testNum);
    
    // Check if test files exist
    ifstream testCheck(testFile);
    if (!testCheck.is_open()) {
        return true; // Skip missing tests
    }
    testCheck.close();
    
    ifstream eoutCheck(eoutFile);
    if (!eoutCheck.is_open()) {
        cout << YELLOW << "[SKIP]" << RESET << " Test " << testNum 
             << " - Expected output file not found" << endl;
        return true;
    }
    eoutCheck.close();
    
    // Run main program with test input
    sprintf(command, "./main < %s > %s 2>&1", testFile, actualFile);
    int result = system(command);
    
    if (result != 0) {
        cout << RED << "[FAIL]" << RESET << " Test " << testNum 
             << " - Program crashed" << endl;
        remove(actualFile);
        return false;
    }
    
    // Compare output files
    bool passed = compareFiles(actualFile, eoutFile);
    
    if (passed) {
        cout << GREEN << "[PASS]" << RESET << " Test " << testNum << endl;
    } else {
        cout << RED << "[FAIL]" << RESET << " Test " << testNum 
             << " - Output mismatch" << endl;
    }
    
    // Clean up
    remove(actualFile);
    
    return passed;
}

int main() {
    cout << CYAN << "========================================" << RESET << endl;
    cout << CYAN << "  Dynamic Array Test Suite" << RESET << endl;
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
    
    for (int i = 1; i <= totalTests; i++) {
        bool result = runTest(i);
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