# A1 – Design the Polymorphic Bill Hierarchy

## A1.1 – Identify the Common Interface

### Introduction

A hospital billing system handles different types of bills such as Outpatient, Inpatient, Day Care Surgery and Emergency bills.

Although each bill has a different calculation method, all bills share some common information and operations.

To handle all bill types uniformly, an abstract base class named `Bill` is designed.

### 1. Common Data Members

The following data members are common to all bill types:

| Data Member | Description |
|---|---|
| patientName | Stores the patient's name |
| patientId | Stores the unique patient identification number |

### 2. Common Operations

| Function | Purpose |
|---|---|
| total() | Calculates the total bill amount |
| type() | Returns the type of bill |
| print() | Displays patient and bill details |

### 3. Abstract Base Class

The `Bill` class acts as a common interface for all bill types.

- `total()` is a pure virtual function because each bill has a different calculation.
- `type()` is a pure virtual function because each bill has its own type.
- `print()` is a common virtual function that displays the bill details.
- A virtual destructor is provided for safe deletion through base-class pointers.

### 4. Derived Classes

**OutPatientBill**
- Stores consultation charges and test charges.
- Total = Consultation Charges + Test Charges.

**InPatientBill**
- Stores number of days, room charges per day, procedure charges and medicine charges.
- Total = (Days × Room Charges) + Procedure Charges + Medicine Charges.

**DayCareBill**
- Stores the package price.
- Total = Package Price.

**EmergencyBill**
- Stores base charges, hourly charges and number of hours.
- Total = Base Charges + (Hourly Charges × Hours).

### Conclusion

The common interface provides a uniform way to handle different hospital bills. Runtime polymorphism allows the correct total() function to execute according to the actual bill object.
