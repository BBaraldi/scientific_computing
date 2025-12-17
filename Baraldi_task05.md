# Task 05

## Python Code
```python
import numpy as np

def kahan_sum(values):
    tot = 0.0
    c = 0.0  # Compensation for lost low-order bits
    for v in values:
        y = v - c
        t = tot + y
        c = (t - tot) - y
        tot = t
    return tot

# --------------------------------------------------
# Part (a)
# --------------------------------------------------
vec = [1.0, 1.0e16, -1.0e16, -0.5]

# Sum using a for loop
s_loop = 0.0
for v in vec:
    s_loop += v

# Sum using built-in summation
s_builtin = sum(vec)

# Sum using Kahan summation algorithm
s_kahan = kahan_sum(vec)

# Print results
print("-------------- PART (a) --------------")
print("Summations:")
print(f"   - Expected : +{0.5}")
print(f"   - For loop : {s_loop}")
print(f"   - Built-in : {s_builtin}")
print(f"   - Kahan    : {s_kahan}")

# --------------------------------------------------
# Part (b)
# --------------------------------------------------
# Daxpy algorithm
a = 1.0
n = 1_000_000
x = np.random.normal(0.0, 1.0, n)
y = np.random.normal(0.0, 1.0, n)
d = a * x + y

# Test Daxpy algorithm
mean_builtin  = sum(d) / n
devs2_builtin = [(x - mean_builtin)**2 for x in d]
var_builtin   = sum(devs2_builtin) / n  

mean_kahan    = kahan_sum(d) / n
devs2_kahan   = [(x - mean_kahan)**2 for x in d]
var_kahan     = kahan_sum(devs2_kahan) / n

# Print results
print("\n-------------- PART (b) --------------")
print("Mean of d:")
print(f"   - Expected : {0.0}")
print(f"   - Built-in : {mean_builtin}")
print(f"   - Kahan    : {mean_kahan}")
print("Variance of d:")
print(f"   - Expected : {(a**2 + 1)}")
print(f"   - Built-in : {var_builtin}")
print(f"   - Kahan    : {var_kahan}")
```

## Results
``` bash
-------------- PART (a) --------------
Summations:
   - Expected : +0.5
   - For loop : -0.5
   - Built-in : -0.5
   - Kahan    : -0.5

-------------- PART (b) --------------
Mean of d:
   - Expected : 0.0
   - Built-in : 0.0007726097127937223
   - Kahan    : 0.0007726097127937107
Variance of d:
   - Expected : 2.0
   - Built-in : 2.00065836607698
   - Kahan    : 2.000658366076997
```

## Answer to Questions

**a) Are the three summation results the same? If not, can you guess why?**
In this example, all three methods return −0.5, but the mathematically correct sum of `vec` should be +0.5. This discrepancy arises from floating-point round-off errors. When adding numbers of very different magnitudes, the smaller numbers can be "lost" because floating-point arithmetic cannot represent them accurately after large numbers have been added. 
Here, \(10^{16} + (-10^{16})\) cancels to 0 in floating-point arithmetic. The smaller value 1.0 is then lost, and subtracting 0.5 gives −0.5 instead of the correct 0.5. This affects all three methods:    
- The for-loop and built-in sums perform naive addition and are directly affected by this cancellation.
- The Kahan summation algorithm compensates for lost low-order bits, but with this particular order of summation, the very large numbers are processed first, still overwhelming the small 1.0 and resulting in −0.5.

This example illustrates that summation order and numerical stability are critical when adding numbers of widely varying magnitudes. By simply reordering `vec` to add the larger numbers first followed by the small ones (e.g., `[1.0e16, -1.0e16, 1.0, -0.5]`), all three methods return the expected result, +0.5.

**b) How can you test that d, the sum of x and y, is correct?**
Since the elements of `x` and `y` are random, validation of the DAXPY algorithm is best performed through statistical testing rather than element-wise comparison. Therefore, to test that `d` is correct, one can:  
1. Compute the sample mean of `d` and check it is close to the expected mean.  
2. Compute the sample variance of `d` and check it is close to the expected variance.  
3. Optionally, compare results using built-in summation and the Kahan summation algorithm to detect numerical errors.  

Given that `x` and `y` are independent Gaussian variables with mean 0 and variance 1:  
- The expected mean of `d` is \(\mathbb{E}[d] = a\,\mathbb{E}[x] + \mathbb{E}[y] = 0\).  
- The expected variance of `d` is \(\mathrm{Var}(d) = a^2\,\mathrm{Var}(x) + \mathrm{Var}(y) = a^2 + 1\).  

If the observed mean and variance match the theoretical values within expected statistical fluctuations, this provides strong evidence that the DAXPY implementation is correct.
