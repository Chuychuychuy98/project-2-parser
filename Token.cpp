#include "Token.h"

Token::Token(TokenType type, std::string description, int line) {
    this->type = type;
    this->description = description;
    this->line = line;
}

std::string Token::ToString() const {
    std::string typeString;
    switch (type) {
        case TokenType::COLON:
            typeString = "COLON";
            break;
        case TokenType::COLON_DASH:
            typeString = "COLON_DASH";
            break;
        case TokenType::COMMA:
            typeString = "COMMA";
            break;
        case TokenType::PERIOD:
            typeString = "PERIOD";
            break;
        case TokenType::Q_MARK:
            typeString = "Q_MARK";
            break;
        case TokenType::LEFT_PAREN:
            typeString = "LEFT_PAREN";
            break;
        case TokenType::RIGHT_PAREN:
            typeString = "RIGHT_PAREN";
            break;
        case TokenType::MULTIPLY:
            typeString = "MULTIPLY";
            break;
        case TokenType::ADD:
            typeString = "ADD";
            break;
        case TokenType::SCHEMES:
            typeString = "SCHEMES";
            break;
        case TokenType::FACTS:
            typeString = "FACTS";
            break;
        case TokenType::RULES:
            typeString = "RULES";
            break;
        case TokenType::QUERIES:
            typeString = "QUERIES";
            break;
        case TokenType::ID:
            typeString = "ID";
            break;
        case TokenType::STRING:
            typeString = "STRING";
            break;
        case TokenType::COMMENT:
            typeString = "COMMENT";
            break;
        case TokenType::END_OF_FILE:
            typeString = "EOF";
            break;
        case TokenType::UNDEFINED:
            typeString = "UNDEFINED";
            break;
    }
    return "(" + typeString +",\"" + description + "\"," + std::to_string(line) + ")\n";
}
