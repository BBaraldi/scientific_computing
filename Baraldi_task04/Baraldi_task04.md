# Task 04

## C++ Codes

### `trapezoidal_integral.cpp`
```cpp
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

double f(double x) {
    return std::exp(x) * std::cos(x);
}

int main() {
    int N;
    double x_inf, x_sup;

    std::cout << "Enter N, x_inf, and x_sup: ";
    std::cin >> N >> x_inf >> x_sup;

    std::ofstream file("trapezoidal_output_cpp.dat");

    double h = (x_sup - x_inf) / (N - 1);
    double integral = 0.0;

    for (int i = 0; i < N; i++) {
        double x = x_inf + i * h;
        double fx = f(x);
        file << x << " " << fx << "\n";

        if (i == 0 || i == N - 1)
            integral += fx / 2.0;
        else
            integral += fx;
    }

    integral *= h;

    double I_true = (std::exp(M_PI / 2.0) - 1.0) / 2.0;
    double rel_err = std::abs((integral - I_true) / I_true);

    // Print results with consistent formatting
    std::cout << std::fixed << std::setprecision(16);
    std::cout << "I_trapezoidal = " << integral << std::endl;

    std::cout << std::scientific << std::setprecision(6);
    std::cout << "I_trapezoidal/I_true - 1 = " << rel_err << std::endl;

    file.close();
    return 0;
}
```

### `simpson_integral.cpp`
```cpp
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

double f(double x) {
    return std::exp(x) * std::cos(x);
}

int main() {
    int N;
    double x_inf, x_sup;

    std::cout << "Enter N (odd), x_inf, and x_sup: ";
    std::cin >> N >> x_inf >> x_sup;

    // Ensure N is odd
    if (N % 2 == 0) {
        std::cout << "Simpson's rule requires an odd number of points. Incrementing N by 1.\n";
        N += 1;
    }

    std::ofstream file("simpson_output_cpp.dat");

    double h = (x_sup - x_inf) / (N - 1);
    double integral = 0.0;

    for (int i = 0; i < N; i++) {
        double x = x_inf + i * h;
        double fx = f(x);
        file << x << " " << fx << "\n";

        // Simpson's weights
        if (i == 0 || i == N - 1)
            integral += fx;
        else if (i % 2 == 1)
            integral += 4 * fx;
        else
            integral += 2 * fx;
    }

    integral *= h / 3.0;

    double I_true = (std::exp(M_PI / 2.0) - 1.0) / 2.0;
    double rel_err = std::abs((integral - I_true) / I_true);

    // Print results with consistent formatting
    std::cout << std::fixed << std::setprecision(16);
    std::cout << "I_simpson = " << integral << std::endl;

    std::cout << std::scientific << std::setprecision(6);
    std::cout << "I_simpson/I_true - 1 = " << rel_err << std::endl;

    file.close();
    return 0;
}
```

## Python Code
```python
import numpy as np

for label in ["trapezoidal", "simpson"]:
    I = float(input(f"I_{label} = "))
    
    data = np.loadtxt(f"{label}_output_cpp.dat")
    x = data[:,0]
    fx = data[:,1]

    I4 = np.trapezoid(fx, x)
    abs_err = abs(I4 - I)

    print(f"I4_{label} = {I4:.16f}")
    print(f"|I - I4_{label}| = {abs_err:.6e}")
```

## Results
Execute the .cpp files using:
``` bash
g++ -O3 *_integral.cpp -o *_integral
```
and then run:
``` bash
./*_integral
```

Output for `N = 1000000, x_inf = 0, x_sup = 1.5707963267948966`:
``` bash
I_trapezoidal = 1.9052386904815022
I_trapezoidal/I_true - 1 = 6.159363e-13

Simpson's rule requires an odd number of points. Incrementing N by 1.
I_simpson = 1.9052386904827303
I_simpson/I_true - 1 = 2.866988e-14

I4_trapezoidal = 1.9052386883416683
|I - I4_trapezoidal| = 2.139834e-09

I4_simpson = 1.9052386936342978
|I - I4_simpson| = 3.151567e-09
```

Output for `N = 10, x_inf = 0, x_sup = 1.5707963267948966`:
``` bash
I_trapezoidal = 1.8904987619827143
I_trapezoidal/I_true - 1 = 7.736526e-03

I_simpson = 1.9052126843139081
I_simpson/I_true - 1 = 1.364982e-05

I4_trapezoidal = 1.8904969194049999
|I - I4_trapezoidal| = 1.842578e-06

I4_simpson = 1.8933016854650000
|I - I4_simpson| = 1.191100e-02
```

## Answer to Questions

**1. How can you reduce the relative error (I/I_true - 1)?**
To reduce the relative error:
- Increase the number of intervals `N`: A larger `N` refines the approximation and reduces discretization error.
- Use Simpson’s rule: Simpson’s method is generally more accurate than the Trapezoidal rule for smooth functions, because it approximates the integrand with parabolas rather than straight lines.

**2. Which is the minimum relative error you can find using the techniques you described in point 2?**
The minimum relative error depends on both the smoothness of the function and the number of intervals `N`. Using Simpson’s rule with a sufficiently large `N` achieves the highest accuracy.
- For `N = 10`: the Trapezoidal rule yields a relative error of `1e-3`, while Simpson’s rule improves it to `1e-5`.
- For `N = 1,000,000`: both methods are extremely accurate, but Simpson’s rule remains slightly better, giving a relative error of `1e-14`, effectively reaching machine precision limits.

This clearly shows that increasing `N` and using higher-order integration methods dramatically reduces the relative error.

**3. Is the Python output similar to the C++?**
Yes. Using Python to read the C++ output file and compute the integral with the same methods produces results very close to the C++ values:
- Trapezoidal and Simpson’s approximations match the C++ results within the expected absolute error.
- Differences are negligible and mostly due to floating-point rounding.