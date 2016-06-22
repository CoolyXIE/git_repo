#include <winsock2.h> //包含头文件
#include <stdio.h>
#include <windows.h>
#include <iostream>

using namespace std;

#pragma comment(lib, "WS2_32.lib")   //显式连接套接字库

void testTCP() {
    char in[20];
    WSADATA data;   //定义WSADATA结构体对象
    WORD w = MAKEWORD(2, 0); //定义版本号码
    char sztext[] = "欢迎你\r\n";   //要发送的内容
    ::WSAStartup(w, &data); //初始化套接字库
    SOCKET s, s1;
    s = ::socket(AF_INET, SOCK_STREAM, 0); //创建TCP套接字
    sockaddr_in addr, addr2; //定义套接字地址结构
    int n = sizeof(addr2);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(75);
    addr.sin_addr.S_un.S_addr = INADDR_ANY;
    ::bind(s, (sockaddr*)&addr, sizeof(addr));



    ::listen(s, 5);
    printf("TCP服务器已经启动\r\n");
    while (true) {
        s1 = ::accept(s, (sockaddr*)&addr2, &n);  //接受连接请求
        if (s1!=NULL) {
            printf("%s已经连接上\r\n", inet_ntoa(addr2.sin_addr));
            ::send(s1, sztext, sizeof(sztext), 0);
            while(true) {
                ::recv(s1, in, sizeof(in), 0);
                cout << in << endl;
            }
        }
        ::closesocket(s);
        ::closesocket(s1);
        ::WSACleanup();
        if (getchar()) {
            return ;
        } else {
            ::Sleep(100);
        }
    }
}


void testUDP() {
    char in[20];
    WSADATA data;   //定义WSADATA结构体对象
    WORD w = MAKEWORD(2, 0); //定义版本号码
    char sztext[] = "欢迎你\r\n";   //欢迎信息
    ::WSAStartup(w, &data); //初始化套接字库
    SOCKET s;  //定义套接字句柄
    s = ::socket(AF_INET, SOCK_DGRAM, 0); //创建UDP套接字
    sockaddr_in addr, addr2; //定义套接字地址结构
    int n = sizeof(addr2);
    char buff[10] = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(75);
    addr.sin_addr.S_un.S_addr = INADDR_ANY;
    ::bind(s, (sockaddr*)&addr, sizeof(addr));
    ::listen(s, 5);
    printf("UDP服务器已经启动\r\n");
    if(::recvfrom(s, buff, 10, 0, (sockaddr*)&addr2, &n)!= -1) { //接受客户端信息
        printf("%s已经连接上\r\n", inet_ntoa(addr2.sin_addr));
        ::sendto(s, sztext, sizeof(sztext), 0, (sockaddr*)&addr2, n);  //发送数据到客户端
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
