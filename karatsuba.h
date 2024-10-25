#ifndef KARATSUBA_H
#define KARATSUBA_H

#include <vector>
#include <algorithm>
#include <string>

// Функция для чисел в столбик
std::string multiply_large_numbers(const std::string& x, const std::string& y);

// Функция для умножения двух чисел, представленных в виде строк
std::string karatsuba(const std::string& x, const std::string& y);

// Функция для сложения двух больших чисел, представленных строками
std::string add(const std::string& a, const std::string& b);

// Функция для вычитания одного большого числа из другого (строк)
std::string subtract(const std::string& a, const std::string& b);

// Умножение числа на 10^n (добавление нулей в конце)
std::string shift(const std::string& num, int n);

// Функция Карацубы
std::string karatsuba(const std::string& x, const std::string& y) {
    int n = std::max(x.size(), y.size());
    if (n % 2 != 0) n++;

    if (n <= 32) {
        return multiply_large_numbers(x, y);
    }

    // Выровняем длины чисел
    std::string x_pad = std::string(n - x.size(), '0') + x;
    std::string y_pad = std::string(n - y.size(), '0') + y;
    int half = n / 2;

    std::string x1 = x_pad.substr(0, half);
    std::string x0 = x_pad.substr(half);
    std::string y1 = y_pad.substr(0, half);
    std::string y0 = y_pad.substr(half);

    std::string z0 = karatsuba(x0, y0);
    std::string z2 = karatsuba(x1, y1);
    std::string z1 = karatsuba(add(x0, x1), add(y0, y1));

    std::string result = add(shift(z2, 2 * half), shift(subtract(subtract(z1, z2), z0), half));
    result = add(result, z0);

    return result;
}

std::string multiply_large_numbers(const std::string& x, const std::string& y) {
    int n = x.size();
    int m = y.size();
    
    // Вектор для хранения результата (максимальная длина результата — n + m)
    std::vector<int> result(n + m, 0);

    // Умножаем числа в столбик
    for (int i = n - 1; i >= 0; --i) {
        for (int j = m - 1; j >= 0; --j) {
            int product = (x[i] - '0') * (y[j] - '0');
            int sum = product + result[i + j + 1];
            
            result[i + j + 1] = sum % 10;
            result[i + j] += sum / 10;
        }
    }

    // Преобразуем вектор результата в строку, убирая ведущие нули
    std::string result_str;
    bool leading_zero = true;
    for (int digit : result) {
        if (digit == 0 && leading_zero) {
            continue;
        }
        leading_zero = false;
        result_str.push_back(digit + '0');
    }

    return result_str.empty() ? "0" : result_str;
}

// Функция для сложения двух строк, представляющих числа
std::string add(const std::string& a, const std::string& b) {
    std::string result;
    int carry = 0;
    int a_len = a.size(), b_len = b.size();
    int max_len = std::max(a_len, b_len);

    for (int i = 0; i < max_len; ++i) {
        int digit_a = i < a_len ? a[a_len - 1 - i] - '0' : 0;
        int digit_b = i < b_len ? b[b_len - 1 - i] - '0' : 0;
        int sum = digit_a + digit_b + carry;
        carry = sum / 10;
        result.push_back((sum % 10) + '0');
    }

    if (carry) result.push_back(carry + '0');
    std::reverse(result.begin(), result.end());
    return result;
}

std::string subtract(const std::string& a, const std::string& b) {
    std::string result;
    int borrow = 0;
    int a_len = a.size(), b_len = b.size();

    for (int i = 0; i < a_len; ++i) {
        int digit_a = a[a_len - 1 - i] - '0';
        int digit_b = i < b_len ? b[b_len - 1 - i] - '0' : 0;
        int sub = digit_a - digit_b - borrow;
        if (sub < 0) {
            sub += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.push_back(sub + '0');
    }

    while (result.size() > 1 && result.back() == '0') {
        result.pop_back();
    }

    std::reverse(result.begin(), result.end());
    return result;
}

std::string shift(const std::string& num, int n) {
    return num + std::string(n, '0');
}

#endif 