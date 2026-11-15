/*
** EPITECH PROJECT, 2025
** c++
** File description:
** c++
*/

#include "Error.hpp"

char header[44] = {0};

bool is_Convert(const std::string &str)
{

    int j = 0;
    const char *ptr = str.c_str();
    for (int i = 0; ptr[i] != '\0'; i++) {
        if (ptr[i]>= '0' && ptr[i] <= '9')
            j++;
    }
    if (j != strlen(ptr))
        return false;
    return true;
}

bool is_Alpha(std::string str)
{
    const char *ptr = str.c_str();
    for (int i = 0; ptr[i] != '\0'; i++) {
        std::string ch = (ptr[i]+ "");
        if (!isalpha(ptr[i]) && ptr[i] != ' ' && is_Convert(ch))
            return false;
    }
    return true;
}
