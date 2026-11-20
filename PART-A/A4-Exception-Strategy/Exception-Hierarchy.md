# A4 – Design the Exception Strategy

## A4.1 – Identify the Errors (2 Marks)

### 1. Introduction

A hospital billing system must handle errors safely. It should detect invalid charges, incorrect insurance claims, missing patient records and memory allocation failures.

C++ exception handling provides a mechanism to report errors using `throw` and handle them using `try` and `catch`.

### 2. Errors in the Hospital Billing System

| S.No. | Error Condition | Exception |
|---|---|---|
| 1 | Negative billing charges | InvalidChargeError |
| 2 | Claim amount exceeds insurance cover | ClaimError |
| 3 | Unknown government package | UnknownPackageError |
| 4 | Patient record is missing | PatientNotFoundError |
| 5 | Memory allocation failure | std::bad_alloc |

### 3. Exception Class Hierarchy

All custom exception classes are derived from `std::exception` through a common base class named `BillingError`.

```text
                 std::exception
                       |
                  BillingError
                       |
          +------------+-------------+
          |            |             |
    ClaimError   InvalidChargeError  PatientNotFoundError
                       |
              UnknownPackageError

Memory allocation failure:
std::bad_alloc (standard exception)
```

### 4. Description of Exception Classes

**BillingError**
- Common base class for hospital billing errors.
- Provides a common error-reporting interface.

**InvalidChargeError**
- Raised when a billing charge is negative.

**ClaimError**
- Raised when an insurance claim exceeds the available cover.

**UnknownPackageError**
- Raised when a government package is not available.

**PatientNotFoundError**
- Raised when the requested patient record does not exist.

**std::bad_alloc**
- Standard C++ exception raised when a memory allocation request fails.

### 5. Example C++ Design

```cpp
#include <exception>
#include <string>

class BillingError : public std::exception {
protected:
    std::string message;

public:
    explicit BillingError(const std::string& msg)
        : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class InvalidChargeError : public BillingError {
public:
    InvalidChargeError()
        : BillingError("Negative billing charge") {}
};

class ClaimError : public BillingError {
public:
    ClaimError()
        : BillingError("Claim exceeds available cover") {}
};

class UnknownPackageError : public BillingError {
public:
    UnknownPackageError()
        : BillingError("Unknown government package") {}
};

class PatientNotFoundError : public BillingError {
public:
    PatientNotFoundError()
        : BillingError("Patient record not found") {}
};
```

### 6. Conclusion

A structured exception hierarchy makes error handling easier and provides clear error messages. It allows different billing errors to be caught individually or through the common BillingError base class.
