#pragma ide diagnostic ignored "hicpp-exception-baseclass"
//
// Created by Chandler Rowe on 9/22/21.
//

#include "Parser.h"

#include <initializer_list>
#include <iostream>

Parser::Parser(const std::vector<Token*> &tokens) {
    this->tokens = tokens;
}

DatalogProgram *Parser::Parse() {
    auto prog = new DatalogProgram();
    try {
        if (tokens.at(index)->GetType() != TokenType::SCHEMES) {
            throw tokens.at(index)->ToString();
        }
        index++;

        if (tokens.at(index)->GetType() != TokenType::COLON) {
            throw tokens.at(index)->ToString();
        }
        index++;

        if (!FIRST("scheme").count(tokens.at(index)->GetType())) {
            throw tokens.at(index)->ToString();
        }
        prog->AddScheme(ParseScheme());

        if (FIRST("schemeList").count(tokens.at(index)->GetType())) {
            ParseSchemeList(prog);
        }
        else if (!FOLLOW("schemeList").count(tokens.at(index)->GetType())) {
            throw tokens.at(index)->ToString();
        }

        if (tokens.at(index)->GetType() != TokenType::FACTS) {
            throw tokens.at(index)->ToString();
        }
        index++;

        if (tokens.at(index)->GetType() != TokenType::COLON) {
            throw tokens.at(index)->ToString();
        }
        index++;

        if (FIRST("factList").count(tokens.at(index)->GetType())) {
            ParseFactList(prog);
        }
        else if (!FOLLOW("factList").count(tokens.at(index)->GetType())) {
            throw tokens.at(index)->ToString();
        }

        if (tokens.at(index)->GetType() != TokenType::RULES) {
            throw tokens.at(index)->ToString();
        }
        index++;

        if (tokens.at(index)->GetType() != TokenType::COLON) {
            throw tokens.at(index)->ToString();
        }
        index++;

        if (FIRST("ruleList").count(tokens.at(index)->GetType())) {
            ParseRuleList(prog);
        }
        else if (!FOLLOW("ruleList").count(tokens.at(index)->GetType())) {
            throw tokens.at(index)->ToString();
        }

        if (tokens.at(index)->GetType() != TokenType::QUERIES) {
            throw tokens.at(index)->ToString();
        }
        index++;

        if (tokens.at(index)->GetType() != TokenType::COLON) {
            throw tokens.at(index)->ToString();
        }
        index++;

        if (!FIRST("query").count(tokens.at(index)->GetType())) {
            throw tokens.at(index)->ToString();
        }
        prog->AddQuery(ParseQuery());

        if (FIRST("queryList").count(tokens.at(index)->GetType())) {
            ParseQueryList(prog);
        }
        else if (!FOLLOW("queryList").count(tokens.at(index)->GetType())) {
            throw tokens.at(index)->ToString();
        }

        if (tokens.at(index)->GetType() != TokenType::END_OF_FILE) {
            throw tokens.at(index)->ToString();
        }
        std::cout << "Success!" << std::endl;
        std::cout << prog->ToString();
        return prog;
    }
    catch(std::string &message) {
        std::cout << "Failure!" << std::endl << "  " << message << std::endl;
        return prog;
    }
    catch(std::out_of_range &e) {
        std::cout << "Exception in Parse: Reached end of file early." << std::endl;
        return prog;
    }
}

std::set<TokenType> Parser::FIRST(const std::string &toCheck) {
    if (toCheck == "scheme" || toCheck == "schemeList" || toCheck == "fact" || toCheck == "factList" || toCheck == "ruleList"
        || toCheck == "rule" || toCheck == "headPredicate" || toCheck == "predicate" || toCheck == "query" || toCheck == "queryList") {
        return std::set<TokenType> (std::initializer_list<TokenType> {TokenType::ID});
    }
    else if (toCheck == "idList" || toCheck == "stringList" || toCheck == "parameterList" || toCheck == "predicateList") {
        return std::set<TokenType> (std::initializer_list<TokenType> {TokenType::COMMA});
    }
    else if (toCheck == "parameter") {
        return std::set<TokenType> (std::initializer_list<TokenType> {TokenType::STRING, TokenType::ID});
    }
    return std::set<TokenType>();
}

std::set<TokenType> Parser::FOLLOW(const std::string &toCheck) {
    if (toCheck == "idList" || toCheck == "stringList" || toCheck == "parameterList") {
        return std::set<TokenType> (std::initializer_list<TokenType> {TokenType::RIGHT_PAREN});
    }
    else if (toCheck == "schemeList") {
        return std::set<TokenType> (std::initializer_list<TokenType> {TokenType::FACTS});
    }
    else if (toCheck == "factList") {
        return std::set<TokenType> (std::initializer_list<TokenType> {TokenType::RULES});
    }
    else if (toCheck == "ruleList") {
        return std::set<TokenType> (std::initializer_list<TokenType> {TokenType::QUERIES});
    }
    else if (toCheck == "predicateList") {
        return std::set<TokenType> (std::initializer_list<TokenType> {TokenType::PERIOD});
    }
    else if (toCheck == "queryList") {
        return std::set<TokenType> (std::initializer_list<TokenType> {TokenType::END_OF_FILE});
    }
    return std::set<TokenType>();
}

