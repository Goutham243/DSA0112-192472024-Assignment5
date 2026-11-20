
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <algorithm>
using namespace std;

// ===============================
// EXISTING BILL HIERARCHY
// Keep existing classes unchanged
// ===============================

class Bill {
protected:
    string patientName;
    int patientId;

public:
    Bill(string name, int id)
        : patientName(name), patientId(id) {}

    virtual double total() const = 0;
    virtual string type() const = 0;

    virtual void print() const {
        cout << "Bill Type: " << type() << endl;
        cout << "Patient: " << patientName << endl;
        cout << "Patient ID: " << patientId << endl;
        cout << "Total: Rs. " << total() << endl;
    }

    virtual ~Bill() = default;
};

// Existing Outpatient Bill
class OutPatientBill : public Bill {
private:
    double consultation, tests;

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

// Existing Inpatient Bill
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
        return days * roomCharge
               + procedureCharge + medicineCharge;
    }

    string type() const override {
        return "Inpatient";
    }
};

// Existing Day Care Bill
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
        return "Day Care";
    }
};

// Existing Emergency Bill
class EmergencyBill : public Bill {
private:
    double baseCharge, hourlyCharge;
    int hours;

public:
    EmergencyBill(string name, int id,
                  double base, double hourly, int h)
        : Bill(name, id), baseCharge(base),
          hourlyCharge(hourly), hours(h) {}

    double total() const override {
        return baseCharge + hourlyCharge * hours;
    }

    string type() const override {
        return "Emergency";
    }
};

// ===============================
// B4.1 - NEW BILL TYPE
// ===============================

class DialysisBill : public Bill {
private:
    int sessions;
    double sessionCharge;
    double consumables;

public:
    DialysisBill(string name, int id, int s,
                 double charge, double extra)
        : Bill(name, id), sessions(s),
          sessionCharge(charge), consumables(extra) {}

    double total() const override {
        return sessions * sessionCharge + consumables;
    }

    string type() const override {
        return "Dialysis";
    }
};

// ===============================
// EXISTING PAYER HIERARCHY
// ===============================

class Payer {
public:
    virtual double amountCovered(const Bill& bill) const = 0;
    virtual string name() const = 0;

    virtual ~Payer() = default;
};

// Self payment
class SelfPay : public Payer {
public:
    double amountCovered(const Bill&) const override {
        return 0;
    }

    string name() const override {
        return "Self Pay";
    }
};

// Insurance payer
class Insurance : public Payer {
private:
    double coverLimit;
    double copayPercent;

public:
    Insurance(double limit, double copay)
        : coverLimit(limit), copayPercent(copay) {}

    double amountCovered(const Bill& bill) const override {
        double eligible = bill.total() *
                          (1 - copayPercent / 100.0);

        return min(eligible, coverLimit);
    }

    string name() const override {
        return "Insurance";
    }
};

// Government health scheme
class GovernmentScheme : public Payer {
public:
    double amountCovered(const Bill& bill) const override {
        if (bill.type() == "Outpatient")
            return min(bill.total(), 1500.0);

        if (bill.type() == "Inpatient")
            return min(bill.total(), 45000.0);

        if (bill.type() == "Day Care")
            return min(bill.total(), 20000.0);

        if (bill.type() == "Emergency")
            return min(bill.total(), 6000.0);

        if (bill.type() == "Dialysis")
            return min(bill.total(), 9000.0);

        return 0;
    }

    string name() const override {
        return "Government Scheme";
    }
};

// ===============================
// B4.1 - NEW PAYER
// ===============================

class CorporatePayer : public Payer {
private:
    double coveragePercent;
    double maximumLimit;

public:
    CorporatePayer(double percent, double limit)
        : coveragePercent(percent), maximumLimit(limit) {}

    double amountCovered(const Bill& bill) const override {
        double amount =
            bill.total() * coveragePercent / 100.0;

        return min(amount, maximumLimit);
    }

    string name() const override {
        return "Corporate Tie-Up";
    }
};

// ===============================
// B4.2 - EXCEPTION SAFETY
// ===============================

class BillingError : public runtime_error {
public:
    using runtime_error::runtime_error;
};

class Guard {
private:
    string resource;

public:
    Guard(string name) : resource(name) {
        cout << "Resource acquired: "
             << resource << endl;
    }

    ~Guard() {
        cout << "Resource released: "
             << resource << endl;
    }
};

void testExceptionSafety() {
    Guard g("Exception Test");

    throw BillingError("Test billing exception");
}

// ===============================
// MAIN FUNCTION
// ===============================

int main() {

    cout << "HOSPITAL BILLING SYSTEM - B4\n";
    cout << "============================\n\n";

    vector<unique_ptr<Bill>> bills;

    // Original four bill types
    bills.push_back(make_unique<OutPatientBill>(
        "Ravi", 101, 500, 1200));

    bills.push_back(make_unique<InPatientBill>(
        "Meena", 102, 3, 2500, 40000, 5000));

    bills.push_back(make_unique<DayCareBill>(
        "Arjun", 103, 25000));

    bills.push_back(make_unique<EmergencyBill>(
        "Priya", 104, 3000, 1000, 4));

    // New bill type
    bills.push_back(make_unique<DialysisBill>(
        "Kiran", 105, 5, 1800, 1200));

    // Verify all bill types
    cout << "BILL DETAILS\n";
    cout << "------------\n";

    double grandTotal = 0;

    for (const auto& b : bills) {
        b->print();
        cout << "--------------------\n";
        grandTotal += b->total();
    }

    cout << "Grand Total: Rs. "
         << grandTotal << endl;

    // New payer test
    CorporatePayer corporate(80, 20000);

    cout << "\nNEW PAYER TEST\n";
    cout << "--------------\n";

    cout << "Payer: " << corporate.name() << endl;

    cout << "Dialysis Bill: Rs. "
         << bills.back()->total() << endl;

    cout << "Corporate Covered: Rs. "
         << corporate.amountCovered(*bills.back())
         << endl;

    cout << "Patient Pays: Rs. "
         << bills.back()->total()
            - corporate.amountCovered(*bills.back())
         << endl;

    // Test existing payer classes
    SelfPay self;
    Insurance insurance(50000, 20);
    GovernmentScheme government;

    cout << "\nEXISTING PAYER TEST\n";
    cout << "-------------------\n";

    cout << self.name() << ": Rs. "
         << self.amountCovered(*bills[0]) << endl;

    cout << insurance.name() << ": Rs. "
         << insurance.amountCovered(*bills[0]) << endl;

    cout << government.name() << ": Rs. "
         << government.amountCovered(*bills[0]) << endl;

    // Exception handling test
    cout << "\nEXCEPTION SAFETY TEST\n";
    cout << "---------------------\n";

    try {
        testExceptionSafety();
    }
    catch (const BillingError& e) {
        cout << "Caught exception: "
             << e.what() << endl;
    }

    cout << "\nAll tests completed successfully.\n";

    return 0;
}
