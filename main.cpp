#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include "HugeInteger.hpp"
int main() {
    HugeInteger a1("20"), a2("15");
    std::cout << a1 * a2 << std::endl;
    HugeInteger a, b;
    HugeInteger d("123"), e(1ULL << 63);
    std::cin >> a >> b;
    int c;
    std::cin >> c;
    std::cout << std::boolalpha << (a * c == c * b) << std::endl;
    std::cout << (a + 4 < b) << std::endl;
    std::cout << (a <= b) << std::endl;
    std::cout << (a != b * c) << std::endl;
    std::cout << (a >= b - 10) << std::endl;
    std::cout << (a == -b) << std::endl;
    std::cout << (a > b - 10) << std::endl;
    std::cout << (d + c) * e << std::endl;
    try {
        a += b;
        b = a - b;
        a -= b;
        std::cout << a + b << std::endl;
        std::cout << a - b << std::endl;
        std::cout << a * b << std::endl;
    } catch (BigIntegerOverflow) {
        std::cout << "BigIntegerOverflow" << std::endl;
    }
}
