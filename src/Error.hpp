/*
** EPITECH PROJECT, 2025
** Error
** File description:
** Class header
*/

#ifndef _ERROR_HPP_
#define _ERROR_HPP_

#include <string>
#include <ostream>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <exception>
#include "dft.hpp"

class Error: public std::exception
{
    private:
    std::string message;
    public:
    Error(const std::string &mess) : message(mess) {}
    const char* what() const throw () {
        return message.c_str();
    }
    Error() = default;
    ~Error() = default;
};


bool is_AlphanumericOrSpace(const std::string &str);
bool is_Convert(const std::string &str);
bool is_Alpha(std::string str);

#endif
