//
// Created by Даниил on 21.09.2017.
//

#include "Pill.hpp"


Pill::Pill (float pill_percentage, float death_rate, float problems_rate, float no_reaction_rate) : pill_percentage (
        pill_percentage), death_rate (death_rate), problems_rate (problems_rate), no_reaction_rate (no_reaction_rate) {}


float Pill::get_death_rate () const {
    return death_rate;
}


float Pill::get_problems_rate () const {
    return problems_rate;
}


float Pill::get_no_reaction_rate () const {
    return no_reaction_rate;
}


float Pill::get_joint_rate (float rate) const {
    return pill_percentage * rate;
}
