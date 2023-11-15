#include <iostream>
#include <chrono>

void FillRandom(double** matrix, int rowCount, int columnCount);

void MultiplySequential(double** a, int aRowCount, int aColumnCount,
    double** b, int bColumnCount, double** result);
