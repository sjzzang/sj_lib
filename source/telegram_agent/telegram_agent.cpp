#include "telegram_agent.h"

// 텔레그램 API 키

telegram_agent::telegram_agent(std::string api_key, std::string chat_id){
    //m_Api_key = api_key;
    //m_Chat_id = chat_id;

    //sendMessage(m_Api_key, m_Chat_id);
}
telegram_agent::~telegram_agent(){

}

void telegram_agent::sendMessage(std::string chatId, std::string text) {

    std::string url = "https://api.telegram.org/bot" + getApikey() + "/sendMessage?chat_id=" + chatId + "&text=" + text;
    /*CURL *curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }*/
}
// 텔레그램 봇 메시지 전송 함수

