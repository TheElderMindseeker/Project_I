//
// Created by Даниил on 18.09.2017.
//

#ifndef PROJECT_I_STUDENT_HPP
#define PROJECT_I_STUDENT_HPP


#include "../date/Date.hpp"


struct Student {
    /**
     * @brief Constructs Student object with specified birth date
     *
     * @param birth_date Birth date
     */
    Student (std::string name, Date birth_date, unsigned height) : name (name), birth_date (birth_date), height (height) {}

    /**
     * @brief Tells the age of current Student
     *
     * @param today The day to answer a question "what is your age?"
     *
     * @return Age of the Student in years
     */
    unsigned age (Date today) const;

    /**
     * @brief Student name
     */
    std::string name;

    /**
     * @brief Birth date of Student
     */
    Date birth_date;

    /**
     * @brief Student height in centimeters (rounded to integral type)
     */
    unsigned height;
};


#endif //PROJECT_I_STUDENT_HPP
