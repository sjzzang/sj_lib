#include "telegram_agent.h"

// 텔레그램 API 키
using namespace std;
telegram_agent::telegram_agent(std::string api_key, std::string chat_id){
    m_Api_key = api_key;
    m_Chat_id = chat_id;

    initCurl();
    //sendMessage(chat_id, "Agent_ON");
}
telegram_agent::~telegram_agent(){
    Stop();
}

void telegram_agent::initCurl()
{
    //for Message Get Curl
    m_get_headerlist = curl_slist_append(m_get_headerlist, "Content-Type:application/json");


    m_get_curl =curl_easy_init();
    m_send_curl = curl_easy_init();

    //curl_easy_setopt(m_get_curl, CURLOPT_HTTPHEADER, m_get_curl);

    curl_easy_setopt(m_get_curl, CURLOPT_TIMEOUT, 1);
    curl_easy_setopt(m_get_curl, CURLOPT_ENCODING, "UTF-8");

    //curl_easy_setopt(m_send_curl, CURLOPT_HTTPHEADER, m_get_curl);
    curl_easy_setopt(m_send_curl, CURLOPT_TIMEOUT, 1);
    curl_easy_setopt(m_send_curl, CURLOPT_ENCODING, "UTF-8");

}

void telegram_agent::sendMessage(std::string chatId, std::string text) {

    std::string url = "https://api.telegram.org/bot" + getApikey() + "/sendMessage?chat_id=" + chatId + "&text=" + text;
    std::string data;
    cout<<url<<endl;

    if (m_send_curl) {
        curl_easy_setopt(m_send_curl, CURLOPT_URL, url.c_str());
        //curl_easy_setopt(m_send_curl, CURLOPT_WRITEDATA, &data);

        CURLcode rc =   curl_easy_perform(m_send_curl);
 //       curl_easy_cleanup(m_send_curl);
    }
}
void telegram_agent::getMessage()
{
    cout<<"Come"<<endl;
    std::string data;
    std::string strGet_url = "https://api.telegram.org/bot" + getApikey() + "/getUpdates";
    curl_easy_setopt(m_get_curl, CURLOPT_WRITEFUNCTION, write_to_string);
    curl_easy_setopt(m_get_curl, CURLOPT_WRITEDATA, &data);
    curl_easy_setopt(m_get_curl, CURLOPT_URL, strGet_url.c_str());
    int rc = curl_easy_perform(m_get_curl);
    //curl_easy_cleanup(m_get_curl);
    if (rc != CURLE_OK) {
        cout<<"CURL FAILD"<<endl;
        return;
    }

    long http_code = 0;
    curl_easy_getinfo(m_get_curl, CURLINFO_RESPONSE_CODE, &http_code);
    if (http_code != 200) {
        cout<<"CURL FAILD"<<endl;
        return;
    }

    cout<<data<<endl;
    /*Json::Reader reader;
    Json::Value root;
    bool parsingRet = reader.parse(out, root);
    if (!parsingRet) {
        Log(ERROR_LOG_LEVEL, "[fence_manager] Send fence data fail.[parse:%s]", reader.getFormattedErrorMessages().c_str());
        return;
    }
*/
}
int telegram_agent::Proc(){

    sendMessage(m_Chat_id,"proc");
    getMessage();

    return 0;
}

