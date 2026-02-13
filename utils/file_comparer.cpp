#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;

// Color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"

// Compare two files
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

        if (!has1 && !has2) break;

        if (has1 != has2 || strcmp(line1, line2) != 0) {
            return false;
        }

        line1[0] = '\0';
        line2[0] = '\0';
    }

    return true;
}

bool runTest(int testNum, const char* testDir) {
    char testFile[256];
    char eoutFile[256];
    char actualFile[64];
    char command[512];

    sprintf(testFile, "%s/test%d.txt", testDir, testNum);
    sprintf(eoutFile, "%s/eout%d.txt", testDir, testNum);
    sprintf(actualFile, "actual%d.txt", testNum);
    
    ifstream testCheck(testFile);
    if (!testCheck.is_open()) {
        return true;
    }
    testCheck.close();
    
    ifstream eoutCheck(eoutFile);
    if (!eoutCheck.is_open()) {
        cout << YELLOW << "[SKIP]" << RESET
             << " Test " << testNum
             << " - Expected output file not found\n";
        return true;
    }
    eoutCheck.close();
    
    sprintf(command, "./main < %s > %s 2>&1", testFile, actualFile);
    int result = system(command);
    
    if (result != 0) {
        cout << RED << "[FAIL]" << RESET
             << " Test " << testNum
             << " - Program crashed\n";
        remove(actualFile);
        return false;
    }
    
    bool passed = compareFiles(actualFile, eoutFile);
    
    if (passed) {
        cout << GREEN << "[PASS]" << RESET
             << " Test " << testNum << "\n";
    } else {
        cout << RED << "[FAIL]" << RESET
             << " Test " << testNum
             << " - Output mismatch\n";
    }
    
    remove(actualFile);
    return passed;
}
