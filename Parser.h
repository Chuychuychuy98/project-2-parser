//
// Created by Chandler Rowe on 9/22/21.
//

#ifndef PROJECT_2_PARSER_PARSER_H
#define PROJECT_2_PARSER_PARSER_H

#include <vector>
#include <set>
#include "Predicate.h"
#include "DatalogProgram.h"
#include "Token.h"

class Parser {
public:
    Parser(const std::vector<Token*> &tokens);
    DatalogProgram Parse();

private:
    std::vector<Predicate*> predicates;
    static std::set<TokenType> FIRST(const std::string &toCheck);
    static std::set<TokenType> FOLLOW(const std::string &toCheck);
    void ParseScheme();
    void ParseSchemeList();
    void ParseFactList();
    void ParseRuleList();
    void ParseQuery();
    void ParseQueryList();
    void ParseIDList();
    void ParseFact();
    void ParseStringList();
    void ParseRule();
    void ParseHeadPredicate();
    void ParsePredicate();
    void ParsePredicateList();
    void ParseParameter();
    void ParseParameterList();
    int index = 0;
    std::vector<Token*> tokens;

};


#endif //PROJECT_2_PARSER_PARSER_H
