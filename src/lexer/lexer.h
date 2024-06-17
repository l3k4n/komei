#ifndef LEXER_H
#define LEXER_H

#include <fstream>

#include "src/tokens/tokens.h"

class Lexer {
    std::ifstream& m_fin;

    Token scan_identifier_or_keyword();
    Token scan_number();
    Token scan_string();
    void consume_whitespace();

public:
    Lexer(std::ifstream& fin);
    Token read();
    bool eof();
};

#endif
