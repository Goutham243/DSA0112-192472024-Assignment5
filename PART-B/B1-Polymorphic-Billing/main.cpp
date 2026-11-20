
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Abstract Base Class
class Bill {
protected:
    string patientName;
    int patientId;

public:
    Bill(string name, int id)
        : patientName(name), patientId(id) {}

    // Pure virtual functions
    virtual double total() const = 0;
    virtual string type() const = 0;

    // Common function
    virtual void print() const {
        cout << "Bill Type: " << type() << endl;
        cout << "Patient Name: " << patientName << endl;
        cout << "Patient ID: " << patientId << endl;
        cout << "Total Amount: Rs. " << total() << endl;
        cout << "------------------------" << endl;
    }

    // Virtual destructor
    virtual ~Bill() = default;
};

// 1. Outpatient Bill
class OutPatientBill : public Bill {
private:
    double consultation;
    double tests;

public:
    OutPatientBill(string name, int id,
                   double c, double t)
        : Bill(name, id), consultation(c), tests(t) {}

    double total() const override {
        return consultation + tests;
    }

    string type() const override {
        return "Outpatient";
    }
};

// 2. Inpatient Bill
class InPatientBill : public Bill {
private:
    int days;
    double roomCharge;
    double procedureCharge;
    double medicineCharge;

public:
    InPatientBill(string name, int id, int d,
                  double room, double procedure,
                  double medicine)
        : Bill(name, id), days(d),
          roomCharge(room),
          procedureCharge(procedure),
          medicineCharge(medicine) {}

    double total() const override {
        return (days * roomCharge)
               + procedureCharge + medicineCharge;
    }

    string type() const override {
        return "Inpatient";
    }
};

// 3. Day Care Surgery Bill
class DayCareBill : public Bill {
private:
    double packagePrice;

public:
    DayCareBill(string name, int id, double price)
        : Bill(name, id), packagePrice(price) {}

    double total() const override {
        return packagePrice;
    }

    string type() const override {
        return "Day Care Surgery";
    }
};

// 4. Emergency Bill
class EmergencyBill : public Bill {
private:
    double baseCharge;
    double hourlyCharge;
    int hours;

public:
    EmergencyBill(string name, int id,
                  double base, double hourly, int h)
        : Bill(name, id), baseCharge(base),
          hourlyCharge(hourly), hours(h) {}

    double total() const override {
        return baseCharge + (hourlyCharge * hours);
    }

    string type() const override {
        return "Emergency";
    }
};

// Main Function
int main() {

    vector<Bill*> bills;

    bills.push_back(
        new OutPatientBill("Ravi", 101, 500, 1200));

    bills.push_back(
        new InPatientBill("Meena", 102, 3,
                          2500, 40000, 5000));

    bills.push_back(
        new DayCareBill("Arjun", 103, 25000));

    bills.push_back(
        new EmergencyBill("Priya", 104, 3000, 1000, 4));

    double grandTotal = 0;

    cout << "HOSPITAL BILLING SYSTEM" << endl;
    cout << "========================" << endl;

    // Runtime polymorphism
    for (Bill* b : bills) {
        b->print();
        grandTotal += b->total();
    }

    cout << "Grand Total: Rs. "
         << grandTotal << endl;

    // Free allocated memory
    for (Bill* b : bills) {
        delete b;
    }

    bills.clear();

    return 0;
}
