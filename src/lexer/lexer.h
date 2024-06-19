#ifndef LEXER_H
#define LEXER_H

#include <fstream>
#include <memory>

#include "src/tokens/tokens.h"

class Lexer {
    std::ifstream& m_fin;
    std::unique_ptr<Token> m_peeked;

    Token scan_identifier_or_keyword();
    Token scan_number();
    Token scan_string();
    void consume_whitespace();
    Token read();

public:
    Lexer(std::ifstream& fin);
    Token next();
    Token& peek();
    bool eof();
};

#endif
