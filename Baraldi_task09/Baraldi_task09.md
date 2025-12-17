# Task 09

## C++ code

### serial_daxpy.cpp
```cpp
#include <iostream>
#include <vector>
#include <chrono>

int main() {
    const size_t N = 5'000'000;

    std::vector<double> x(N, 1.0);
    std::vector<double> y(N, 2.0);
    std::vector<double> d(N);

    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < N; ++i) {
        d[i] = x[i] + y[i];
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Serial time: " << elapsed.count() << " seconds\n";
    return 0;
}
```

### openmp_daxpy.cpp
```cpp
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
```

### mpi_daxpy.cpp
```cpp
#include <mpi.h>
#include <vector>
#include <iostream>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int N = 5'000'000;
    int local_N = N / size;

    std::vector<double> x_local(local_N);
    std::vector<double> y_local(local_N);
    std::vector<double> d_local(local_N);

    std::vector<double> x, y, d;

    if (rank == 0) {
        x.resize(N, 1.0);
        y.resize(N, 2.0);
        d.resize(N);
    }

    MPI_Scatter(x.data(), local_N, MPI_DOUBLE,
                x_local.data(), local_N, MPI_DOUBLE,
                0, MPI_COMM_WORLD);

    MPI_Scatter(y.data(), local_N, MPI_DOUBLE,
                y_local.data(), local_N, MPI_DOUBLE,
                0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);
    double start = MPI_Wtime();

    for (int i = 0; i < local_N; ++i) {
        d_local[i] = x_local[i] + y_local[i];
    }

    double end = MPI_Wtime();

    MPI_Gather(d_local.data(), local_N, MPI_DOUBLE,
               d.data(), local_N, MPI_DOUBLE,
               0, MPI_COMM_WORLD);

    if (rank == 0) {
        std::cout << "MPI time (" << size
                  << " processes): " << end - start << " seconds\n";
    }

    MPI_Finalize();
    return 0;
}
```

## Results
Compilation and execution:
* Serial
    ``` bash
    g++ -O3 serial_daxpy.cpp -o serial
    ./serial
    ```
* OpenMP
    ``` bash
    g++ -O3 -fopenmp openmp_daxpy.cpp -o openmp
    export OMP_NUM_THREADS=4
    ./openmp
    ```
* MPI
    ``` bash
    mpic++ -O3 mpi_daxpy.cpp -o mpi_daxpy
    mpirun -np 4 ./mpi_daxpy
    ```

Sample output:
``` bash
Serial time: 0.014512 seconds
OpenMP time: 0.004469 seconds
MPI time (4 processes): 0.00254 seconds
```
| Version | Threads / Processes | Time (s) | Speedup |
| ------- | ------------------- | -------- | ------- |
| Serial  | 1                   | 0.014512 | 1×      |
| OpenMP  | 4                   | 0.004469 | 3.25×   |
| MPI     | 4                   | 0.00254  | 5.71×   |

*Note: Actual times will vary depending on hardware, memory bandwidth, and system load.*

## Comments
- Serial vs OpenMP
    * OpenMP achieves a speedup of ~3.25× with 4 threads.
    * The loop in DAXPY is embarrassingly parallel, so threads can compute independently without synchronization overhead.
    * Speedup is slightly below ideal (4×) due to memory bandwidth limits and thread management overhead.
- Serial vs MPI
    * MPI achieves a speedup of ~5.7× with 4 processes.
    * On a single node, MPI can still outperform OpenMP in some cases because each process may have its own memory buffer reducing cache contention.
    * However, MPI generally has higher communication overhead, so its advantage is context-dependent.
- OpenMP vs MPI
    * OpenMP is usually preferable for shared-memory systems (single machine) due to simplicity and lower overhead.
    * MPI is more suitable for distributed-memory systems or clusters.
- General Observations
    * DAXPY is memory-bound, so the speedup is limited by how fast data can be read/written in memory.
    * The choice of parallelization strategy depends on hardware architecture:
      * Shared memory → OpenMP
      * Distributed memory → MPI

In conclusion, parallelization using either OpenMP or MPI significantly reduces execution time compared to serial implementation. On a single machine, OpenMP offers an efficient, low-overhead approach, while MPI demonstrates scalability potential for multi-node systems. Proper choice of parallelization technique is crucial to maximize performance for a given hardware setup.