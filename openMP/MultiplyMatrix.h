#include <iostream>
#include <chrono>
#include <omp.h>

void FillRandom(double* matrix, int rowCount, int columnCount);

void MultiplyOpenMP(double* a, int aRowCount, int aColumnCount,
    double* b, int bColumnCount, int threadCount, double* result);
