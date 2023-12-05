#define CPPHTTPLIB_OPENSSL_SUPPORT
#define CPPHTTPLIB_ZLIB_SUPPORT

#include "login.hpp"
#include "queryinfo.hpp"
#include <cstdio>
#include <stdio.h>

using namespace std;

int enterhall(string ticket);

int main() {
  int choice = 0;
  string ticket;
  wprintf(reinterpret_cast<const wchar_t *const>("欢迎登录南师大一站式事务系统\n"));
  printf("请选择：（输入数字序号）\n");
  printf("1.登录南师一站式系统\n");
  printf("2.退出\n");
  choice = scanf("%d", &choice);
  switch (choice) {
  case 1:
    printf("请选择：（输入数字序号）\n");
    printf("1.使用全新账号登录\n");
    printf("2.使用已有账号登录\n");
    printf("0.退出\n");
    scanf("%d", &choice);
    switch (choice) {
    case 0:
      printf("感谢使用！\n");
      return 0;
      break;
    case 1:
      printf("想使用什么方式登录呢？（输入数字序号）\n");
      printf("1.扫码登录\n");
      scanf("%d", &choice);
      switch (choice) {
      case 1:
        char name[10];
        printf("请输入你的学号：\n");
        scanf("%s", name);
        ticket = qrcodeTicketForFirstLogin(name);
        enterhall(ticket);
        break;
      }
      break;
    case 2:
      char name[10];
      printf("请输入你的学号：\n");
      scanf("%s", name);
    }
    break;

    break;
  case 2:
    printf("感谢使用！\n");
    return 0;
    break;
  }
}

int enterhall(string ticket) {
  int choice;
  string username = getstudentname(ticket);
  int unread_messages = getunreadmessage(ticket);
  string mailmessage = getmailmessage(ticket);
  printf("\n欢迎你，%s同学！你当前有%d条未读消息，校园邮箱共%s\n",
         username.c_str(), unread_messages, mailmessage.c_str());
  printf("请选择你要访问的服务：（输入数字序号）\n");
  printf("1.我的考试安排\n");
  printf("0.退出\n");
  scanf("%d", &choice);
  switch (choice) {
  case 0:
    printf("感谢使用！\n");
    return 0;
    break;
  case 1:
    string weu = getWEU(ticket);
    int examall = getexamall(ticket, weu);
    int examarranged = getexamarranged(ticket, weu);
    printf("你本学期现在共有%d门考试，其中%d门已经安排，%d门未安排\n", examall,
           examarranged, examall - examarranged);
    if (examarranged == 0) {
      printf("你目前还没有任何考试安排哦～\n");
      return 0;
    }
  }
  return 0;
}
