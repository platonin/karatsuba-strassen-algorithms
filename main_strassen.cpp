#include <iostream>
#include <vector>
#include "strassen.h"

int main() {
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    cin >> n;

    matrix A(n, vector<long long>(n));
    matrix B(n, vector<long long>(n));

    // Ввод матрицы A
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }

    // Ввод матрицы B
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> B[i][j];
        }
    }

    // Умножение матриц
    matrix C = strassen(A, B);

    // Вывод результата
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}