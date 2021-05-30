#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

/*

int blackjackServer() {

	SOCKET s ,cs; // ������ Ŭ���̾�Ʈ�� ���� �ڵ� ����ü
	WSADATA wasData; // ���������� ���� ����ü 
	SOCKADDR_IN sin, cli_addr; //������ Ŭ���̾�Ʈ�� �����ּ� ������ ���� ����ü

	if (WSAStartup(WINSOCK_VERSION, &wasData) != 0) { //������ wasData�� ������������ ä���ش�, Ws2_32.dill �� �ҷ��� �޸𸮿� ��������ش�
		printf("WSAStartup() ���� �����ڵ� : %d\n", WasGetLastError());//������ 0�� ��ȯ
		return -1;
	}

	//���ϻ��� ,socket(����� �ּ�ġ��(IPv4),
	//����Ÿ��(����������/������ ����� Ŭ���̾�Ʈ�͸� �����ͼۼ���
	//������ ���۹��(TCP))
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (s == INVALID_SOCKET) {
		printf("���ϻ��� ���� �����ڵ� : %d\n", WasGetLastError()); //socket �Լ��� ���� ���н� INVALID_SOCKET ��ȯ
		WASClenup(); //WAS���� �ݳ�
		return -1;
	}
	
	// ���ϻ����� ���� �ּ� ����ä����
	sin.sin_family = AF_INET;
	sin.sin_port = htons(5000); //������Ʈ ����
	sin.sin_addr.S_un.S_addr = htonl(ADDR_ANY);
	
	//bind
	if (bind(s, (SOCKADDR*)&sin, sizeof(sin)) == SOCKET_ERROR) {
		printf("bind() ���� �����ڵ� : %d\n", WasGetLastError()); //socket �Լ��� ���� ���н� INVALID_SOCKET ��ȯ
		closesocket(s); //������ ���� ����
		WASClenup(); //WAS���� �ݳ�
		return -1;
		}
	
	//Listen
	if (listen(s, 1) != 0){ //1���� ���� �ο��� ����, ��û�� Queue �� ����.
		printf("listen ��� ���� ����, �����ڵ� : %d", WasGetLastError());
		closesocket(s); //������ ���� ����
		WASClenup(); //WAS���� �ݳ�
		return -1;

	}

	printf("��������\n");
	printf("Ŭ���̾�Ʈ�� ������ ��ٸ������Դϴ�.\n");


	//Accept
	int cli_size = sizeof(cli_addr); //accpet�Լ��� cli_dddr�� ũ�⸦ �ּҷ� �Ѱ��ֱ����� ����

	//Ŭ���̾�Ʈ ����, ������ ������ ���� ���Ѵ��, 
	//������ Ŭ���̾�Ʈ �����ڵ� cs �� Ŭ���̾�Ʈ ������ �������ִ´�.
	//accpet �Լ��� listen�� ������ Queue���� ���� �õ��� Ŭ���̾�Ʈ�� ������ ó���Ѵ�. ������ ���Ѵ��
	//accpet(��������, Ŭ���̾�Ʈ����������ü, Ŭ���̾�Ʈ ����������ü ũ��)
	cs = accpet(s, (SOCKADDR*)&cli_addr, &cli_size);
	if (cs == INVALID_SOCKET) {
		printf("���ӽ��� ����, �����ڵ� : %d", WasGetLastError());
		closesocket(s); //������ ���� ����
		WASClenup(); //WAS���� �ݳ�
		return -1;
	}

	//�ۼ���


	return 0;
}

*/

void ErrorHandling(char* message);



int test1(int argc, char* argv[])

{

	WSADATA wsaData;

	SOCKET hServSock, hClntSock;

	SOCKADDR_IN servAddr, clntAddr;



	int szClntAddr;

	char message[] = "Hello World!";

	if (argc != 2)

	{

		printf("Usage:%s <port>\n", argv[0]);

		exit(1);

	}



	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) //���� ���̺귯�� �ʱ�ȭ

		ErrorHandling("WSAStartup() error!");



	hServSock = socket(PF_INET, SOCK_STREAM, 0); //���ϻ���

	if (hServSock == INVALID_SOCKET)

		ErrorHandling("socket() error");



	memset(&servAddr, 0, sizeof(servAddr));

	servAddr.sin_family = AF_INET;

	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	servAddr.sin_port = htons(atoi(argv[1]));



	if (bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) //���Ͽ� IP�ּҿ� PORT ��ȣ �Ҵ�

		ErrorHandling("bind() error");



	if (listen(hServSock, 5) == SOCKET_ERROR) //listen �Լ�ȣ���� ���ؼ� ������ ������ ���� �������� �ϼ�

		ErrorHandling("listen() error");



	szClntAddr = sizeof(clntAddr);

	hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &szClntAddr); //Ŭ���̾�Ʈ �����û �����ϱ� ���� accept�Լ� ȣ��

	if (hClntSock == INVALID_SOCKET)

		ErrorHandling("accept() error");



	send(hClntSock, message, sizeof(message), 0); //send�Լ� ȣ���� ���ؼ� ����� Ŭ���̾�Ʈ�� �����͸� ����

	closesocket(hClntSock);

	closesocket(hServSock);

	WSACleanup(); //���α׷� ���� ���� �ʱ�ȭ�� ���� ���̺귯�� ����

	return 0;

}



void ErrorHandling(char* message)

{

	fputs(message, stderr);

	fputc('\n', stderr);

	exit(1);

}




