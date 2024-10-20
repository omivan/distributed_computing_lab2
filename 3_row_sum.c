#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "config.h" 

int main(int argc, char* argv[]) {
    int sizes[] = MATRIX_SIZES; 
    int num_sizes = NUM_SIZES;

    int default_threads[] = {2, 4, 8, 16}; 
    int num_threads = 4; 
    int *threads = default_threads;

    FILE *output = fopen(ROW_SUM_RESULTS_FILE, "w");
    if (output == NULL) {
        printf("Не вдалося відкрити файл для запису результатів.\n");
        return 1;
    }

    fprintf(output, "Розмір матриці,Час 2 потоків (сек.),Час 4 потоків (сек.),Час 8 потоків (сек.),Час 16 потоків (сек.),Час послідовно (сек.)\n");

    int i, j;

    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];

        double **a = (double **)malloc(n * sizeof(double *));
        for (i = 0; i < n; i++) {
            a[i] = (double *)malloc(n * sizeof(double));
        }

        if (a == NULL) {
            printf("Не вдалося виділити пам'ять для матриці.\n");
            return 1;
        }

        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                a[i][j] = i + j;
            }
        }

        fprintf(output, "%d", n);

        for (int t = 0; t < num_threads; t++) {
            int num_threads = threads[t];
            double t1, t2;

            t1 = omp_get_wtime(); 

            #pragma omp parallel for shared(a) private(i, j) num_threads(num_threads)
            for (i = 0; i < n; i++) {
                double sum = 0.0;
                for (j = 0; j < n; j++) {
                    sum += a[i][j];
                }
            }

            t2 = omp_get_wtime();
            double parallel_time = t2 - t1;

            fprintf(output, ",%lf", parallel_time);
            printf("Розмір матриці: %d, Кількість потоків: %d, Час паралельно: %lf секунд\n", n, num_threads, parallel_time);
        }

        double t1 = omp_get_wtime(); 

        for (i = 0; i < n; i++) {
            double sum = 0.0;
            for (j = 0; j < n; j++) {
                sum += a[i][j];
            }
        }

        double t2 = omp_get_wtime(); 
        double sequential_time = t2 - t1;

        fprintf(output, ",%lf\n", sequential_time);
        printf("Розмір матриці: %d, Час послідовно: %lf секунд\n", n, sequential_time);

        for (i = 0; i < n; i++) {
            free(a[i]);
        }
        free(a);
    }

    fclose(output);

    printf("Програма завершила роботу. Результати записані у файл matrix_results.csv.\n");

    return 0;
}
