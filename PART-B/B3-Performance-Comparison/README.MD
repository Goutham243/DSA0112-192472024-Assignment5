# B3 – Performance Comparison

**Assignment:** Assignment 5 – CO5

## Programs

1. `virtual_billing.cpp` – Implements runtime polymorphism using virtual functions.
2. `switch_billing.cpp` – Implements billing using a type field and switch statement.
3. `exception_benchmark.cpp` – Compares exception handling with return codes.
4. `variant_billing.cpp` – Implements billing using std::variant and std::visit.

## Compilation

All programs are compiled using C++17 with optimization enabled.

```bash
g++ -std=c++17 -O2 -Wall -Wextra virtual_billing.cpp -o virtual_billing
g++ -std=c++17 -O2 -Wall -Wextra switch_billing.cpp -o switch_billing
g++ -std=c++17 -O2 -Wall -Wextra exception_benchmark.cpp -o exception_benchmark
g++ -std=c++17 -O2 -Wall -Wextra variant_billing.cpp -o variant_billing
```

## Experiments

- Compared virtual functions and switch statements using 10 identical bills.
- Measured execution time for 1,000, 1,000,000 and 10,000,000 bills.
- Compared exception handling and return codes for 0%, 1% and 50% invalid bills.
- Implemented std::variant and measured its execution time for 10 million bills.

## Complexity Analysis

**Virtual functions:** O(n) time for processing n bills.

**Switch statement:** O(n) time for processing n bills.

**Exception handling:** O(1) normal-path validation per bill; throwing and catching exceptions involves additional overhead.

**Return codes:** O(1) validation per bill with explicit error checking.

**std::variant:** O(n) time for processing n bills.

## Result

The four implementations were developed to compare correctness, execution time, memory usage and extensibility. Actual benchmark measurements are recorded in results.csv and used to evaluate the engineering trade-offs.
