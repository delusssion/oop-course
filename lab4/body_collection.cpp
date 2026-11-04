#include "body_collection.h"
#include <stdexcept>
#include <utility>

BodyCollection::BodyCollection() : data_(nullptr), size_(0), capacity_(0) {}

BodyCollection::BodyCollection(const BodyCollection& other) : data_(nullptr), size_(0), capacity_(0) {
    if (other.size_ == 0) {
        return;
    }
    data_ = new CelestialBody*[other.size_];
    capacity_ = other.size_;
    for (std::size_t i = 0; i < other.size_; i++) {
        data_[i] = other.data_[i]->clone();
        size_++;
    }
}

BodyCollection::BodyCollection(BodyCollection&& other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

BodyCollection& BodyCollection::operator=(const BodyCollection& other) {
    if (this != &other) {
        BodyCollection tmp(other);
        swap(tmp);
    }
    return *this;
}

BodyCollection& BodyCollection::operator=(BodyCollection&& other) noexcept {
    if (this != &other) {
        clear();
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

BodyCollection::~BodyCollection() {
    clear();
    delete[] data_;
}

void BodyCollection::swap(BodyCollection& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

void BodyCollection::add(CelestialBody* body) {
    if (body == nullptr) {
        return;
    }
    if (size_ == capacity_) {
        std::size_t new_capacity = capacity_ * 2;
        if (capacity_ == 0) {
            new_capacity = 4;
        }
        CelestialBody** new_data = new CelestialBody*[new_capacity];
        for (std::size_t i = 0; i < size_; i++) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }
    data_[size_] = body;
    size_++;
}

bool BodyCollection::remove(std::size_t index) {
    if (index >= size_) {
        return false;
    }
    delete data_[index];
    for (std::size_t i = index; i + 1 < size_; i++) {
        data_[i] = data_[i + 1];
    }
    size_--;
    return true;
}

void BodyCollection::clear() {
    for (std::size_t i = 0; i < size_; i++) {
        delete data_[i];
        data_[i] = nullptr;
    }
    size_ = 0;
}

std::size_t BodyCollection::size() const {
    return size_;
}

bool BodyCollection::empty() const {
    return size_ == 0;
}

CelestialBody& BodyCollection::operator[](std::size_t index) {
    if (index >= size_) {
        throw std::out_of_range("BodyCollection index out of range");
    }
    return *data_[index];
}

const CelestialBody& BodyCollection::operator[](std::size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("BodyCollection index out of range");
    }
    return *data_[index];
}

double BodyCollection::totalMetric() const {
    double sum = 0;
    for (std::size_t i = 0; i < size_; i++) {
        sum += data_[i]->metric();
    }
    return sum;
}

void BodyCollection::printAll(std::ostream& out) const {
    for (std::size_t i = 0; i < size_; i++) {
        out << i << ") " << *data_[i] << std::endl;
    }
}
