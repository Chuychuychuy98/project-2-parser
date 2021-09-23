//
// Created by Chandler Rowe on 9/10/21.
//

#include "RulesAutomaton.h"

//
// Created by Chandler Rowe on 9/10/21.
//

#include "RulesAutomaton.h"

void RulesAutomaton::S0(const std::string &input) {
    if (input[index] == 'R') {
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void RulesAutomaton::S1(const std::string &input) {
    if (input[index] == 'u') {
        index++;
        S2(input);
    }
    else {
        Serr();
    }
}

void RulesAutomaton::S2(const std::string &input) {
    if (input[index] == 'l') {
        index++;
        S3(input);
    }
    else {
        Serr();
    }
}

void RulesAutomaton::S3(const std::string &input) {
    if (input[index] == 'e') {
        index++;
        S4(input);
    }
    else {
        Serr();
    }
}

void RulesAutomaton::S4(const std::string &input) {
    if (input[index] == 's') {
        index++;
        inputRead = 5;
    } else {
        Serr();
    }
}