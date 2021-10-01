#pragma clang diagnostic push
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

DatalogProgram Parser::Parse() {
    try {
        if (tokens.at(index)->GetType() != TokenType::SCHEMES) {
            throw "Expected SCHEMES, got " + tokens.at(index)->ToString();
        }
        index++;

        if (tokens.at(index)->GetType() != TokenType::COLON) {
            throw "Expected COLON, got " + tokens.at(index)->ToString();
        }
        index++;

        if (!FIRST("scheme").count(tokens.at(index)->GetType())) {
            throw "Expected scheme, got " + tokens.at(index)->ToString();
        }
        ParseScheme();

        if (FIRST("schemeList").count(tokens.at(index)->GetType())) {
            ParseSchemeList();
        }
        else if (!FOLLOW("schemeList").count(tokens.at(index)->GetType())) {
            throw "Expected schemeList, got " + tokens.at(index)->ToString();
        }

        if (tokens.at(index)->GetType() != TokenType::FACTS) {
            throw "Expected FACTS, got " + tokens.at(index)->ToString();
        }
        index++;

        if (tokens.at(index)->GetType() != TokenType::COLON) {
            throw "Expected COLON, got " + tokens.at(index)->ToString();
        }
        index++;

        if (FIRST("factList").count(tokens.at(index)->GetType())) {
            ParseFactList();
        }
        else if (!FOLLOW("factList").count(tokens.at(index)->GetType())) {
            throw "Expected factList, got " + tokens.at(index)->ToString();
        }

        if (tokens.at(index)->GetType() != TokenType::RULES) {
            throw "Expected RULES, got " + tokens.at(index)->ToString();
        }
        index++;

        if (tokens.at(index)->GetType() != TokenType::COLON) {
            throw "Expected COLON, got " + tokens.at(index)->ToString();
        }
        index++;

        if (FIRST("ruleList").count(tokens.at(index)->GetType())) {
            ParseRuleList();
        }
        else if (!FOLLOW("ruleList").count(tokens.at(index)->GetType())) {
            throw "Expected ruleList, got " + tokens.at(index)->ToString();
        }

        if (tokens.at(index)->GetType() != TokenType::QUERIES) {
            throw "Expected QUERIES, got " + tokens.at(index)->ToString();
        }
        index++;

        if (tokens.at(index)->GetType() != TokenType::COLON) {
            throw "Expected COLON, got " + tokens.at(index)->ToString();
        }
        index++;

        if (!FIRST("query").count(tokens.at(index)->GetType())) {
            throw "Expected query, got " + tokens.at(index)->ToString();
        }
        ParseQuery();

        if (FIRST("queryList").count(tokens.at(index)->GetType())) {
            ParseQueryList();
        }
        else if (!FOLLOW("queryList").count(tokens.at(index)->GetType())) {
            throw "Expected queryList, got " + tokens.at(index)->ToString();
        }

        if (tokens.at(index)->GetType() != TokenType::END_OF_FILE) {
            throw "Expected EOF, got " + tokens.at(index)->ToString();
        }
    }
    catch(std::string &message) {
        std::cout << "Exception in Parse: " << message << std::endl;
    }
    catch(std::out_of_range &e) {
        std::cout << "Exception in Parse: Reached end of file early." << std::endl;
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
}

void Parser::ParseScheme() {
    try {
        if (tokens.at(index)->GetType() != TokenType::ID) {
            throw "Expected ID, got " + tokens.at(index)->ToString();
        }
        index++;

        if (tokens.at(index)->GetType() != TokenType::LEFT_PAREN) {
            throw "Expected LEFT_PAREN, got " + tokens.at(index)->ToString();
        }
        index++;

        if (tokens.at(index)->GetType() != TokenType::ID) {
            throw "Expected ID, got " + tokens.at(index)->ToString();
        }
        index++;

        if (FIRST("idList").count(tokens.at(index)->GetType())) {
            //idList -> COMMA ID idList
            ParseIDList();
        } else if (!FOLLOW("idList").count(tokens.at(index)->GetType())) {
            throw "Expected idList, got " + tokens.at(index)->ToString();
        }
        //idList -> lambda

        if (tokens.at(index)->GetType() != TokenType::RIGHT_PAREN) {
            throw "Expected RIGHT_PAREN, got " + tokens.at(index)->ToString();
        }
        index++;
    }
    catch (std::string &message) {
        std::cout << "Exception in ParseScheme():"  << message << std::endl;
    }
    catch (std::out_of_range &e) {
        std::cout << "Exception in ParseScheme(): Reached end of file early." << std::endl;
    }
}

void Parser::ParseSchemeList() {

}

void Parser::ParseFactList() {
    try {
        if (!FIRST("fact").count(tokens.at(index)->GetType())) {
            throw "Expected fact, got " + tokens.at(index)->ToString();
        }
        ParseFact();
        if (FIRST("factList").count(tokens.at(index)->GetType())) {
            ParseFactList();
        }
        else if (!FOLLOW("factList").count(tokens.at(index)->GetType())) {
            throw "Expected factList, got " + tokens.at(index)->ToString();
        }
    }
    catch (std::string &message) {
        std::cout << "Exception in ParseFactList(): " << message << std::endl;
    }
    catch (std::out_of_range &e) {
        std::cout << "Exception in ParseFactList(): Reached end of file prematurely." << std::endl;
    }
}

void Parser::ParseRuleList() {
    try {
        if (!FIRST("rule").count(tokens.at(index)->GetType())) {

        }
        ParseRule();

        if (FIRST("ruleList").count(tokens.at(index)->GetType())) {
            ParseRuleList();
        }
        else if (!FOLLOW("ruleList").count(tokens.at(index)->GetType())) {
            throw "Expected ruleList, got " + tokens.at(index)->ToString();
        }
    }
    catch (std::string &message) {
        std::cout << "Exception in ParseRuleList(): " << message << std::endl;
    }
    catch (std::out_of_range &e) {
        std::cout << "Exception in ParseRuleList(): Reached end of file prematurely." << std::endl;
    }
}

void Parser::ParseQuery() {
    try {
        if (!FIRST("predicate").count(tokens.at(index)->GetType())) {
            throw "Expected predicate, got " + tokens.at(index)->ToString();
        }
        ParsePredicate();

        if (tokens.at(index)->GetType() != TokenType::Q_MARK) {
            throw "Expected Q_MARK, got " + tokens.at(index)->ToString();
        }
        index++;
    }
    catch (std::string &message) {
        std::cout << "Exception in ParseQuery(): " << message << std::endl;
    }
    catch (std::out_of_range &e) {
        std::cout << "Exception in ParseQuery(): Reached end of file prematurely." << std::endl;
    }
}

void Parser::ParseQueryList() {

}

void Parser::ParseIDList() {
    try {
        if (tokens.at(index)->GetType() != TokenType::COMMA) {
            throw "Expected COMMA, got " + tokens.at(index)->ToString();
        }
        index++;

        if (tokens.at(index)->GetType() != TokenType::ID) {
            throw "Expected ID, got " + tokens.at(index)->ToString();
        }
        index++;

        if (FIRST("idList").count(tokens.at(index)->GetType())) {
            //idList -> COMMA ID idList
            ParseIDList();
        } else if (!FOLLOW("idList").count(tokens.at(index)->GetType())) {
            throw "Expected idList, got " + tokens.at(index)->ToString();
        }
        //idList -> lambda
    }
    catch (std::string &message) {
        std::cout << "Exception in ParseIDList(): " << message << std::endl;
    }
    catch (std::out_of_range &e) {
        std::cout << "Exception in ParseIDList(): Reached end of file prematurely." << std::endl;
    }
}

void Parser::ParseFact() {
    try {
        if (tokens.at(index)->GetType() != TokenType::ID) {
            throw "Expected ID, got " + tokens.at(index)->ToString();
        }
        index++;

        if (tokens.at(index)->GetType() != TokenType::LEFT_PAREN) {
            throw "Expected LEFT_PAREN, got " + tokens.at(index)->ToString();
        }
        index++;

        if (tokens.at(index)->GetType() != TokenType::STRING) {
            throw "Expected STRING, got " + tokens.at(index)->ToString();
        }
        index++;

        if (FIRST("stringList").count(tokens.at(index)->GetType())) {
            ParseStringList();
        }
        else if (!FOLLOW("stringList").count(tokens.at(index)->GetType())) {
            throw "Expected stringList, got " + tokens.at(index)->ToString();
        }

        if (tokens.at(index)->GetType() != TokenType::RIGHT_PAREN) {
            throw "Expected RIGHT_PAREN, got " + tokens.at(index)->ToString();
        }
        index++;

        if (tokens.at(index)->GetType() != TokenType::PERIOD) {
            throw "Expected PERIOD, got " + tokens.at(index)->ToString();
        }
        index++;
    }
    catch (std::string &message) {
        std::cout << "Exception in ParseFact(): " << message << std::endl;
    }
    catch (std::out_of_range &e) {
        std::cout << "Exception in ParseFact(): Reached end of file prematurely." << std::endl;
    }
}

void Parser::ParseStringList() {

}

void Parser::ParseRule() {
    try {
        if (!FIRST("headPredicate").count(tokens.at(index)->GetType())) {
            throw "Expected headPredicate, got " + tokens.at(index)->ToString();
        }
        ParseHeadPredicate();

        if (tokens.at(index)->GetType() != TokenType::COLON_DASH) {
            throw "Expected COLON_DASH, got " + tokens.at(index)->ToString();
        }
        index++;

        if (!FIRST("predicate").count(tokens.at(index)->GetType())) {
            throw "Expected predicate, got " + tokens.at(index)->ToString();
        }
        ParsePredicate();

        if (FIRST("predicateList").count(tokens.at(index)->GetType())) {
            ParsePredicateList();
        }
        else if (!FOLLOW("predicateList").count(tokens.at(index)->GetType())) {
            throw "Expected predicateList, got " + tokens.at(index)->ToString();
        }

        if (tokens.at(index)->GetType() != TokenType::PERIOD) {
            throw "Expected PERIOD, got " + tokens.at(index)->ToString();
        }
        index++;
    }
    catch (std::string &message) {
        std::cout << "Exception in ParseRule(): " << message << std::endl;
    }
    catch (std::out_of_range &e) {
        std::cout << "Exception in ParseRule(): Reached end of file prematurely." << std::endl;
    }
}

void Parser::ParseHeadPredicate() {
    try {
        if (tokens.at(index)->GetType() != TokenType::ID) {
            throw "Expected ID, got " + tokens.at(index)->ToString();
        }
        index++;

        if (tokens.at(index)->GetType() != TokenType::LEFT_PAREN) {
            throw "Expected LEFT_PAREN, got " + tokens.at(index)->ToString();
        }
        index++;

        if (tokens.at(index)->GetType() != TokenType::ID) {
            throw "Expected ID, got " + tokens.at(index)->ToString();
        }
        index++;

        if (FIRST("idList").count(tokens.at(index)->GetType())) {
            ParseIDList();
        }
        else if (!FOLLOW("idList").count(tokens.at(index)->GetType())) {
            throw "Expected idList, got " + tokens.at(index)->ToString();
        }

        if (tokens.at(index)->GetType() != TokenType::RIGHT_PAREN) {
            throw "Expected RIGHT_PAREN, got " + tokens.at(index)->ToString();
        }
        index++;
    }
    catch (std::string &message) {
        std::cout << "Exception in ParseHeadPredicate(): " << message << std::endl;
    }
    catch (std::out_of_range &e) {
        std::cout << "Exception in ParseHeadPredicate(): Reached end of file prematurely." << std::endl;
    }
}

void Parser::ParsePredicate() {
    try {
        if (tokens.at(index)->GetType() != TokenType::ID) {
            throw "Expected ID, got " + tokens.at(index)->ToString();
        }
        index++;

        if (tokens.at(index)->GetType() != TokenType::LEFT_PAREN) {
            throw "Expected LEFT_PAREN, got " + tokens.at(index)->ToString();
        }
        index++;

        if (!FIRST("parameter").count(tokens.at(index)->GetType())) {
            throw "Expected parameter, got " + tokens.at(index)->ToString();
        }
        ParseParameter();

        if (FIRST("parameterList").count(tokens.at(index)->GetType())) {
            ParseParameterList();
        }
        else if (!FOLLOW("parameterList").count(tokens.at(index)->GetType())) {
            throw "Expected parameterList, got " + tokens.at(index)->ToString();
        }

        if (tokens.at(index)->GetType() != TokenType::RIGHT_PAREN) {
            throw "Expected RIGHT_PAREN, got " + tokens.at(index)->ToString();
        }
        index++;
    }
    catch (std::string &message) {
        std::cout << "Exception in ParsePredicate(): " << message << std::endl;
    }
    catch (std::out_of_range &e) {
        std::cout << "Exception in ParsePredicate(): Reached end of file prematurely." << std::endl;
    }
}

void Parser::ParsePredicateList() {

}

void Parser::ParseParameter() {
    try {
        if (tokens.at(index)->GetType() != TokenType::STRING && tokens.at(index)->GetType() != TokenType::ID) {
            throw "Expected STRING or ID, got " + tokens.at(index)->ToString();
        }
        index++;
    }
    catch (std::string &message) {
        std::cout << "Exception in ParseParameter(): " << message << std::endl;
    }
    catch (std::out_of_range &e) {
        std::cout << "Exception in ParseParameter(): Reached end of file prematurely." << std::endl;
    }
}

void Parser::ParseParameterList() {

}
#pragma clang diagnostic pop