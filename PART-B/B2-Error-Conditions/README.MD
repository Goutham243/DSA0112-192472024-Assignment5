# B2 – Engineer Error Conditions

**Assignment:** Assignment 5 – CO5  
**Topic:** Reliable Software with Runtime Polymorphism and Exceptions

## Programs

1. `error_testing.cpp` – Tests negative charges, invalid claims, unknown packages, invalid input and memory allocation failure.
2. `claim_error.cpp` – Demonstrates custom exceptions, throwing, catching and rethrowing.
3. `predict_output.cpp` – Demonstrates exception propagation and rethrowing.

## Compilation Commands

```bash
g++ -std=c++17 -Wall -Wextra error_testing.cpp -o error_testing
g++ -std=c++17 -Wall -Wextra claim_error.cpp -o claim_error
g++ -std=c++17 -Wall -Wextra predict_output.cpp -o predict_output
```

## Concepts Used

- Exception handling
- try, catch and throw
- Custom exception classes
- std::invalid_argument
- std::out_of_range
- std::bad_alloc
- Stack unwinding
- Resource management using destructors

## Result

Successfully implemented and tested different error conditions in the hospital billing system. Exception handling ensures errors are reported and the program continues safely.
