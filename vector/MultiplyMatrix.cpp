#include "MultiplyMatrix.h"

//g++ -march=native -ftree-vectorize MultiplyMatrix.cpp -o MultiplyMatrix

void FillRandom(double* matrix, int rowCount, int columnCount)
{
    srand(time(0));

    for (int i = 0; i < rowCount * columnCount; i++)
    {
        matrix[i] = rand() % 100;
    }
}

void MultiplyVector(double* a, int aRowCount, int aColumnCount,
    double* b, int bColumnCount, double* result)
{
    for (int i = 0; i < aRowCount * bColumnCount; i++)
    {
        result[i] = 0;
    }

    for (int rowIndex = 0; rowIndex < aRowCount; rowIndex++)
    {
        for (int k = 0; k < aColumnCount; k++)
        {
            for (int columnIndex = 0; columnIndex < bColumnCount; columnIndex++)
            {
                result[rowIndex * bColumnCount + columnIndex] +=
                    a[rowIndex * aColumnCount + k] * b[k * bColumnCount + columnIndex];
            }
        }
    }
}

int main() {
    const int aRowCount = 500;
    const int aColumnCount = 500;
    const int bRowCount = 500;
    const int bColumnCount = 500;

    double* a = new double[aRowCount * aColumnCount];
    double* b = new double[bRowCount * bColumnCount];
    double* result = new double[aRowCount * bColumnCount];

    FillRandom(a, aRowCount, aColumnCount);
    FillRandom(b, bRowCount, bColumnCount);

    auto start = std::chrono::high_resolution_clock::now();
    MultiplyVector(a, aRowCount, aColumnCount, b, bColumnCount, result);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time taken by function: " << duration.count() << " milliseconds" << std::endl;

    delete[] a;
    delete[] b;
    delete[] result;

    return 0;
}