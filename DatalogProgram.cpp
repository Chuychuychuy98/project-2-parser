//
// Created by Chandler Rowe on 9/22/21.
//

#include "DatalogProgram.h"
#include <set>

std::string DatalogProgram::ToString() {
    std::string toReturn = "";
    std::set<std::string> stringsInFacts;
    toReturn += "Schemes(" + std::to_string(schemes.size()) + "):\n";
    for (Predicate* scheme : schemes) {
        toReturn += "  " + scheme->ToString() + "\n";
    }
    toReturn += "Facts(" + std::to_string(facts.size()) + "):\n";

    for (Predicate* fact : facts) {
        for (Parameter* param : fact->GetParameters()) {
            stringsInFacts.insert(param->GetId());
        }
        toReturn += "  " + fact->ToString() + ".\n";
    }
    toReturn += "Rules(" + std::to_string(rules.size()) + "):\n";
    for (Rule* rule : rules) {
        toReturn += "  " + rule->ToString() + "\n";
    }
    toReturn += "Queries(" + std::to_string(queries.size()) + "):\n";
    for (Predicate* query : queries) {
        toReturn += "  " + query->ToString() + "?\n";
    }
    toReturn += "Domain(" + std::to_string(stringsInFacts.size()) + "):\n";
    for (Predicate* fact : facts) {

        for (const std::string &s : stringsInFacts) {
            toReturn += "  " + s + "\n";
        }
    }
    return toReturn;
}