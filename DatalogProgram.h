//
// Created by Chandler Rowe on 9/22/21.
//

#ifndef PROJECT_2_PARSER_DATALOGPROGRAM_H
#define PROJECT_2_PARSER_DATALOGPROGRAM_H
#include <vector>
#include "Predicate.h"
#include "Rule.h"


class DatalogProgram {
public:
    DatalogProgram() = default;
    std::string ToString();

    const std::vector<Predicate*> &GetSchemes() {return schemes;}
    const std::vector<Predicate*> &GetFacts() {return facts;}
    const std::vector<Predicate*> &GetQueries() {return queries;}
    const std::vector<Rule*> &GetRules() {return rules;}

    void AddScheme(Predicate* scheme) {schemes.push_back(scheme);}
    void AddFact(Predicate* fact) {facts.push_back(fact);}
    void AddQuery(Predicate* query) {queries.push_back(query);}
    void AddRule(Rule* rule) {rules.push_back(rule);}
private:
    std::vector<Predicate*> schemes;
    std::vector<Predicate*> facts;
    std::vector<Predicate*> queries;
    std::vector<Rule*> rules;
};


#endif //PROJECT_2_PARSER_DATALOGPROGRAM_H
