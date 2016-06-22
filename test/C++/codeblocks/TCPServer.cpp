#include <winsock2.h> //包含头文件
#include <stdio.h>
#include <windows.h>
#pragma comment(lib, "WS2_32.lib")   //显式连接套接字库

int main() {
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
	printf("服务器已经启动\r\n");
	while (true) {
		s1 = ::accept(s, (sockaddr*)&addr2, &n);  //接受连接请求
		if (s1!=NULL) {
			printf("%s已经连接上\r\n", inet_ntoa(addr2.sin_addr));
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
