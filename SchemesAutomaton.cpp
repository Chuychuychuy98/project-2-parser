//
// Created by Chandler Rowe on 9/10/21.
//

#include "SchemesAutomaton.h"

void SchemesAutomaton::S0(const std::string &input) {
    if (input[index] == 'S') {
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void SchemesAutomaton::S1(const std::string &input) {
    if (input[index] == 'c') {
        index++;
        S2(input);
    }
    else {
        Serr();
    }
}

void SchemesAutomaton::S2(const std::string &input) {
    if (input[index] == 'h') {
        index++;
        S3(input);
    }
    else {
        Serr();
    }
}

void SchemesAutomaton::S3(const std::string &input) {
    if (input[index] == 'e') {
        index++;
        S4(input);
    }
    else {
        Serr();
    }
}

void SchemesAutomaton::S4(const std::string &input) {
    if (input[index] == 'm') {
        index++;
        S5(input);
    }
    else {
        Serr();
    }
}

void SchemesAutomaton::S5(const std::string &input) {
    if (input[index] == 'e') {
        index++;
        S6(input);
    }
}
void SchemesAutomaton::S6(const std::string &input) {
    if (input[index] == 's') {
        index++;
        inputRead = 7;
    }
    else {
        Serr();
    }
}