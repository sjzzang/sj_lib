//
// Created by root on 3/30/23.
//

#include "util.h"
size_t write_to_string(void *contents, size_t size, size_t nmemb, std::string *s) {
    size_t newLength = size * nmemb;
    size_t oldLength = s->size();
    try {
        s->resize(oldLength + newLength);
    }
    catch(std::bad_alloc &e) {
        return 0;
    }
    std::copy((char *)contents, (char *)contents+newLength, s->begin() + oldLength);
    return size * nmemb;
}