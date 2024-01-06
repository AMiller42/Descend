#ifndef _TOKEN_H
#define _TOKEN_H

#include <iostream>
#include <string>

enum class TokenType : char
{
    // Asymmetrical Delimited
    angleOpen           = '<',
    angleClose          = '>',
    curlyOpen           = '{',
    curlyClose          = '}',
    entityOpen          = '&',
    entityClose         = ';',
    parenthesisOpen     = '(',
    parenthesisClose    = ')',
    squareOpen          = '[',
    squareClose         = ']',

    // Symmetrical Delimited
    bold                = '*',
    code                = '`',
    codeBlock           = '$',
    highlight           = '=',
    italics             = '_',
    shortcode           = ':',
    strikethrough       = '~',
    subscript           = '!',
    superscript         = '^',

    // Newline Delimited
    elementId           = '@',
    header1             = '1',
    header2             = '2',
    header3             = '3',
    header4             = '4',
    header5             = '5',
    header6             = '6',
    listItem            = '+',
    listNumber          = '.',
    taskTrue            = 'T',
    taskFalse           = 'F',
    tableCell           = '|',
    thematicBreak       = '-',

    // Not Delimited
    escape              = '\\',
    newline             = '\n',
    space               = ' ',
    tab                 = '\t',
    text                = '\0' // Default, plain ol' text
};

class Token
{
    public:
        TokenType type;
        std::string data {};

        Token(TokenType t) : type(t) {};

        friend std::ostream& operator<< (std::ostream& os, const Token&);
};

#endif
