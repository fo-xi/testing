#include <iostream>
#include <chrono>
#include <cstring>
#include <cstdlib>
#include <immintrin.h>

using namespace std;

void FillRandom(double* matrix, int rowCount, int columnCount);

void MultiplyAlignment(double* a, int aRowCount, int aColumnCount,
	double* b, int bColumnCount, double* result);
