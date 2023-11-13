#include <fstream>
#define CPPHTTPLIB_OPENSSL_SUPPORT
#define CPPHTTPLIB_ZLIB_SUPPORT

#include "httplib.h"
#include "json.hpp"
#include <iostream>
#include <regex>
#include <string>
#include <ctime>
#include <chrono>



using json = nlohmann::json;
using namespace httplib;
using namespace std;

Headers headers_first = {
    {"Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7"},
    {"Accept-Encoding", "gzip, deflate, br, zstd"},
    {"Accept-Language", "zh-CN,zh;q=0.9"},
    {"Referer", "https://authserver.nnu.edu.cn/authserver/login?type=qrcode&service=http%3A%2F%2Fehall.nnu.edu.cn%2Flogin%3Fservice%3Dhttp%3A%2F%2Fehall.nnu.edu.cn%2Fywtb-portal%2Fstandard%2Findex.html%23%2FWorkBench%2Fworkbench"},
    {"Sec-Ch-Ua", "\"Not=A?Brand\";v=\"99\", \"Chromium\";v=\"118\""},
    {"Sec-Ch-Ua-Mobile", "?0"},
    {"Sec-Ch-Ua-Platform", "macOS"},
    {"Sec-Fetch-Dest", "document"},
    {"Sec-Fetch-Mode", "navigate"},
    {"Sec-Fetch-Site", "same-origin"},
    {"User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/118.0.5993.90 Safari/537.36"}
};

Headers headers_code = {
    {"Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7"},
    {"Accept-Encoding", "gzip, deflate, br, zstd"},
    {"Accept-Language", "zh-CN,zh;q=0.9"},
    {"Referer", "https://authserver.nnu.edu.cn/authserver/login?type=qrcode&service=http%3A%2F%2Fehall.nnu.edu.cn%2Flogin%3Fservice%3Dhttp%3A%2F%2Fehall.nnu.edu.cn%2Fywtb-portal%2Fstandard%2Findex.html%23%2FWorkBench%2Fworkbench"},
    {"Sec-Ch-Ua", "\"Not=A?Brand\";v=\"99\", \"Chromium\";v=\"118\""},
    {"Sec-Ch-Ua-Mobile", "?0"},
    {"Sec-Ch-Ua-Platform", "macOS"},
    {"Sec-Fetch-Dest", "document"},
    {"Sec-Fetch-Mode", "navigate"},
    {"Sec-Fetch-Site", "same-origin"},
    {"X-Requested-With", "XMLHttpRequest"},
    {"User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/118.0.5993.90 Safari/537.36"}
};

Headers headers = {
    {"Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7"},
    {"Accept-Encoding", "gzip, deflate, br, zstd"},
    {"Accept-Language", "zh-CN,zh;q=0.9"},
    {"Cache-Control", "max-age=0"},
    {"Content-Length", "5636"},
    {"Content-Type", "application/x-www-form-urlencoded"},
    {"Cookie", "JSESSIONID=F40D5C27EF45F5EB87C06EA396B4DA8F; route=7e13d3d276af8b7437ce5afd5a9783e9; org.springframework.web.servlet.i18n.CookieLocaleResolver.LOCALE=zh_CN"},
    {"Origin", "http://authserver.nnu.edu.cn"},
    {"Referer", "http://authserver.nnu.edu.cn/authserver/login?type=qrcode&service=http%3A%2F%2Fehall.nnu.edu.cn%2Flogin%3Fservice%3Dhttp%3A%2F%2Fehall.nnu.edu.cn%2Fywtb-portal%2Fstandard%2Findex.html%23%2FWorkBench%2Fworkbench"},
    {"Sec-Ch-Ua", "\"Not=A?Brand\";v=\"99\", \"Chromium\";v=\"118\""},
    {"Sec-Ch-Ua-Mobile", "?0"},
    {"Sec-Ch-Ua-Platform", "macOS"},
    {"Sec-Fetch-Dest", "document"},
    {"Sec-Fetch-Mode", "navigate"},
    {"Sec-Fetch-Site", "same-origin"},
    {"Upgrade-Insecure-Requests", "1"},
    {"User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/118.0.5993.90 Safari/537.36"}
};
time_t GetCurrentTimeMsec()
{
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

}
int getaccount(){
    string body;
    Client cli("https://authserver.nnu.edu.cn");
    auto res = cli.Get("/authserver/login?type=qrcode&service=http%3A%2F%2Fehall.nnu.edu.cn%2Flogin%3Fservice%3Dhttp%3A%2F%2Fehall.nnu.edu.cn%2Fywtb-portal%2Fstandard%2Findex.html%23%2FWorkBench%2Fworkbench", headers_first, 
  [&](const Response &response) {
    string jsess,rout;
    for(auto value  : response.headers){
        if (value.first == "Set-Cookie") {
            smatch jsession,route;
            
            auto retroute = regex_search(value.second, route, regex("route=(.*?);"));
            auto retjsession = regex_search(value.second, jsession, regex("JSESSIONID=(.*?);"));
            if (retjsession) {
                jsess = jsession[1];
            }
            if (retroute) {
                rout = route[1];
            }
        }
    }
    headers_code.emplace("Cookie", "JSESSIONID=" + jsess + "; route=" + rout + "; org.springframework.web.servlet.i18n.CookieLocaleResolver.LOCALE=zh_CN");
    return true; 
  },
  [&](const char *data, size_t data_length) {
    body.append(data, data_length);
    return true;
  });
  cli.set_keep_alive(true);
  smatch m;
  string execution;
  auto ret = regex_search(body, m, regex("<input type=\"hidden\" name=\"execution\" value=\"(.*?)\"/>"));
  if(ret){
      execution = m[1];
  }
  auto uuidget = cli.Get("/authserver/qrCode/getToken?ts="+to_string(GetCurrentTimeMsec()), headers_code);
  cli.set_keep_alive(true);
  string uuid = uuidget->body;
  auto qrcode = cli.Get("/authserver/qrCode/getCode?uuid=" + uuid, headers_code);
  ofstream ofs("./output.png", ios::binary);
  ofs.write(qrcode->body.c_str(), qrcode->body.size());
  ofs.close();
  return 0;
}
int main(){
    getaccount();
    return 0;
}



