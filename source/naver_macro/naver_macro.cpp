//
// Created by root on 7/3/23.
//

#include "naver_macro.h"
using namespace std;
naver_macro::naver_macro(){

}
naver_macro::~naver_macro(){
    Stop();
}


int naver_macro::Proc(){

    return 0;
}
int naver_macro::setIndex(int nIndex)
{
    return get_ini(nIndex);
}

int naver_macro::get_ini(int nIndex)
{
    int nReturn = 0;
    try{
        std::string f( "/settings/config.ini" );
        boost::property_tree::ptree read_pt;
        member_id=read_pt.get<std::string>(util::format("NAVER%d.NAVER_ID",nIndex));
        member_password=read_pt.get<std::string>(util::format("NAVER%d.NAVER_PW",nIndex));
        naver_cid=read_pt.get<std::string>(util::format("NAVER%d.NAVER_PW",nIndex));
        naver_csec=read_pt.get<std::string>(util::format("NAVER%d.NAVER_PW",nIndex));
        nReturn = nIndex;
    }
    catch (exception e)
    {

    }
    return nReturn;
}


