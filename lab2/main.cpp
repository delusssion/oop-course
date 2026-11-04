#include <iostream>
#include <utility>
#include "my_string.h"

int main() {
    String s1;
    String s2("Hello");
    String s3(s2);
    String s4(std::move(s3));

    s1 = s2;
    s1.append(", World!");
    s1.print(std::cout);
    std::cout << std::endl;

    std::size_t pos = s1.find("World");
    std::cout << pos << std::endl;

    String text("AAABCC");
    String packed = text.rle_compress();
    std::cout << text << " -> " << packed << std::endl;

    packed.rle_decompress();
    std::cout << "decompress -> " << packed << std::endl;

    std::cout << "Введите строку для сжатия: ";
    char buffer[256];
    if (std::cin.getline(buffer, 256)) {
        String input(buffer);
        String compressed = input.rle_compress();
        std::cout << "Сжато: " << compressed << std::endl;
        compressed.rle_decompress();
        std::cout << "Восстановлено: " << compressed << std::endl;
    }
    return 0;
}
