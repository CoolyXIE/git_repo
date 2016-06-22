#include <winsock2.h> //����ͷ�ļ�
#include <stdio.h>
#include <windows.h>
#include <iostream>
#pragma comment(lib, "WS2_32.lib")   //��ʽ�����׽��ֿ�


using namespace std;

void testTCP() {
    WSADATA data;   //����WSADATA�ṹ�����
    WORD w = MAKEWORD(2, 0); //����汾����
    ::WSAStartup(w, &data); //��ʼ���׽��ֿ�
    SOCKET s;
    char income[10] = {0};
    char out[20];
    s = ::socket(AF_INET, SOCK_STREAM, 0); //����TCP�׽���
    sockaddr_in addr; //�����׽��ֵ�ַ�ṹ
    addr.sin_family = AF_INET;
    addr.sin_port = htons(75);
    addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    printf("TCP�ͻ����Ѿ�����\r\n");
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
    WSADATA data;   //����WSADATA�ṹ�����
    WORD w = MAKEWORD(2, 0); //����汾����
    ::WSAStartup(w, &data); //��ʼ���׽��ֿ�
    SOCKET s;
    s = ::socket(AF_INET, SOCK_DGRAM, 0); //����UDP�׽���
    sockaddr_in addr,addr2; //�����׽��ֵ�ַ�ṹ
    int n = sizeof(addr2);
    char buff[10] = {0};
    char sztext[20] = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(75);
    addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    printf("UDP�ͻ����Ѿ�����\r\n");
    if(::sendto(s, sztext, sizeof(sztext), 0, (sockaddr*)&addr, n )!= 0) {
        recvfrom(s, buff, 10, 0, (sockaddr*)&addr2, &n);
        printf("������˵:%s\r\n", buff);
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

