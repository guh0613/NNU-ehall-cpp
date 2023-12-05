#define CPPHTTPLIB_OPENSSL_SUPPORT
#define CPPHTTPLIB_ZLIB_SUPPORT

#include "httplib.h"
#include "json.hpp"
#include <iostream>
#include <regex>
#include <string>
#include <ctime>
#include <chrono>
#include <cstdio>
#include <fstream>



using json = nlohmann::json;
using namespace httplib;
using namespace std;


int saveCastgcToFile(string castgc, string name);
string qrcodeTicketForFirstLogin(string name);
string getWEU(string ticket);

Headers headers_first_login = {
    {"Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7"},
    {"Accept-Encoding", "gzip, deflate, br"},
    {"Accept-Language", "zh-CN,zh;q=0.9"},
    {"Host", "authserver.nnu.edu.cn"},
    {"Upgrade-Insecure-Requests", "1"},
    {"Referer", "https://ehall.nnu.edu.cn/"},
    {"Sec-Ch-Ua", "\"Chromium\";v=\"119\", \"Not?A_Brand\";v=\"24\""},
    {"Sec-Ch-Ua-Mobile", "?0"},
    {"Sec-Ch-Ua-Platform", "\"macOS\""},
    {"Sec-Fetch-Dest", "document"},
    {"Sec-Fetch-Mode", "navigate"},
    {"Sec-Fetch-Site", "same-origin"},
    {"Priority", "u=0, i"},
    {"Connection", "close"},
    {"User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/118.0.5993.90 Safari/537.36"}
};
Headers headers_second_login = {
    {"Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7"},
    {"Accept-Encoding", "gzip, deflate, br"},
    {"Accept-Language", "zh-CN,zh;q=0.9"},
    {"Host", "authserver.nnu.edu.cn"},
    {"Upgrade-Insecure-Requests", "1"},
    {"Referer", "https://authserver.nnu.edu.cn/authserver/login?service=https%3A%2F%2Fehall.nnu.edu.cn%2Flogin%3Fservice%3Dhttp%3A%2F%2Fehall.nnu.edu.cn%2Fywtb-portal%2Fstandard%2Findex.html"},
    {"Sec-Ch-Ua", "\"Chromium\";v=\"119\", \"Not?A_Brand\";v=\"24\""},
    {"Sec-Ch-Ua-Mobile", "?0"},
    {"Sec-Ch-Ua-Platform", "\"macOS\""},
    {"Sec-Fetch-Dest", "document"},
    {"Sec-Fetch-Mode", "navigate"},
    {"Sec-Fetch-Site", "same-origin"},
    {"Priority", "u=0, i"},
    {"Connection", "close"},
    {"User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/118.0.5993.90 Safari/537.36"}
};

Headers headers_code = {
    {"Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7"},
    {"Accept-Encoding", "gzip, deflate, br"},
    {"Accept-Language", "zh-CN,zh;q=0.9"},
    {"Upgrade-Insecure-Requests", "1"},
    {"Referer", "https://authserver.nnu.edu.cn/authserver/login?type=qrcode&service=https%3A%2F%2Fehall.nnu.edu.cn%2Flogin%3Fservice%3Dhttp%3A%2F%2Fehall.nnu.edu.cn%2Fywtb-portal%2Fstandard%2Findex.html%23%2FWorkBench%2Fworkbench"},
    {"Sec-Ch-Ua", "\"Chromium\";v=\"119\", \"Not?A_Brand\";v=\"24\""},
    {"Sec-Ch-Ua-Mobile", "?0"},
    {"Sec-Ch-Ua-Platform", "\"macOS\""},
    {"Sec-Fetch-Dest", "document"},
    {"Sec-Fetch-Mode", "navigate"},
    {"Sec-Fetch-Site", "same-origin"},
    {"X-Requested-With", "XMLHttpRequest"},
    {"Priority", "u=0, i"},
    {"Connection", "close"},
    {"User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/118.0.5993.90 Safari/537.36"}
};

