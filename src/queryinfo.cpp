#define CPPHTTPLIB_OPENSSL_SUPPORT
#define CPPHTTPLIB_ZLIB_SUPPORT

#include "httplib.h"
#include "json.hpp"
#include <string>

using json = nlohmann::json;
using namespace std;


int getunreadmessage(string ticket);
string getstudentname(string ticket);
string getmailmessage(string ticket);
int getexamall(string ticket, string weu);
int getexamarranged(string ticket, string weu);


httplib::Headers headers = {
  {"Accept", "application/json, text/plain, */*"},
  {"Accept-Encoding", "gzip, deflate"},
  {"Connection", "close"},
  {"Content-Type", "application/json"},
  {"Host", "ehall.nnu.edu.cn"},
  {"User-Agent", "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/17.0 Safari/605.1.15"},
  {"Referer", "https://ehall.nnu.edu.cn/ywtb-portal/standard/index.html"},
  {"Accept-Language", "zh-CN,zh-Hans;q=0.9"},
  {"X-Requested-With", "XMLHttpRequest"},
  {"Sec-Fetch-Dest", "empty"},
  {"Sec-Fetch-Mode", "cors"},
  {"Sec-Fetch-Site", "same-origin"},
  {"Sec-Ch-Ua", "\"Chromium\";v=\"119\", \"Not?A_Brand\";v=\"24\""},
  {"User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/119.0.6045.159 Safari/537.36"}
};

httplib::Headers headersapp = {
  {"Accept", "application/json, text/javascript, */*; q=0.01"},
  {"Accept-Encoding", "gzip, deflate, br"},
  {"Accept-Language", "zh-CN,zh-Hans;q=0.9"},
  {"Host", "ehallapp.nnu.edu.cn"},
  {"Connection", "close"},
  {"Origin", "https://ehallapp.nnu.edu.cn"},
  {"User-Agent", "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/17.0 Safari/605.1.15"},
  {"Referer", "https://ehallapp.nnu.edu.cn/jwapp/sys/studentWdksapApp/*default/index.do?t_s=1700753954664&amp_sec_version_=1&gid_=WGhYYWREa2ZBczZBZnNrdTF2aEhma2lWbnlnd1IxT21ubUpoaWtZeHdKVmZlQUVKalQrSzBmUm5NQ1FPUkR1ditON1E5SFc4dTV1cEF6aW1UamRCSFE9PQ&EMAP_LANG=zh&THEME=teal"},
  {"Accept-Language", "zh-CN,zh-Hans;q=0.9"},
{"Priority", "u=1, i"},
{"Sec-Fetch-Dest", "empty"},
{"Sec-Fetch-Mode", "cors"},
{"Sec-Fetch-Site", "same-origin"},
{"Sec-Ch-Ua", "\"Chromium\";v=\"119\", \"Not?A_Brand\";v=\"24\""},
{"Sec-Ch-Ua-Mobile", "?0"},
{"Sec-Ch-Ua-Platform", "\"macOS\""},
  {"X-Requested-With", "XMLHttpRequest"}
};



int getunreadmessage(string ticket){
  //Cookie: route=34e12749345e5a1ad7cc6d0324fa3b1c; JSESSIONID=rOv77UsOCI-c0QrfjDs4dj71VP9wieuAoSHcEfBzedJaql6LejLF!-1803388596; amp.locale=zh_CN; MOD_AUTH_CAS=MOD_AUTH_ST-21803-ACbgeAofbuNmB95YLckhthR8u8Eids7authserver1; asessionid=9b7b1f8c-a17e-4a82-ac48-586362fc9117
  headers.emplace("Cookie", "route=34e12749345e5a1ad7cc6d0324fa3b1c; JSESSIONID=rOv77UsOCI-c0QrfjDs4dj71VP9wieuAoSHcEfBzedJaql6LejLF!-1803388596; amp.locale=zh_CN; MOD_AUTH_CAS=MOD_AUTH_"+ticket+"; asessionid=9b7b1f8c-a17e-4a82-ac48-586362fc9117");
httplib::Client cli("https://ehall.nnu.edu.cn");
  auto res = cli.Get("/jsonp/ywtb/getUnreadMessageCount", headers);
  json j = json::parse(res->body);
  return j["data"]["totalSize"];
}

