#include <winsock2.h> //包含头文件
#include <stdio.h>
#include <windows.h>
#include <iostream>
#pragma comment(lib, "WS2_32.lib")   //显式连接套接字库


using namespace std;

void testTCP() {
    WSADATA data;   //定义WSADATA结构体对象
    WORD w = MAKEWORD(2, 0); //定义版本号码
    ::WSAStartup(w, &data); //初始化套接字库
    SOCKET s;
    char income[10] = {0};
    char out[20];
    s = ::socket(AF_INET, SOCK_STREAM, 0); //创建TCP套接字
    sockaddr_in addr; //定义套接字地址结构
    addr.sin_family = AF_INET;
    addr.sin_port = htons(75);
    addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    printf("TCP客户端已经启动\r\n");
    ::connect(s, (sockaddr*)&addr, sizeof(addr));
    ::recv(s, income, sizeof(income), 0);
    printf("%s\r\n", income);

    while(true) {
        cin.getline(out, 20);
        ::send(s, out, sizeof(out), 0);
    }


    ::closesocket(s);
    ::WSACleanup();
    if (getchar()) {
        return ;
    } else {
        ::Sleep(100);
    }
}

void testUDP() {
    WSADATA data;   //定义WSADATA结构体对象
    WORD w = MAKEWORD(2, 0); //定义版本号码
    ::WSAStartup(w, &data); //初始化套接字库
    SOCKET s;
    s = ::socket(AF_INET, SOCK_DGRAM, 0); //创建UDP套接字
    sockaddr_in addr,addr2; //定义套接字地址结构
    int n = sizeof(addr2);
    char buff[10] = {0};
    char sztext[20] = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(75);
    addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    printf("UDP客户端已经启动\r\n");
    if(::sendto(s, sztext, sizeof(sztext), 0, (sockaddr*)&addr, n )!= 0) {
        recvfrom(s, buff, 10, 0, (sockaddr*)&addr2, &n);
        printf("服务器说:%s\r\n", buff);
        ::closesocket(s);
        ::WSACleanup();
    }
    if(getchar()) {
        return ;
    } else {
        ::Sleep(100);
    }


}
int main() {
    testUDP();
    return 0;
}

