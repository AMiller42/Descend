#include "lexer.hpp"
#include "token.hpp"

#include <algorithm>
#include <string_view>
#include <vector>

using namespace std;

Lexer::Lexer(const char* str)
{
    code = str;
    nextChar = str;
}

inline int eol_offset(string_view str)
    { return min(str.find('\n')-1, str.size()-1); }

// Helpers for working with the tokens in the vector
inline Token* Lexer::thisToken()
    { return &tokenList.back(); }
inline void Lexer::newToken(TokenType type)
    { tokenList.push_back(Token{type}); }

/* =========================================================================
 * TODO: UPDATE THIS DESCRIPTION, IT IS VERY OUT OF DATE
 *
 *  We use a vector of Token objects to represent the program structure.
 *  The initial token defaults to text, otherwise starting plaintext would
 *  be unlexed. Depending on context, the intial token may be left blank.
 *  This is fine, as the parser will remove any blank tokens later on.
 *  Most tokens have data that describes the token's content, which will be
 *  used by the parser later on. Each lexing function returns a bool that
 *  indicates if it successfully lexed the associated token type.
 *
 *  Lexed example:
 *  This is *bold* text. This is _italic_ text. This is \*regular\* text.
 *  text("This is ") bold("bold") text(" text. This is ") italics("italic")
 *    text(" text. This is *regular* text.")
 * =========================================================================
 */
void Lexer::lex()
{
    bool eol { true };
    newToken(TokenType::text);
    while (*nextChar != '\0')
    {
        if (eol)
        {
            eol = false;
            switch (*nextChar)
            {
                // Tab or Space at the start of a line should still treat the
                // next char as the start of the line (allows for indentation)
                case '\t':
                    newToken(TokenType::tab);
                    eol = true;
                    break;
                case ' ':
                    newToken(TokenType::space);
                    eol = true;
                    break;
                case '#':
                    if (rules::is_header6(nextChar))
                    {
                        newToken(TokenType::header6);
                        if (nextChar[1] == '#')
                            nextChar += 5;
                        else nextChar++;
                    }
                    else if (rules::is_header5(nextChar))
                    {
                        newToken(TokenType::header5);
                        if (nextChar[1] == '#')
                            nextChar += 4;
                        else nextChar++;
                    }
                    else if (rules::is_header4(nextChar))
                    {
                        newToken(TokenType::header4);
                        if (nextChar[1] == '#')
                            nextChar += 3;
                        else nextChar++;
                    }
                    else if (rules::is_header3(nextChar))
                    {
                        newToken(TokenType::header3);
                        if (nextChar[1] == '#')
                            nextChar += 2;
                        else nextChar++;
                    }
                    else if (rules::is_header2(nextChar))
                    {
                        newToken(TokenType::header2);
                        nextChar++;
                    }
                    else if (rules::is_header1(nextChar))
                    {
                        newToken(TokenType::header1);
                        if (nextChar[1] == '1')
                            nextChar++;
                    }
                    break;
                case '*':
                case '+':
                    if (rules::is_listItem(nextChar))
                        newToken(TokenType::listItem);
                    else if (rules::is_thematicBreak)
                    {
                        newToken(TokenType::thematicBreak);
                        nextChar += eol_offset(nextChar);
                    }
                    break;
                case '=':
                    if (rules::is_thematicBreak(nextChar))
                    {
                        newToken(TokenType::thematicBreak);
                        nextChar += eol_offset(nextChar);
                    }
                    break;
                case '-':
                    if (rules::is_taskTrue(nextChar))
                    {
                        newToken(TokenType::taskTrue);
                        nextChar += 3;
                    }
                    else if (rules::is_taskFalse(nextChar))
                    {
                        newToken(TokenType::taskFalse);
                        nextChar += 2;
                    }
                    else if (rules::is_thematicBreak(nextChar))
                    {
                        newToken(TokenType::thematicBreak);
                        nextChar += eol_offset(nextChar);
                    }
                    else if (rules::is_listItem(nextChar))
                        newToken(TokenType::listItem);
                    break;
                case '.':
                    if (rules::is_listNumber(nextChar))
                        newToken(TokenType::listNumber);
                    break;
                case '`':
                    if (rules::is_codeBlock(nextChar))
                        newToken(TokenType::codeBlock);
                    break;
                case '~':
                    if (rules::is_thematicBreak(nextChar))
                    {
                        newToken(TokenType::thematicBreak);
                        nextChar += eol_offset(nextChar);
                    }
                    break;
                default:
                    // If none matched, lex the char again as inline
                    nextChar--;
            }
        }
        else
        {
            switch (*nextChar)
            {
                case '\\':
                    newToken(TokenType::escape);
                    break;
                case '\n':
                    newToken(TokenType::newline);
                    eol = true;
                    break;
                case '\t':
                    newToken(TokenType::tab);
                    break;
                case ' ':
                    newToken(TokenType::space);
                    break;
                case '!':
                    newToken(TokenType::subscript);
                    break;
                case '&':
                    newToken(TokenType::entityOpen);
                    break;
                case '(':
                    newToken(TokenType::parenthesisOpen);
                    break;
                case ')':
                    newToken(TokenType::parenthesisClose);
                    break;
                case '*':
                    newToken(TokenType::bold);
                    break;
                case ':':
                    newToken(TokenType::shortcode);
                    break;
                case ';':
                    newToken(TokenType::entityClose);
                    break;
                case '<':
                    newToken(TokenType::angleOpen);
                    break;
                case '=':
                    newToken(TokenType::highlight);
                    break;
                case '>':
                    newToken(TokenType::angleClose);
                    break;
                case '@':
                    newToken(TokenType::elementId);
                    break;
                case '[':
                    newToken(TokenType::squareOpen);
                    break;
                case ']':
                    newToken(TokenType::squareClose);
                    break;
                case '^':
                    newToken(TokenType::superscript);
                    break;
                case '_':
                    newToken(TokenType::italics);
                    break;
                case '`':
                    newToken(TokenType::code);
                    break;
                case '{':
                    newToken(TokenType::curlyOpen);
                    break;
                case '|':
                    newToken(TokenType::tableCell);
                    break;
                case '}':
                    newToken(TokenType::curlyClose);
                    break;
                case '~':
                    newToken(TokenType::strikethrough);
                    break;
                default:
                    if (thisToken()->type != TokenType::text)
                        newToken(TokenType::text);
                    thisToken()->data += *nextChar;
            }
        }
        ++nextChar;
    }
}

