//
// Created by Chandler Rowe on 9/10/21.
//

#ifndef PROJECT_1_FACTSAUTOMATON_H
#define PROJECT_1_FACTSAUTOMATON_H

#include "Automaton.h"

class FactsAutomaton : public Automaton {
public:
    FactsAutomaton() : Automaton(TokenType::FACTS) {}

    void S0(const std::string &input);
private:
    void S1(const std::string &input);
    void S2(const std::string &input);
    void S3(const std::string &input);
    void S4(const std::string &input);
};


#endif //PROJECT_1_FACTSAUTOMATON_H
