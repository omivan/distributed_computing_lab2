// config.h - файл конфігурації для параметрів матричних обчислень

#ifndef CONFIG_H
#define CONFIG_H

// Розміри матриць, що використовуються у програмі
#define MATRIX_SIZES {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048}
#define NUM_SIZES 11

// Масив кількості потоків, що використовуються у програмі
#define DEFAULT_THREADS {2, 4, 8, 16}
#define NUM_DEFAULT_THREADS 4

// Ім'я файлу для збереження результатів
#define ROW_SUM_RESULTS_FILE "row_sum_results.csv"
#define MATRIX_SUM_RESULTS_FILE "matrix_sum_results.csv"
#define MATRIX_MULTIPLICATION_RESULTS_FILE "matrix_multiplication_results.csv"

#endif // CONFIG_H

