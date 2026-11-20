## A2.1 – Early and Late Binding

### 1. Early Binding (Compile-Time Binding)

Early binding is the process in which the function call is resolved by the compiler during compile time.

- It is also called static binding.
- It is commonly used with non-virtual functions.
- The function to be executed is determined using the declared type of the object or pointer.
- It generally has less function-dispatch overhead.

**Example:**

```cpp
class Bill {
public:
    double total() const {
        return 1000;
    }
};

Bill b;
Bill* ptr = &b;
cout << ptr->total();
```

The compiler resolves the call to `Bill::total()`.

### 2. Late Binding (Run-Time Binding)

Late binding is the process in which the function call is resolved during program execution.

- It is also called dynamic binding.
- It is achieved using virtual functions.
- The function to be executed is selected according to the actual object type.
- It supports runtime polymorphism.

**Example:**

```cpp
class Bill {
public:
    virtual double total() const = 0;
    virtual ~Bill() = default;
};

class OutPatientBill : public Bill {
public:
    double total() const override {
        return 1700;
    }
};

Bill* ptr = new OutPatientBill();
cout << ptr->total();
delete ptr;
```

Although `ptr` is a `Bill*`, the actual object is `OutPatientBill`. Therefore, `OutPatientBill::total()` is executed.

### 3. Comparison

| Early Binding | Late Binding |
|---|---|
| Resolved at compile time | Resolved at runtime |
| Static binding | Dynamic binding |
| Usually uses non-virtual functions | Uses virtual functions |
| Based on declared type | Based on actual object type |
| Does not provide runtime polymorphism | Supports runtime polymorphism |

### Conclusion

Late binding is useful in the hospital billing system because a single Bill pointer can refer to different bill objects and automatically execute the correct total() function.
