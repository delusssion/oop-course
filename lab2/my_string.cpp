#include "my_string.h"
#include <cstring>
#include <utility>

String::String() : data_(new char[2]), size_(0), capacity_(1) {
    data_[0] = '\0';
}

String::String(const char* str) : data_(nullptr), size_(0), capacity_(0) {
    if (str == nullptr) {
        str = "";
    }
    size_ = std::strlen(str);
    capacity_ = size_;
    if (capacity_ < 1) {
        capacity_ = 1;
    }
    data_ = new char[capacity_ + 1];
    std::strcpy(data_, str);
}

String::String(const String& other)
    : data_(new char[other.capacity_ + 1]), size_(other.size_), capacity_(other.capacity_) {
    for (std::size_t i = 0; i < size_; i++) {
        data_[i] = other.data_[i];
    }
    data_[size_] = '\0';
}

String::String(String&& other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

String& String::operator=(String other) {
    swap(other);
    return *this;
}

String::~String() {
    delete[] data_;
}

void String::swap(String& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

std::size_t String::size() const {
    return size_;
}

std::size_t String::capacity() const {
    return capacity_;
}

bool String::empty() const {
    return size_ == 0;
}

const char* String::c_str() const {
    if (data_ == nullptr) {
        return "";
    }
    return data_;
}

char& String::operator[](std::size_t index) {
    return data_[index];
}

const char& String::operator[](std::size_t index) const {
    return data_[index];
}

void String::reserve(std::size_t new_capacity) {
    if (new_capacity <= capacity_) {
        return;
    }
    char* new_data = new char[new_capacity + 1];
    for (std::size_t i = 0; i < size_; i++) {
        new_data[i] = data_[i];
    }
    new_data[size_] = '\0';
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
}

void String::push_back(char c) {
    if (size_ == capacity_) {
        if (capacity_ == 0) {
            reserve(1);
        } else {
            reserve(capacity_ * 2);
        }
    }
    data_[size_] = c;
    size_++;
    data_[size_] = '\0';
}

void String::append(const char* str) {
    if (str == nullptr) {
        return;
    }
    std::size_t len = std::strlen(str);
    for (std::size_t i = 0; i < len; i++) {
        push_back(str[i]);
    }
}

void String::append(const String& other) {
    String copy(other);
    for (std::size_t i = 0; i < copy.size_; i++) {
        push_back(copy.data_[i]);
    }
}

void String::clear() {
    size_ = 0;
    if (data_ != nullptr) {
        data_[0] = '\0';
    }
}

std::size_t String::find(const char* sub) const {
    if (sub == nullptr) {
        return npos;
    }
    std::size_t len = std::strlen(sub);
    if (len > size_) {
        return npos;
    }
    for (std::size_t i = 0; i + len <= size_; i++) {
        std::size_t j = 0;
        while (j < len && data_[i + j] == sub[j]) {
            j++;
        }
        if (j == len) {
            return i;
        }
    }
    return npos;
}

void String::print(std::ostream& out) const {
    out << c_str();
}

String String::rle_compress() const {
    String result;
    std::size_t i = 0;
    while (i < size_) {
        char c = data_[i];
        std::size_t count = 0;
        while (i < size_ && data_[i] == c) {
            count++;
            i++;
        }
        result.push_back(c);

        char digits[32];
        int n = 0;
        while (count > 0) {
            digits[n] = static_cast<char>('0' + count % 10);
            count /= 10;
            n++;
        }
        for (int k = n - 1; k >= 0; k--) {
            result.push_back(digits[k]);
        }
    }
    return result;
}

void String::rle_decompress() {
    String result;
    std::size_t i = 0;
    while (i < size_) {
        char c = data_[i];
        i++;
        std::size_t count = 0;
        bool has_digits = false;
        while (i < size_ && data_[i] >= '0' && data_[i] <= '9') {
            count = count * 10 + static_cast<std::size_t>(data_[i] - '0');
            has_digits = true;
            i++;
        }
        if (!has_digits) {
            count = 1;
        }
        for (std::size_t k = 0; k < count; k++) {
            result.push_back(c);
        }
    }
    swap(result);
}

bool operator==(const String& a, const String& b) {
    return std::strcmp(a.c_str(), b.c_str()) == 0;
}

std::ostream& operator<<(std::ostream& out, const String& s) {
    s.print(out);
    return out;
}
