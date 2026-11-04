#pragma once
#include <cstddef>
#include <iostream>

class String {
public:
    static inline const std::size_t npos = static_cast<std::size_t>(-1);

    String();
    String(const char* str);
    String(const String& other);
    String(String&& other) noexcept;
    String& operator=(String other);
    ~String();

    void swap(String& other) noexcept;

    std::size_t size() const;
    std::size_t capacity() const;
    bool empty() const;
    const char* c_str() const;

    char& operator[](std::size_t index);
    const char& operator[](std::size_t index) const;

    void push_back(char c);
    void append(const char* str);
    void append(const String& other);
    void clear();

    std::size_t find(const char* sub) const;
    void print(std::ostream& out) const;

    String rle_compress() const;
    void rle_decompress();

private:
    char* data_;
    std::size_t size_;
    std::size_t capacity_;

    void reserve(std::size_t new_capacity);
};

bool operator==(const String& a, const String& b);
std::ostream& operator<<(std::ostream& out, const String& s);
