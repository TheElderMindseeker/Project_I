//
// Created by Даниил on 21.09.2017.
//

#ifndef PROJECT_I_PILL_HPP
#define PROJECT_I_PILL_HPP


class Pill {
public:
    Pill (float pill_percentage, float death_rate, float problems_rate, float no_reaction_rate);

    float get_death_rate () const;

    float get_problems_rate () const;

    float get_no_reaction_rate () const;

    float get_joint_rate (float rate) const;

private:
    float pill_percentage;

    float death_rate;

    float problems_rate;

    float no_reaction_rate;
};


#endif //PROJECT_I_PILL_HPP
