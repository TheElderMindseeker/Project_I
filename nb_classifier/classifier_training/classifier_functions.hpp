//
// Created by Даниил on 25.09.2017.
//

#ifndef PROJECT_I_CLASSIFIER_FUNCTIONS_HPP
#define PROJECT_I_CLASSIFIER_FUNCTIONS_HPP


#include <list>
#include <memory>
#include "../classifier_state.hpp"


/**
 * @brief Fits the classifier to the training data provided in files which are specified in master file via key value pairs.
 *
 * @param master_file Master file name.
 *
 * @return Trained classifier state.
 */
std::unique_ptr<classifier_state> fit (const std::string &master_file);


/**
 * @brief Fits the classifier to the training data provided in files specified by filenames.
 *
 * @param filenames List of pairs of filenames together with flag if the file is spam.
 *
 * @return Trained classifier state.
 */
std::unique_ptr<classifier_state> fit (const std::list<std::pair<std::string, bool>> &filenames);


/**
 * @brief Predicts if the given mail is spam.
 *
 * @param filename File name with mail text.
 * @param clf Trained classifier.
 * @param threshold Spam classification threshold.
 *
 * @return True if the mail is spam, false otherwise.
 */
bool predict (const std::string &filename, const std::unique_ptr<classifier_state> &clf, float threshold = 0.8f);


/**
 * @brief Predicts if the given mail is spam.
 *
 * @param clf Classifier trained to distinguish spam and ham.
 * @param mail Mail to be classifier.
 * @param threshold Spam classification threshold.
 *
 * @return True if the mail is spam, false otherwise.
 */
bool predict (const std::unique_ptr<classifier_state> &clf, const std::string &mail, float threshold = 0.8f);


#endif //PROJECT_I_CLASSIFIER_FUNCTIONS_HPP
