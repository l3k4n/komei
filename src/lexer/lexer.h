#include <fstream>

#include "src/tokens/tokens.h"

class Lexer {
    std::ifstream& m_fin;

    Token read_identifier();
    Token read_number();
    Token read_string();
    void consume_whitespace();

public:
    Lexer(std::ifstream& fin);
    Token read();
    bool eof();
};
