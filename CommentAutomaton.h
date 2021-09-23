//
// Created by Chandler Rowe on 9/13/21.
//

#ifndef PROJECT_1_COMMENTAUTOMATON_H
#define PROJECT_1_COMMENTAUTOMATON_H

#include "Automaton.h"

class CommentAutomaton : public Automaton {
public:
    CommentAutomaton() : Automaton(TokenType::COMMENT) {}
    void S0(const std::string &input);
private:
    void S1(const std::string &input);
    void S2(const std::string &input);
    void SB1(const std::string &input);
    void SB2(const std::string &input);
};


#endif //PROJECT_1_COMMENTAUTOMATON_H
