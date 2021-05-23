#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <process.h>
#include <winsock2.h>

extern int poker();
extern void pokermulti(int);
int server_flag = 0;
void ErrorHandling(char* message);
void serverExit(int hServSock)
{
	char ch;
	while (1)
	{
		if (server_flag)
			break;
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'q' || ch == 'Q') {
				closesocket(hServSock);
				WSACleanup();
				break;
			}
				
		}
		Sleep(1);
	}
	
	return;
}
int poker_server(int money) {
	WSADATA    wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAddr, clntAddr;

	int szClntAddr;
	int strLen;
	char serverScoreMessage[20];
	char clientScoreMessage[20];
	char resultMessage[20];
	char joinMessage[5];
	char moneys[20];
	int winlose;
	int serverScore, clientScore;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("WSAStartup() error!");
		_getch();
		system("cls");
		return money;
	}

	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hServSock == INVALID_SOCKET) {
		printf("socket() error");
		_getch();
		system("cls");
		return money;
	}

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(8678);

	if (bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) {
		printf("bind() error");
		_getch();
		system("cls");
		return money;
	}
	server_flag = 0; // ������ Ż��� ��������
	_beginthreadex(NULL, 0, (_beginthreadex_proc_type)serverExit, (void*)hServSock, 0, NULL); // ���� ���� �� ��Ҹ� ���� ������ ����

	if (listen(hServSock, 5) == SOCKET_ERROR) {
		printf("listen() error");
		_getch();
		system("cls");
		return money;
	}
	
	szClntAddr = sizeof(clntAddr);
	
	hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &szClntAddr);
	server_flag = 1;

	if (hClntSock == INVALID_SOCKET) {
		printf("accept() error");
		_getch();
		system("cls");
		return money;
	}
	
	system("cls");
	printf("������ �����߽��ϴ�. ������ �ǵ��� ���� �������� ���� �� �Դϴ�.\n");

	sprintf(moneys, "%d", money);
	send(hClntSock, moneys, (int)strlen(moneys), 0); // Ŭ���̾�Ʈ���� �� ȸ��

	strLen = recv(hClntSock, joinMessage, sizeof(joinMessage) - 1, 0); // Ŭ���̾�Ʈ�� �����Ұ��� ���
	if (strLen == -1) {
		printf("read() error!");
		_getch();
		system("cls");
		return money;
	}
	joinMessage[strLen] = '\0';

	if (strcmp(joinMessage, "exit") == 0) {
		printf("������ �ǵ��� ���� ������ �ź��߽��ϴ�. �ƹ�Ű�� ������ ���� �޴��� ���ư��ϴ�.\n");
		closesocket(hClntSock);
		WSACleanup();
		_getch();
		system("cls");
		return money;
	} 
	system("cls");
	serverScore = poker(); // ���� ���� ���� ����
	printf("�����: ");
	pokermulti(serverScore);

	sprintf(serverScoreMessage, "%d", serverScore);
	send(hClntSock, serverScoreMessage, (int)strlen(serverScoreMessage), 0); // ���� ���� Ŭ���̾�Ʈ ����

	strLen = recv(hClntSock, clientScoreMessage, sizeof(clientScoreMessage) - 1, 0); // Ŭ���̾�Ʈ ���� �ޱ��� ���� ���
	if (strLen == -1) {
		printf("read() error!");
		_getch();
		system("cls");
		return money;
	}
	clientScoreMessage[strLen] = '\0';

	printf("����: ");
	clientScore = atoi(clientScoreMessage);
	pokermulti(clientScore);

	if (serverScore > clientScore) {
		printf("����� �¸�!!\n%d���� ������!\n", money * 2);
		winlose = 0;
	}
	else if (serverScore == clientScore) {
		printf("���º�!\n�ƹ� �ҵ浵 ������...");
		winlose = 1;
	}
	else {
		printf("����� �й� �Ф�\n");
		winlose = 2;
	}

	sprintf(resultMessage, "%d", winlose);
	send(hClntSock, resultMessage, (int)strlen(resultMessage), 0); // Ŭ���̾�Ʈ���� ��� ������
	closesocket(hServSock);
	closesocket(hClntSock);
	WSACleanup();
	_getch();
	system("cls");
	if (winlose == 0)
		return money * 2;
	else if (winlose == 1)
		return money;
	else
		return 0;
}

