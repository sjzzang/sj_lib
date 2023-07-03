//
// Created by root on 7/3/23.
//
#include "string"
#include "xthread.h"
#include "util.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#ifndef TELEGRAM_MACRO_NAVER_MACRO_H
#define TELEGRAM_MACRO_NAVER_MACRO_H
using namespace std;

class naver_macro : public xthread {
public:
    naver_macro();
    virtual ~naver_macro();

    int setIndex(int nIndex =1);

private:
    string member_id;
    string member_password;
    string naver_cid;
    string naver_csec;

    virtual int Proc();
    int get_ini(int nIndex);
};


#endif //TELEGRAM_MACRO_NAVER_MACRO_H
