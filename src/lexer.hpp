#ifndef _LEXER_H
#define _LEXER_H

#include "token.hpp"

#include <string_view>
#include <vector>

class Lexer
{
    private:
        std::vector<Token> tokenList {};
        std::string_view code;
        const char* nextChar;

        Token* thisToken();
        void newToken(TokenType type);

    public:
        Lexer(const char* str);

        void lex();

        std::vector<Token> getTokens() const { return tokenList; }
};

namespace rules
{
    inline bool is_angleOpen(const char* c);
    inline bool is_angleClose(const char* c);
    inline bool is_curlyOpen(const char* c);
    inline bool is_curlyClose(const char* c);
    inline bool is_entityOpen(const char* c);
    inline bool is_entityClose(const char* c);
    inline bool is_parenthesisOpen(const char* c);
    inline bool is_parenthesisClose(const char* c);
    inline bool is_squareOpen(const char* c);
    inline bool is_squareClose(const char* c);

    inline bool is_bold(const char* c);
    inline bool is_code(const char* c);
    inline bool is_codeBlock(const char* c);
    inline bool is_highlight(const char* c);
    inline bool is_italics(const char* c);
    inline bool is_shortcode(const char* c);
    inline bool is_strikethrough(const char* c);
    inline bool is_subscript(const char* c);
    inline bool is_superscript(const char* c);

    inline bool is_elementId(const char* c);
    inline bool is_header1(const char* c);
    inline bool is_header2(const char* c);
    inline bool is_header3(const char* c);
    inline bool is_header4(const char* c);
    inline bool is_header5(const char* c);
    inline bool is_header6(const char* c);
    inline bool is_listItem(const char* c);
    inline bool is_listNumber(const char* c);
    inline bool is_taskTrue(const char* c);
    inline bool is_taskFalse(const char* c);
    inline bool is_tableCell(const char* c);
    inline bool is_thematicBreak(const char* c);
}

#endif
