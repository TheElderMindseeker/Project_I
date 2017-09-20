#include <iostream>
#include <sstream>
#include <map>
#include <cmath>
#include <vector>
#include <iomanip>
#include "Date.hpp"
#include "Student.hpp"


const int TEAM_MEMBERS = 3;
const int CURRENT_YEAR = 2017;


void sentence_information_amount (std::vector<Student> &team);
size_t calculate_text_entropy (std::vector<Student> &team);
void calculate_watch_choice_probability (size_t M);

float question_information (const std::vector<Student> &team, const Date question_date);
float phrase_entropy (const std::string phrase);


int main (int argc, char **argv) {
    std::vector<Student> team;
    team.reserve (TEAM_MEMBERS);
    team.push_back (Student (std::string ("Daniil"), Date ("01.03.1999")));
    team.push_back (Student (std::string ("Andrey"), Date ("31.05.1998")));
    team.push_back (Student (std::string ("Niyaz"), Date ("14.11.1998")));

    sentence_information_amount (team);
    size_t M = calculate_text_entropy (team);
    calculate_watch_choice_probability (M);

    return 0;
}


void sentence_information_amount (std::vector<Student> &team) {
    std::string today_s;

    Date today;

    bool valid_input;
    do {
        std::cout << "Input current date (in a format dd.mm.yyyy): ";
        std::cin >> today_s;
        valid_input = true;

        try {
            today = Date (today_s);
        }
        catch (std::invalid_argument e) {
            std::cout << e.what () << '\n';
            valid_input = false;
        }
    }
    while (! valid_input);

    float information_amount = question_information (team, today);

    std::cout << "The amount of information in sentence 'Random student age is " << team.back ().age (today) << "' is equal to ";
    std::cout << std::setprecision (3) << std::setiosflags (std::ios_base::fixed | std::ios_base::showpoint);
    std::cout << information_amount << std::endl;
}


size_t calculate_text_entropy (std::vector<Student> &team) {
    std::vector<Date> dates;
    dates.reserve (4);
    dates.push_back (Date ("01.01.2017"));
    for (auto iter = team.begin (); iter != team.end (); iter++) {
        dates.push_back (iter->birth_date);
    }

    std::ostringstream text_generator;

    text_generator << "Minimal amount of information bits for previous question for ";
    for (auto iter = team.begin (); iter != team.end (); iter++) {
        text_generator << iter->name << ", ";
    }
    text_generator << "is ";

    Date current_date = dates.front ();
    current_date.set_year (CURRENT_YEAR);
    Date min_date = current_date;
    float min_info_amount = question_information (team, min_date);
    for (auto iter = dates.begin () + 1; iter != dates.end (); iter++) {
        current_date = *iter;
        current_date.set_year (CURRENT_YEAR);
        float candidate = question_information (team, current_date);
        if (candidate <= min_info_amount) {
            min_date = current_date;
            min_info_amount = candidate;
        }
    }

    text_generator << std::setiosflags (std::ios_base::showpoint | std::ios_base::fixed) << std::setprecision (3)
                   << min_info_amount << " bits. This value can be achieved for previous question asked on ";
    text_generator << std::setiosflags (std::ios_base::right) << std::setw (2) << std::setfill ('0')
                   << min_date.get_day () << '.' << std::setw (2) << std::setfill ('0')
                   << min_date.get_month () << '.' << min_date.get_year () << '.';

    std::cout << "\nThe entropy of the following phrase:\n" << text_generator.str () << "\n\tis "
              << phrase_entropy (text_generator.str ()) << std::endl;

    return text_generator.str ().length ();
}


void calculate_watch_choice_probability (size_t M) {
    const unsigned N = 120;

    unsigned orient = M,
            casio = N + M,
            swatch = 2 * M;
    unsigned total = orient + casio + swatch;

    float first_orient = (float) orient / total;
    float cond_second_swatch = (float) swatch / (total - 1);

    std::cout << "\nThe probability of picking Orient as the first model is "
              << std::setiosflags (std::ios_base::showpoint | std::ios_base::fixed) << std::setprecision (2)
              << first_orient << ".\n";
    std::cout << "The probability of picking Swatch as the second model given that we've picked Orient as first is "
              << std::setiosflags (std::ios_base::showpoint | std::ios_base::fixed) << std::setprecision (2)
              << cond_second_swatch << ".\n";
}


float question_information (const std::vector<Student> &team, const Date question_date) {
    std::vector<unsigned> ages;
    ages.reserve (3);
    for (auto iter = team.begin (); iter != team.end (); iter++) {
        ages.push_back (iter->age (question_date));
    }

    std::map<unsigned, float> age_frequencies;
    for (auto iter = ages.begin (); iter != ages.end (); iter++) {
        if (age_frequencies.find (*iter) == age_frequencies.end ()) {
            age_frequencies.emplace (*iter, 1.0f / TEAM_MEMBERS);
        }
        else {
            age_frequencies.at (*iter) += 1.0f / TEAM_MEMBERS;
        }
    }

    unsigned chosen_age = ages.back ();
    float age_probability = age_frequencies.at (chosen_age);
    float information_amount = std::abs (log2f (age_probability));

    return information_amount;
}


float phrase_entropy (const std::string phrase) {
    std::map<char, unsigned> symbols;
    for (auto iter = phrase.begin (); iter != phrase.end (); iter++) {
        auto entry = symbols.find (*iter);
        if (entry == symbols.end ()) {
            symbols.emplace (*iter, 1);
        }
        else {
            ++entry->second;
        }
    }

    const size_t phrase_length = phrase.length ();
    float entropy = 0.0f;
    for (auto iter = symbols.begin (); iter != symbols.end (); iter++) {
        float probability = (float) iter->second / phrase_length;
        entropy += std::abs (probability * log2f (probability));
    }

    return entropy;
}