#pragma once
#include <cstddef>

// базовые операции с динамическим массивом
int* array_create(std::size_t size);
void array_delete(int*& arr);
int* array_resize(int* arr, std::size_t size, std::size_t new_size);
int* array_insert(int* arr, std::size_t& size, std::size_t pos, int value);
int* array_remove(int* arr, std::size_t& size, std::size_t pos);
void array_print(const int* arr, std::size_t size);
