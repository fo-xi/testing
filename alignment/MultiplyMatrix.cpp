#include "MultiplyMatrix.h"

// g++ -march=native -ftree-vectorize MultiplyMatrix.cpp -o MultiplyMatrix
// g++ -O2 -march=native -ftree-vectorize MultiplyMatrix.cpp -o MultiplyMatrix

void FillRandom(double* matrix, int rowCount, int columnCount)
{
    srand(time(0));

    for (int i = 0; i < rowCount * columnCount; i++)
    {
        matrix[i] = rand() % 10;
    }
}

int alignSize(int size, int alignment)
{
    if (alignment % size == 0) 
    {
        return alignment;
    }
    else 
    {
        return ((size / alignment) + 1) * alignment;
    }
}

void MultiplyAlignment(double* a, int aRowCount, int aColumnCount,
    double* b, int bColumnCount, double* result)
{
    #pragma vector aligned
    for (int i = 0; i < aRowCount * bColumnCount; i++)
    {
        result[i] = 0;
    }

    double temp;

    #pragma vector aligned
    for (int rowIndex = 0; rowIndex < aRowCount; rowIndex++)
    {
        for (int k = 0; k < aColumnCount; k++)
        {
            temp = a[rowIndex * aColumnCount + k];
            for (int columnIndex = 0; columnIndex < bColumnCount; columnIndex++)
            {
                result[rowIndex * bColumnCount + columnIndex] +=
                    temp * b[k * bColumnCount + columnIndex];
            }
        }
    }
}

int main()
{
    int aRowCount = 10;
    int aColumnCount = 10;
    int bRowCount = 10;
    int bColumnCount = 10;

    int aColumnCountPrevious = aColumnCount;

    double* a = new double[aRowCount * aColumnCount];
    double* b = new double[bRowCount * bColumnCount];
    double* result = new double[aRowCount * bColumnCount];

    FillRandom(a, aRowCount, aColumnCount);
    FillRandom(b, bRowCount, bColumnCount);

    aColumnCount = alignSize(aColumnCount, 4);

    double* a_aligned = (double*)_mm_malloc(aRowCount * aColumnCount * sizeof(double), 32);
    double* b_aligned = (double*)_mm_malloc(aColumnCount * bColumnCount * sizeof(double), 32);
    double* result_aligned = (double*)_mm_malloc(aRowCount * bColumnCount * sizeof(double), 32);

    for (int i = 0; i < aRowCount; i++)
    {
        for (int j = 0; j < aColumnCount; j++)
        {
            if (j < aColumnCountPrevious)
            {
                a_aligned[i * aColumnCount + j] = a[i * aColumnCountPrevious + j];
            }
            else
            {
                a_aligned[i * aColumnCount + j] = 0;
            }
        }
    }

    for (int i = 0; i < aColumnCount; i++)
    {
        for (int j = 0; j < bColumnCount; j++)
        {
            if (i < aColumnCountPrevious)
            {
                b_aligned[i * bColumnCount + j] = b[i * bColumnCount + j];
            }
            else
            {
                b_aligned[i * bColumnCount + j] = 0;
            }
        }
    }

    auto start = std::chrono::high_resolution_clock::now();
    MultiplyAlignment(a_aligned, aRowCount, aColumnCount, b_aligned, bColumnCount, result_aligned);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time taken by function: " << duration.count() << " milliseconds" << std::endl;

    for (int i = 0; i < aRowCount; i++)
    {
        std::cout << "Address of row " << i << " in a: " << &a[i * aColumnCount] << std::endl;
    }

    for (int i = 0; i < bRowCount; i++)
    {
        std::cout << "Address of row " << i << " in b: " << &b[i * bColumnCount] << std::endl;
    }

    _mm_free(a_aligned);
    _mm_free(b_aligned);
    _mm_free(result_aligned);

    return 0;
}


