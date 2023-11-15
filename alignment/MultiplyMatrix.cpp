#include "MultiplyMatrix.h"

// g++ -march=native MultiplyMatrix.cpp -o MultiplyMatrix
// g++ -O2 -march=native MultiplyMatrix.cpp -o MultiplyMatrix

void FillRandom(double* matrix, int rowCount, int columnCount)
{
    srand(time(0));

    for (int i = 0; i < rowCount * columnCount; i++)
    {
        matrix[i] = rand() % 10;
    }
}

void PrintMatrix(double* matrix, int rowCount, int columnCount)
{
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < columnCount; j++)
        {
            std::cout << matrix[i * columnCount + j] << " ";
        }
        std::cout << std::endl;
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
    for (int columnIndex = 0; columnIndex < bColumnCount; columnIndex++)
    {
        for (int k = 0; k < aColumnCount; k++)
        {
            temp = b[k * bColumnCount + columnIndex];
            for (int rowIndex = 0; rowIndex < aRowCount; rowIndex++)
            {
                result[rowIndex * bColumnCount + columnIndex] +=
                    a[rowIndex * aColumnCount + k] * temp;
            }
        }
    }

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
    int aRowCount = 1500;
    int aColumnCount = 1500;
    int bColumnCount = 1500;

    int aColumnCountPrevious = aColumnCount;

    //double* a = new double[aRowCount * aColumnCount];
    //double* b = new double[aColumnCount * bColumnCount];

    /*if (aColumnCount % 8 != 0) {
        aColumnCount += 8 - (aColumnCount % 8);
    }*/

    double* a_aligned = (double*)_mm_malloc(aRowCount * aColumnCount * sizeof(double), 32);
    double* b_aligned = (double*)_mm_malloc(aColumnCount * bColumnCount * sizeof(double), 32);
    double* result_aligned = (double*)_mm_malloc(aRowCount * bColumnCount * sizeof(double), 32);

    FillRandom(a_aligned, aRowCount, aColumnCount);
    FillRandom(b_aligned, aColumnCount, bColumnCount);

    /*for (int i = 0; i < aRowCount; i++)
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
    }*/

    /*for (int i = 0; i < aRowCount * aColumnCount; i++)
    {
        cout << a_aligned[i] << " ";
    }

    cout << endl;

    for (int i = 0; i < aColumnCount * bColumnCount; i++)
    {
        cout << b_aligned[i] << " ";
    }

    cout << endl;*/

    auto start = std::chrono::high_resolution_clock::now();
    MultiplyAlignment(a_aligned, aRowCount, aColumnCount, b_aligned, bColumnCount, result_aligned);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time taken by function: " << duration.count() << " milliseconds" << std::endl;

    //PrintMatrix(result_aligned, aRowCount, bColumnCount);

    //delete[] a;
    //delete[] b;

    _mm_free(a_aligned);
    _mm_free(b_aligned);
    _mm_free(result_aligned);

    return 0;

    /*int aRowCount = 5;
    int aColumnCount = 5;
    int bColumnCount = 4;

    int aColumnCountPrevious = aColumnCount;

    double aData[5][5] = {{ 11, -15, 1, 5, -9},
                          { 8, -8, -7, 12, -9},
                          { 9, -6, 1, 9, -9},
                          { -14, 15, 7, -5, -9},
                          { 11, 23, 7, 5, -9} };

    double bData[5][4] = {{ 10, -17, 9, 5 },
                          { -7, 18, 4, -16 },
                          { 8, -6, 3, -13 },
                          { 11, 15, 2, 1 },
                          { -1, -23, 1, 5 }};

    if (aColumnCount % 8 != 0) {
        aColumnCount += 8 - (aColumnCount % 8);
    }

    double* a = (double*)_mm_malloc(aRowCount * aColumnCount * sizeof(double), 32);
    double* b = (double*)_mm_malloc(aColumnCount * bColumnCount * sizeof(double), 32);
    double* result = (double*)_mm_malloc(aRowCount * bColumnCount * sizeof(double), 32);

    for (int i = 0; i < aRowCount; i++)
    {
        for (int j = 0; j < aColumnCount; j++)
        {
            if (j < aColumnCountPrevious)
            {
                a[i * aColumnCount + j] = aData[i][j];
            }
            else
            {
                a[i * aColumnCount + j] = 0;
            }
        }
    }

    for (int i = 0; i < aColumnCount; i++)
    {
        for (int j = 0; j < bColumnCount; j++)
        {
            if (i < aColumnCountPrevious)
            {
                b[i * bColumnCount + j] = bData[i][j];
            }
            else
            {
                b[i * bColumnCount + j] = 0;
            }
        }
    }

    for (int i = 0; i < aRowCount * aColumnCount; i++)
    {
        cout << a[i] << " ";
    }

    cout << endl;

    for (int i = 0; i < aColumnCount * bColumnCount; i++)
    {
        cout << b[i] << " ";
    }

    auto start = std::chrono::high_resolution_clock::now();
    MultiplyAlignment(a, aRowCount, aColumnCount, b, bColumnCount, result);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time taken by function: " << duration.count() << " milliseconds" << std::endl;

    PrintMatrix(result, aRowCount, bColumnCount);

    _mm_free(a);
    _mm_free(b);
    _mm_free(result);

    return 0;*/
}


