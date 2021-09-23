//
// Created by Chandler Rowe on 9/10/21.
//

#include "FactsAutomaton.h"

void FactsAutomaton::S0(const std::string &input) {
    if (input[index] == 'F') {
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void FactsAutomaton::S1(const std::string &input) {
    if (input[index] == 'a') {
        index++;
        S2(input);
    }
    else {
        Serr();
    }
}

void FactsAutomaton::S2(const std::string &input) {
    if (input[index] == 'c') {
        index++;
        S3(input);
    }
    else {
        Serr();
    }
}

void FactsAutomaton::S3(const std::string &input) {
    if (input[index] == 't') {
        index++;
        S4(input);
    }
    else {
        Serr();
    }
}

void FactsAutomaton::S4(const std::string &input) {
    if (input[index] == 's') {
        index++;
        inputRead = 5;
    } else {
        Serr();
    }
}