Predicate* Parser::ParseScheme() {
    if (tokens.at(index)->GetType() != TokenType::ID) {
        throw tokens.at(index)->ToString();
    }
    auto pred = new Predicate(tokens.at(index)->GetDescription());
    index++;

    if (tokens.at(index)->GetType() != TokenType::LEFT_PAREN) {
        throw tokens.at(index)->ToString();
    }
    index++;

    if (tokens.at(index)->GetType() != TokenType::ID) {
        throw tokens.at(index)->ToString();
    }
    pred->AddParameter(new Parameter(tokens.at(index)->GetDescription()));
    index++;

    if (FIRST("idList").count(tokens.at(index)->GetType())) {
        //idList -> COMMA ID idList
        ParseIDList(pred);
    } else if (!FOLLOW("idList").count(tokens.at(index)->GetType())) {
        throw tokens.at(index)->ToString();
    }
    //idList -> lambda

    if (tokens.at(index)->GetType() != TokenType::RIGHT_PAREN) {
        throw tokens.at(index)->ToString();
    }
    index++;
    return pred;
}

void Parser::ParseSchemeList(DatalogProgram* prog) {
    if (!FIRST("scheme").count(tokens.at(index)->GetType())) {
        throw tokens.at(index)->ToString();
    }
    prog->AddScheme(ParseScheme());
    if (FIRST("schemeList").count(tokens.at(index)->GetType())) {
        ParseSchemeList(prog);
    }
    else if (!FOLLOW("schemeList").count(tokens.at(index)->GetType())) {
        throw tokens.at(index)->ToString();
    }
}

void Parser::ParseFactList(DatalogProgram* prog) {
    if (!FIRST("fact").count(tokens.at(index)->GetType())) {
        throw tokens.at(index)->ToString();
    }
    prog->AddFact(ParseFact());
    if (FIRST("factList").count(tokens.at(index)->GetType())) {
        ParseFactList(prog);
    }
    else if (!FOLLOW("factList").count(tokens.at(index)->GetType())) {
        throw tokens.at(index)->ToString();
    }
}

void Parser::ParseRuleList(DatalogProgram* prog) {
    if (!FIRST("rule").count(tokens.at(index)->GetType())) {
        throw tokens.at(index)->ToString();
    }
    prog->AddRule(ParseRule());

    if (FIRST("ruleList").count(tokens.at(index)->GetType())) {
        ParseRuleList(prog);
    }
    else if (!FOLLOW("ruleList").count(tokens.at(index)->GetType())) {
        throw tokens.at(index)->ToString();
    }
}

Predicate* Parser::ParseQuery() {
    if (!FIRST("predicate").count(tokens.at(index)->GetType())) {
        throw tokens.at(index)->ToString();
    }
    Predicate* pred = ParsePredicate();

    if (tokens.at(index)->GetType() != TokenType::Q_MARK) {
        throw tokens.at(index)->ToString();
    }
    index++;
    return pred;
}

void Parser::ParseQueryList(DatalogProgram* prog) {
    if (!FIRST("query").count(tokens.at(index)->GetType())) {
        throw tokens.at(index)->ToString();
    }
    prog->AddQuery(ParseQuery());

    if (FIRST("queryList").count(tokens.at(index)->GetType())) {
        ParseQueryList(prog);
    }
    else if (!FOLLOW("queryList").count(tokens.at(index)->GetType())) {
        throw tokens.at(index)->ToString();
    }
}

void Parser::ParseIDList(Predicate* pred) {

    if (tokens.at(index)->GetType() != TokenType::COMMA) {
        throw tokens.at(index)->ToString();
    }
    index++;

    if (tokens.at(index)->GetType() != TokenType::ID) {
        throw tokens.at(index)->ToString();
    }
    pred->AddParameter(new Parameter(tokens.at(index)->GetDescription()));
    index++;

    if (FIRST("idList").count(tokens.at(index)->GetType())) {
        //idList -> COMMA ID idList
        ParseIDList(pred);
    } else if (!FOLLOW("idList").count(tokens.at(index)->GetType())) {
        throw tokens.at(index)->ToString();
    }
}

Predicate* Parser::ParseFact() {
    if (tokens.at(index)->GetType() != TokenType::ID) {
        throw tokens.at(index)->ToString();
    }
    auto pred = new Predicate(tokens.at(index)->GetDescription());
    index++;

    if (tokens.at(index)->GetType() != TokenType::LEFT_PAREN) {
        throw tokens.at(index)->ToString();
    }
    index++;

    if (tokens.at(index)->GetType() != TokenType::STRING) {
        throw tokens.at(index)->ToString();
    }
    pred->AddParameter(new Parameter(tokens.at(index)->GetDescription()));
    index++;

    if (FIRST("stringList").count(tokens.at(index)->GetType())) {
        ParseStringList(pred);
    }
    else if (!FOLLOW("stringList").count(tokens.at(index)->GetType())) {
        throw tokens.at(index)->ToString();
    }

    if (tokens.at(index)->GetType() != TokenType::RIGHT_PAREN) {
        throw tokens.at(index)->ToString();
    }
    index++;

    if (tokens.at(index)->GetType() != TokenType::PERIOD) {
        throw tokens.at(index)->ToString();
    }
    index++;
    return pred;
}

