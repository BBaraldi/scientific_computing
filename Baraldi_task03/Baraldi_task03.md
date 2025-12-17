# Task 03

## Python code (except point 3)

### Create and save x, y vectors
```python
import numpy as np
import h5py
import os

# Ask user for N, prefix, and HDF5 choice
N = int(input("N = "))
prefix = str(input("/path/to/my/outputdir/ = "))
h5 = input("H5 version (True/False) = ").strip().lower() == "true"

# Create output directory if it does not exist
os.makedirs(prefix, exist_ok = True)

# Create vectors
x = np.full(N, 0.1)
y = np.full(N, 7.1)

# Save vectors
if not h5:
    np.savetxt(f"{prefix}vector_N{N}_x.dat", x)
    np.savetxt(f"{prefix}vector_N{N}_y.dat", y)
    print(f"Saved {prefix}vector_N{N}_x.dat and y.dat")
else:
    with h5py.File(f"{prefix}vectors_N{N}.h5", "w") as f:
        f.create_dataset("x", data = x)
        f.create_dataset("y", data = y)
    print(f"Saved {prefix}vectors_N{N}.h5 with datasets x, y")
```

### `config_file.py`
```python
N = 10
a = 3.0
prefix = "./"  # Change to your preference

# Input/output filenames
x_file = f"{prefix}vector_N{N}_x.dat"
y_file = f"{prefix}vector_N{N}_y.dat"
output_file = f"{prefix}vector_N{N}_d.dat"
```

### DAXPY
```python
import numpy as np
import h5py
from config_file import*

# HDF5 and GSL-style choice
h5 = input("H5 version (True/False) = ").strip().lower() == "true"
GSL = input("GSL version (True/False) = ").strip().lower() == "true"

if not h5:
    # Load text files
    x = np.loadtxt(x_file)
    y = np.loadtxt(y_file)
    
    if not GSL:
        # Explicit loop
        d = np.empty(len(x))
        for i in range(len(x)):
            d[i] = a * x[i] + y[i]
    else:
        # Vectorized GSL-style
        d = np.empty_like(x)
        np.multiply(x, a, out = d)
        np.add(d, y, out = d)
    
    # Save result
    np.savetxt(output_file, d)
    print(f"DAXPY result saved to {output_file}")

else:
    # Load HDF5
    h5_file = f"{prefix}vectors_N{N}.h5"
    with h5py.File(h5_file, "r+") as f:
        x = f["x"][:]
        y = f["y"][:]
        
        if not GSL:
            # Explicit loop
            d = np.empty(len(x))
            for i in range(len(x)):
                d[i] = a * x[i] + y[i]
        else:
            # Vectorized GSL-style
            d = np.empty_like(x)
            np.multiply(x, a, out = d)
            np.add(d, y, out = d)
        
        # Save result to HDF5
        if "d" in f:
            del f["d"]  # overwrite if exists
        f.create_dataset("d", data = d)

    print(f"DAXPY result saved in {h5_file} dataset 'd'")
```

## Python code (point 3)

### `generate_vectors.py`
```python
import numpy as np
import os

# Parameters
N = 10
prefix = "./makefile_output/"

if __name__ == "__main__":
    # Ensure output directory exists
    os.makedirs(prefix, exist_ok = True)
    
    # Create vectors
    x = np.full(N, 0.1)
    y = np.full(N, 7.1)
    
    # Save to text files
    x_filename = f"{prefix}vector_N{N}_x.dat"
    y_filename = f"{prefix}vector_N{N}_y.dat"
    
    np.savetxt(x_filename, x)
    np.savetxt(y_filename, y)
    
    print(f"Vector x saved to {x_filename}")
    print(f"Vector y saved to {y_filename}")
```

### `config_file.py`
```python
from generate_vectors import prefix

N = 10
a = 3

# Input/output filenames
x_file = f"{prefix}vector_N{N}_x.dat"
y_file = f"{prefix}vector_N{N}_y.dat"
output_file = f"{prefix}vector_N{N}_d.dat"
```

### `daxpy_from_config.py`
```python
import numpy as np
from config_file import *

# Load vectors
x = np.loadtxt(x_file)
y = np.loadtxt(y_file)

# Perform DAXPY
N = len(x)
d = np.empty(N)
for i in range(N):
    d[i] = a * x[i] + y[i]

# Save result
np.savetxt(output_file, d)
print(f"DAXPY result saved to {output_file}")
```

### `Makefile`
```makefile
.PHONY: all generate daxpy clean

all: generate daxpy

generate:
	python generate_vectors.py

daxpy:
	python daxpy_from_config.py

clean:
	rm -f output/*.dat
```

By running:

```bash
make
```
the following output is produced:
``` bash
python generate_vectors.py
Vector x saved to ./makefile_output/vector_N10_x.dat
Vector y saved to ./makefile_output/vector_N10_y.dat
python daxpy_from_config.py
DAXPY result saved to ./makefile_output/vector_N10_d.dat
```
This shows that:
- The vectors `x` and `y` have been generated and saved successfully.
- The DAXPY operation has been performed, producing the output vector `d`.