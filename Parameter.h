//
// Created by Chandler Rowe on 9/22/21.
//

#ifndef PROJECT_2_PARSER_PARAMETER_H
#define PROJECT_2_PARSER_PARAMETER_H
#include <string>

class Parameter {
public:
    Parameter() = default;
    Parameter(std::string id) : id(move(id)) {}
    std::string GetId() {return id;}
private:
    std::string id;
};


#endif //PROJECT_2_PARSER_PARAMETER_H
