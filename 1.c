#include <stdio.h>
#include <omp.h>

void task2(){
    double start_time, end_time, tick;
    start_time = omp_get_wtime();
    end_time = omp_get_wtime();
    tick = omp_get_wtick();
    printf("Час на вимірювання часу %lf\n", end_time-start_time);
    printf("Точність таймеру %lf\n", tick);
}

void task3(){
#pragma omp parallel
    {
        printf("Hello World !\n");
    }
}
int main(int argc, char *argv[])
{
    task2();
    printf("------------\n");
    task3();
}
