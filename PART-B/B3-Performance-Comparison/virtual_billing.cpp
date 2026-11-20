
#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace chrono;

// Abstract base class
class Bill {
public:
    virtual double total() const = 0;
    virtual ~Bill() = default;
};

// Outpatient bill
class OutPatient : public Bill {
    double consultation, tests;

public:
    OutPatient(double c, double t)
        : consultation(c), tests(t) {}

    double total() const override {
        return consultation + tests;
    }
};

// Inpatient bill
class InPatient : public Bill {
    int days;
    double room, surgery;

public:
    InPatient(int d, double r, double s)
        : days(d), room(r), surgery(s) {}

    double total() const override {
        return days * room + surgery;
    }
};

// Benchmark function
void benchmark(int n) {
    vector<OutPatient> op;
    vector<InPatient> ip;
    vector<Bill*> bills;

    op.reserve((n + 1) / 2);
    ip.reserve(n / 2);
    bills.reserve(n);

    for (int i = 0; i < n; i++) {
        if (i % 2 == 0)
            op.emplace_back(500, 1200);
        else
            ip.emplace_back(3, 2500, 40000);
    }

    size_t oi = 0, ii = 0;

    for (int i = 0; i < n; i++) {
        if (i % 2 == 0)
            bills.push_back(&op[oi++]);
        else
            bills.push_back(&ip[ii++]);
    }

    volatile double sum = 0;

    auto start = high_resolution_clock::now();

    for (Bill* b : bills) {
        sum += b->total();
    }

    auto stop = high_resolution_clock::now();

    auto time = duration_cast<microseconds>(
        stop - start).count();

    cout << n << " bills: "
         << time << " microseconds"
         << " | Total: " << sum << endl;
}

int main() {
    cout << "VIRTUAL FUNCTION BILLING\n";
    cout << "------------------------\n";

    // Verify same 10 bills
    OutPatient op(500, 1200);
    InPatient ip(3, 2500, 40000);

    Bill* bills[10] = {
        &op, &ip, &op, &ip, &op,
        &ip, &op, &ip, &op, &ip
    };

    double sum = 0;

    for (Bill* b : bills)
        sum += b->total();

    cout << "Total of 10 bills: " << sum << endl;

    cout << "\nPerformance Testing\n";

    benchmark(1000);
    benchmark(1000000);
    benchmark(10000000);

    return 0;
}
