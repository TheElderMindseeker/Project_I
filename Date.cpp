//
// Created by Даниил on 18.09.2017.
//

#include <cstring>
#include "Date.hpp"


Date::Date (std::string date) throw (std::invalid_argument) {
    int day, month, year;
    parse (date, day, month, year);

    this->day = day;
    this->month = month;
    this->year = year;
}


Date::Date (int day, int month, int year) throw (std::invalid_argument) {
    check_date (day, month, year);

    this->day = day;
    this->month = month;
    this->year = year;
}


int Date::get_day () const {
    return day;
}


int Date::get_month () const {
    return month;
}


int Date::get_year () const {
    return year;
}


long long int Date::operator - (const Date &other) const {
    return std::abs (this->days_ad () - other.days_ad ());
}


void Date::parse (std::string date, int &day, int &month, int &year) const throw (std::invalid_argument) {
    char copy [DATE_FORMAT_STRING_LENGTH + 1];
    std::strncpy (copy, date.c_str (), DATE_FORMAT_STRING_LENGTH);

    const char *token = std::strtok (copy, ".");

    if (token == nullptr)
        throw std::invalid_argument ("Date string parse error");

    day = std::strtol (token, NULL, 10);
    token = std::strtok (NULL, ".");

    if (token == nullptr)
        throw std::invalid_argument ("Date string parse error");

    month = std::strtol (token, NULL, 10);
    token = std::strtok (NULL, ".");

    if (token == nullptr)
        throw std::invalid_argument ("Date string parse error");

    year = std::strtol (token, NULL, 10);

    check_date (day, month, year);
}


long long int Date::days_ad () const {
    long long int result = 0;
    int day = this->day, month = this->month, year = this->year;

    --year;
    result += (year / 4) * (365 * 4 + 1);
    year %= 4;
    result += year * 365;

    for (int i = 1; i < month; i++) {
        result += days_in_month () [i];
    }

    result += day;

    return result;
}


void Date::check_date (int day, int month, int year) const throw (std::invalid_argument) {
    if (year <= 0)
        throw std::invalid_argument ("Year cannot be less than 1");

    if (month < 1 || month > 12)
        throw std::invalid_argument ("Month must be between 1 and 12 inclusively");

    if (day < 1 || day > days_in_month () [month - 1])
        if (year % 4 != 0 || day != 29)
            throw std::invalid_argument ("Invalid day");
}
