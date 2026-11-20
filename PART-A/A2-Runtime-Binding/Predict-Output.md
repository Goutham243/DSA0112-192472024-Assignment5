# A2 – Predict the Output

## Given Program

```cpp
#include <iostream>
struct Bill {
    virtual ~Bill() { std::cout << "~Bill "; }
    virtual double total() const = 0;
    void show() const { std::cout << total() << ' '; }
};

struct OPBill : Bill {
    ~OPBill() override { std::cout << "~OPBill "; }
    double total() const override { return 500; }
};

int main()
{
    Bill* b = new OPBill;
    b->show();
    delete b;
    std::cout << '\n';
}
```

## 1. My Predicted Output

```text
500 ~OPBill ~Bill
```

## 2. Explanation

1. `new OPBill` creates an Outpatient Bill object dynamically.
2. The base-class pointer `b` stores the address of the derived object.
3. `b->show()` calls the non-virtual show() function.
4. Inside show(), the virtual total() function is called.
5. Runtime binding executes `OPBill::total()`, which returns 500.
6. `delete b` deletes the object through a base-class pointer.
7. Since the base destructor is virtual, the derived destructor executes first.
8. Finally, the base-class destructor executes.

Therefore, the output is:

```text
500 ~OPBill ~Bill
```

## 3. Why Did the Non-Virtual show() Reach OPBill::total()?

The show() function is non-virtual, so its implementation is selected through the base-class interface.

However, show() internally calls total(), which is virtual. Therefore, runtime binding selects the overridden function based on the actual object type.

Hence, OPBill::total() is executed.

## 4. Remove virtual from the Base Destructor

If virtual is removed from the Bill destructor, deleting an OPBill object through a Bill pointer causes undefined behavior.

The derived destructor is not guaranteed to execute. The program may appear to print only:

```text
500 ~Bill
```

However, this output is not guaranteed because the behavior is undefined.

When compiled with AddressSanitizer, the program may report a deletion-size mismatch or another diagnostic, depending on the compiler and platform.

## 5. Result

Virtual functions provide runtime binding, while a virtual destructor ensures proper destruction of derived objects through base-class pointers.
