# B4 – Final Engineering Decision

**Assignment:** Assignment 5 – CO5

## B4.1 – Practical Extension

Added a new bill type and a new payer without modifying existing classes.

### New Bill Type
- DialysisBill
- Calculates total using number of sessions, session charge and consumables.

### New Payer
- CorporatePayer
- Covers 80% of the bill amount, subject to a maximum limit of Rs. 20,000.

### Existing Classes
- OutPatientBill
- InPatientBill
- DayCareBill
- EmergencyBill
- SelfPay
- Insurance
- GovernmentScheme

All existing bill and payer classes remain unchanged.

## B4.2 – Resource Safety

Used:
- Virtual destructors
- std::unique_ptr
- RAII resource management
- Exception handling
- AddressSanitizer

The exception test verifies that the Guard destructor executes during stack unwinding.

Sanitizer execution was performed using:

```bash
g++ -std=c++17 -Wall -Wextra -g -fsanitize=address -fno-omit-frame-pointer main.cpp -o b4_asan
```

The actual sanitizer result is provided in `sanitizer_output.png`.

## B4.3 – Production Decision

**Decision: YES**

The polymorphic billing architecture with exception handling is suitable for the hospital group, subject to peak-load testing, concurrency testing and security validation.

Reasons:
1. New bill types can be added without modifying existing bill classes.
2. New payers can be introduced through inheritance.
3. Exceptions provide clear error reporting.
4. RAII and smart pointers improve resource safety.
5. The architecture supports maintainability and future extensions.

## Alternative Concept – Configuration-Based Rules

A configuration-based approach can store billing rates and payer percentages outside the C++ classes.

Advantages:
- Rates can be updated without recompiling the application.
- New simple billing packages can be configured easily.
- Rules can be validated during application startup.

Disadvantages:
- Configuration errors can cause incorrect billing.
- Complex billing calculations still require additional logic.
- Rule interpretation and validation introduce overhead.

A hybrid architecture is recommended: use polymorphism for billing and payer behaviour, exceptions for exceptional failures, and validated configuration files for frequently changing rates.

## Result

Successfully extended the hospital billing system with a new bill type and payer, verified existing bill calculations, demonstrated exception safety and prepared a production engineering recommendation.
