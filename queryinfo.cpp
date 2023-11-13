#include "httplib.h"
#include "json.hpp"
#include <iostream>
#include <string>

using json = nlohmann::json;
using namespace std;

namespace getinfo {
httplib::Headers headers = {
  {"Accept", "application/json, text/plain, */*"},
  {"Accept-Encoding", "gzip, deflate"},
  {"Connection", "keep-alive"},
  {"User-Agent", "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/17.0 Safari/605.1.15"},
  {"Referer", "http://ehall.nnu.edu.cn/ywtb-portal/standard/index.html"},
  {"Accept-Language", "zh-CN,zh-Hans;q=0.9"},
  {"X-Requested-With", "XMLHttpRequest"},
};

httplib::Headers headersapp = {
  {"Accept", "application/json, text/javascript, */*; q=0.01"},
  {"Accept-Encoding", "gzip, deflate"},
  {"Accept-Language", "zh-CN,zh-Hans;q=0.9"},
  {"Content-Length", "18"},
  {"Content-Type", "application/x-www-form-urlencoded; charset=UTF-8"},
  {"Host", "ehallapp.nnu.edu.cn"},
  {"Origin", "http://ehallapp.nnu.edu.cn"},
  {"Connection", "keep-alive"},
  {"User-Agent", "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/17.0 Safari/605.1.15"},
  {"Referer", "http://ehallapp.nnu.edu.cn/jwapp/sys/studentWdksapApp/*default/index.do?t_s=1698567688342&amp_sec_version_=1&gid_=WGhYYWREa2ZBczZBZnNrdTF2aEhma2lWbnlnd1IxT21ubUpoaWtZeHdKVmZlQUVKalQrSzBmUm5NQ1FPUkR1ditON1E5SFc4dTV1cEF6aW1UamRCSFE9PQ&EMAP_LANG=zh&THEME=teal"},
  {"Accept-Language", "zh-CN,zh-Hans;q=0.9"},
  {"X-Requested-With", "XMLHttpRequest"},
};



int getunreadmessage(){
httplib::Client cli("http://ehall.nnu.edu.cn");
  auto res = cli.Get("/jsonp/ywtb/getUnreadMessageCount", headers);
  json j = json::parse(res->body);
  return j["data"]["totalSize"];
}

string getstudentname(){
  httplib::Client cli("http://ehall.nnu.edu.cn");
  auto res = cli.Get("/jsonp/ywtb/info/getUserInfoAndSchoolInfo", headers);
  json j = json::parse(res->body);
  return j["data"]["userName"];
}


string getmailmessage(){
  httplib::Client cli("http://ehall.nnu.edu.cn");
  auto res = cli.Get("/jsonp/ywtb/card/getViewDataDetail?wid=cd02610dafaf42cb8f6da5632c317669", headers);
  json j = json::parse(res->body);
  return j["data"][0]["imptInfo"];
}

int getexamall(){
  httplib::Client cli("http://ehallapp.nnu.edu.cn");
  auto res = cli.Post("/jwapp/sys/studentWdksapApp/modules/wdksap/cxyxkwapkwdkc.do", headersapp, "XNXQDM=2023-2024-1", "application/x-www-form-urlencoded; charset=UTF-8");
  json j = json::parse(res->body);
  return j["datas"]["cxyxkwapkwdkc"]["totalSize"];
  
}

int getexamarranged(){
  httplib::Client cli("http://ehallapp.nnu.edu.cn");
  auto res = cli.Post("/jwapp/sys/studentWdksapApp/modules/wdksap/wdksap.do", headersapp, "XNXQDM=2023-2024-1", "application/x-www-form-urlencoded; charset=UTF-8");
  json j = json::parse(res->body);
  return j["datas"]["wdksap"]["totalSize"];
}
}
  