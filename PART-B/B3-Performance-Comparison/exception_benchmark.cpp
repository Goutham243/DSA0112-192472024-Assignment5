
#include <iostream>
#include <chrono>
#include <stdexcept>
using namespace std;
using namespace chrono;

// Return code validation
bool validateReturn(bool invalid) {
    return !invalid;
}

// Exception validation
void validateException(bool invalid) {
    if (invalid)
        throw runtime_error("Invalid bill");
}

// Benchmark return codes
void testReturn(int percent) {
    int n = 1000000;
    int errors = 0;

    auto start = high_resolution_clock::now();

    for (int i = 0; i < n; i++) {
        bool invalid = (i % 100) < percent;

        if (!validateReturn(invalid))
            errors++;
    }

    auto stop = high_resolution_clock::now();

    auto time = duration_cast<microseconds>(
        stop - start).count();

    cout << percent << "% invalid - Return codes: "
         << time << " microseconds"
         << " | Errors: " << errors << endl;
}

// Benchmark exceptions
void testException(int percent) {
    int n = 1000000;
    int errors = 0;

    auto start = high_resolution_clock::now();

    for (int i = 0; i < n; i++) {
        bool invalid = (i % 100) < percent;

        try {
            validateException(invalid);
        }
        catch (const exception&) {
            errors++;
        }
    }

    auto stop = high_resolution_clock::now();

    auto time = duration_cast<microseconds>(
        stop - start).count();

    cout << percent << "% invalid - Exceptions: "
         << time << " microseconds"
         << " | Errors: " << errors << endl;
}

int main() {
    cout << "EXCEPTION VS RETURN CODE BENCHMARK\n";
    cout << "----------------------------------\n";

    for (int percent : {0, 1, 50}) {
        testReturn(percent);
        testException(percent);
        cout << endl;
    }

    return 0;
}
