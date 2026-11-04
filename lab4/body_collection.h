#pragma once
#include <cstddef>
#include "celestial_body.h"

class BodyCollection {
public:
    BodyCollection();
    BodyCollection(const BodyCollection& other);
    BodyCollection(BodyCollection&& other) noexcept;
    BodyCollection& operator=(const BodyCollection& other);
    BodyCollection& operator=(BodyCollection&& other) noexcept;
    ~BodyCollection();

    void swap(BodyCollection& other) noexcept;

    void add(CelestialBody* body);
    bool remove(std::size_t index);
    void clear();

    std::size_t size() const;
    bool empty() const;
    CelestialBody& operator[](std::size_t index);
    const CelestialBody& operator[](std::size_t index) const;

    double totalMetric() const;
    void printAll(std::ostream& out) const;

private:
    CelestialBody** data_;
    std::size_t size_;
    std::size_t capacity_;
};
