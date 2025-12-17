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
