
#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>
#include <new>
using namespace std;

// Resource management class
class Guard {
public:
    Guard() {
        cout << "Object created" << endl;
    }

    ~Guard() {
        cout << "Object destroyed" << endl;
    }
};

// Custom exception
class ClaimError : public runtime_error {
public:
    using runtime_error::runtime_error;
};

// Validate charges
void validateCharge(double amount) {
    Guard g;

    if (amount < 0)
        throw invalid_argument("Negative charge");

    cout << "Charge valid: " << amount << endl;
}

// Validate insurance claim
void validateClaim(double bill, double cover) {
    Guard g;

    if (bill > cover)
        throw ClaimError("Claim exceeds cover");

    cout << "Claim approved" << endl;
}

// Validate package
void validatePackage(string code) {
    Guard g;

    if (code != "PKG101" && code != "PKG102")
        throw runtime_error("Unknown package code");

    cout << "Package valid" << endl;
}

// Convert text to number
void convertInput(string input) {
    Guard g;

    double value = stod(input);

    cout << "Converted value: " << value << endl;
}

// Force memory allocation failure

void testMemory() {
    Guard g;

    volatile size_t count =
        numeric_limits<size_t>::max();

    int* arr = new int[count];

    delete[] arr;

    cout << "Memory allocated" << endl;
}


// Main function
int main() {

    cout << "HOSPITAL ERROR TESTING" << endl;
    cout << "----------------------" << endl;

    // Test 1: Negative charge
    try {
        validateCharge(-500);
    }
    catch (const exception& e) {
        cout << "Caught: " << e.what() << endl;
    }
    catch (...) {
        cout << "Unknown error" << endl;
    }

    // Test 2: Claim exceeding cover
    try {
        validateClaim(60000, 50000);
    }
    catch (const exception& e) {
        cout << "Caught: " << e.what() << endl;
    }
    catch (...) {
        cout << "Unknown error" << endl;
    }

    // Test 3: Unknown package
    try {
        validatePackage("PKG999");
    }
    catch (const exception& e) {
        cout << "Caught: " << e.what() << endl;
    }
    catch (...) {
        cout << "Unknown error" << endl;
    }

    // Test 4: Invalid text input
    try {
        convertInput("hello");
    }
    catch (const exception& e) {
        cout << "Caught: " << e.what() << endl;
    }
    catch (...) {
        cout << "Unknown error" << endl;
    }

    // Test 5: Memory allocation failure
    try {
        testMemory();
    }
    catch (const bad_alloc& e) {
        cout << "Caught bad_alloc: "
             << e.what() << endl;
    }
    catch (const exception& e) {
        cout << "Caught allocation error: "
             << e.what() << endl;
    }
    catch (...) {
        cout << "Unknown memory error" << endl;
    }

    cout << "Program continues safely" << endl;

    return 0;
}
