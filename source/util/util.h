//
// Created by root on 3/30/23.
//
#include <vector>
#include <string>
#include <cstdarg>
#include <sstream>
#include <unicode/unistr.h>
#ifndef TELEGRAM_MACRO_UTIL_H
#define TELEGRAM_MACRO_UTIL_H


class util {
public:
    static size_t write_to_string(void *contents, size_t size, size_t nmemb, std::string *s);
    static std::string format(const char *format, ...);
    static std::vector<std::string> split(std::string input, char delimiter);
    static std::string unicode_to_utf8(std::string unicode_string);
};

#endif //TELEGRAM_MACRO_UTIL_H
