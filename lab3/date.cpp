#include "date.h"

bool is_leap_year(int year) {
    if (year % 400 == 0) {
        return true;
    }
    if (year % 100 == 0) {
        return false;
    }
    return year % 4 == 0;
}

int days_in_month(int month, int year) {
    if (month == 2) {
        if (is_leap_year(year)) {
            return 29;
        }
        return 28;
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }
    return 31;
}

Date::Date() : day_(1), month_(1), year_(2000) {}

Date::Date(int day, int month, int year) : day_(day), month_(month), year_(year) {}

int Date::day() const {
    return day_;
}

int Date::month() const {
    return month_;
}

int Date::year() const {
    return year_;
}

bool Date::is_valid() const {
    if (year_ < 1) {
        return false;
    }
    if (month_ < 1 || month_ > 12) {
        return false;
    }
    if (day_ < 1 || day_ > days_in_month(month_, year_)) {
        return false;
    }
    return true;
}

bool Date::operator==(const Date& other) const {
    return day_ == other.day_ && month_ == other.month_ && year_ == other.year_;
}

bool Date::operator!=(const Date& other) const {
    return !(*this == other);
}

bool Date::operator<(const Date& other) const {
    if (year_ != other.year_) {
        return year_ < other.year_;
    }
    if (month_ != other.month_) {
        return month_ < other.month_;
    }
    return day_ < other.day_;
}

std::ostream& operator<<(std::ostream& out, const Date& d) {
    if (d.day_ < 10) {
        out << '0';
    }
    out << d.day_ << '.';
    if (d.month_ < 10) {
        out << '0';
    }
    out << d.month_ << '.' << d.year_;
    return out;
}
