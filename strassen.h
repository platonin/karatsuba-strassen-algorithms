#ifndef STRASSEN_H
#define STRASSEN_H
#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<long long>> matrix;

// Функция для сложения матриц
matrix add(const matrix &A, const matrix &B) {
    int n = A.size();
    matrix C(n, vector<long long>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

// Функция для вычитания матриц
matrix subtract(const matrix &A, const matrix &B) {
    int n = A.size();
    matrix C(n, vector<long long>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

// Обычное умножение матриц
matrix multiply(const matrix &A, const matrix &B) {
    int n = A.size();
    matrix C(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

// Алгоритм Штрассена
matrix strassen(const matrix &A, const matrix &B) {
    int n = A.size();
    
    // Базовый случай
    if (n <= 64) {
        return multiply(A, B);
    }

    int newSize = n / 2;
    matrix A11(newSize, vector<long long>(newSize));
    matrix A12(newSize, vector<long long>(newSize));
    matrix A21(newSize, vector<long long>(newSize));
    matrix A22(newSize, vector<long long>(newSize));
    
    matrix B11(newSize, vector<long long>(newSize));
    matrix B12(newSize, vector<long long>(newSize));
    matrix B21(newSize, vector<long long>(newSize));
    matrix B22(newSize, vector<long long>(newSize));
    
    // Разделение матриц A и B на 4 подматрицы
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];
            
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }
    
    // Вычисление промежуточных матриц
    matrix P1 = strassen(add(A11, A22), add(B11, B22));
    matrix P2 = strassen(add(A21, A22), B11);
    matrix P3 = strassen(A11, subtract(B12, B22));
    matrix P4 = strassen(A22, subtract(B21, B11));
    matrix P5 = strassen(add(A11, A12), B22);
    matrix P6 = strassen(subtract(A21, A11), add(B11, B12));
    matrix P7 = strassen(subtract(A12, A22), add(B21, B22));

    // Собираем итоговые подматрицы
    matrix C11 = add(subtract(add(P1, P4), P5), P7);
    matrix C12 = add(P3, P5);
    matrix C21 = add(P2, P4);
    matrix C22 = add(subtract(add(P1, P3), P2), P6);

    // Объединение подматриц в одну большую матрицу
    matrix C(n, vector<long long>(n));
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }

    return C;
}

#endif