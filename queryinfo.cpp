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
  {"Cookie", "route=d68a40386be0931ea6cbdda4cfe3192d; amp.locale=zh; MOD_AUTH_CAS=MOD_AUTH_ST-1112930-d5upbXIkHIpSFjJ4bKg8a5tVqWAids7authserver1; asessionid=e2474196-09f2-4a1f-aeb4-b9cd38903570; zg_=%7B%22sid%22%3A%201698567016302%2C%22updated%22%3A%201698567400292%2C%22info%22%3A%201698567016303%2C%22superProperty%22%3A%20%22%7B%7D%22%2C%22platform%22%3A%20%22%7B%7D%22%2C%22utm%22%3A%20%22%7B%7D%22%2C%22referrerDomain%22%3A%20%22ehall.nnu.edu.cn%22%2C%22cuid%22%3A%20%2221220626%22%7D; zg_did=%7B%22did%22%3A%20%2218b7a7bcf6c1f1f-0a56a1fea101b18-3f626a4b-1fa400-18b7a7bcf6d2712%22%7D; route=34e12749345e5a1ad7cc6d0324fa3b1c; JSESSIONID=uUt6O7_XTePghL5-kDVimMd2zL3aUVih-2G7Fe6F1EdO7plhtdkl!-626136051"},
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
  {"Cookie", "route=62d05b9ac924b10f592a23a36a53438f; EMAP_LANG=zh; THEME=teal; _WEU=khvqxpg1g0zLKMrpFbVPms9w3VFB68z2qWLkzkdXvcl9mHI7LQ*BSREqTGVnaV95lFztZ10w9X0GogjwcgArL9C8J3RNT45ppdsFCrinF_6DCNfdy5YLnj..; JSESSIONID=90EC1D9E67965999DA2E7C57D54C9716; zg_=%7B%22sid%22%3A%201698567016302%2C%22updated%22%3A%201698567400292%2C%22info%22%3A%201698567016303%2C%22superProperty%22%3A%20%22%7B%7D%22%2C%22platform%22%3A%20%22%7B%7D%22%2C%22utm%22%3A%20%22%7B%7D%22%2C%22referrerDomain%22%3A%20%22ehall.nnu.edu.cn%22%2C%22cuid%22%3A%20%2221220626%22%7D; zg_did=%7B%22did%22%3A%20%2218b7a7bcf6c1f1f-0a56a1fea101b18-3f626a4b-1fa400-18b7a7bcf6d2712%22%7D; MOD_AUTH_CAS=MOD_AUTH_ST-1111877-oON49yKkcr9nh5oRq7DTni-BcScids7authserver1"},
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
  