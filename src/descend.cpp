#include "lexer.hpp"
#include "token.hpp"

#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
    std::ifstream in { argv[1] };
    std::string contents { (std::istreambuf_iterator<char>(in)),
        std::istreambuf_iterator<char>() };
    contents.erase(
            std::remove(contents.begin(), contents.end(), '\r'),
            contents.end()
        );
    Lexer lexer { contents.c_str() };
    lexer.lex();

    for (Token t : lexer.getTokens())
        std::cout << t;
    std::cout << '\n';

    return 0;
}
