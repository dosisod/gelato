# Gelato

Create user-defined attributes in C++.

## How

Gelato is a GCC plugin that allows for user defined attributes. When loaded, the Gelato plugin
will register attributes for you, allowing you to defined your own attributes.

## Why

One Python feature I love that C++ is lacking are decorators:

```python
def wrapper(f):
    def inner():
        print("pre call")
        f()
        print("post call")

    return inner

@wrapper
def f():
    print("hello from f")

f()
```

The above code prints the following when ran:

```
pre call
hello from f
post call
```

You can improve this code by using a context manager which yields control back
to the caller mid-execution:

```python
from contextlib import contextmanager

@contextmanager
def wrapper():
    print("pre call")
    yield
    print("post call")

@wrapper()
def f():
    print("hello from f")

f()
```

Having something like this in C++ is hard/impossible, especially if you want it to look nice.

The proposed syntax for these sorts of decorators in C++ are as follows:

```c++
#include <iostream>

void wrapper() {
  std::cout << "pre call\n";

  [[gnu::yield]];

  std::cout << "post call\n";
}

[[gnu::wrap(wrapper)]]
void f() {
  std::cout << "hello from f\n";
}
```

## Status

Gelato does not work (yet), but is under active development!
