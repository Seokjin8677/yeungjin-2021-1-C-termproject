#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#define LOGIN_SIZE 20
#define MAIN_MENU 3
#define SINGLE_MENU 8
#define MULTI_MENU 4
#define MULTI_SEL_MENU 3
#define KEY_UP  0x48
#define KEY_DOWN 0x50
#define KEY_LEFT  0x4B
#define KEY_RIGHT 0x4D
#define KEY_RETURN 0x0D
#define MAX_MENU_CHAR 20
typedef struct user {
	char id[LOGIN_SIZE];		// 아이디
	char password[LOGIN_SIZE];	// 비밀번호
	int userMoney;
} USER;
extern void textcolor(int);
extern int poker();
extern int pokersingle(int, int);
extern int poker_server(int);
extern void poker_client(int*);
void gotoxy(int, int);
int moneyCheck(int, int);
void CursorView() // 커서 숨기는 함수
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
	cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
int pullDownMenu(int,char**); // 메모리 절약을 위한 래그드 배열 사용
int sel = 0;
int startadd; // 돈 불러오기 위한 위치값 저장

int id_check(FILE* fp, char* id) {
	USER data;
	fseek(fp, 0, SEEK_SET);	// 파일의 처음으로 간다
	while (!feof(fp)) {		// 파일의 끝까지 반복한다
		fread(&data, sizeof(data), 1, fp);
		if (strcmp(data.id, id) == 0) {	// 이름을 비교한다
			return 1;
		}
	}
	return 0;
}
USER get_record(FILE *fp)
{
	USER data;
	fflush(stdin);		// 표준 입력의 버퍼를 비운다
	do {
		printf("아이디: ");
		gets_s(data.id, LOGIN_SIZE);	// 이름을 입력받는다
		printf("비밀번호: ");
		gets_s(data.password, LOGIN_SIZE);	// 주소를 입력받는다
		if ((strcmp(data.id, "") == 0 )||(strcmp(data.password, "") == 0)) {
			printf("공백을 입력할 수 없습니다.\n");
			system("pause");
			system("cls");
			continue;
		}
		break;
	} while (1);
	data.userMoney = 10000;
	return data;
}

void add_record(FILE* fp)
{
	USER data;
	data = get_record(fp);	// 사용자로부터 데이터를 받아서 구조체에 저장
	if (id_check(fp, data.id)) {
		printf("중복된 아이디 입니다!\n");
		system("pause");
		return;
	}
	fseek(fp, 0, SEEK_END);	// 파일의 끝으로 간다	
	fwrite(&data, sizeof(data), 1, fp);	// 구조체 데이터를 파일에 쓴다
}
int login_record(FILE* fp, int* money)
{
	char id[LOGIN_SIZE];
	char password[LOGIN_SIZE];
	USER data;
	fseek(fp, 0, SEEK_SET);	// 파일의 처음으로 간다
	fflush(stdin);
	printf("아이디: ");
	gets_s(id, LOGIN_SIZE);		// 이름을 입력받는다
	fflush(stdin);
	printf("비밀번호: ");
	gets_s(password, LOGIN_SIZE);
	while (!feof(fp)) {		// 파일의 끝까지 반복한다
		fread(&data, sizeof(data), 1, fp);
		if ((strcmp(data.id, id) == 0)&& (strcmp(data.password, password) == 0)) {	// 이름을 비교한다
			//printf("\n현재 파일 위치 지시자의 위치 : %ld\n", ftell(fp));
			*money = data.userMoney;
			startadd = ftell(fp)-4;
			//printf("로그인 성공!\n");
			return 0;
			/*if ((strcmp(data.password, password) == 0)) {
				return 0;
			}*/
		}
	}
	//printf("\n현재 파일 위치 지시자의 위치 : %ld\n", ftell(fp));
	printf("해당되는 계정이 없거나 비밀번호가 맞지 않습니다.\n");
	return 1;
}
void update_record(FILE* fp,int *money)
{
	//printf("\n현재 파일 위치 지시자의 위치 : %ld\n", ftell(fp));
	//USER data;
	//data.userMoney = *money;
	//printf("%d\n", data.userMoney);
	//fopen_s(&fp, "user.dat", "wb");
	fopen_s(fp, "user.dat", "r+t");
	//printf("%d", startadd);
	fseek(fp, startadd, SEEK_SET);
	//printf("\n현재 파일 위치 지시자의 위치 : %ld\n", ftell(fp));
	fwrite(money,sizeof(int),1,fp);
	fclose(fp);
}
int main(void) {
	int menu;
	int money = 0;
	int insertmoney;
	char *loginmenulist[MAIN_MENU] = {"로그인","계정생성","종료"};
	char *mainmenulist[MAIN_MENU] = { "싱글플레이","멀티플레이","종료" };
	char *singlemenulist[SINGLE_MENU] = { "포커","블랙잭","슬릇머신","룰렛","경마","잔액조회","돈벌기","이전" };
	char *multimenulist[MULTI_MENU] = { "포커","블랙잭","잔액조회","이전" };
	char *multimenu_pokerlist[MULTI_SEL_MENU] = { "게임 생성","게임 참가","이전" };
	CursorView(); // 커서 숨기기
	FILE* fp = NULL;
	int select;
	int loginStatus = 0;
	// 이진 파일을 추가 모드로 오픈한다. 
	if (fopen_s(&fp,"user.dat", "a+")) {
		//printf(stderr, "입력을 위한 파일을 열 수 없습니다");
		exit(1);
	}
	do {
		menu = pullDownMenu(MAIN_MENU, loginmenulist);
		switch (menu)
		{
		case 0:
			printf("계정 로그인");
			system("cls");
			if (login_record(fp,&money)) {
				system("pause");
				system("cls");
				break;
			}
			system("cls");
			loginStatus = 1;
			fclose(fp);
			break;
		case 1:
			printf("계정 생성");
			system("cls");
			add_record(fp);
			break;
		case 2:
			fclose(fp);
			PlaySound(TEXT("sound\\poweroff.wav"), NULL, SND_SYNC);
			return 0;
		}
		system("cls");
	} while (loginStatus != 1);
	do {
		menu = pullDownMenu(MAIN_MENU, mainmenulist);
		switch (menu)
		{
		case 0:
			do {
				menu = pullDownMenu(SINGLE_MENU, singlemenulist);
				switch (menu)
				{
				case 0:
					printf("판돈을 입력하세요: ");
					scanf_s("%d", &insertmoney);
					if (moneyCheck(money,insertmoney)) {
						system("cls");
						money -= insertmoney;
						money += pokersingle(insertmoney, poker());
						system("pause");
						system("cls");
					}
					update_record(fp, &money);
					break;
				case 1:
					//printf("준비중입니다.\n");
					_getch();
					system("cls");
					break;
				case 2:
					printf("준비중입니다.\n");
					_getch();
					system("cls");
					break;
				case 3:
					printf("준비중입니다.\n");
					_getch();
					system("cls");
					break;
				case 4:
					printf("준비중입니다.\n");
					_getch();
					system("cls");
					break;
				case 5:
					printf("잔액: %d\n", money);
					_getch();
					system("cls");
					break;
				case 6:
					money += 1000;
					update_record(fp, &money);
					printf("1000원을 벌었습니다.\n");
					_getch();
					system("cls");
					break;
				case 7:
					break;
				}
			} while (menu != 7);
			sel = 0; // 메인 메뉴로 갈시 싱글플레이 메뉴 선택되게
			break;
		case 1:
			sel = 0; // 멀티플레이 메뉴 접속 시 1번 메뉴부터 선택되게
			do
			{
				menu = pullDownMenu(MULTI_MENU, multimenulist);
				switch (menu)
				{
				case 0:
					sel = 0;
					do
					{
						menu = pullDownMenu(MULTI_SEL_MENU, multimenu_pokerlist);
						switch (menu)
						{
						case 0:
							printf("판돈을 입력하세요: ");
							scanf_s("%d", &insertmoney);
							if (moneyCheck(money, insertmoney)) {
								system("cls");
								money -= insertmoney;
								printf("사용자의 접속을 기다리는 중...\n이전으로 가려면 q를 입력하세요.\n");
								money += poker_server(insertmoney);
							}
							update_record(fp, &money);
							break;
						case 1:
							poker_client(&money);
							update_record(fp, &money);
							break;
						case 2:
							break;
						}
					} while (menu != 2);
					sel = 0;
					break;
				case 1:
					printf("준비중입니다.\n");
					_getch();
					system("cls");
					break;
				case 2:
					printf("준비중입니다.\n");
					_getch();
					system("cls");
					break;
				case 3:
					break;
				}
			} while (menu != 3);
			sel = 1; // 메인 메뉴로 갈시 멀티플레이 메뉴 선택되게
			break;
		case 2:
			break;
		}
	} while (menu != 2);
	PlaySound(TEXT("sound\\poweroff.wav"), NULL, SND_SYNC);
	return 0;
}

