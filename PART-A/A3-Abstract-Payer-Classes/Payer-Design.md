# A3 – Design with Abstract Classes

## A3.1 – Payer Interface (3 Marks)

### 1. Introduction

In a hospital billing system, bills can be paid by different types of payers, such as the patient, an insurance company or a government health scheme.

Each payer follows a different payment policy. To handle these payment methods uniformly, an abstract base class named `Payer` is designed.

### 2. Abstract Base Class – Payer

The `Payer` class provides a common interface for all payment methods.

**Function:**

`amountCovered(const Bill&)`

- It is a pure virtual function.
- It receives a reference to a hospital Bill object.
- It calculates and returns the amount covered by the payer.
- Each derived class implements its own payment policy.

### 3. Derived Classes

**1. SelfPay**

- The patient pays the entire bill amount.
- The payer covers zero amount.
- Amount Covered = 0.

**2. Insurance**

- Stores the policy cover limit and co-payment percentage.
- The insurance company pays the eligible amount after applying the co-payment.
- The payment cannot exceed the remaining policy cover.

Formula:

Insurance Amount = Minimum of:

- Bill Amount × (1 − Co-payment Percentage / 100)
- Remaining Cover Limit

**3. GovernmentScheme**

- Provides fixed package rates for different bill types.
- Checks the bill type and its corresponding approved package rate.
- Covers the eligible amount according to the scheme's package policy.

### 4. Class Design

| Class | Data Members | Function |
|---|---|---|
| Payer | Common interface | amountCovered() – pure virtual |
| SelfPay | No additional data | Returns 0 |
| Insurance | coverLimit, coPaymentPercentage | Calculates insurance coverage |
| GovernmentScheme | Fixed package rates | Calculates scheme coverage |

### A3.2 – Extension: Adding a New Payer (2 Marks)

A new payer named `CorporatePayer` can be added by inheriting from the abstract `Payer` class.

**CorporatePayer:**
- Stores the corporate coverage percentage.
- Implements the `amountCovered(const Bill&)` function.
- Calculates the amount covered based on the corporate agreement.

Formula:

Corporate Coverage = Bill Amount × Corporate Coverage Percentage / 100

### Example Design

```text
Payer
  |
  |-- SelfPay
  |
  |-- Insurance
  |
  |-- GovernmentScheme
  |
  |-- CorporatePayer (New)
```

The new class implements the existing pure virtual function. There is no need to modify the existing `Payer`, `SelfPay`, `Insurance` or `GovernmentScheme` classes.

### Advantages of This Design

1. Supports runtime polymorphism.
2. Makes the system easy to extend.
3. Reduces code duplication.
4. Supports different payment policies through a common interface.
5. Improves maintainability.

## Alternative Concept and Complexity Analysis

### Using Function Pointers or std::function Instead of an Abstract Payer Class

Instead of creating an abstract `Payer` class, payment policies can be represented using function pointers or `std::function` objects.

Each payer can have a separate policy function that calculates the covered amount.

### Example Using std::function

```cpp
#include <functional>
#include <algorithm>

struct InsurancePolicy {
    double coverLimit;
    double coPaymentPercentage;
};

std::function<double(double)> createInsurancePolicy(
    InsurancePolicy policy)
{
    return [policy](double billAmount) {
        double eligible = billAmount *
            (1.0 - policy.coPaymentPercentage / 100.0);

        return std::min(eligible, policy.coverLimit);
    };
}
```

The policy data is stored with the callable object using a captured value.

### Complexity Comparison

| Factor | Abstract Payer Class | std::function |
|---|---|---|
| Function call | Virtual function call | Callable function |
| Time per call | O(1) | O(1) |
| Space per payer | Object data and typically a vptr | Callable storage and captured data |
| Cover limit | Stored as a class data member | Stored in captured policy data |
| Extension | Add a derived class | Create a new policy function |
| Design | Object-oriented | Function-based |

### Conclusion

Both approaches provide O(1) time per payment calculation. An abstract Payer class is suitable when payment methods have separate data and behavior. `std::function` is useful when payment policies need to be selected dynamically as callable objects.

The abstract class approach provides a clear object-oriented structure and supports easy extension of the hospital billing system.
