//
// Created by Chandler Rowe on 9/10/21.
//

#ifndef PROJECT_1_QUERIESAUTOMATON_H
#define PROJECT_1_QUERIESAUTOMATON_H

#include "Automaton.h"

class QueriesAutomaton : public Automaton {
public:
    QueriesAutomaton() : Automaton(TokenType::QUERIES) {}

    void S0(const std::string &input);
private:
    void S1(const std::string &input);
    void S2(const std::string &input);
    void S3(const std::string &input);
    void S4(const std::string &input);
    void S5(const std::string &input);
    void S6(const std::string &input);
};


#endif //PROJECT_1_QUERIESAUTOMATON_H