Headers headers_third_login = {
    {"Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7"},
    {"Accept-Encoding", "gzip, deflate, br"},
    {"Accept-Language", "zh-CN,zh;q=0.9"},
    {"Cache-Control", "max-age=0"},
    {"Host", "authserver.nnu.edu.cn"},
    {"Content-Length", "5780"},
    {"Content-Type", "application/x-www-form-urlencoded"},
    {"Origin", "https://authserver.nnu.edu.cn"},
    {"Referer", "https://authserver.nnu.edu.cn/authserver/login?type=qrcode&service=https%3A%2F%2Fehall.nnu.edu.cn%2Flogin%3Fservice%3Dhttp%3A%2F%2Fehall.nnu.edu.cn%2Fywtb-portal%2Fstandard%2Findex.html%23%2FWorkBench%2Fworkbench"},
    {"Sec-Ch-Ua", "\"Chromium\";v=\"119\", \"Not?A_Brand\";v=\"24\""},
    {"Sec-Ch-Ua-Mobile", "?0"},
    {"Sec-Ch-Ua-Platform", "\"macOS\""},
    {"Sec-Fetch-Dest", "document"},
    {"Sec-Fetch-Mode", "navigate"},
    {"Sec-Fetch-Site", "same-origin"},
    {"Upgrade-Insecure-Requests", "1"},
    {"Sec-Fetch-User", "?1"},
    {"Priority", "u=0, i"},
    {"Connection", "close"},
    {"User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/118.0.5993.90 Safari/537.36"}
};
Headers headers_verify = {
{"Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7"},
    {"Accept-Encoding", "gzip, deflate, br"},
    {"Accept-Language", "zh-CN,zh;q=0.9"},
    {"Cache-Control", "max-age=0"},
    {"Host", "ehall.nnu.edu.cn"},
    {"Cookie", "route=d68a40386be0931ea6cbdda4cfe3192b; JSESSIONID=GWL8ryp6XssPLARVSnuFzKAB1QmYzL8jnsvV3JANpmBJxvNa-Wmv!-750103191; amp.locale=zh_CN"},
    {"Referer", "https://authserver.nnu.edu.cn/"},
    {"Sec-Ch-Ua", "\"Chromium\";v=\"119\", \"Not?A_Brand\";v=\"24\""},
    {"Sec-Ch-Ua-Mobile", "?0"},
    {"Sec-Ch-Ua-Platform", "\"macOS\""},
    {"Sec-Fetch-Dest", "document"},
    {"Sec-Fetch-Mode", "navigate"},
    {"Sec-Fetch-Site", "same-origin"},
    {"Upgrade-Insecure-Requests", "1"},
    {"Priority", "u=0, i"},
    {"User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/118.0.5993.90 Safari/537.36"}
};

