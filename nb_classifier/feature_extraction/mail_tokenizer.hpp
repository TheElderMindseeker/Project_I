//
// Created by Даниил on 24.09.2017.
//

#ifndef PROJECT_I_MAIL_TOKENIZER_HPP
#define PROJECT_I_MAIL_TOKENIZER_HPP


#include <string>
#include <memory>
#include <list>
#include <map>
#include "../classifier_state.hpp"


/**
 * @brief Updates word frequencies using data from provided mail.
 *
 * @param words Map from word to number of occurrences in all mails.
 * @param mail Mail as single string.
 * @param locale Locale to use for letter parse.
 */
void update_word_frequencies (std::map<std::string, long long unsigned> &words, const std::string &mail,
                              std::locale locale = std::locale ("C"));


template <typename t_char>
struct locale_tolower {
    t_char operator () (t_char c) const;

    std::locale loc;
};


#endif //PROJECT_I_MAIL_TOKENIZER_HPP
