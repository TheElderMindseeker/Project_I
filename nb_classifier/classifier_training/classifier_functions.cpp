//
// Created by Даниил on 25.09.2017.
//


#include <cmath>
#include <numeric>
#include <fstream>
#include <cstring>
#include <iostream>
#include "classifier_functions.hpp"
#include "../feature_extraction/mail_tokenizer.hpp"


const unsigned RARITY_THRESHOLD = 100;


std::unique_ptr<classifier_state> fit (const std::string &master_file) {
    static const int BUFFER_SIZE = 1024;

    std::list<std::pair<std::string, bool>> filenames;
    std::ifstream master (master_file.c_str ());
    char buffer [BUFFER_SIZE];

    while (! master.eof ()) {
        master.getline (buffer, BUFFER_SIZE);

        if (std::strchr (buffer, ':') != nullptr) {
            const char *filename = std::strtok (buffer, ":");
            const char *spam_flag = std::strtok (NULL, ":\n ");

            bool is_spam = *spam_flag == '1';

            filenames.push_back (std::pair<std::string, bool> (std::string (filename), is_spam));
        }
    }

    return fit (filenames);
}


std::unique_ptr<classifier_state> fit (const std::list<std::pair<std::string, bool>> &filenames) {
    std::map<std::string, long long unsigned> spam, ham;

    for (auto file = filenames.begin (); file != filenames.end (); file++) {
        std::ifstream input (file->first, std::ios_base::in | std::ios_base::binary | std::ios_base::ate);

        auto file_size = input.tellg ();
        input.seekg (0);

        char *buffer = new char [file_size];
        input.read (buffer, file_size); // TODO: Add exception throw

        std::string mail (buffer, file_size);
        delete[] (buffer);

        if (file->second) {
            update_word_frequencies (spam, mail);
        }
        else {
            update_word_frequencies (ham, mail);
        }
    }

    for (auto iter = spam.begin (); iter != spam.end (); iter++) {
        if (iter->second < RARITY_THRESHOLD) {
            iter = spam.erase (iter);
            --iter;
        }
    }

    for (auto iter = ham.begin (); iter != ham.end (); iter++) {
        if (iter->second < RARITY_THRESHOLD) {
            iter = ham.erase (iter);
            --iter;
        }
    }

    long long unsigned total_words_spam = 0, total_words_ham = 0;
    std::list<long long unsigned> spam_words, ham_words;

    for (auto spam_iter = spam.begin (); spam_iter != spam.end (); spam_iter++) {
        spam_words.push_back (spam_iter->second);
    }
    for (auto ham_iter = ham.begin (); ham_iter != ham.end (); ham_iter++) {
        ham_words.push_back (ham_iter->second);
    }

    total_words_spam = std::accumulate (spam_words.begin (), spam_words.end (), total_words_spam);
    total_words_ham = std::accumulate (ham_words.begin (), ham_words.end (), total_words_ham);

    std::unique_ptr<classifier_state> clf_state (new classifier_state);

    for (auto spam_iter = spam.begin (); spam_iter != spam.end (); spam_iter++) {
        clf_state->spamness [spam_iter->first] = (float) spam_iter->second / total_words_spam;
    }
    for (auto ham_iter = ham.begin (); ham_iter != ham.end (); ham_iter++) {
        clf_state->hamness [ham_iter->first] = (float) ham_iter->second / total_words_ham;
    }

    return clf_state;
}


bool predict (const std::string &filename, const std::unique_ptr<classifier_state> &clf, float threshold) {
    std::ifstream mail_reader (filename, std::ios_base::in | std::ios_base::binary | std::ios_base::ate);

    auto file_size = mail_reader.tellg ();
    mail_reader.seekg (0);

    char *buffer = new char [file_size];
    mail_reader.read (buffer, file_size);

    std::string mail (buffer, file_size);
    delete[] (buffer);

    return predict (clf, mail, threshold);
}


bool predict (const std::unique_ptr<classifier_state> &clf, const std::string &mail, float threshold) {
    static const float DELTA = 1e-5f;

    std::map<std::string, long long unsigned> words;
    update_word_frequencies (words, mail);

    float nu = 0.0f;

    for (auto iter = words.begin (); iter != words.end (); iter++) {
        if (clf->spamness.find (iter->first) != clf->spamness.end () && clf->hamness.find (iter->first) != clf->hamness.end ()) {
            float word_spamliness = clf->spamness.at (iter->first) / (clf->spamness.at (iter->first) + clf->hamness.at (iter->first));

            nu += std::log (1 - word_spamliness) - std::log (word_spamliness);
        }
    }

    float probability = 1 / (1 + std::exp (nu));

    return probability > threshold + DELTA;
}