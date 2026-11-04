#pragma once
#include <iostream>

class Date {
public:
    Date();
    Date(int day, int month, int year);

    int day() const;
    int month() const;
    int year() const;

    bool is_valid() const;

    bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;
    bool operator<(const Date& other) const;

    friend std::ostream& operator<<(std::ostream& out, const Date& d);

private:
    int day_;
    int month_;
    int year_;
};

bool is_leap_year(int year);
int days_in_month(int month, int year);
