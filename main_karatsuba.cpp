#include <iostream>
#include <string>
#include "karatsuba.h"

int main() {
    std::string x;
    std::string y;

    std::cin >> x >> y;
    std::string ans = karatsuba(x, y);

    // Удаление нулей вначале числа
    int i = 0;
    while (ans[i] == '0') {
        i++;
    }
    if (i == ans.length()) {
        ans = "0";
    } else {
        ans = ans.substr(i);
    }

    std::cout << ans;

    return 0;
}