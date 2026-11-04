#include <iostream>
#include "date_set.h"

int main() {
    DateSet a;
    a.add(Date(15, 3, 2024));
    a.add(Date(1, 1, 2024));
    a.add(Date(29, 2, 2024));
    a += Date(10, 10, 2023);

    std::cout << "A = " << a << std::endl;
    std::cout << "add 30.02.2024: " << a.add(Date(30, 2, 2024)) << std::endl;
    std::cout << "add 01.01.2024 again: " << a.add(Date(1, 1, 2024)) << std::endl;

    DateSet b;
    b += Date(1, 1, 2024);
    b += Date(31, 12, 2024);
    b += Date(10, 10, 2023);
    std::cout << "B = " << b << std::endl;

    std::cout << "A | B = " << (a | b) << std::endl;
    std::cout << "A & B = " << (a & b) << std::endl;
    std::cout << "A - B = " << (a - b) << std::endl;
    std::cout << "A contains 29.02.2024: " << a(Date(29, 2, 2024)) << std::endl;

    a -= Date(15, 3, 2024);
    std::cout << "A after remove = " << a << std::endl;
    std::cout << "A == B: " << (a == b) << std::endl;

    std::cout << "Введите даты (день месяц год), 0 0 0 для конца:" << std::endl;
    DateSet input;
    int d = 0;
    int m = 0;
    int y = 0;
    while (std::cin >> d >> m >> y) {
        if (d == 0 && m == 0 && y == 0) {
            break;
        }
        if (!input.add(Date(d, m, y))) {
            std::cout << "не добавлена (некорректная или повтор)" << std::endl;
        }
    }
    std::cout << "Итог: " << input << std::endl;
    return 0;
}
