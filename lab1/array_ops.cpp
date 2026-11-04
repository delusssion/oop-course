#include "array_ops.h"
#include <iostream>

int* array_create(std::size_t size) {
    if (size == 0) {
        return nullptr;
    }
    int* arr = new int[size];
    for (std::size_t i = 0; i < size; i++) {
        arr[i] = 0;
    }
    return arr;
}

void array_delete(int*& arr) {
    delete[] arr;
    arr = nullptr;
}

int* array_resize(int* arr, std::size_t size, std::size_t new_size) {
    int* result = array_create(new_size);
    std::size_t count = size;
    if (new_size < size) {
        count = new_size;
    }
    for (std::size_t i = 0; i < count; i++) {
        result[i] = arr[i];
    }
    delete[] arr;
    return result;
}

int* array_insert(int* arr, std::size_t& size, std::size_t pos, int value) {
    if (pos > size) {
        return arr;
    }
    int* result = new int[size + 1];
    for (std::size_t i = 0; i < pos; i++) {
        result[i] = arr[i];
    }
    result[pos] = value;
    for (std::size_t i = pos; i < size; i++) {
        result[i + 1] = arr[i];
    }
    delete[] arr;
    size++;
    return result;
}

int* array_remove(int* arr, std::size_t& size, std::size_t pos) {
    if (pos >= size) {
        return arr;
    }
    int* result = array_create(size - 1);
    for (std::size_t i = 0; i < pos; i++) {
        result[i] = arr[i];
    }
    for (std::size_t i = pos + 1; i < size; i++) {
        result[i - 1] = arr[i];
    }
    delete[] arr;
    size--;
    return result;
}

void array_print(const int* arr, std::size_t size) {
    std::cout << "[";
    for (std::size_t i = 0; i < size; i++) {
        std::cout << arr[i];
        if (i + 1 < size) {
            std::cout << ", ";
        }
    }
    std::cout << "] (size = " << size << ")" << std::endl;
}
