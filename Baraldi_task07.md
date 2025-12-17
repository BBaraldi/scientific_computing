# Task 07

## Python Code

### `my_daxpy.py`
```python
def daxpy(a, x, y):
    if len(x) != len(y):
        raise ValueError("x and y must be of the same length!")
    for i in range(len(x)):
        y[i] = a * x[i] + y[i]
    return y
```

### `test_daxpy.py`
```python
import pytest
from math import isclose
from my_daxpy import daxpy

def test_base_case():
    assert daxpy(2.0, [1, 2, 3], [4, 5, 6]) == [6.0, 9.0, 12.0]

def test_zero_scalar():
    assert daxpy(0.0, [1.5, -2.0], [10.0, 10.0]) == [10.0, 10.0]

def test_negative_scalar():
    out = daxpy(-1.0, [1.0, 2.0], [3.0, 4.0])
    expected = [2.0, 2.0]
    assert all(isclose(a, b, rel_tol = 1e-12, abs_tol = 1e-12) for a, b in zip(out, expected))

def test_empty_vectors():
    assert daxpy(1.23, [], []) == []

def test_length_mismatch():
    with pytest.raises(ValueError):
        daxpy(1.0, [1, 2, 3], [1, 2])

def test_floating_point_tolerance():
    out = daxpy(0.1, [0.1, 0.2, 0.3], [0.3, 0.2, 0.1])
    expected = [0.31, 0.22, 0.13]
    assert all(isclose(a, b, rel_tol = 1e-12, abs_tol = 1e-12) for a, b in zip(out, expected))

def test_large_numbers():
    x = [1e308, 1e308]
    y = [1e308, -1e308]
    out = daxpy(1.0, x, y)
    assert all(val == float("inf") or val == 0.0 for val in out)

def test_small_numbers():
    x = [1e-308, 1e-308]
    y = [0.0, 0.0]
    out = daxpy(1.0, x, y)
    assert all(isclose(val, 1e-308, rel_tol = 0, abs_tol = 1e-320) for val in out)
```

## Results
Execute the tests using:
``` bash
pytest test_daxpy.py -v
```
The -v (verbose) flag shows the status of each test individually.

Expected output:
``` bash
test_daxpy.py::test_base_case PASSED                                     
test_daxpy.py::test_zero_scalar PASSED                                   
test_daxpy.py::test_negative_scalar PASSED                               
test_daxpy.py::test_empty_vectors PASSED                                 
test_daxpy.py::test_length_mismatch PASSED                              
test_daxpy.py::test_floating_point_tolerance PASSED                     
test_daxpy.py::test_large_numbers PASSED                                
test_daxpy.py::test_small_numbers PASSED                                                          
```

## Comments
- my_daxpy.py contains the DAXPY function that modifies y in-place.
- test_daxpy.py contains 8 unit tests, covering:
  1. Base case
  2. Zero scalar
  3. Negative scalar
  4. Empty vectors
  5. Length mismatch (error)
  6. Floating-point precision
  7. Large numbers (overflow)
  8. Small numbers (underflow)
- Using pytest makes tests shorter, cleaner, and easier to maintain than unittest. Assertions are simpler, and manual print statements are unnecessary.