//
// Created by Даниил on 24.09.2017.
//

#ifndef PROJECT_I_MAIL_TOKENIZER_HPP
#define PROJECT_I_MAIL_TOKENIZER_HPP


#include <string>
#include <memory>
#include <list>
#include <map>
#include "classifier_state.hpp"


/**
 * @brief Updates word frequencies using data from provided mail.
 *
 * @param words Map from word to number of occurrences in all mails.
 * @param mail Mail as single string.
 * @param locale Locale to use for letter parse.
 */
void update_word_frequencies (std::map<std::string, long long unsigned> &words, const std::string &mail,
                              std::locale locale = std::locale ("C"));


/**
 * @brief Fits the classifier to the training data provided in files specified by filenames.
 *
 * @param filenames List of pairs of filenames together with flag if the file is spam.
 *
 * @return Classifier state.
 */
std::unique_ptr<classifier_state> fit (const std::list<std::pair<std::string, bool>> &filenames);


/**
 * @brief Predicts if the given mail is spam.
 *
 * @param clf Classifier trained to distinguish spam and ham.
 * @param mail Mail to be classifier.
 *
 * @return True if the mail is spam, false otherwise.
 */
bool predict (const std::unique_ptr<classifier_state> &clf, const std::string &mail, float threshold = 0.8);


#endif //PROJECT_I_MAIL_TOKENIZER_HPP
