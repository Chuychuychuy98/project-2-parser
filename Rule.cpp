//
// Created by Chandler Rowe on 9/22/21.
//

#include "Rule.h"

std::string Rule::ToString() {
    std::string toReturn = head->ToString() + " :- ";
    for (Predicate* pred : predicates) {
        toReturn += pred->ToString();
        if (pred != predicates.at(predicates.size() - 1)) {
            toReturn += ",";
        }
    }
    return toReturn;
}