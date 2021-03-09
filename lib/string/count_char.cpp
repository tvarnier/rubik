#include "lib.hpp"

int     lib::count_char(char const *str, char c)
{
    int     i{-1};
    int     count{0};

    while(str[++i])
        if (str[i] == c)
            count++;
    return (count);
}