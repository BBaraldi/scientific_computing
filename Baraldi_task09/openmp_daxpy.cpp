#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

int main() {
    const size_t N = 5'000'000;

    std::vector<double> x(N, 1.0);
    std::vector<double> y(N, 2.0);
    std::vector<double> d(N);

    auto start = std::chrono::high_resolution_clock::now();

    #pragma omp parallel for
    for (size_t i = 0; i < N; ++i) {
        d[i] = x[i] + y[i];
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "OpenMP time: " << elapsed.count() << " seconds\n";
    return 0;
}