void poker_client(int *money) {
	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN servAddr;
	char serverScoreMessage[20];
	char clientScoreMessage[20];
	char resultMessage[20];
	char moneys[20];
	int strLen;
	int insertmoney = 0;
	int result;
	char ipadd[15];
	char ch;
	int serverScore, clientScore;
	
	printf("������ ������ �����Ǹ� �Է��ϼ���(����Ϸ��� -1 �Է�): ");
	scanf("%s", ipadd);
	rewind(stdin);
	if (ipadd[0] == '-' && ipadd[1] == '1') {
		system("cls");
		return;
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("WSAStartup() error!");
		_getch();
		system("cls");
		return;
	}

	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET) {
		printf("hSocketet() error");
		_getch();
		system("cls");
		return;
	}

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(ipadd);
	servAddr.sin_port = htons(8678);

	if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) {
		printf("connect() error!");
		_getch();
		system("cls");
		return;
	}
	strLen = recv(hSocket, moneys, sizeof(moneys) - 1, 0);
	if (strLen == -1) {
		printf("read() error!");
		_getch();
		system("cls");
		return;
	}
	moneys[strLen] = '\0';
	insertmoney = atoi(moneys);

	system("cls");
	printf("������ �ǵ��� %d�� �Դϴ�. �����Ϸ��� �ƹ�Ű�� �����ų�\n ������ �������� q�� �Է��ϼ���.\n", insertmoney); // �ǵ��� ���� ���ӿ� �������� ����

	ch = _getch();
	

	if (ch == 'Q' || ch == 'q') {
		char joinMessage[] = "exit";
		printf("������ ����߽��ϴ�. ����Ϸ��� �ƹ�Ű�� ��������.\n");
		send(hSocket, joinMessage, (int)strlen(joinMessage), 0);
		closesocket(hSocket);
		WSACleanup();
		_getch();
		system("cls");
		return;
	}
	else {
		char joinMessage[] = "go";
		send(hSocket, joinMessage, (int)strlen(joinMessage), 0);
	}
	
	*money -= insertmoney; // ������ ������ �ǵ� ����
	system("cls");
	printf("������ ��Ŀ�� ���������� ��ٸ��� �� �Դϴ�.\n");

	strLen = recv(hSocket, serverScoreMessage, sizeof(serverScoreMessage) - 1, 0); // ������ ��Ŀ ���������� ���
	if (strLen == -1) {
		printf("read() error!");
		_getch();
		system("cls");
		return;
	}
	serverScoreMessage[strLen] = '\0';

	serverScore = atoi(serverScoreMessage); // ���� ���ھ� ����
	clientScore = poker(); // Ŭ���̾�Ʈ ��Ŀ ����
	printf("�����: ");
	pokermulti(clientScore);

	sprintf(clientScoreMessage, "%d", clientScore);
	send(hSocket, clientScoreMessage, (int)strlen(clientScoreMessage), 0); // ������ ��Ŀ ��� ����
	
	
	printf("����: ");
	pokermulti(serverScore); // ���� ��� ���

	strLen = recv(hSocket, resultMessage, sizeof(resultMessage) - 1, 0); // ������ ��� ��ٸ���
	if (strLen == -1) {
		printf("read() error!");
		_getch();
		system("cls");
		return;
	}
	resultMessage[strLen] = '\0';

	result = atoi(resultMessage);
	//printf("%d\n", result);
	switch (result)
	{
	case 0:
		printf("����� �й� �Ф�\n");
		break;
	case 1:
		printf("���º�!\n�ƹ� �ҵ浵 ������...");
		*money += insertmoney;
		break;
	case 2:
		printf("����� �¸�!!\n%d���� ������!\n", insertmoney*2);
		*money += insertmoney * 2;
		break;
	default:
		break;
	}
	
	closesocket(hSocket);
	WSACleanup();
	_getch();
	system("cls");
	return;
}

void ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}