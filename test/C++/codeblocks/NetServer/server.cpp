#include <winsock2.h> //����ͷ�ļ�
#include <stdio.h>
#include <windows.h>
#include <iostream>

using namespace std;

#pragma comment(lib, "WS2_32.lib")   //��ʽ�����׽��ֿ�

void testTCP() {
    char in[20];
    WSADATA data;   //����WSADATA�ṹ�����
    WORD w = MAKEWORD(2, 0); //����汾����
    char sztext[] = "��ӭ��\r\n";   //Ҫ���͵�����
    ::WSAStartup(w, &data); //��ʼ���׽��ֿ�
    SOCKET s, s1;
    s = ::socket(AF_INET, SOCK_STREAM, 0); //����TCP�׽���
    sockaddr_in addr, addr2; //�����׽��ֵ�ַ�ṹ
    int n = sizeof(addr2);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(75);
    addr.sin_addr.S_un.S_addr = INADDR_ANY;
    ::bind(s, (sockaddr*)&addr, sizeof(addr));



    ::listen(s, 5);
    printf("TCP�������Ѿ�����\r\n");
    while (true) {
        s1 = ::accept(s, (sockaddr*)&addr2, &n);  //������������
        if (s1!=NULL) {
            printf("%s�Ѿ�������\r\n", inet_ntoa(addr2.sin_addr));
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
    WSADATA data;   //����WSADATA�ṹ�����
    WORD w = MAKEWORD(2, 0); //����汾����
    char sztext[] = "��ӭ��\r\n";   //��ӭ��Ϣ
    ::WSAStartup(w, &data); //��ʼ���׽��ֿ�
    SOCKET s;  //�����׽��־��
    s = ::socket(AF_INET, SOCK_DGRAM, 0); //����UDP�׽���
    sockaddr_in addr, addr2; //�����׽��ֵ�ַ�ṹ
    int n = sizeof(addr2);
    char buff[10] = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(75);
    addr.sin_addr.S_un.S_addr = INADDR_ANY;
    ::bind(s, (sockaddr*)&addr, sizeof(addr));
    ::listen(s, 5);
    printf("UDP�������Ѿ�����\r\n");
    if(::recvfrom(s, buff, 10, 0, (sockaddr*)&addr2, &n)!= -1) { //���ܿͻ�����Ϣ
        printf("%s�Ѿ�������\r\n", inet_ntoa(addr2.sin_addr));
        ::sendto(s, sztext, sizeof(sztext), 0, (sockaddr*)&addr2, n);  //�������ݵ��ͻ���
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
