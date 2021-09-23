//
// Created by Chandler Rowe on 9/13/21.
//

#include "IDAutomaton.h"

void IDAutomaton::S0(const std::string &input) {
    if (isalpha(input[index])) {
        index++;
        inputRead++;
        S1(input);
    }
    else {
        Serr();
    }
}

void IDAutomaton::S1(const std::string &input) {
    if ((int)input.size() <= index || isspace(input[index])) {
        return;
    }
    else if (isalnum(input[index])) {
        index++;
        inputRead++;
        S1(input);
    }

    else {
    }
}
