#include <stdio.h>

#define N 20  // Define vector size

int main() {
    double a = 3;
    double x[N], y[N], z[N];

    // Initialize x as ones and y as fours
    for (int i = 0; i < N; i++) {
        x[i] = 1.0;
        y[i] = 4.0;
    }

    // Compute z = a * x + y
    for (int i = 0; i < N; i++) {
        z[i] = a * x[i] + y[i];
    }

    // Save to file
    FILE *file = fopen("output_C.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    fprintf(file, "z = ");
    for (int i = 0; i < N; i++) {
        fprintf(file, "%.2f ", z[i]);
    }
    fprintf(file, "\n");
    fclose(file);

    printf("Computation complete. Results saved to output_C.txt\n");
    return 0;
}
