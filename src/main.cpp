#include <cstdio>
#include <fstream>

#include "src/lexer/lexer.h"

int main() {
    std::ifstream fin("samples/basic.komei");
    Lexer lexer(fin);
}
