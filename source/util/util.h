//
// Created by root on 3/30/23.
//
#include <vector>
#include <string>
#include <cstdarg>
#ifndef TELEGRAM_MACRO_UTIL_H
#define TELEGRAM_MACRO_UTIL_H


class util {
public:

};
size_t write_to_string(void *contents, size_t size, size_t nmemb, std::string *s);
std::string format(const char *format, ...);
#endif //TELEGRAM_MACRO_UTIL_H
