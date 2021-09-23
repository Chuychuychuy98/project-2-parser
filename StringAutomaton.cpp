//
// Created by Chandler Rowe on 9/13/21.
//

#include "StringAutomaton.h"

void StringAutomaton::S0(const std::string &input) {
    if (input[index] == '\'') {
        index++;
        inputRead++;
        S1(input);
    }
    else {
        Serr();
    }
}

void StringAutomaton::S1(const std::string &input) {
    if ((int)input.size() <= index) {
        Serr();
    }
    else if (input[index] == '\'') {
        index++;
        inputRead++;
        S2(input);
    }
    else if (input[index] == '\n') {
        index++;
        inputRead++;
        newLines++;
        S1(input);
    }
    else {
        index++;
        inputRead++;
        S1(input);
    }
}

void StringAutomaton::S2(const std::string &input) {
    if ((int)input.size() <= index) {
       index++;
       inputRead++;
    }
    else if (input[index] == '\'' && inputRead > 1) {
        index++;
        inputRead++;
        S1(input);
    }
}