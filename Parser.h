//
// Created by Chandler Rowe on 9/22/21.
//

#ifndef PROJECT_2_PARSER_PARSER_H
#define PROJECT_2_PARSER_PARSER_H

#include <vector>
#include <set>
#include "Predicate.h"
#include "DatalogProgram.h"
#include "Predicate.h"
#include "Rule.h"
#include "Parameter.h"
#include "Token.h"

class Parser {
public:
    Parser(const std::vector<Token*> &tokens);
    DatalogProgram* Parse();

private:
    std::vector<Predicate*> predicates;
    static std::set<TokenType> FIRST(const std::string &toCheck);
    static std::set<TokenType> FOLLOW(const std::string &toCheck);
    Predicate* ParseScheme();
    void ParseSchemeList(DatalogProgram* prog);
    void ParseFactList(DatalogProgram* prog);
    void ParseRuleList(DatalogProgram* prog);
    Predicate* ParseQuery();
    void ParseQueryList(DatalogProgram* prog);
    void ParseIDList(Predicate* pred);
    Predicate* ParseFact();
    void ParseStringList(Predicate* pred);
    Rule* ParseRule();
    Predicate* ParseHeadPredicate();
    Predicate* ParsePredicate();
    void ParsePredicateList(Rule* rule);
    Parameter* ParseParameter();
    void ParseParameterList(Predicate* pred);
    int index = 0;
    std::vector<Token*> tokens;

};


#endif //PROJECT_2_PARSER_PARSER_H
