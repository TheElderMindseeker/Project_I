#include <iostream>
#include <map>
#include <cmath>
#include <vector>
#include <iomanip>
#include "Date.hpp"
#include "Student.hpp"


const int TEAM_MEMBERS = 3;


int main () {
    std::vector<Student> team;
    team.reserve (TEAM_MEMBERS);
    team.push_back (Student (Date ("01.03.1999")));
    team.push_back (Student (Date ("31.05.1998")));
    team.push_back (Student (Date ("07.05.1998")));

    std::string today_s;
    std::cout << "Input current date (in a format dd.mm.yyyy): ";
    std::cin >> today_s;
    
    Date today ("01.01.0001"); // TODO: Add default ctor to Date

    try {
        today = Date (today_s);
    }
    catch (std::invalid_argument e) {
        std::cout << e.what ();
        return -1;
    }

    std::vector<unsigned> ages;
    ages.reserve (3);
    for (auto iter = team.begin (); iter != team.end (); iter++) {
        ages.push_back (iter->age (today));
    }

    std::map<unsigned, float> age_frequencies;
    for (auto iter = ages.begin (); iter != ages.end (); iter++) {
        if (age_frequencies.find (*iter) == age_frequencies.end ()) {
            age_frequencies.emplace (*iter, 1.0f / 3);
        }
        else {
            age_frequencies.at (*iter) += 1.0f / 3;
        }
    }

    float sum = 0.0f;
    for (auto iter = age_frequencies.begin (); iter != age_frequencies.end (); iter++) {
        sum -= iter->second * std::log2 (iter->second);
    }

    unsigned chosen_age = ages.back ();
    float age_probability = age_frequencies.at (chosen_age);
    float information_amount = - log2f (age_probability);

    std::cout << "The amount of information in sentence 'Random student age is " << ages.back () << "' is equal to ";
    std::cout << std::setprecision (3) << std::setiosflags (std::ios_base::fixed | std::ios_base::showpoint);
    std::cout << information_amount << std::endl;

    return 0;
}