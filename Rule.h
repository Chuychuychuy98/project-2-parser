//
// Created by Chandler Rowe on 9/22/21.
//

#ifndef PROJECT_2_PARSER_RULE_H
#define PROJECT_2_PARSER_RULE_H

#include <string>
#include "Predicate.h"
#include <vector>

class Rule {
public:
    Rule() = default;
    Rule(Predicate* head) : head(head) {}
    void AddPredicate(Predicate* pred) {predicates.push_back(pred);}
    const std::vector<Predicate*> &GetPredicates() const {return predicates;}
    const Predicate* GetHead() const {return head;}
    std::string ToString();

private:
    Predicate* head;
    std::vector<Predicate*> predicates;

};


#endif //PROJECT_2_PARSER_RULE_H
