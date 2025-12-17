# Task 02 

## Python Code
```python
import numpy as np

# --------------------------------------------------
# Vector sum
# --------------------------------------------------
N = [10, 10**6, 10**8]  
a = 3 

for n in N:  
    x = np.full(n, 0.1)  
    y = np.full(n, 7.1)  
    z = a * x + y  

    print(f"Vector sum with {n} elements:")
    if np.allclose(z, 7.4):
        print(f"All elements of d are equal to 7.4.\n")
    else:
        print(f"Not all elements of d are equal to 7.4.\n")
    
# --------------------------------------------------
# Matrix multiplication
# --------------------------------------------------
N = [10, 10**2, 10**4]  

for n in N:
    A = np.full((n, n), 3, dtype = np.float32)
    B = np.full((n, n), 7.1, dtype = np.float32)
    C = A @ B / n

    print(f"Matrix multiplication with {n} × {n} matrices:")
    if np.allclose(C, 21.3):
        print(f"All elements of C are equal to 21.3.\n")
    else:
        print(f"Not all elements of C are equal to 21.3.\n")
```

## C++ Code
```cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

/* 
 Vector sum 
*/
void vectorSum() {
    std::vector<int> N = {10, 1000000, 100000000};
    double a = 3.0;

    for (int n : N) {
        std::vector<double> x(n, 0.1);
        std::vector<double> y(n, 7.1);
        std::vector<double> z(n);

        for (int i = 0; i < n; ++i) {
            z[i] = a * x[i] + y[i];
        }

        std::cout << "Vector sum with " << n << " elements:" << std::endl;
        if (std::all_of(z.begin(), z.end(), [](double val) { return std::fabs(val - 7.4) < 1e-6; })) {
            std::cout << "All elements of z are equal to 7.4.\n" << std::endl;
        } else {
            std::cout << "Not all elements of z are equal to 7.4.\n" << std::endl;
        }
    }
}

/* 
# Matrix multiplication
*/
void matrixMultiplication() {
    std::vector<int> N = {10, 100, 10000};

    for (int n : N) {
        std::vector<std::vector<float>> A(n, std::vector<float>(n, 3.0f));
        std::vector<std::vector<float>> B(n, std::vector<float>(n, 7.1f));
        std::vector<std::vector<float>> C(n, std::vector<float>(n, 0.0f));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) {
                    C[i][j] += A[i][k] * B[k][j];
                }
                C[i][j] /= n;
            }
        }

        std::cout << "Matrix multiplication with " << n << " × " << n << " matrices:" << std::endl;
        bool allEqual = true;
        for (int i = 0; i < n && allEqual; ++i) {
            for (int j = 0; j < n && allEqual; ++j) {
                if (std::fabs(C[i][j] - 21.3f) > 1e-3) {
                    allEqual = false;
                }
            }
        }

        if (allEqual) {
            std::cout << "All elements of C are equal to 21.3.\n" << std::endl;
        } else {
            std::cout << "Not all elements of C are equal to 21.3.\n" << std::endl;
        }
    }
}

int main() {
    vectorSum();
    matrixMultiplication();
    return 0;
}
```

## Answer to Questions

**1. Did you find any problems in running the codes for some N? If so, do you have an idea why?**
   - **Python:** Everything ran smoothly except for the multiplication of \(10^4 \times 10^4\) matrices. This operation was `Killed` due to excessive memory usage. Storing such matrices requires around 2.5 GB of memory, and if the system runs out of memory, the process is terminated. One solution is to use `np.float32` instead of `np.float64`, which reduces memory usage to about 1.2 GB for \(10^4 \times 10^4\) matrices and allows the program to handle larger N values more efficiently.
   - **C++:** A similar issue occurred in C++ when multiplying \(10^4 \times 10^4\) matrices. However, in this case, the problem was performance-related rather than memory-related: the computation time became impractically long. As N increases, matrix multiplication slows significantly due to its \(O(N^3)\) complexity. While more efficient algorithms could reduce computation time, they were not implemented in this code.

**2. Where you able to test correctly the sum of vectors and product of matrices? If so, how? If not, what was the problem?**
   - **Python:** Initially, I compared the results using `X == a`, but this returned an array of `False` values, even though the elements appeared equal. This was due to floating-point precision errors, where tiny numerical differences made direct comparisons fail. To address this, I used `np.allclose(X, a)`, which checks equality within a small tolerance, ensuring correct verification despite minor floating-point inaccuracies.
   - **C++:** I verified the results by checking that the difference between each element of `X` and `a` was less than \(10^{-3}\). This approach worked well for small N, but for large N matrix multiplication became impractical due to high memory usage and long computation times, making verification either very slow or impossible.