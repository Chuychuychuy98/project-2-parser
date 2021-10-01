#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include "Automaton.h"
#include "Token.h"

class Lexer
{
private:
    std::vector<Automaton*> automata;
    std::vector<Token*> tokens;

    void CreateAutomata();

public:
    Lexer();
    ~Lexer();
    std::vector<Token*> GetTokens() const { return tokens; }

    void Run(std::string& input);

};

#endif // LEXER_H

