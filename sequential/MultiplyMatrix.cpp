#include "MultiplyMatrix.h"

void FillRandom(double** matrix, int rowCount, int columnCount)
{
    srand(time(0));

    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < columnCount; j++)
        {
            matrix[i][j] = rand() % 10;
        }
    }
}

void MultiplySequential(double** a, int aRowCount, int aColumnCount,
    double** b, int bColumnCount, double** result)
{
    for (int rowIndex = 0; rowIndex < aRowCount; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < bColumnCount; columnIndex++)
        {
            result[rowIndex][columnIndex] = 0;
            for (int k = 0; k < aColumnCount; k++)
            {
                result[rowIndex][columnIndex] += a[rowIndex][k] * b[k][columnIndex];
            }
        }
    }
}

int main() {
    const int aRowCount = 1500;
    const int aColumnCount = 1500;
    const int bRowCount = 1500;
    const int bColumnCount = 1500;

    double** a = new double* [aRowCount];
    for (int i = 0; i < aRowCount; i++)
    {
        a[i] = new double[aColumnCount];
    }

    double** b = new double* [bRowCount];
    for (int i = 0; i < bRowCount; i++)
    {
        b[i] = new double[bColumnCount];
    }

    double** result = new double* [aRowCount];
    for (int i = 0; i < aRowCount; i++)
    {
        result[i] = new double[bColumnCount];
    }

    FillRandom(a, aRowCount, aColumnCount);
    FillRandom(b, bRowCount, bColumnCount);

    auto start = std::chrono::high_resolution_clock::now();
    MultiplySequential(a, aRowCount, aColumnCount, b, bColumnCount, result);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time taken by function: " << duration.count() << " milliseconds" << std::endl;

    for (int i = 0; i < aRowCount; ++i) {
        delete[] a[i];
        delete[] b[i];
        delete[] result[i];
    }

    delete[] a;
    delete[] b;
    delete[] result;

    return 0;
}