time_t GetCurrentTimeMsec()
{
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

}
string qrcodeTicketForFirstLogin(string name){
    string body,body_second;
    Client cli("https://authserver.nnu.edu.cn:443");
    auto res = cli.Get("/authserver/login?service=https%3A%2F%2Fehall.nnu.edu.cn%2Flogin%3Fservice%3Dhttp%3A%2F%2Fehall.nnu.edu.cn%2Fywtb-portal%2Fstandard%2Findex.html", headers_first_login, 
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
    headers_second_login.emplace("Cookie", "JSESSIONID=" + jsess + "; route=" + rout + "; org.springframework.web.servlet.i18n.CookieLocaleResolver.LOCALE=zh_CN");
    headers_third_login.emplace("Cookie", "JSESSIONID=" + jsess + "; route=" + rout + "; org.springframework.web.servlet.i18n.CookieLocaleResolver.LOCALE=zh_CN");
    return true; 
  },
  [&](const char *data, size_t data_length) {
    body.append(data, data_length);
    return true;
  });
  auto secondloginres = cli.Get("/authserver/login?type=qrcode&service=https%3A%2F%2Fehall.nnu.edu.cn%2Flogin%3Fservice%3Dhttp%3A%2F%2Fehall.nnu.edu.cn%2Fywtb-portal%2Fstandard%2Findex.html%23%2FWorkBench%2Fworkbench",headers_second_login,
  [&](const Response &response) {
    return true; 
  },
  [&](const char *data, size_t data_length) {
    body_second.append(data, data_length);
    return true;
  });
  smatch m;
  string execution;
  auto ret = regex_search(body_second, m, regex("<input type=\"hidden\" name=\"execution\" value=\"(.*?)\"/>"));
  if(ret){
      execution = m[1];
  }
  auto uuidres = cli.Get("/authserver/qrCode/getToken?ts="+to_string(GetCurrentTimeMsec()), headers_code);
  string uuid = uuidres->body;
  auto qrcode = cli.Get("/authserver/qrCode/getCode?uuid=" + uuid, headers_code);
  ofstream ofs("./output.png", ios::binary);
  ofs.write(qrcode->body.c_str(), qrcode->body.size());
  ofs.close();
  printf("%s", "请扫码登录,扫码登录完成后，请按下键盘上的任意键");
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
        Params params{
            {"uuid", uuid},
            {"execution", execution},
            {"_eventId","submit"},
            {"cllt","qrLogin"},
            {"dllt", "generalLogin"},
            {"lt", ""},
            {"rmShown", "1"}
        };
        cli.set_keep_alive(false);
        auto loginres = cli.Post("/authserver/login?display=qrLogin&service=https%3A%2F%2Fehall.nnu.edu.cn%2Flogin%3Fservice%3Dhttp%3A%2F%2Fehall.nnu.edu.cn%2Fywtb-portal%2Fstandard%2Findex.html%23%2FWorkBench%2Fworkbench", headers_third_login, params);
        string newurl;
        string newpath;
        for (auto value : loginres->headers) {
            
            if (value.first == "Location") {
                newurl = value.second;
                //cout << newurl << endl;
            }
            if (value.first == "Set-Cookie") {
                string cookie = value.second;
                smatch castgcm;
                auto ret = regex_search(cookie, castgcm, regex("CASTGC=(.*?);"));
                if (ret) {
                    saveCastgcToFile(castgcm[1], name);
                }

            }
        }
        string ticket;
        smatch m2;
        //https://ehall.nnu.edu.cn/login?service=https://ehall.nnu.edu.cn/ywtb-portal/standard/index.html&ticket=ST-2633833-1eyFK59FZiVRAORN86hi0fe7BQAids7authserver4#/WorkBench/workbench
        //we need the path which is the content after the domain name
        auto ret2 = regex_search(newurl, m2, regex("ticket=(.*?)#"));
        if (ret2) {
            ticket = m2[1];
        }

        Client cli2("https://ehall.nnu.edu.cn");
        cli2.Get("/login?service=http://ehall.nnu.edu.cn/ywtb-portal/standard/index.html&ticket="+ticket, headers_verify);
        //cli.set_follow_location(true);
        //auto nnures2 = cli.Get("/",headers);

  return ticket;
}
int saveCastgcToFile(string castgc, string name){
    const string DATA_PATH = "./data/login_tgc.json";
    json j;
    //if the file and folder does not exist, create it,or open it;
    //then save the new tgc json data to the file
    ifstream ifs(DATA_PATH);
    if (!ifs) {
        j[name] = castgc;
        ofstream ofs(DATA_PATH);
        ofs << j;
        ofs.close();
        return 0;
    } else {
        //do not load if the file is empty
        if (ifs.peek() == EOF) {
            ifs.close();
            j[name] = castgc;
            ofstream ofs(DATA_PATH);
            ofs << j;
            ofs.close();
            return 0;
        } else {
        j = json::parse(ifs);
        ifs.close();
        j[name] = castgc;
        ofstream ofs(DATA_PATH);
        ofs << j;
        ofs.close();
        return 0;
        }
    }
    

    return 1;
}

