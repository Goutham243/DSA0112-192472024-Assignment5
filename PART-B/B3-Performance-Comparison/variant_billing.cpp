
#include <iostream>
#include <vector>
#include <variant>
#include <chrono>
using namespace std;
using namespace chrono;

// Outpatient bill
struct OutPatientBill {
    double consultation;
    double tests;

    double total() const {
        return consultation + tests;
    }
};

// Inpatient bill
struct InPatientBill {
    int days;
    double room;
    double surgery;

    double total() const {
        return days * room + surgery;
    }
};

// Variant type
using Bill = variant<OutPatientBill, InPatientBill>;

int main() {
    cout << "VARIANT BILLING SYSTEM\n";
    cout << "----------------------\n";

    vector<Bill> bills;
    bills.reserve(10000000);

    // Create 10 million bills
    for (int i = 0; i < 10000000; i++) {
        if (i % 2 == 0) {
            bills.emplace_back(
                OutPatientBill{500, 1200});
        } else {
            bills.emplace_back(
                InPatientBill{3, 2500, 40000});
        }
    }

    volatile double sum = 0;

    auto start = high_resolution_clock::now();

    // Process using std::visit
    for (const Bill& b : bills) {
        sum += visit(
            [](const auto& bill) {
                return bill.total();
            }, b);
    }

    auto stop = high_resolution_clock::now();

    auto time = duration_cast<microseconds>(
        stop - start).count();

    cout << "Total bills: " << bills.size() << endl;
    cout << "Grand Total: " << sum << endl;
    cout << "Execution Time: "
         << time << " microseconds" << endl;

    cout << "Size of one Variant: "
         << sizeof(Bill) << " bytes" << endl;

    return 0;
}
