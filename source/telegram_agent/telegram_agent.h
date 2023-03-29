//
// Created by root on 3/25/23.
//

#ifndef UNTITLED_TELEGRAM_AGENT_H
#define UNTITLED_TELEGRAM_AGENT_H

#include <curl/curl.h>
#include <jsoncpp/json/json.h>
#include "xthread.h"

class telegram_agent {

public:
    telegram_agent(std::string api_key, std::string chat_id);
    virtual ~telegram_agent();

    static void sendMessage(std::string chatId, std::string text);
private:
    static std::string m_Api_key;
    static std::string m_Chat_id;

    static std::string getApikey(){ return m_Api_key;}
};


#endif //UNTITLED_TELEGRAM_AGENT_H
