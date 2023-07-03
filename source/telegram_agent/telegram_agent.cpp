#include "telegram_agent.h"

// 텔레그램 API 키
using namespace std;
telegram_agent::telegram_agent(std::string api_key, vector<string> chat_id, int update_id =0){
    m_Api_key = api_key;
    vChatId = chat_id;
    update_id_ = update_id;

    initCurl();

    naverMacro = new naver_macro();
    naverMacro->setIndex(1);
    naverMacro->SetCPS(1/30);
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
    vector<telegram_struct> vStruct;
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "offset: 101");
    std::string strData;
    std::string strGet_url = "https://api.telegram.org/bot" + getApikey() + "/getUpdates" + "?offset=" + to_string(update_id_+1);
    curl_easy_setopt(m_get_curl, CURLOPT_WRITEFUNCTION, util::write_to_string);
    curl_easy_setopt(m_get_curl, CURLOPT_WRITEDATA, &strData);
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

    cout<<strData<<endl;
    Json::Reader reader;
    Json::Value root;
    std::string strMessage;
    bool parsingRet = reader.parse(strData, root);
    if (!parsingRet) {
        cout<<util::format("[telegram_agent] Can't parse data.[parse:%s]", reader.getFormattedErrorMessages().c_str())<<endl;
        return;
    }

    Json::Value &data = root["ok"];

    if(data.asString().compare("true")==0)
    {
        Json::Value &array = root["result"];
        int array_size = array.size();
        for(int i =0; i<array_size; i++)
        {
            Json::Value &result = array[i];
            int temp_update_id = result["update_id"].asInt();
            if(temp_update_id <= update_id_)
                break;
            else
            {
                update_id_ = temp_update_id;
                string id = result["message"]["chat"]["id"].asString();

                for(auto it = vChatId.begin(); it != vChatId.end(); it++)
                {
                    if(*it != id) continue;

                    telegram_struct temp;
                    temp.update_id = temp_update_id;
                    temp.chat_id = *it;
                    temp.text = util::unicode_to_utf8(result["message"]["text"].asString());

                    vStruct.insert(vStruct.begin(), temp);
                }
            }
            set_ini();
        }
        for(auto it = vStruct.begin(); it !=vStruct.end(); it++)
        {
            if(strcmp(it->text.c_str(), "start")==0)
            {
                naverMacro->Start(nullptr);
                //Macro Start
            }
            else if(strcmp(it->text.c_str(), "end")==0)
            {
                naverMacro->Stop();
                //Macro End
            }
            else if(strcmp(it->text.substr(0,6).c_str(), "header")==0)
            {
                int a=1;
                //naver_macro->setHeader();
                //Macro Header set
            }
            else if(strcmp(it->text.substr(0,3).c_str(), "men")==0)
            {
                //Macro Member Change
            }
            else if(strcmp(it->text.substr(0,5).c_str(), "women")==0)
            {
                //Macro Member Change
            }
        }
    }
}
int telegram_agent::Proc(){

    //sendMessage(m_Chat_id,"proc");
    getMessage();

    return 0;
}

void telegram_agent::set_ini()
{
    std::string f( "/settings/config.ini" );
    boost::property_tree::ptree write_pt;
    string strchatId;
    for(auto it = vChatId.begin(); it!=vChatId.end(); it++)
    {
        strchatId += *it;
        strchatId += "|";
    }
    strchatId.erase(strchatId.length()-1,1);
    write_pt.put("TELEGRAM.API_KEY", m_Api_key);
    write_pt.put("TELEGRAM.CHAT_ID", strchatId);
    write_pt.put("TELEGRAM.UPDATE_ID",update_id_);
    boost::property_tree::write_ini(f, write_pt);
}
