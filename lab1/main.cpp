#include <iostream>
#include <limits>
#include "array_ops.h"

bool read_int(int& value) {
    if (!(std::cin >> value)) {
        if (std::cin.eof()) {
            return false;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка ввода, нужно целое число" << std::endl;
        return read_int(value);
    }
    return true;
}

bool read_size(std::size_t& value) {
    int x = 0;
    while (true) {
        if (!read_int(x)) {
            return false;
        }
        if (x >= 0) {
            value = static_cast<std::size_t>(x);
            return true;
        }
        std::cout << "Число должно быть >= 0, попробуйте ещё раз: ";
    }
}

void print_menu() {
    std::cout << std::endl;
    std::cout << "1. Создать массив        2. Напечатать" << std::endl;
    std::cout << "3. Вставить элемент      4. Удалить элемент" << std::endl;
    std::cout << "5. Изменить размер       6. Сортировка и бинарный поиск" << std::endl;
    std::cout << "7. Алгоритм варианта (gnome sort + удалить все вхождения)" << std::endl;
    std::cout << "0. Выход" << std::endl;
    std::cout << "> ";
}

int main() {
    int* arr = nullptr;
    std::size_t size = 0;

    while (true) {
        print_menu();
        int choice = 0;
        if (!read_int(choice)) {
            break;
        }

        if (choice == 0) {
            break;
        } else if (choice == 1) {
            std::cout << "Размер: ";
            std::size_t n = 0;
            if (!read_size(n)) {
                break;
            }
            array_delete(arr);
            arr = array_create(n);
            size = n;
            if (n > 0) {
                std::cout << "Введите " << n << " чисел: ";
            }
            for (std::size_t i = 0; i < n; i++) {
                if (!read_int(arr[i])) {
                    break;
                }
            }
            array_print(arr, size);
        } else if (choice == 2) {
            array_print(arr, size);
        } else if (choice == 3) {
            std::cout << "Позиция (0.." << size << "): ";
            std::size_t pos = 0;
            if (!read_size(pos)) {
                break;
            }
            std::cout << "Значение: ";
            int value = 0;
            if (!read_int(value)) {
                break;
            }
            if (pos > size) {
                std::cout << "Неверная позиция" << std::endl;
            } else {
                arr = array_insert(arr, size, pos, value);
            }
            array_print(arr, size);
        } else if (choice == 4) {
            if (size == 0) {
                std::cout << "Массив пуст" << std::endl;
                continue;
            }
            std::cout << "Позиция (0.." << size - 1 << "): ";
            std::size_t pos = 0;
            if (!read_size(pos)) {
                break;
            }
            if (pos >= size) {
                std::cout << "Неверная позиция" << std::endl;
            } else {
                arr = array_remove(arr, size, pos);
            }
            array_print(arr, size);
        } else if (choice == 5) {
            std::cout << "Новый размер: ";
            std::size_t new_size = 0;
            if (!read_size(new_size)) {
                break;
            }
            arr = array_resize(arr, size, new_size);
            size = new_size;
            array_print(arr, size);
        } else if (choice == 6) {
            array_gnome_sort(arr, size);
            std::cout << "После сортировки: ";
            array_print(arr, size);
            std::cout << "Что ищем: ";
            int target = 0;
            if (!read_int(target)) {
                break;
            }
            std::size_t index = 0;
            if (array_binary_search(arr, size, target, index)) {
                std::cout << "Найдено, индекс = " << index << std::endl;
            } else {
                std::cout << "Не найдено" << std::endl;
            }
        } else if (choice == 7) {
            array_gnome_sort(arr, size);
            std::cout << "После сортировки: ";
            array_print(arr, size);
            std::cout << "Какое значение удалить: ";
            int value = 0;
            if (!read_int(value)) {
                break;
            }
            std::size_t removed = array_remove_all(arr, size, value);
            std::cout << "Удалено элементов: " << removed << std::endl;
            array_print(arr, size);
        } else {
            std::cout << "Нет такого пункта" << std::endl;
        }
    }

    array_delete(arr);
    return 0;
}
