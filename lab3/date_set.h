#pragma once
#include <cstddef>
#include <iostream>
#include "date.h"

class DateSet {
public:
    DateSet();
    DateSet(const DateSet& other);
    DateSet(DateSet&& other) noexcept;
    DateSet& operator=(const DateSet& other);
    DateSet& operator=(DateSet&& other) noexcept;
    ~DateSet();

    void swap(DateSet& other) noexcept;

    bool add(const Date& d);
    bool remove(const Date& d);
    bool contains(const Date& d) const;
    bool operator()(const Date& d) const;

    std::size_t size() const;
    std::size_t capacity() const;
    bool empty() const;

    const Date& operator[](std::size_t index) const;

    DateSet& operator+=(const Date& d);
    DateSet& operator-=(const Date& d);

    DateSet operator|(const DateSet& other) const;
    DateSet operator&(const DateSet& other) const;
    DateSet operator-(const DateSet& other) const;

    bool operator==(const DateSet& other) const;
    bool operator!=(const DateSet& other) const;

    friend std::ostream& operator<<(std::ostream& out, const DateSet& s);

private:
    Date* data_;
    std::size_t size_;
    std::size_t capacity_;

    std::size_t lower_bound(const Date& d) const;
    void grow();
    void push_back(const Date& d);
};