void Parser::ParseStringList(Predicate* pred) {
    if (tokens.at(index)->GetType() != TokenType::COMMA) {
        throw tokens.at(index)->ToString();
    }
    index++;

    if (tokens.at(index)->GetType() != TokenType::STRING) {
        throw tokens.at(index)->ToString();
    }
    pred->AddParameter(new Parameter(tokens.at(index)->GetDescription()));
    index++;

    if (FIRST("stringList").count(tokens.at(index)->GetType())) {
        //idList -> COMMA STRING stringList
        ParseIDList(pred);
    } else if (!FOLLOW("stringList").count(tokens.at(index)->GetType())) {
        throw tokens.at(index)->ToString();
    }
}

Rule* Parser::ParseRule() {
    if (!FIRST("headPredicate").count(tokens.at(index)->GetType())) {
        throw tokens.at(index)->ToString();
    }

    Rule* rule = new Rule(ParseHeadPredicate());

    if (tokens.at(index)->GetType() != TokenType::COLON_DASH) {
        throw tokens.at(index)->ToString();
    }
    index++;

    if (!FIRST("predicate").count(tokens.at(index)->GetType())) {
        throw tokens.at(index)->ToString();
    }
    rule->AddPredicate(ParsePredicate());

    if (FIRST("predicateList").count(tokens.at(index)->GetType())) {
        ParsePredicateList(rule);
    }
    else if (!FOLLOW("predicateList").count(tokens.at(index)->GetType())) {
        throw tokens.at(index)->ToString();
    }

    if (tokens.at(index)->GetType() != TokenType::PERIOD) {
        throw tokens.at(index)->ToString();
    }
    index++;
    return rule;
}

Predicate* Parser::ParseHeadPredicate() {
    if (tokens.at(index)->GetType() != TokenType::ID) {
        throw tokens.at(index)->ToString();
    }
    auto pred = new Predicate(tokens.at(index)->GetDescription());
    index++;

    if (tokens.at(index)->GetType() != TokenType::LEFT_PAREN) {
        throw tokens.at(index)->ToString();
    }
    index++;

    if (tokens.at(index)->GetType() != TokenType::ID) {
        throw tokens.at(index)->ToString();
    }
    pred->AddParameter(new Parameter(tokens.at(index)->GetDescription()));
    index++;

    if (FIRST("idList").count(tokens.at(index)->GetType())) {
        ParseIDList(pred);
    }
    else if (!FOLLOW("idList").count(tokens.at(index)->GetType())) {
        throw tokens.at(index)->ToString();
    }

    if (tokens.at(index)->GetType() != TokenType::RIGHT_PAREN) {
        throw tokens.at(index)->ToString();
    }
    index++;
    return pred;
}

Predicate* Parser::ParsePredicate() {
    if (tokens.at(index)->GetType() != TokenType::ID) {
        throw tokens.at(index)->ToString();
    }
    auto pred = new Predicate(tokens.at(index)->GetDescription());
    index++;

    if (tokens.at(index)->GetType() != TokenType::LEFT_PAREN) {
        throw tokens.at(index)->ToString();
    }
    index++;

    if (!FIRST("parameter").count(tokens.at(index)->GetType())) {
        throw tokens.at(index)->ToString();
    }
    pred->AddParameter(ParseParameter());

    if (FIRST("parameterList").count(tokens.at(index)->GetType())) {
        ParseParameterList(pred);
    }
    else if (!FOLLOW("parameterList").count(tokens.at(index)->GetType())) {
        throw tokens.at(index)->ToString();
    }

    if (tokens.at(index)->GetType() != TokenType::RIGHT_PAREN) {
        throw tokens.at(index)->ToString();
    }
    index++;
    return pred;
}

void Parser::ParsePredicateList(Rule* rule) {
    if (tokens.at(index)->GetType() != TokenType::COMMA) {
        throw tokens.at(index)->ToString();
    }
    index++;

    if (!FIRST("predicate").count(tokens.at(index)->GetType())) {
        throw tokens.at(index)->ToString();
    }
    rule->AddPredicate(new Predicate(tokens.at(index)->GetDescription()));
    index++;

    if (FIRST("predicateList").count(tokens.at(index)->GetType())) {
        //idList -> COMMA ID idList
        ParsePredicateList(rule);
    } else if (!FOLLOW("predicateList").count(tokens.at(index)->GetType())) {
        throw tokens.at(index)->ToString();
    }
}

Parameter* Parser::ParseParameter() {
    if (tokens.at(index)->GetType() != TokenType::STRING && tokens.at(index)->GetType() != TokenType::ID) {
        throw tokens.at(index)->ToString();
    }
    auto param = new Parameter(tokens.at(index)->GetDescription());
    index++;
    return param;
}

void Parser::ParseParameterList(Predicate* pred) {

}