# A4.2 – Specify Exceptions (2 Marks)

## 1. Functions That May Throw Exceptions

The following functions may throw exceptions because they perform operations that can fail.

| Function | Possible Exception | Reason |
|---|---|---|
| calculateBill() | InvalidChargeError | Negative charges |
| processClaim() | ClaimError | Claim exceeds cover |
| getPackageRate() | UnknownPackageError | Unknown package |
| findPatient() | PatientNotFoundError | Missing patient record |
| allocateResources() | std::bad_alloc | Memory allocation failure |

These functions should not be marked `noexcept` because they may need to report errors to their callers.

## 2. Functions That Must Not Throw Exceptions

Some functions must not allow exceptions to escape.

| Function | Specification | Reason |
|---|---|---|
| Destructor | noexcept | Must safely destroy objects |
| cleanup() | noexcept | Releases resources |
| logStatus() | noexcept, if implemented safely | Prevents logging failures from escaping |
| what() | noexcept | Follows the std::exception interface |

### Example

```cpp
class Bill {
public:
    virtual ~Bill() noexcept = default;
};

void cleanup() noexcept {
    // Release resources safely
}
```

## 3. Why Should Destructors Not Throw?

1. Destructors are called automatically when objects are destroyed.
2. During exception handling, stack unwinding invokes destructors.
3. If a destructor throws another exception while an exception is already being processed, the program may terminate.
4. Therefore, destructors should not throw exceptions.
5. Resource cleanup must be performed safely.

## 4. Alternative Concept – Return Codes Instead of Exceptions

Instead of using exceptions, errors can be reported using an enum Status and an output error message.

### Example

```cpp
#include <string>

enum class Status {
    SUCCESS,
    INVALID_CHARGE,
    CLAIM_EXCEEDS_COVER,
    UNKNOWN_PACKAGE,
    PATIENT_NOT_FOUND
};

Status validateCharge(double charge, std::string& error) {
    if (charge < 0) {
        error = "Negative billing charge";
        return Status::INVALID_CHARGE;
    }

    error = "Success";
    return Status::SUCCESS;
}
```

### Comparison

| Factor | Exceptions | Return Codes |
|---|---|---|
| Normal path | Usually low overhead when no exception is thrown | Explicit status checking |
| Error path | Exception propagation and stack unwinding | Returns an error status |
| Time on normal path | Usually O(1) per check | O(1) per check |
| Extra space | Exception runtime storage when thrown | Status and error-message storage |
| Code structure | try, throw and catch | Check status after each call |
| Error propagation | Automatic propagation | Every caller must pass/check the result |

### Advantages of Return Codes

- Simple and explicit error reporting.
- Does not require exception handling syntax.
- Useful in systems where predictable control flow is important.

### Disadvantages of Return Codes

- Every function caller must check the returned status.
- Errors can be accidentally ignored.
- Error messages must be passed separately.
- Multiple error paths can make the code lengthy.

### Conclusion

Exceptions provide structured error propagation and separate normal logic from error handling. Return codes provide explicit control but require additional checks at every function call. For the hospital billing system, exceptions provide a clean way to handle different billing and claim errors.
