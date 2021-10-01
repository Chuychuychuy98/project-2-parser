//
// Created by Chandler Rowe on 9/22/21.
//

#ifndef PROJECT_2_PARSER_PREDICATE_H
#define PROJECT_2_PARSER_PREDICATE_H

#include <string>
#include <vector>
#include "Parameter.h"

class Predicate {
public:
    Predicate() = default;
    Predicate(std::string id) : id(move(id)) {}
    std::string ToString();
    void AddParameter(Parameter* parameter) {parameters.push_back(parameter);}
    const std::vector<Parameter*> &GetParameters() {return parameters;}
    const std::string &GetId() {return id;}

private:
    std::string id;
    std::vector<Parameter*> parameters;

};


#endif //PROJECT_2_PARSER_PREDICATE_H
