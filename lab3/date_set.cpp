#include "date_set.h"
#include <stdexcept>
#include <utility>

DateSet::DateSet() : data_(nullptr), size_(0), capacity_(0) {}

DateSet::DateSet(const DateSet& other) : data_(nullptr), size_(other.size_), capacity_(other.capacity_) {
    if (capacity_ > 0) {
        data_ = new Date[capacity_];
        for (std::size_t i = 0; i < size_; i++) {
            data_[i] = other.data_[i];
        }
    }
}

DateSet::DateSet(DateSet&& other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

DateSet& DateSet::operator=(const DateSet& other) {
    if (this != &other) {
        DateSet tmp(other);
        swap(tmp);
    }
    return *this;
}

DateSet& DateSet::operator=(DateSet&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

DateSet::~DateSet() {
    delete[] data_;
}

void DateSet::swap(DateSet& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

std::size_t DateSet::lower_bound(const Date& d) const {
    std::size_t left = 0;
    std::size_t right = size_;
    while (left < right) {
        std::size_t mid = left + (right - left) / 2;
        if (data_[mid] < d) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

void DateSet::grow() {
    std::size_t new_capacity = capacity_ * 2;
    if (capacity_ == 0) {
        new_capacity = 4;
    }
    Date* new_data = new Date[new_capacity];
    for (std::size_t i = 0; i < size_; i++) {
        new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
}

void DateSet::push_back(const Date& d) {
    if (size_ == capacity_) {
        grow();
    }
    data_[size_] = d;
    size_++;
}

bool DateSet::add(const Date& d) {
    if (!d.is_valid()) {
        return false;
    }
    std::size_t pos = lower_bound(d);
    if (pos < size_ && data_[pos] == d) {
        return false;
    }
    if (size_ == capacity_) {
        grow();
    }
    for (std::size_t i = size_; i > pos; i--) {
        data_[i] = data_[i - 1];
    }
    data_[pos] = d;
    size_++;
    return true;
}

bool DateSet::remove(const Date& d) {
    std::size_t pos = lower_bound(d);
    if (pos >= size_ || data_[pos] != d) {
        return false;
    }
    for (std::size_t i = pos; i + 1 < size_; i++) {
        data_[i] = data_[i + 1];
    }
    size_--;
    return true;
}

bool DateSet::contains(const Date& d) const {
    std::size_t pos = lower_bound(d);
    return pos < size_ && data_[pos] == d;
}

bool DateSet::operator()(const Date& d) const {
    return contains(d);
}

std::size_t DateSet::size() const {
    return size_;
}

std::size_t DateSet::capacity() const {
    return capacity_;
}

bool DateSet::empty() const {
    return size_ == 0;
}

const Date& DateSet::operator[](std::size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("DateSet index out of range");
    }
    return data_[index];
}

DateSet& DateSet::operator+=(const Date& d) {
    add(d);
    return *this;
}

DateSet& DateSet::operator-=(const Date& d) {
    remove(d);
    return *this;
}

DateSet DateSet::operator|(const DateSet& other) const {
    DateSet result;
    std::size_t i = 0;
    std::size_t j = 0;
    while (i < size_ && j < other.size_) {
        if (data_[i] < other.data_[j]) {
            result.push_back(data_[i]);
            i++;
        } else if (other.data_[j] < data_[i]) {
            result.push_back(other.data_[j]);
            j++;
        } else {
            result.push_back(data_[i]);
            i++;
            j++;
        }
    }
    while (i < size_) {
        result.push_back(data_[i]);
        i++;
    }
    while (j < other.size_) {
        result.push_back(other.data_[j]);
        j++;
    }
    return result;
}

DateSet DateSet::operator&(const DateSet& other) const {
    DateSet result;
    std::size_t i = 0;
    std::size_t j = 0;
    while (i < size_ && j < other.size_) {
        if (data_[i] < other.data_[j]) {
            i++;
        } else if (other.data_[j] < data_[i]) {
            j++;
        } else {
            result.push_back(data_[i]);
            i++;
            j++;
        }
    }
    return result;
}

DateSet DateSet::operator-(const DateSet& other) const {
    DateSet result;
    std::size_t i = 0;
    std::size_t j = 0;
    while (i < size_ && j < other.size_) {
        if (data_[i] < other.data_[j]) {
            result.push_back(data_[i]);
            i++;
        } else if (other.data_[j] < data_[i]) {
            j++;
        } else {
            i++;
            j++;
        }
    }
    while (i < size_) {
        result.push_back(data_[i]);
        i++;
    }
    return result;
}

bool DateSet::operator==(const DateSet& other) const {
    if (size_ != other.size_) {
        return false;
    }
    std::size_t i = 0;
    std::size_t j = 0;
    while (i < size_ && j < other.size_) {
        if (data_[i] != other.data_[j]) {
            return false;
        }
        i++;
        j++;
    }
    return true;
}

bool DateSet::operator!=(const DateSet& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const DateSet& s) {
    if (s.size_ == 0) {
        out << "{ }";
        return out;
    }
    out << "{ ";
    for (std::size_t i = 0; i < s.size_; i++) {
        out << s.data_[i];
        if (i + 1 < s.size_) {
            out << ", ";
        }
    }
    out << " }";
    return out;
}
