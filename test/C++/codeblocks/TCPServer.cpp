#include <winsock2.h> //����ͷ�ļ�
#include <stdio.h>
#include <windows.h>
#pragma comment(lib, "WS2_32.lib")   //��ʽ�����׽��ֿ�

int main() {
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
	printf("�������Ѿ�����\r\n");
	while (true) {
		s1 = ::accept(s, (sockaddr*)&addr2, &n);  //������������
		if (s1!=NULL) {
			printf("%s�Ѿ�������\r\n", inet_ntoa(addr2.sin_addr));
			::send(s1, sztext, sizeof(sztext), 0);
		}
		::closesocket(s);
		::closesocket(s1);
		::WSACleanup();
		if (getchar()) {
			return 0;
		}
		else {
			::Sleep(100);
		}
	}
}
