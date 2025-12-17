# Task 06

## Python Code
```python
import numpy as np

np.random.seed(0)  # reproducibility
N = 1000
A = np.random.normal(loc = 1.0, scale = 1.0, size = (N, N))

def kahan_sum(values):
    tot = 0.0
    c = 0.0  # Compensation for lost low-order bits
    for v in values:
        y = v - c
        t = tot + y
        c = (t - tot) - y
        tot = t
    return tot

def error_metrics(A, A_ifft):
    abs_err = np.abs(A - A_ifft)
    rel_err = abs_err / np.abs(A)

    mean_abs = np.sqrt(np.mean(abs_err**2))
    median_abs = np.sqrt(np.median(abs_err**2))

    mean_rel = np.sqrt(np.mean(rel_err**2))
    median_rel = np.sqrt(np.median(rel_err**2))

    return mean_abs, median_abs, mean_rel, median_rel

def print_error_metrics(errors):
    mean_abs, median_abs, mean_rel, median_rel = errors
    print(f"Mean abs err   : {mean_abs:.6e}")
    print(f"Median abs err : {median_abs:.6e}")
    print(f"Mean rel err   : {mean_rel:.6e}")
    print(f"Median rel err : {median_rel:.6e}")

# --------------------------------------------------
# Complex-to-complex FFT
# --------------------------------------------------
C = np.fft.fft2(A)
A_c2c = np.fft.ifft2(C).real
c2c_errors = error_metrics(A, A_c2c)

# Print results
print("---------- c2c FFT ----------")
print_error_metrics(c2c_errors)

# --------------------------------------------------
# Real-to-complex FFT
# --------------------------------------------------
R = np.fft.rfft2(A)
A_r2c = np.fft.irfft2(R, s = A.shape)
r2c_errors = error_metrics(A, A_r2c)

# Print results
print("\n---------- r2c FFT ----------")
print_error_metrics(r2c_errors)

# --------------------------------------------------
# DC component
# --------------------------------------------------
C00 = C[0, 0].real
R00 = R[0, 0].real
sum_direct = np.sum(A)
sum_kahan = kahan_sum(A)

# Print results
print("\n--------- DC components ---------")
print("C[0,0]       :", C00)
print("R[0,0]       :", R00)
print("Built-in sum :", np.sum(A))
print("Kahan sum    :", kahan_sum(A.flatten()))
```

## Results
``` bash
---------- c2c FFT ----------
Mean abs err   : 5.386648e-16
Median abs err : 4.440892e-16
Mean rel err   : 1.661308e-13
Median rel err : 3.595450e-16

---------- r2c FFT ----------
Mean abs err   : 6.265115e-16
Median abs err : 4.440892e-16
Mean rel err   : 2.126541e-13
Median rel err : 4.065785e-16

--------- DC components ---------
C[0,0]       : 1001512.1465155362
R[0,0]       : 1001512.1465155362
Built-in sum : 1001512.1465155364
Kahan sum    : 1001512.1465155362
```

## Answer to Questions

**1. Are you reaching machine precision with c2c and r2c FFT? If not, try to comment on why.**
Both the complex-to-complex (c2c) and real-to-complex (r2c) FFTs followed by their inverse transforms reach the limits of numerical precision. The tiny discrepancies (~1e-16) are due entirely to floating-point arithmetic, not the FFT algorithm.
- **c2c FFT:** Mean and median absolute errors are on the order of 1e-16, essentially machine epsilon for double-precision, showing that fft2 and ifft2 reconstruct the original matrix with negligible numerical noise.
- **r2c FFT:** Errors are slightly larger but still near machine precision. The small difference arises because rfft2 stores only half the spectrum (Hermitian symmetry for real inputs), introducing minor rounding effects in the inverse transform.

In conclusion, both FFT types perform as expected, with reconstruction errors limited only by floating-point precision.

**2.What is the value of `C[0,0]` or `R[0,0]`? Can you guess its meaning?**
The elements `C[0,0]` and `R[0,0]` represent the zero-frequency (DC) component of the Fourier transform, which captures the constant, non-oscillatory part of the matrix. Numerically, this is equal to the sum of all elements in A, which can be computed directly or using the Kahan summation algorithm to reduce floating-point errors. Kahan summation illustrates the subtle effects of rounding, yet the FFT’s DC component matches it exactly, demonstrating that the FFT preserves the total sum with very high precision.

