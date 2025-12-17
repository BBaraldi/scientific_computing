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