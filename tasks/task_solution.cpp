//
// Created by Даниил on 25.09.2017.
//

#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>
#include <cmath>
#include "task_solution.hpp"
#include "../pill/Pill.hpp"


float rv_matrix [4][6];


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


void pill_probabilities (std::vector<Student> &team) {
    unsigned total_height = 0;
    for (auto iter = team.begin (); iter != team.end (); iter++)
        total_height += iter->height;

    auto iter = team.begin ();

    Pill killing_pill ((float) iter->height / total_height, 0.90f, 0.07f, 0.03f);
    ++iter;
    Pill normal_pill ((float) iter->height / total_height, 0.05f, 0.02f, 0.93f);
    ++iter;
    Pill placebo ((float) iter->height / total_height, 0.007f, 0.003f, 0.99f);

    float killing_pill_given_death = killing_pill.get_joint_rate (killing_pill.get_death_rate ())
                                     / (killing_pill.get_joint_rate (killing_pill.get_death_rate ())
                                        + normal_pill.get_joint_rate (normal_pill.get_death_rate ())
                                        + placebo.get_joint_rate (placebo.get_death_rate ()));

    float survival_probability = (1 - killing_pill.get_death_rate ())
                                 * (1 - normal_pill.get_death_rate ())
                                 * (1 - placebo.get_death_rate ());

    std::cout << "\nThe probability the person took killing pill given that he died is "
              << std::setiosflags (std::ios_base::showpoint | std::ios_base::fixed) << std::setprecision (4)
              << killing_pill_given_death << ".\n";
    std::cout << "The probability of person surviving taking all the three types of pills is "
              << std::setiosflags (std::ios_base::showpoint | std::ios_base::fixed) << std::setprecision (4)
              << survival_probability << ".\n";
}


void compute_entropies () {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 6; j++)
            rv_matrix [i][j] = 0;

    add_letter (0, 0, 0);
    compute_total_number_of_outcomes ();

    std::cout.setf (std::ios_base::fixed | std::ios_base::showpoint);
    std::cout.precision (3);

    std::cout << "\nH(X)\t= " << h_of_x ();
    std::cout << "\nH(Y)\t= " << h_of_y ();
    std::cout << "\nH(X|Y)\t= " << h_of_x_given_y ();
    std::cout << "\nH(Y|X)\t= " << h_of_y_given_x ();
    std::cout << "\nH(X,Y)\t= " << h_of_x_and_y ();
    std::cout << "\nI(X;Y)\t= " << i_of_x_and_y ();

    std::cout << std::endl;
}


void add_letter (int A, int B, int C) {
    if (A == 3) {
        ++rv_matrix [0][A+B+C-3];
    }
    else if (B == 3) {
        ++rv_matrix [1][A+B+C-3];
    }
    else if (C == 3) {
        ++rv_matrix [2][A+B+C-3];
    }
    else {
        add_letter (A + 1, B, C);
        add_letter (A, B + 1, C);
        add_letter (A, B, C + 1);
    }
}


void compute_total_number_of_outcomes () {
    // Compute total number of outcomes for every event in Y
    // rv_matrix [3][y] is number of outcomes for Y = y + 3
    for (int y = 0; y < 5; y++)
        for (int x = 0; x < 3; x++)
            rv_matrix[3][y] += rv_matrix[x][y];

    // Compute marginals for every event in X
    // rv_matrix [x][5] is number of outcomes for X = x
    // (0==A, 1==B, 2==C)
    for (int x = 0; x < 3; x++)
        for (int y = 0; y < 5; y++)
            rv_matrix[x][5] += rv_matrix[x][y];

    // Compute total number of outcomes in joint distribution
    for (int x = 0; x < 3; x++)
        rv_matrix[3][5] += rv_matrix[x][5];
}


float h_of_x () {
    float H = 0;
    for (int x = 0; x < 3; x++) {
        float probability = rv_matrix [x][5] / rv_matrix [3][5];
        H += probability * log2f (1 / probability);
    }
    return H;
}


float h_of_y () {
    float H = 0;
    for (int y = 0; y < 5; y++) {
        float probability = rv_matrix [3][y] / rv_matrix [3][5];
        H += probability * log2f (1 / probability);
    }
    return H;
}


float h_of_x_given_y () {
    float h = 0;
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 5; y++) {
            float probability_y = rv_matrix [3][y] / rv_matrix [3][5];
            float probability_x_and_y = rv_matrix [x][y] / rv_matrix [3][5];
            h += probability_x_and_y * log2f (probability_y / probability_x_and_y);
        }
    }
    return h;
}


float h_of_y_given_x () {
    float h = 0;
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 5; y++) {
            float probability_x = rv_matrix [x][5] / rv_matrix [3][5];
            float probability_x_and_y = rv_matrix [x][y] / rv_matrix [3][5];
            h += probability_x_and_y * log2f (probability_x / probability_x_and_y);
        }
    }
    return h;
}


float h_of_x_and_y () {
    return h_of_x() + h_of_y_given_x ();
}


float i_of_x_and_y() {
    return h_of_y() - h_of_y_given_x ();
}