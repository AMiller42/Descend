#include "lexer.hpp"

#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
    std::vector<Token> tokens { lex(argv[1]) };

    for (Token i : tokens)
        std::cout << i << " ";
    std::cout << '\n';

    return 0;
}
