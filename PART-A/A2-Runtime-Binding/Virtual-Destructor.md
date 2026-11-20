# A2.3 – Importance of Virtual Destructors

A virtual destructor is required in the base class when objects of derived classes may be deleted through base-class pointers.

### Why is a Virtual Destructor Required?

1. It ensures that the derived-class destructor is called first.
2. After that, the base-class destructor is called.
3. It prevents incomplete destruction of derived objects.
4. It helps release resources allocated by derived classes.
5. It avoids undefined behavior when deleting a derived object through a base-class pointer.

### Example

```cpp
class Bill {
public:
    virtual ~Bill() {
        cout << "~Bill ";
    }
};

class OutPatientBill : public Bill {
public:
    ~OutPatientBill() override {
        cout << "~OutPatientBill ";
    }
};
```

```cpp
Bill* b = new OutPatientBill();
delete b;
```

**Output:**

```text
~OutPatientBill ~Bill
```

### Conclusion

A virtual destructor ensures proper destruction of derived objects through base-class pointers and helps maintain resource safety in a polymorphic billing system.
