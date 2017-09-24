//
// Created by Даниил on 24.09.2017.
//


#include <algorithm>
#include <numeric>
#include <fstream>
#include <locale>
#include <cmath>

#include "mail_tokenizer.hpp"


void update_word_frequencies (std::map<std::string, long long unsigned> &words, const std::string &mail,
                              std::locale locale) {
    std::string word;
    for (auto iter = mail.begin (); iter != mail.end (); iter++) {
        if (std::isalpha (*iter, locale)) {
            word.append (1, *iter);
        }
        else {
            if (word.length () > 0) {
                std::transform (word.begin (), word.end (), word.begin (), ::tolower); // TODO: Find a way to do lowercase locale-specific
                words [word] += 1;
                word.clear ();
            }
        }
    }
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


bool predict (const std::unique_ptr<classifier_state> &clf, const std::string &mail, float threshold) {
    static const float DELTA = 1e-5f;

    std::map<std::string, long long unsigned> words;
    update_word_frequencies (words, mail);

    float joint_spamness = 1.0f, joint_hamness = 1.0f;

    for (auto iter = words.begin (); iter != words.end (); iter++) {
        // TODO: Refactor next two lines into something more understandable
        auto word_spamness = (clf->spamness.find (iter->first) != clf->spamness.end ()) ? clf->spamness.at (iter->first) : 1.0f;
        auto word_hamness = (clf->hamness.find (iter->first) != clf->hamness.end ()) ? clf->hamness.at (iter->first) : 1.0f;

        joint_spamness *= word_spamness;
        joint_hamness *= word_hamness;
    }

    float factor = std::pow ((1 - clf->spam_probability) / clf->spam_probability, (float) 1 - words.size ());

    float probability = joint_spamness / (joint_spamness + factor * joint_hamness);

    return probability > threshold + DELTA;
}