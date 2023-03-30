//
// Created by root on 3/25/23.
//

#include <curl/curl.h>
#include <jsoncpp/json/json.h>
#include "xthread.h"
#include "util.h"

#ifndef UNTITLED_TELEGRAM_AGENT_H
#define UNTITLED_TELEGRAM_AGENT_H
#endif //UNTITLED_TELEGRAM_AGENT_H

class telegram_agent : public xthread {
public:
    telegram_agent(std::string api_key, std::string chat_id);
    virtual ~telegram_agent();

private:
    virtual int Proc();

private:
    std::string m_Api_key;
    std::string m_Chat_id;
    CURL *m_get_curl = nullptr;
    CURL *m_send_curl = nullptr;
    struct curl_slist *m_get_headerlist = nullptr;
    struct curl_slist *m_send_headerlist = nullptr;
private:
    std::string getApikey(){ return m_Api_key;}
    void initCurl();
    void sendMessage(std::string chatId, std::string text);
    void getMessage();
};



