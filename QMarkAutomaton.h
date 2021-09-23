//
// Created by Chandler Rowe on 9/9/21.
//

#ifndef PROJECT_1_QMARKAUTOMATON_H
#define PROJECT_1_QMARKAUTOMATON_H

#include "Automaton.h"

class QMarkAutomaton : public Automaton {
public:
    QMarkAutomaton() : Automaton(TokenType::Q_MARK) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif //PROJECT_1_QMARKAUTOMATON_H
