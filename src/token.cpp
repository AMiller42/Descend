#include "token.hpp"

#include <iostream>
#include <string_view>

std::ostream& operator<< (std::ostream& os, const Token& tkn)
{
    std::string_view sv { tkn.data };
    if ((char)tkn.type == '\0')
        return os << "(" << sv << ")";
    else
        return os << (char)tkn.type;
}
