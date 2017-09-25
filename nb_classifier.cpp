//
// Created by Даниил on 24.09.2017.
//


#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "nb_classifier/feature_extraction/mail_tokenizer.hpp"
#include "nb_classifier/classifier_training/classifier_functions.hpp"


void test_classifier (std::unique_ptr<classifier_state> &clf, float threshold = 0.7f);


int main (int argc, char **argv) {
    try {
        std::unique_ptr<classifier_state> clf = fit (std::string ("train/master.txt"));

        for (float f = 0.1f; f < 1.0f - 1e-5; f += 0.1f)
            test_classifier (clf, f);
    }
    catch (...) {
        std::cout << "This program must be run in datasets as its working directory\n";
        return -1;
    }

    return 0;
}


void test_classifier (std::unique_ptr<classifier_state> &clf, float threshold) {
    static const int BUFFER_SIZE = 1024;

    std::list<std::pair<std::string, bool>> filenames;
    std::ifstream master ("test/master.txt");
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

    unsigned total_spam = 0, total_ham = 0, correct_spam = 0, correct_ham = 0;

    for (auto iter = filenames.begin (); iter != filenames.end (); iter++) {
        bool prediction = predict (iter->first, clf, threshold);

        if (iter->second) {
            ++total_spam;
            if (prediction)
                ++correct_spam;
        }
        else {
            ++total_ham;
            if (! prediction)
                ++correct_ham;
        }
    }

    std::cout.setf (std::ios_base::fixed | std::ios_base::showpoint);
    std::cout.precision (2);
    std::cout << "\nThreshold = " << threshold << std::endl;
    std::cout << "FAR = " << 100.0f * (1.0f - (float) correct_spam / total_spam) << '%' << std::endl;
    std::cout << "FRR = " << 100.0f * (1.0f - (float) correct_ham / total_ham) << '%' << std::endl;
}