string getWEU(string ticket){
    string path,body,body2,weu_long= "";
    Headers headers_appshow = {
    {"Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7"},
    {"Accept-Encoding", "gzip, deflate, br"},
    {"Accept-Language", "zh-CN,zh;q=0.9"},
    {"Cache-Control", "max-age=0"},
    {"Host", "ehall.nnu.edu.cn"},
    {"Sec-Ch-Ua", "\"Chromium\";v=\"119\", \"Not?A_Brand\";v=\"24\""},
    {"Sec-Ch-Ua-Mobile", "?0"},
    {"Sec-Ch-Ua-Platform", "\"macOS\""},
    {"Sec-Fetch-Dest", "document"},
    {"Sec-Fetch-Mode", "navigate"},
    {"Sec-Fetch-Site", "same-origin"},
    {"Upgrade-Insecure-Requests", "1"},
    {"Priority", "u=0, i"},
    {"User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/118.0.5993.90 Safari/537.36"}
};
Headers headers_weu = {
    {"Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7"},
    {"Accept-Encoding", "gzip, deflate, br"},
    {"Accept-Language", "zh-CN,zh;q=0.9"},
    {"Cache-Control", "max-age=0"},
    {"Host", "ehallapp.nnu.edu.cn"},
    {"Sec-Ch-Ua", "\"Chromium\";v=\"119\", \"Not?A_Brand\";v=\"24\""},
    {"Sec-Ch-Ua-Mobile", "?0"},
    {"Sec-Ch-Ua-Platform", "\"macOS\""},
    {"Sec-Fetch-Dest", "document"},
    {"Sec-Fetch-Mode", "navigate"},
    {"Sec-Fetch-Site", "same-origin"},
    {"Upgrade-Insecure-Requests", "1"},
    {"Priority", "u=0, i"},
    {"User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/118.0.5993.90 Safari/537.36"}
};
  headers_appshow.emplace("Cookie", "MOD_AUTH_CAS=MOD_AUTH_"+ticket+"; asessionid=9b7b1f8c-a17e-4a82-ac48-586362fc9117; amp.locale=zh; JSESSIONID=xTX77bTzr2YPuNS9LsfY5FjSXHXgL2fNc3LThTQdkmO06Blb--k0!-750103190; route=34e12749345e5a1ad7cc6d0324fa3b1c");
  headers_weu.emplace("Cookie", "MOD_AUTH_CAS=MOD_AUTH_"+ticket+"; route=34e12749345e5a1ad7cc6d0324fa3b1c");
  Client cli("https://ehall.nnu.edu.cn");
  auto res = cli.Get("/appShow?appId=4768687067472349", headers_appshow, 
  [&](const Response &response) {
    for(auto value  : response.headers){
        //cout << value.first << ":" << value.second << endl;
      if(response.status == 302 && value.first == "Location"){
        string location = value.second;
        //Location: http://ehallapp.nnu.edu.cn/jwapp/sys/studentWdksapApp/*default/index.do?t_s=1700738745482&amp_sec_version_=1&gid_=WGhYYWREa2ZBczZBZnNrdTF2aEhma2lWbnlnd1IxT21ubUpoaWtZeHdKVmZlQUVKalQrSzBmUm5NQ1FPUkR1ditON1E5SFc4dTV1cEF6aW1UamRCSFE9PQ&EMAP_LANG=zh&THEME=teal
        regex pattern("/jwapp.*");
        smatch result;
        regex_search(location, result, pattern);
        path = result[0];
        //cout << "path:" << path << endl;
      }
    }
    return true; 
  },
  [&](const char *data, size_t data_length) {
    body.append(data, data_length);
    return true;
});
    Client cli2("https://ehallapp.nnu.edu.cn");
    auto res2 = cli2.Get(path, headers_weu,
    [&](const Response &response2) {
    //we want the long one, not the short one
    for(auto value2  : response2.headers){
        if (value2.first == "Set-Cookie"){
            string cookie = value2.second;
            regex pattern("_WEU=([^;]+\\.)");
            smatch result;
            regex_search(cookie, result, pattern);
            string weu = result[1];
            if (weu.length() > weu_long.length()){
                weu_long = weu;
                
            }

        }
    }
    return true; 
  },
  [&](const char *data, size_t data_length) {
    body2.append(data, data_length);
    return true;
  });
  return weu_long;
}

