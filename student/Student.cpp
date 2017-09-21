//
// Created by Даниил on 18.09.2017.
//

#include "Student.hpp"


unsigned Student::age (Date today) const {
    long long int days = today - birth_date;
    unsigned age = 0;

    for (int y = birth_date.get_year (); days > 0; y++) {
        if (y % 4 == 0) {
            if (days >= 366) {
                ++age;
                days -= 366;
            }
            else {
                days = 0;
            }
        }
        else {
            if (days >= 365) {
                ++age;
                days -= 365;
            }
            else {
                days = 0;
            }
        }
    }

    return age;
}
