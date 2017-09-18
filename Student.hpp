//
// Created by Даниил on 18.09.2017.
//

#ifndef PROJECT_I_STUDENT_HPP
#define PROJECT_I_STUDENT_HPP


#include "Date.hpp"


struct Student {
    Student (Date birth_date) : birth_date (birth_date) {}

    unsigned age (Date today) const;

    Date birth_date;
};


#endif //PROJECT_I_STUDENT_HPP
