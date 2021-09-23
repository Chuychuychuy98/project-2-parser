//
// Created by Chandler Rowe on 9/9/21.
//

#include "RightParenAutomaton.h"

void RightParenAutomaton::S0(const std::string& input) {
    if (input[index] == ')') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}
