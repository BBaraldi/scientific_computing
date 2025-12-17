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