int pullDownMenu(int max_menu, char** menulist)
{
	char ch;
	while (1) {
		for (int i = 0; i < max_menu; i++) {
			if (sel == i)
				textcolor(12);
			else
				textcolor(15);
			if (max_menu % 2 == 1) {
				gotoxy(20 * i + 1, 3);
				printf("%d.%s", i + 1, menulist[i]);
			}
			else {
				if (i < max_menu / 2) {
					gotoxy(20 * i + 1, 3);
					printf("%d.%s", i + 1, menulist[i]);
				}
				else {
					gotoxy(20 * (i - max_menu / 2) + 1, 6);
					printf("%d.%s", i + 1, menulist[i]);
				}
			}
		}
		textcolor(15);
		ch = _getch();
		if (ch == KEY_LEFT) {
			PlaySound(TEXT("sound\\button2.wav"), NULL, SND_ASYNC);
			sel = ((sel - 1) + max_menu) % max_menu;
		}
		else if (ch == KEY_RIGHT) {
			PlaySound(TEXT("sound\\button2.wav"), NULL, SND_ASYNC);
			sel = (sel + 1) % max_menu;
		}
		else if (ch == KEY_UP && max_menu % 2 == 0) {
			PlaySound(TEXT("sound\\button2.wav"), NULL, SND_ASYNC);
			sel = ((sel + max_menu / 2) + max_menu) % max_menu;
		}
		else if (ch == KEY_DOWN && max_menu % 2 == 0) {
			PlaySound(TEXT("sound\\button2.wav"), NULL, SND_ASYNC);
			sel = ((sel - max_menu / 2) + max_menu) % max_menu;
		}
		else if (ch == KEY_RETURN) {
			PlaySound(TEXT("sound\\button.wav"), NULL, SND_ASYNC);
			break;
		}
		Sleep(1);
	}
	system("cls");
	return sel;
}

void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos); //프로토타입의 값대로 위치이동
}

int moneyCheck(int money, int insertmoney) {
	if (insertmoney > money) {
		PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
		printf("가지고 있는 돈이 적습니다...\n");
		system("pause");
		system("cls");
		return 0;
	}
	if (insertmoney < 0) {
		PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
		printf("1원 이상 넣어주세요!\n");
		system("pause");
		system("cls");
		return 0;
	}
	return 1;
}