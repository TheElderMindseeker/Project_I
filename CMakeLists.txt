cmake_minimum_required(VERSION 3.8)
project(Project_I)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp date/Date.cpp date/Date.hpp student/Student.cpp student/Student.hpp pill/Pill.cpp pill/Pill.hpp)
add_executable(Project_I ${SOURCE_FILES})

set(SOURCE_FILES_NB_CLASSIFIER nb_classifier.cpp nb_classifier/feature_extraction/classifier_state.hpp nb_classifier/feature_extraction/mail_tokenizer.cpp nb_classifier/feature_extraction/mail_tokenizer.hpp)
add_executable(NB_classifier ${SOURCE_FILES_NB_CLASSIFIER})