//
// Created by root on 3/25/23.
//

#include <curl/curl.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <jsoncpp/json/json.h>
#include "xthread.h"
#include "util.h"
#include "naver_macro.h"
#include "cstring"

#ifndef UNTITLED_TELEGRAM_AGENT_H
#define UNTITLED_TELEGRAM_AGENT_H
#endif //UNTITLED_TELEGRAM_AGENT_H


typedef struct telegram_struct {
    string update_id;
    string chat_id;
    string text;

    telegram_struct() {

    }
} telegram_struct;



class telegram_agent : public xthread {
public:
    telegram_agent(std::string api_key, vector<string> chat_id, int update_id);
    virtual ~telegram_agent();

private:
    virtual int Proc();
    void set_ini();
private:
    std::string m_Api_key;
    vector<string> vChatId;
    CURL *m_get_curl = nullptr;
    CURL *m_send_curl = nullptr;
    struct curl_slist *m_get_headerlist = nullptr;
    struct curl_slist *m_send_headerlist = nullptr;

    thread member_macro_th;
    int update_id_;

    naver_macro* naverMacro;
private:
    std::string getApikey(){ return m_Api_key;}
    void initCurl();
    void sendMessage(std::string chatId, std::string text);
    void getMessage();
};



