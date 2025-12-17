# Task 08

## Python Code
```python
import numpy as np

a = 1.0
n = 1_000_000
x = np.random.rand(n)
y = np.random.rand(n)

# --------------------------------------------------
# Original DAXPY
# --------------------------------------------------
d_original = np.zeros(n)

for i in range(n):
    d_original[i] = a * x[i] + y[i]

original_sum = np.sum(d_original)

# --------------------------------------------------
# Chunked DAXPY
# --------------------------------------------------
chunk_size = 8
number_of_chunks = int(np.ceil(n / chunk_size))

d_chunked = np.zeros(n)
partial_chunk_sum = np.zeros(number_of_chunks)

for chunk_index in range(number_of_chunks):
    current_start = chunk_index * chunk_size
    current_end = min(current_start + chunk_size, n)

    for i in range(current_start, current_end):
        d_chunked[i] = a * x[i] + y[i]
        partial_chunk_sum[chunk_index] += d_chunked[i]

chunked_sum = np.sum(partial_chunk_sum)

# --------------------------------------------------
# Original vs chunked DAXPY
# --------------------------------------------------
arrays_equal = np.allclose(d_original, d_chunked)
sums_equal = np.isclose(original_sum, chunked_sum)
    
if arrays_equal:
    print("DAXPY implementations output identical vectors d"
          " (within floating-point tolerance).")
else:
    max_diff = np.max(np.abs(d_original - d_chunked))
    print("DAXPY implementations output different vectors d,"
          f" with maximum absolute difference of {max_diff}.")

if sums_equal:
    print("DAXPY implementations output identical sums of vector d"
          " (within floating-point tolerance).")
else:
    diff = abs(original_sum - chunked_sum)
    print("DAXPY implementations output different sums of vector d,"
          f" with absolute difference of {diff}.")
```

## Results
``` bash
DAXPY implementations output identical vectors d (within floating-point tolerance).
DAXPY implementations output identical sums of vector d (within floating-point tolerance).
```