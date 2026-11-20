
#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace chrono;

// Bill types
enum BillType {
    OUTPATIENT,
    INPATIENT
};

// Single bill structure
struct Bill {
    BillType type;
    int days;
    double consultation;
    double tests;
    double room;
    double surgery;
};

// Calculate bill using switch
double total(const Bill& b) {
    switch (b.type) {
        case OUTPATIENT:
            return b.consultation + b.tests;

        case INPATIENT:
            return b.days * b.room + b.surgery;
    }

    return 0;
}

// Benchmark
void benchmark(int n) {
    vector<Bill> bills;
    bills.reserve(n);

    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            bills.push_back({
                OUTPATIENT, 0, 500, 1200, 0, 0
            });
        } else {
            bills.push_back({
                INPATIENT, 3, 0, 0, 2500, 40000
            });
        }
    }

    volatile double sum = 0;

    auto start = high_resolution_clock::now();

    for (const Bill& b : bills) {
        sum += total(b);
    }

    auto stop = high_resolution_clock::now();

    auto time = duration_cast<microseconds>(
        stop - start).count();

    cout << n << " bills: "
         << time << " microseconds"
         << " | Total: " << sum << endl;
}

int main() {
    cout << "SWITCH STATEMENT BILLING\n";
    cout << "------------------------\n";

    // Verify same 10 bills
    vector<Bill> bills;

    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            bills.push_back({
                OUTPATIENT, 0, 500, 1200, 0, 0
            });
        } else {
            bills.push_back({
                INPATIENT, 3, 0, 0, 2500, 40000
            });
        }
    }

    double sum = 0;

    for (const Bill& b : bills)
        sum += total(b);

    cout << "Total of 10 bills: " << sum << endl;

    cout << "\nPerformance Testing\n";

    benchmark(1000);
    benchmark(1000000);
    benchmark(10000000);

    return 0;
}