namespace rules
{
    // Helpers
    inline bool is_whitespace(char c)
        { return c == '\t' || c == '\n' || c == ' '; }
    inline int eol_offset(std::string_view str)
        { return std::min(str.find('\n')-1, str.size()-1); }
    inline char peek(const char* str)
        { return str[1]; }
    inline std::string_view peek(std::string_view str, int peek)
        { return str.substr(1,peek); }

    // Not all tokens need a rule for parsing
    #define NO_RULE {return true;}

    inline bool is_angleOpen(const char* c)           NO_RULE
    inline bool is_angleClose(const char* c)          NO_RULE
    inline bool is_curlyOpen(const char* c)           NO_RULE
    inline bool is_curlyClose(const char* c)          NO_RULE
    inline bool is_entityOpen(const char* c)          NO_RULE
    inline bool is_entityClose(const char* c)         NO_RULE
    inline bool is_parenthesisOpen(const char* c)     NO_RULE
    inline bool is_parenthesisClose(const char* c)    NO_RULE
    inline bool is_squareOpen(const char* c)          NO_RULE
    inline bool is_squareClose(const char* c)         NO_RULE

    inline bool is_bold(const char* c)                NO_RULE
    inline bool is_code(const char* c)                NO_RULE
    inline bool is_codeBlock(const char* c)
    {
        return peek(c, eol_offset(c))
                == std::string(eol_offset(c), *c);
    }
    inline bool is_highlight(const char* c)           NO_RULE
    inline bool is_italics(const char* c)             NO_RULE
    inline bool is_shortcode(const char* c)           NO_RULE
    inline bool is_strikethrough(const char* c)       NO_RULE
    inline bool is_subscript(const char* c)           NO_RULE
    inline bool is_superscript(const char* c)         NO_RULE

    inline bool is_elementId(const char* c)
    {
        return peek(c) != '@'
            && !is_whitespace(peek(c));
    }
    inline bool is_header1(const char* c)
    {
        return peek(c) != '#';
    }
    inline bool is_header2(const char* c)
    {
        return (peek(c) == '#'
            || peek(c) == '2');
    }
    inline bool is_header3(const char* c)
    {
        return (peek(c, 2) == "##"
            || peek(c) == '3');
    }
    inline bool is_header4(const char* c)
    {
        return (peek(c, 3) == "###"
            || peek(c) == '4');
    }
    inline bool is_header5(const char* c)
    {
        return (peek(c, 4) == "####"
            || peek(c) == '5');
    }
    inline bool is_header6(const char* c)
    {
        return (peek(c, 5) == "#####"
            || peek(c) == '6');
    }
    inline bool is_listItem(const char* c)
    {
        return !is_whitespace(peek(c))
            && peek(c) != *c;
    }
    inline bool is_listNumber(const char* c)
    {
        return !is_whitespace(peek(c))
            && peek(c) != *c;
    }
    inline bool is_taskTrue(const char* c)
    {
        return peek(c, 3) == "[X]";
    }
    inline bool is_taskFalse(const char* c)
    {
        return peek(c, 2) == "[]";
    }
    inline bool is_tableCell(const char* c)           NO_RULE
    inline bool is_thematicBreak(const char* c)
    {
        return peek(c, eol_offset(c))
                == std::string(eol_offset(c), *c);
    }
}
