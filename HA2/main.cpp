#include <iostream>
#include <cmath>

int karatsuba(int x, int y) {
    if (x < 10 || y < 10) {
        std::cout << x << " * " << y << " = " << x << " * " << y << std::endl;
        return x * y;
    }

    int m = std::max(std::to_string(x).size(), std::to_string(y).size()) / 2;
    int high1 = x / static_cast<int>(std::pow(10, m));
    int low1 = x % static_cast<int>(std::pow(10, m));
    int high2 = y / static_cast<int>(std::pow(10, m));
    int low2 = y % static_cast<int>(std::pow(10, m));

    std::cout << x << " * " << y << " = ((" << high1 << " * 10^" << m << ") + " << low1 << ") * ((" << high2 << " * 10^" << m << ") + " << low2 << ")" << std::endl;

    int z0 = karatsuba(low1, low2);
    int z1 = karatsuba(high1 + low1, high2 + low2);
    int z2 = karatsuba(high1, high2);

    int result = z2 * static_cast<int>(std::pow(10, 2 * m)) + (z1 - z2 - z0) * static_cast<int>(std::pow(10, m)) + z0;

    std::cout << "= (" << high1 << " * " << high2 << " * 10^" << 2 * m << ") + ((" << high1 << " + " << low1 << ") * (" << high2 << " + " << low2 << ") - (" << high1 << " * " << high2 << ") - (" << low1 << " * " << low2 << ")) * 10^" << m << " + " << z0 << std::endl;
    std::cout << "= " << z2 << " * " << static_cast<int>(std::pow(10, 2 * m)) << " + (" << z1 << " - " << z2 << " - " << z0 << ") * " << static_cast<int>(std::pow(10, m)) << " + " << z0 << std::endl;
    std::cout << "= " << z2 << " * " << static_cast<int>(std::pow(10, 2 * m)) << " + " << (z1 - z2 - z0) << " * " << static_cast<int>(std::pow(10, m)) << " + " << z0 << std::endl;
    std::cout << "= " << z2 * static_cast<int>(std::pow(10, 2 * m)) << " + " << (z1 - z2 - z0) * static_cast<int>(std::pow(10, m)) << " + " << z0 << std::endl;

    return result;
}

int main() {
    int x = 4349;
    int y = 8117;

    int result = karatsuba(x, y);
    std::cout << "The result of " << x << " * " << y << " is: " << result << std::endl;

    return 0;
}

