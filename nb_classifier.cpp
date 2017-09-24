//
// Created by Даниил on 24.09.2017.
//


#include <iostream>
#include <iomanip>
#include "nb_classifier/feature_extraction/mail_tokenizer.hpp"


int main (int argc, char **argv) {
    std::list<std::pair<std::string, bool>> filenames;
    filenames.push_back (std::pair<std::string, bool> (std::string ("train/mail_1.txt"), true));
    filenames.push_back (std::pair<std::string, bool> (std::string ("train/mail_2.txt"), false));

    std::string new_mail_1 ("FROM off a hill whose concave womb reworded A plaintful story from a sistering vale, My spirits to attend this double voice accorded, And down I laid to list the sad-tuned tale; Ere long espied a fickle maid full pale, Tearing of papers, breaking rings a-twain, Storming her world with sorrow's wind and rain.");
    std::string new_mail_2 ("Hello! I have a job for you. See if you want to earn some money. A vacancy is open. Money is good!");

    std::unique_ptr<classifier_state> clf = fit (filenames);

    std::cout << "Is first new mail spam? " << std::setiosflags (std::ios_base::boolalpha) << predict (clf, new_mail_1, 0.5) << std::endl;
    std::cout << "Is second new mail spam? " << std::setiosflags (std::ios_base::boolalpha) << predict (clf, new_mail_2, 0.5) << std::endl;

    return 0;
}