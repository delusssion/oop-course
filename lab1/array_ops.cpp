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

void array_gnome_sort(int* arr, std::size_t size) {
    std::size_t i = 0;
    while (i < size) {
        if (i == 0 || arr[i - 1] <= arr[i]) {
            i++;
        } else {
            int tmp = arr[i];
            arr[i] = arr[i - 1];
            arr[i - 1] = tmp;
            i--;
        }
    }
}

bool array_binary_search(const int* arr, std::size_t size, int target, std::size_t& out_index) {
    std::size_t left = 0;
    std::size_t right = size;
    while (left < right) {
        std::size_t mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            out_index = mid;
            return true;
        }
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return false;
}

std::size_t array_remove_all(int* arr, std::size_t& size, int value) {
    std::size_t write = 0;
    for (std::size_t read = 0; read < size; read++) {
        if (arr[read] != value) {
            arr[write] = arr[read];
            write++;
        }
    }
    std::size_t removed = size - write;
    size = write;
    return removed;
}
