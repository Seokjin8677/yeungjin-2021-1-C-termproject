#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <process.h>
#include <winsock2.h>

extern int poker();
extern void pokermulti(int);
extern int moneyCheck(int*, char*,int*, int);
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
	PlaySound(TEXT("sound\\button.wav"), NULL, SND_ASYNC);
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
	server_flag = 0; // 스레드 탈출용 전역변수
	_beginthreadex(NULL, 0, (_beginthreadex_proc_type)serverExit, (void*)hServSock, 0, NULL); // 서버 생성 시 취소를 위한 스레드 생성

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
		//printf("accept() error");
		//_getch();
		system("cls");
		return money;
	}
	
	system("cls");
	PlaySound(TEXT("sound\\scanning.wav"), NULL, SND_ASYNC);
	printf("상대방이 접속했습니다. 상대방이 판돈을 보고 입장할지 결정 중 입니다.\n");

	sprintf(moneys, "%d", money);
	send(hClntSock, moneys, (int)strlen(moneys), 0); // 클라이언트에게 돈 회수

	strLen = recv(hClntSock, joinMessage, sizeof(joinMessage) - 1, 0); // 클라이언트가 참가할건지 대기
	if (strLen == -1) {
		printf("read() error!");
		_getch();
		system("cls");
		return money;
	}
	joinMessage[strLen] = '\0';

	if (strcmp(joinMessage, "exit") == 0) {
		PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
		printf("상대방이 판돈을 보고 참가를 거부했습니다.\n");
		closesocket(hClntSock);
		WSACleanup();
		system("pause");
		system("cls");
		return money;
	} 
	system("cls");
	serverScore = poker(); // 서버 먼저 게임 진행
	printf("사용자: ");
	pokermulti(serverScore);

	sprintf(serverScoreMessage, "%d", serverScore);
	send(hClntSock, serverScoreMessage, (int)strlen(serverScoreMessage), 0); // 서버 점수 클라이언트 전송

	strLen = recv(hClntSock, clientScoreMessage, sizeof(clientScoreMessage) - 1, 0); // 클라이언트 점수 받기전 까지 대기
	if (strLen == -1) {
		printf("read() error!");
		_getch();
		system("cls");
		return money;
	}
	clientScoreMessage[strLen] = '\0';

	printf("상대방: ");
	clientScore = atoi(clientScoreMessage);
	pokermulti(clientScore);

	if (serverScore > clientScore) {
		PlaySound(TEXT("sound\\win.wav"), NULL, SND_ASYNC);
		printf("당신의 승리!!\n%d원을 벌었다!\n", money * 2);
		winlose = 0;
	}
	else if (serverScore == clientScore) {
		PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
		printf("무승부!\n아무 소득도 없었다...");
		winlose = 1;
	}
	else {
		PlaySound(TEXT("sound\\lose.wav"), NULL, SND_ASYNC);
		printf("당신의 패배 ㅠㅠ\n");
		winlose = 2;
	}

	sprintf(resultMessage, "%d", winlose);
	send(hClntSock, resultMessage, (int)strlen(resultMessage), 0); // 클라이언트에게 결과 보내기
	closesocket(hServSock);
	closesocket(hClntSock);
	WSACleanup();
	system("pause");
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
	
	printf("접속할 서버에 아이피를 입력하세요(취소하려면 -1 입력): ");
	scanf_s("%s", ipadd,sizeof(ipadd));
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
		PlaySound(TEXT("sound\\scanning.wav"), NULL, SND_ASYNC);
		printf("접속 실패!\n");
		system("pause");
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
	printf("소지하고 있는 돈: %d\n", *money);
	printf("게임의 판돈은 %d원 입니다.\n진행하려면 아무키나 누르거나, 게임을 나가려면 q를 입력하세요.\n", insertmoney); // 판돈을 보고 게임에 참가할지 결정

	ch = _getch();
	

	if (ch == 'Q' || ch == 'q') {
		char joinMessage[] = "exit";
		PlaySound(TEXT("sound\\scanning.wav"), NULL, SND_ASYNC);
		printf("게임을 취소했습니다.\n");
		send(hSocket, joinMessage, (int)strlen(joinMessage), 0);
		closesocket(hSocket);
		WSACleanup();
		system("pause");
		system("cls");
		return;
	}
	if(moneyCheck(money, moneys,&insertmoney,0) == 0) {
		char joinMessage[] = "exit";
		send(hSocket, joinMessage, (int)strlen(joinMessage), 0);
		closesocket(hSocket);
		WSACleanup();
		return;
	}
	char joinMessage[] = "go";
	send(hSocket, joinMessage, (int)strlen(joinMessage), 0);
	
	*money -= insertmoney; // 서버가 설정한 판돈 내기
	system("cls");
	printf("상대방이 포커를 끝낼때까지 기다리는 중 입니다.\n");

	strLen = recv(hSocket, serverScoreMessage, sizeof(serverScoreMessage) - 1, 0); // 서버가 포커 끝날때까지 대기
	if (strLen == -1) {
		printf("read() error!");
		_getch();
		system("cls");
		return;
	}
	serverScoreMessage[strLen] = '\0';
	system("cls");
	serverScore = atoi(serverScoreMessage); // 서버 스코어 저장
	clientScore = poker(); // 클라이언트 포커 진행
	printf("사용자: ");
	pokermulti(clientScore);

	sprintf(clientScoreMessage, "%d", clientScore);
	send(hSocket, clientScoreMessage, (int)strlen(clientScoreMessage), 0); // 서버에 포커 결과 전송
	
	
	printf("상대방: ");
	pokermulti(serverScore); // 서버 결과 출력

	strLen = recv(hSocket, resultMessage, sizeof(resultMessage) - 1, 0); // 서버측 결과 기다리기
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
		PlaySound(TEXT("sound\\lose.wav"), NULL, SND_ASYNC);
		printf("당신의 패배 ㅠㅠ\n");
		break;
	case 1:
		PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
		printf("무승부!\n아무 소득도 없었다...");
		*money += insertmoney;
		break;
	case 2:
		PlaySound(TEXT("sound\\win.wav"), NULL, SND_ASYNC);
		printf("당신의 승리!!\n%d원을 벌었다!\n", insertmoney*2);
		*money += insertmoney * 2;
		break;
	default:
		break;
	}
	
	closesocket(hSocket);
	WSACleanup();
	system("pause");
	system("cls");
	return;
}

void ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}