//
// Created by Даниил on 24.09.2017.
//

#ifndef PROJECT_I_CLASSIFIER_STATE_HPP
#define PROJECT_I_CLASSIFIER_STATE_HPP


#include <string>
#include <map>


struct classifier_state {
    /**
     * @brief Map from word to its spamness P (S | W_i).
     */
    std::map<std::string, float> spamness;

    /**
     * @brief Map from word to its hamness P (~S | W_i).
     */
    std::map<std::string, float> hamness;

    /**
     * @brief General probability of mail being spam.
     */
    float spam_probability;
};


#endif //PROJECT_I_CLASSIFIER_STATE_HPP
