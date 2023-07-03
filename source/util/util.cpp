//
// Created by root on 3/30/23.
//

#include "util.h"
using namespace std;

size_t util::write_to_string(void *contents, size_t size, size_t nmemb, std::string *s) {
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

string util::format(const char *format, ...)
{
    char logstr[1024] = {0, };
    va_list ap;
    va_start(ap, format);
    vsnprintf(logstr, sizeof(logstr), format, ap);
    va_end(ap);
    std::string strReturn(logstr);
    return strReturn;
}

vector<string> util::split(string input, char delimiter) {
    std::vector<std::string> answer;
    std::stringstream ss(input);
    std::string temp;

    while (getline(ss, temp, delimiter)) {
        answer.push_back(temp);
    }

    return answer;
}

std::string util::unicode_to_utf8(std::string unicode_string)
{
    icu::UnicodeString unicodeString = icu::UnicodeString::fromUTF8(unicode_string);

    // UTF-16 문자열을 UTF-8로 변환
    std::string utf8Str;
    unicodeString.toUTF8String(utf8Str);

    return utf8Str;
}