string getstudentname(string ticket){
  headers.emplace("Cookie", "route=34e12749345e5a1ad7cc6d0324fa3b1c; JSESSIONID=rOv77UsOCI-c0QrfjDs4dj71VP9wieuAoSHcEfBzedJaql6LejLF!-1803388596; amp.locale=zh_CN; MOD_AUTH_CAS=MOD_AUTH_"+ticket+"; asessionid=9b7b1f8c-a17e-4a82-ac48-586362fc9117");
  httplib::Client cli("https://ehall.nnu.edu.cn");
  auto res = cli.Get("/jsonp/ywtb/info/getUserInfoAndSchoolInfo", headers);
  json j = json::parse(res->body);
  return j["data"]["userName"];
}


string getmailmessage(string ticket){
  headers.emplace("Cookie", "route=34e12749345e5a1ad7cc6d0324fa3b1c; JSESSIONID=rOv77UsOCI-c0QrfjDs4dj71VP9wieuAoSHcEfBzedJaql6LejLF!-1803388596; amp.locale=zh_CN; MOD_AUTH_CAS=MOD_AUTH_"+ticket+"; asessionid=9b7b1f8c-a17e-4a82-ac48-586362fc9117");
  httplib::Client cli("https://ehall.nnu.edu.cn");
  auto res = cli.Get("/jsonp/ywtb/card/getViewDataDetail?wid=cd02610dafaf42cb8f6da5632c317669", headers);
  json j = json::parse(res->body);
  return j["data"][0]["imptInfo"];
}

int getexamall(string ticket, string weu){
  //Cookie: EMAP_LANG=zh; THEME=teal; _WEU=bddmyN6TbRF9KGJpXMgZB4Fcdac2Gn387AUMLmWa4FXOcfQ8Tk5rvyiQb9_NTk4iwg5PkJy5f2KZG0Aksq6kvXddMwSXzMy0S4VEDQfQ2Awkk8wXH2G9lo..; JSESSIONID=6F1B2EA14F85DCC7695B45FCB5B15053; MOD_AUTH_CAS=MOD_AUTH_ST-21806-a1p-wXA-Db3Jaxdp6w7hQqqHLXIids7authserver1; route=160cbea5c41d2df27b3fe53ecacb10e9
  headersapp.emplace("Cookie", "EMAP_LANG=zh; THEME=teal; _WEU="+weu+"; JSESSIONID=6F1B2EA14F85DCC7695B45FCB5B15053; MOD_AUTH_CAS=MOD_AUTH_"+ticket+"; route=160cbea5c41d2df27b3fe53ecacb10e9");
  httplib::Client cli("https://ehallapp.nnu.edu.cn");
  auto res = cli.Post("/jwapp/sys/studentWdksapApp/modules/wdksap/cxyxkwapkwdkc.do", headersapp, "XNXQDM=2023-2024-1", "application/x-www-form-urlencoded; charset=UTF-8");
  json j = json::parse(res->body);
  return j["datas"]["cxyxkwapkwdkc"]["totalSize"];
  
}

int getexamarranged(string ticket, string weu){
  headersapp.emplace("Cookie", "EMAP_LANG=zh; THEME=teal; _WEU="+weu+"; JSESSIONID=31CB3CC1A8076B54F1E51950AC53D203; MOD_AUTH_CAS=MOD_AUTH_"+ticket+"; route=7790156147990f68c998a9cea94374a5");
  httplib::Client cli("https://ehallapp.nnu.edu.cn");
  auto res = cli.Post("/jwapp/sys/studentWdksapApp/modules/wdksap/wdksap.do", headersapp, "XNXQDM=2023-2024-1", "application/x-www-form-urlencoded; charset=UTF-8");
  json j = json::parse(res->body);
  return j["datas"]["wdksap"]["totalSize"];
}





  
