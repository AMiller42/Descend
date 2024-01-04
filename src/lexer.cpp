#include "lexer.hpp"

#include <string_view>
#include <vector>

using namespace std;

inline bool is_whitespace(string_view str)
    { char c = str.front(); return c == '\t' || c == '\n' || c == ' '; }
inline string_view peek(string_view str, int peek = 1)
    { return str.substr(1,1); }
inline string_view back(char* str)
    { return string_view{&str[-1]}; }

/* =============================================================================
 *  We use a vector of Token objects to represent the program structure.
 *  The initial token defaults to text, otherwise starting plaintext would
 *  remain unlexed. Depending on context, the intial token may be left blank.
 *  This is fine, as the parser will remove any blank tokens later on.
 *  Most tokens have data that describes the token's content, which will be
 *  used by the parser later on.
 *
 *  Lexed example:
 *  This is *bold* text. This is _italic_ text. This is \*regular\* text.
 *  text("This is ") bold("bold") text(" text. This is ") italics("italic")
 *    text(" text. This is *regular* text.")
 * =============================================================================
 */
vector<Token> lex(char* str)
{
    int pos { 0 };
    vector<Token> tknList {};
    auto thisToken = [&] { return &tknList.back(); };
    auto newToken = [&] (TokenType type) { tknList.push_back(Token{type}); };
    
    newToken(TokenType::text);
    while (str[pos] != '\0')
    {
        switch (str[pos])
        {
            case '\\':
                thisToken()->data += str[++pos];
                break;
            case '*':
                if (thisToken()->type != TokenType::bold)
                {
                    if (peek(&str[pos], 3) == "**\n")
                    {
                        newToken(TokenType::thematicBreak);
                        pos += 3;
                        newToken(TokenType::text);
                    }
                    else if (!is_whitespace(peek(&str[pos])))
                        newToken(TokenType::bold);
                    else
                        thisToken()->data += str[pos];
                }
                else
                {
                    if (is_whitespace(back(&str[pos])))
                        thisToken()->data += str[pos];
                    else
                        newToken(TokenType::text);
                }
                break;
            case '_':
                if (thisToken()->type != TokenType::italics)
                {
                    if (!is_whitespace(peek(&str[pos])))
                        newToken(TokenType::italics);
                    else
                        thisToken()->data += str[pos];
                }
                else
                {
                    if (is_whitespace(back(&str[pos])))
                        thisToken()->data += str[pos];
                    else
                        newToken(TokenType::text);
                }
                break;
            default:
                thisToken()->data += str[pos];
        }
        ++pos;
    }
    return tknList;
}

std::ostream& operator<< (std::ostream& os, const Token& tkn)
{
    std::string_view sv { tkn.data };
    if (tkn.size > 0)
        sv = sv.substr(0, tkn.size);
    switch (tkn.type)
    {
        case TokenType::bold:
            return os << "bold(\"" << sv << "\")";
        case TokenType::italics:
            return os << "italics(\"" << sv << "\")";
        case TokenType::thematicBreak:
            return os << "thematicBreak()";
        default:
            return os << "text(\"" << sv << "\")";
    }
}
