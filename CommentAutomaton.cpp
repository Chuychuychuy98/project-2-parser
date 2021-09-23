//
// Created by Chandler Rowe on 9/13/21.
//

#include "CommentAutomaton.h"

void CommentAutomaton::S0(const std::string &input) {
    if (input[index] == '#') {
        index++;
        inputRead++;
        S1(input);
    }
    else {
        Serr();
    }
}

void CommentAutomaton::S1(const std::string &input) {
    if (input[index] == '|') {
        index++;
        inputRead++;
        SB1(input);
    }
    else if (input[index] == '\n' || input.size() == 1) {
        //index++;
        //inputRead++;
    }
    else {
        index++;
        inputRead++;
        S2(input);
    }
}

void CommentAutomaton::S2(const std::string &input) {
    if (input[index] == '\n') {
        index++;
        //inputRead++;
        //newLines++;
    }
    else {
        index++;
        inputRead++;
        S2(input);
    }
}

void CommentAutomaton::SB1(const std::string &input) {
    if ((int)input.size() <= index) { // Reached end of string
        Serr();
    }
    else if (input[index] == '|') {
        index++;
        inputRead++;
        SB2(input);
    }
    else if (input[index] == '\n') {
        index++;
        inputRead++;
        newLines++;
        SB1(input);
    }
    else {
        index++;
        inputRead++;
        SB1(input);
    }
}

void CommentAutomaton::SB2(const std::string &input){
    if ((int)input.size() <= index) { // end of file
        Serr();
    }
    else if (input[index] == '#') { // end of comment
        index++;
        inputRead++;
    }
    else if (input[index] == '\n') {
        index++;
        inputRead++;
        newLines++;
        SB1(input);
    }
    else { // comment continues
        index++;
        inputRead++;
        SB1(input);
    }
}