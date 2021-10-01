//
// Created by Chandler Rowe on 9/22/21.
//

#include "Predicate.h"

std::string Predicate::ToString() {
    std::string toReturn = id + "(";
    for (Parameter* param : parameters) {
        toReturn += param->GetId();
        if (param != parameters.at(parameters.size() - 1)) {
            toReturn += ",";
        }
    }
    return toReturn + ")";
}