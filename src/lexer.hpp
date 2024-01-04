#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <string>
#include <string_view>
#include <vector>

enum class TokenType
{
    // Asymmetrical Delimited
    openAngle,
    closeAngle,
    openCurly,
    closeCurly,
    openParenthesis,
    closeParenthesis,
    openSquare,
    closeSquare,
    openAmpersand,
    closeSemicolon,

    // Symmetrical Delimited
    bold,
    code,
    highlight,
    italics,
    shortcode,
    strikethrough,
    subscript,
    superscript,

    // Newline Delimited
    elementId,
    header,
    listItem,
    listNumber,
    taskTrue,
    taskFalse,
    defKey,
    defValue,
    tableHeader,
    tableSeparator,
    tableRow,
    thematicBreak,

    // Not Delimited
    newline,
    space,
    tab,
    text // Default, plain ol' text
};

struct Token
{
    TokenType type {};
    std::string data {};
    int size {};

    public:
        friend std::ostream& operator<< (std::ostream& os, const Token&);
};

std::vector<Token> lex(char* str);

#endif
