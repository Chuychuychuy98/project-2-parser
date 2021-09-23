//
// Created by Chandler Rowe on 9/9/21.
//

#ifndef PROJECT_1_MULTIPLYAUTOMATON_H
#define PROJECT_1_MULTIPLYAUTOMATON_H

#include "Automaton.h"

class MultiplyAutomaton : public Automaton {
public:
    MultiplyAutomaton() : Automaton(TokenType::MULTIPLY) {}
    void S0(const std::string &input);
};


#endif //PROJECT_1_MULTIPLYAUTOMATON_H
