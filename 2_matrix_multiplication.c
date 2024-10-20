#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "config.h"

int main(int argc, char* argv[]) {
    int sizes[] = MATRIX_SIZES; 
    int num_sizes = NUM_SIZES;

    int default_threads[] = DEFAULT_THREADS; 
    int num_threads = 0;
    int *threads;

    if (argc < 2) {
        threads = default_threads;
        num_threads = NUM_DEFAULT_THREADS;
    } else {
        num_threads = argc - 1;
        threads = (int *)malloc(num_threads * sizeof(int));
        for (int arg = 1; arg < argc; arg++) {
            threads[arg - 1] = atoi(argv[arg]);
        }
    }

    FILE *output = fopen(MATRIX_MULTIPLICATION_RESULTS_FILE, "w");
    if (output == NULL) {
        printf("Не вдалося відкрити файл для запису результатів.\n");
        return 1;
    }

    fprintf(output, "Розмір матриці");
    for (int t = 0; t < num_threads; t++) {
        fprintf(output, ",Час %d потоків (сек.)", threads[t]);
    }
    fprintf(output, ",Час послідовно (сек.)\n");

    int i, j, k;

    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];

        double **a = (double **)malloc(n * sizeof(double *));
        double **b = (double **)malloc(n * sizeof(double *));
        double **c = (double **)malloc(n * sizeof(double *));
        for (i = 0; i < n; i++) {
            a[i] = (double *)malloc(n * sizeof(double));
            b[i] = (double *)malloc(n * sizeof(double));
            c[i] = (double *)malloc(n * sizeof(double));
        }

        if (a == NULL || b == NULL || c == NULL) {
            printf("Не вдалося виділити пам'ять для матриць.\n");
            return 1;
        }

        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                a[i][j] = i + j; 
                b[i][j] = i - j; 
                c[i][j] = 0.0;  
            }
        }

        fprintf(output, "%d", n);

        for (int t = 0; t < num_threads; t++) {
            int current_threads = threads[t];
            double t_start, t_end;

            t_start = omp_get_wtime();

            #pragma omp parallel for shared(a, b, c) private(i, j, k) num_threads(current_threads)
            for (i = 0; i < n; i++) {
                for (j = 0; j < n; j++) {
                    c[i][j] = 0.0;
                    for (k = 0; k < n; k++) {
                        c[i][j] += a[i][k] * b[k][j];
                    }
                }
            }

            t_end = omp_get_wtime(); 
            double parallel_time = t_end - t_start;

            fprintf(output, ",%lf", parallel_time);
            printf("Розмір матриці: %d, Кількість потоків: %d, Час паралельно: %lf секунд\n", n, current_threads, parallel_time);
        }

        double t_start_seq = omp_get_wtime();

        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                c[i][j] = 0.0;
                for (k = 0; k < n; k++) {
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
        }

        double t_end_seq = omp_get_wtime();
        double sequential_time = t_end_seq - t_start_seq;

        fprintf(output, ",%lf\n", sequential_time);
        printf("Розмір матриці: %d, Час послідовно: %lf секунд\n", n, sequential_time);

        for (i = 0; i < n; i++) {
            free(a[i]);
            free(b[i]);
            free(c[i]);
        }
        free(a);
        free(b);
        free(c);
    }

    fclose(output);

    if (threads != default_threads) {
        free(threads);
    }

    printf("Програма завершила роботу. Результати записані у файл %s.\n", MATRIX_MULTIPLICATION_RESULTS_FILE);

    return 0;
}
