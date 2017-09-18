//
// Created by Даниил on 18.09.2017.
//

#ifndef PROJECT_I_DATE_HPP
#define PROJECT_I_DATE_HPP


#include <string>
#include <stdexcept>


class Date {
public:
    /**
     * @brief Constructs Date object from special format string
     *
     * @param date String in a special format (dd.mm.yyyy)
     *
     * @throw invalid_argument if the string does not conform to specified format
     */
    Date (std::string date) throw (std::invalid_argument);

    /**
     * @brief Constructs Date object from three variables representing day, month and year
     *
     * @param day Day of the month (1-based)
     * @param month Month of the year (1-based)
     * @param year Year A.D.
     *
     * @throw invalid_argument if any of the arguments are out of range
     */
    Date (int day, int month, int year) throw (std::invalid_argument);

    /**
     * Tells day in date
     *
     * @return Day in date
     */
    int get_day () const;

    /**
     * Tells month in date
     *
     * @return Month in date
     */
    int get_month () const;

    /**
     * Tells year in date
     *
     * @return Year in date
     */
    int get_year () const;

    /**
     * Calculates absolute difference in days between two dates
     *
     * @param other Other date
     *
     * @return Absolute difference in days between two dates
     */
    long long int operator - (const Date &other) const;

private:
    /**
     * @brief Tries to parse given string into triple of numbers (day, month, year)
     *
     * @param date Date to be parsed
     * @param day Parsed day
     * @param month Parsed month
     * @param year Parsed year
     *
     * @throw invalid_argument If parse fails
     */
    void parse (std::string date, int &day, int &month, int &year) const throw (std::invalid_argument);

    /**
     * @brief Converts current date into number of days since 1 January 1 A.D.
     *
     * @return Number of days since 01.01.0001
     */
    long long int days_ad () const;

    /**
     * @brief Checks provided date for the validness and throws exception if the date is not valid
     *
     * @param day Day
     * @param month Month
     * @param year Year
     */
    void check_date (int day, int month, int year) const throw (std::invalid_argument);

    int day;

    int month;

    int year;

    static const int *days_in_month () {
        static const int days_data [] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        return days_data;
    }

    static const int DATE_FORMAT_STRING_LENGTH = 2 + 1 + 2 + 1 + 4;
};


#endif //PROJECT_I_DATE_HPP
