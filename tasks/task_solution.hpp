//
// Created by Даниил on 25.09.2017.
//

#ifndef PROJECT_I_TASK_SOLUTION_HPP
#define PROJECT_I_TASK_SOLUTION_HPP


#include <vector>
#include "../student/Student.hpp"


const int TEAM_MEMBERS = 3;
const int CURRENT_YEAR = 2017;


void sentence_information_amount (std::vector<Student> &team);

size_t calculate_text_entropy (std::vector<Student> &team);

void calculate_watch_choice_probability (size_t M);

void pill_probabilities (std::vector<Student> &team);

float question_information (const std::vector<Student> &team, const Date question_date);

float phrase_entropy (const std::string phrase);

void compute_entropies ();

void add_letter (int A, int B, int C);

void compute_total_number_of_outcomes ();

float h_of_x ();

float h_of_y ();

float h_of_x_given_y ();

float h_of_y_given_x ();

float h_of_x_and_y ();

float i_of_x_and_y();


#endif //PROJECT_I_TASK_SOLUTION_HPP
