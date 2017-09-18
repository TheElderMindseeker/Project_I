#include <iostream>
#include <map>
#include <cmath>
#include "Date.hpp"
#include "Student.hpp"


int main () {
    Student Andrey (Date (31, 5, 1998));
    Student Daniil (Date (1, 3, 1999));
    Student Idontknow (Date (7, 5, 1998));

    std::string today_s;
    std::cout << "Input current date (in a format dd.mm.yyyy): ";
    std::cin >> today_s;

    try {
        Date today (today_s);
    }
    catch (std::invalid_argument e) {
        std::cout << e.what ();
        return -1;
    }

    unsigned ages [3];

    ages [0] = Andrey.age (Date (today_s));
    ages [1] = Daniil.age (Date (today_s));
    ages [2] = Idontknow.age (Date (today_s));

    std::map<unsigned, float> age_freqs;
    for (int i = 0; i < 3; i++) {
        std::cout << "Age #" << i + 1 << ": " << ages [i] << '\n';

        if (age_freqs.find (ages [i]) == age_freqs.end ()) {
            age_freqs.emplace (ages [i], 1.0f / 3);
        }
        else {
            age_freqs.at (ages [i]) += 1.0f / 3;
        }
    }

    float sum = 0.0f;
    for (auto iter = age_freqs.begin (); iter != age_freqs.end (); iter++) {
        sum -= iter->second * std::log2 (iter->second);
    }

    float prob = age_freqs.at (Idontknow.age (Date (today_s)));
    float prob_2 = age_freqs.at (Daniil.age (Date (today_s)));

    std::cout << sum << std::endl;
    std::cout << - std::log2 (prob) << std::endl;
    std::cout << - std::log2 (prob_2) << std::endl;

    return 0;
}