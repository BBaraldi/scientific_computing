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