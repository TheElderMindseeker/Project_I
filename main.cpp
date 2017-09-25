#include <iostream>
#include <sstream>
#include <map>
#include <cmath>
#include <vector>
#include <iomanip>
#include "date/Date.hpp"
#include "student/Student.hpp"
#include "tasks/task_solution.hpp"


int main (int argc, char **argv) {
    std::vector<Student> team;
    team.reserve (TEAM_MEMBERS);
    team.push_back (Student (std::string ("Daniil"), Date ("01.03.1999"), 174));
    team.push_back (Student (std::string ("Andrey"), Date ("31.05.1998"), 175));
    team.push_back (Student (std::string ("Niyaz"), Date ("14.11.1998"), 173));

    sentence_information_amount (team);
    size_t M = calculate_text_entropy (team);
    calculate_watch_choice_probability (M);
    compute_entropies ();
    pill_probabilities (team);

    return 0;
}