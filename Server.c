#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32");

#define BUFSIZE 512

int main(int argc, char* argv[]) {
	int retval;

	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return -1;

	//socket()
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	printf("(1) socket ���� �Ϸ�\n");

	//bind()
	SOCKADDR_IN serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(9000);

	bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	printf("(2) bind �Ϸ�.\n");

	//listen()
	listen(listen_sock, SOMAXCONN);
	printf("(3) Ŭ���̾�Ʈ ��� ��\n");

	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	char buf[BUFSIZE];

	//accept()
	addrlen = sizeof(clientaddr);
	client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
	printf("(4) ���� ��û ����\n");

	//recv() & send()
	while (1) {
		retval = recv(client_sock, buf, BUFSIZE, 0);
		buf[retval] = '\0';
		printf("(5) �޽��� ���� : %s \n", buf);
		if (strcmp(buf, "exit") == 0)
			break;
		char buf[BUFSIZE + 1];
		printf("���� ���ڿ� �Է� : ");
		scanf("%s", &buf);
		send(client_sock, buf, strlen(buf), 0);
		printf("(6) �Է� �޽��� �۽�\n");
		
	}
	printf("(7) ����\n");
	closesocket(listen_sock);
	WSACleanup();
	return 0;
}