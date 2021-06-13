#define _CRT_SECURE_NO_WARNINGS
#include "modm.h"





typedef struct user {
	char id[ID_SIZE];		// 아이디
	char password[PASS_SIZE];	// 비밀번호
	char savedborrowmoney[MONEY_SIZE];
	char savedGugeolUpgrade[MONEY_SIZE];
	char savedUserMoney[MONEY_SIZE];
} USER;

MCI_OPEN_PARMS m_mciOpenParms;
MCI_PLAY_PARMS m_mciPlayParms;
DWORD m_dwDeviceID;
MCI_OPEN_PARMS mciOpen;
MCI_PLAY_PARMS mciPlay;

int dwID;
int moneyCheck(int*, char*, int*, int);
int moneyCheck_borrow(int*,char*, int*, int*, int*);
extern void story_explain();
extern void poker_explain();
extern void blackjack_explain();
extern void slot_explain();
extern void roulette_explain();
extern void horse_explain();
extern void shop_explain();
extern int slot(int);
extern int horse(int);
extern int lotto();
extern void textcolor(int);
extern int poker();
extern int pokersingle(int, int);
extern int poker_server(int);
extern void poker_client(int*);
extern int roulette(int);
extern int blackjack(int,int*);
extern void mySHA(unsigned char*, unsigned char*);
void timeprocess(char *);
void gotoxy(int, int);
void quit_message();
void CursorView() // 커서 숨기는 함수
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
	cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
int pullDownMenu(int,char**,int x, int y); // 메모리 절약을 위한 래그드 배열 사용
int pullDownMenu_yesorno(char** menulist, int x, int y);
int id_check(FILE*, char*);
int sel = 0;
long startadd; // 값 불러오기 위한 위치값 저장
USER get_record(FILE*);
void add_record(FILE*);
int login_record(FILE*, int*, int *,int *);
void update_money(FILE*, int*);
void update_gugeolUpgrade(FILE*, int*);
void update_borrowmoney(FILE*, int*);
void login_menu(char*, char*);
void ending();
int money = 0;
int gugeolUpgrade = 1;
int borrowmoney = 0;
int main(void) {
	int menu;
	int insertmoney;
	char *loginmenulist[MAIN_MENU] = {"로그인","계정생성","종료"};
	char *mainmenulist[MAIN_MENU] = { "싱글플레이","멀티플레이","종료" };
	char *singlemenulist[SINGLE_MENU] = { "포커","블랙잭","슬릇머신","룰렛","경마","은행","구걸하기","상점","설명","이전" };
	char* shopmenulist[SHOP_MENU] = { "구걸 업그레이드","로또","이전"};
	char *multimenulist[MULTI_MENU] = { "포커","블랙잭","이전" };
	char *multimenu_pokerlist[MULTI_SEL_MENU] = { "게임 생성","게임 참가","이전" };
	char* bankmenulist[BANK_MENU] = {"잔액조회","대출금 확인","대출상환","이전"};
	char* explainmenulist[EXPLAIN_MENU] = { "스토리","포커","블랙잭","슬릇머신","룰렛","경마","상점","이전" };
	char* yesornomenulist[2] = {"예","아니오"};
	unsigned char plain[32] = { 0 };
	unsigned char encrypt[32] = { 0 };
	char stringmoney[10] = { 0 };
	CursorView(); // 커서 숨기기
	FILE* fp = NULL;
	int loginStatus = 0;
	srand(time(NULL));
	// 이진 파일을 추가 모드로 오픈한다. 
	if (fopen_s(&fp,"user.dat", "a+")) {
		//printf(stderr, "입력을 위한 파일을 열 수 없습니다");
		exit(1);
	}
	
	do {
		menu = pullDownMenu(MAIN_MENU, loginmenulist,1,3);
		switch (menu)
		{
		case 0:
			printf("계정 로그인");
			system("cls");
			if (login_record(fp,&money,&gugeolUpgrade,&borrowmoney)) {
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
			PlaySound(TEXT("sound\\poweroff.wav"), NULL, SND_ASYNC);
			quit_message();
			return 0;
		}
		system("cls");
	} while (loginStatus != 1);
	do {
		menu = pullDownMenu(MAIN_MENU, mainmenulist,1,3);
		switch (menu)
		{
		case 0:
			do {
				menu = pullDownMenu(SINGLE_MENU, singlemenulist,1,3);
				switch (menu)
				{
				case 0:
					printf("소지하고 있는 돈: %d\n", money); // 포커
					printf("판돈을 입력하세요(최대 10만원): ");
					scanf_s("%s", stringmoney,sizeof(stringmoney));
					if (moneyCheck(&money, stringmoney,&insertmoney,100000)) {
						system("cls");
						money -= insertmoney;
						money += pokersingle(insertmoney, poker());
						update_money(fp, &money);
						system("pause");
						system("cls");
					}
					break;
				case 1:
					printf("소지하고 있는 돈: %d\n", money); // 블랙잭
					printf("판돈을 입력하세요(최대 10만원): ");
					scanf_s("%s", stringmoney, sizeof(stringmoney));
					if (moneyCheck(&money, stringmoney, &insertmoney, 100000)) {
						system("cls");
						money -= insertmoney;
						PlaySound(TEXT("sound\\button.wav"), NULL, SND_ASYNC);
						money += blackjack(insertmoney,&money);
						update_money(fp, &money);
						system("cls");
					}
					break;
				case 2:
					printf("소지하고 있는 돈: %d\n", money); // 슬릇머신
					printf("판돈을 입력하세요(최대 10만원): ");
					scanf_s("%s", stringmoney, sizeof(stringmoney));
					if (moneyCheck(&money, stringmoney, &insertmoney, 100000)) {
						system("cls");
						money -= insertmoney;
						money += slot(insertmoney);
						update_money(fp, &money);
						//system("pause");
						system("cls");
					}
					break;
					system("cls");
					break;
				case 3: // 룰렛
					printf("소지하고 있는 돈: %d\n",money);
					printf("판돈을 입력하세요(최대 10만원): ");
					scanf_s("%s", stringmoney, sizeof(stringmoney));
					if (moneyCheck(&money, stringmoney, &insertmoney, 100000)) {
						system("cls");
						money -= insertmoney;
						PlaySound(TEXT("sound\\button.wav"), NULL, SND_ASYNC);
						money += roulette(insertmoney);
						update_money(fp, &money);
						system("cls");
					}
					break;
				case 4:
					printf("소지하고 있는 돈: %d\n", money); // 경마
					printf("판돈을 입력하세요(최대 10만원): ");
					scanf_s("%s", stringmoney, sizeof(stringmoney));
					if (moneyCheck(&money, stringmoney, &insertmoney, 100000)) {
						system("cls");
						money -= insertmoney;
						money += horse(insertmoney);
						update_money(fp, &money);
						system("pause");
						system("cls");
					}
					break;
					
				case 5:
					sel = 0; // 상점 메뉴 접속 시 1번 메뉴부터 선택되게
					do
					{
						menu = pullDownMenu(BANK_MENU, bankmenulist, 1, 3);
						switch (menu)
						{
						case 0:
							printf("소지금: %d\n", money);
							system("pause");
							system("cls");
							break;
						case 1:
							printf("남은 대출금: %d\n",borrowmoney);
							system("pause");
							system("cls");
							break;
						case 2:
							if (borrowmoney <= 0) {
								printf("이미 대출금을 모두 갚았습니다!\n");
								system("pause");
								system("cls");
								break;
							}
							printf("상환할 대출금을 입력하세요: ");
							scanf_s("%s", stringmoney, sizeof(stringmoney));
							if (moneyCheck_borrow(&money,stringmoney ,&insertmoney, &borrowmoney, &gugeolUpgrade)) {
								system("cls");
								PlaySound(TEXT("sound\\button.wav"), NULL, SND_ASYNC);
								money -= insertmoney;
								borrowmoney -= insertmoney;
								update_money(fp, &money);
								update_borrowmoney(fp, &borrowmoney);
								system("cls");
							}
							if (borrowmoney == 0) {
								ending();
							}
							break;
						case 3:
							break;
						}
					} while (menu != 3);
					sel = 5; // 메인 메뉴로 갈시 상점 메뉴 선택되게
					break;
				case 6:
					if (money < 1000) {
						timeprocess("구걸중");
						money += 1000 * gugeolUpgrade;
						update_money(fp, &money);
						printf("%d원을 벌었습니다.\n", 1000 * gugeolUpgrade);
						PlaySound(TEXT("sound\\coin.wav"), NULL, SND_ASYNC);
					}
					else {
						printf("1000원 미만일때만 구걸이 가능합니다!\n");
						PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
					}
						
					system("pause");
					system("cls");
					break;
				case 7:
					sel = 0; // 상점 메뉴 접속 시 1번 메뉴부터 선택되게
					do
					{
						menu = pullDownMenu(SHOP_MENU, shopmenulist,1,3);
						switch (menu)
						{
						case 0:
							printf("구걸시 얻는 돈이 증가합니다.(Max Level 10)\n");
							if (gugeolUpgrade >= 10) {
								printf("현재 스킬 Lv.MAX\n");
								printf("이미 최대 레벨에 도달해서 구매할 수 없습니다!\n");
								PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
								system("pause");
								system("cls");
								break;
							}
							printf("현재 스킬 Lv.%d\n",gugeolUpgrade);
							printf("소지하고 있는 돈: %d\n", money);
							printf("구매 하시겠습니까?(10,000원)\n");
							if (pullDownMenu_yesorno(yesornomenulist, 3, 5) == 0) {
								if (moneyCheck(&money, "10000", &insertmoney,100000)) {
									money -= insertmoney;
									update_money(fp, &money);
									gugeolUpgrade++;
									update_gugeolUpgrade(fp, &gugeolUpgrade);
									printf("구매완료!\n");
									system("pause");
								}
								else 
									break;
							}
							
							system("cls");
							break;
						case 1:
							printf("로또를 구매합니다.\n");
							printf("소지하고 있는 돈: %d\n", money);
							printf("구매 하시겠습니까?(1,000원)\n");
							if (pullDownMenu_yesorno(yesornomenulist, 3, 5) == 0) {
								if (money < 1000) {
									printf("돈이 모자랍니다!");
									PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
									system("pause");
									system("cls");
									break;
								}
								if (money  <= 1000+ gugeolUpgrade * 1000) {
									printf("%d원 보다 많아야 구매가 가능합니다!\n", 1000 + gugeolUpgrade * 1000);
									PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
									system("pause");
									system("cls");
									break;
								}
								money -= 1000;
								money += lotto();
								gotoxy(0, 18);
								update_money(fp, &money);
								system("pause");
							}
							
							system("cls");
							break;
						case 2:
							break;
						}
					} while (menu != 2);
					sel = 7; // 메인 메뉴로 갈시 상점 메뉴 선택되게
					break;
				case 8:
					sel = 0; // 상점 메뉴 접속 시 1번 메뉴부터 선택되게
					do
					{
						menu = pullDownMenu(EXPLAIN_MENU, explainmenulist, 1, 3);
						switch (menu)
						{
						case 0: // 스토리
							story_explain();
							break;
						case 1: // 포커
							poker_explain();
							break;
						case 2: // 블랙잭
							blackjack_explain();
							break;
						case 3: // 슬릇머신
							slot_explain();
							break;
						case 4: // 룰렛
							roulette_explain();
							break;
						case 5: // 경마
							horse_explain();
							break;
						case 6: // 상점
							shop_explain();
							break;
						case 7: //이전
							break;
						}
						system("pause");
						system("cls");
					} while (menu != 7);
					sel = 8; // 메인 메뉴로 갈시 메뉴 선택되게
					break;
				case 9:
					break;
				}
			} while (menu != 9);
			sel = 0; // 메인 메뉴로 갈시 싱글플레이 메뉴 선택되게
			break;
		case 1:
			sel = 0;
			do
			{
				menu = pullDownMenu(MULTI_MENU, multimenulist,1,3);
				switch (menu)
				{
				case 0:
					sel = 0;
					do
					{
						menu = pullDownMenu(MULTI_SEL_MENU, multimenu_pokerlist,1,3);
						switch (menu)
						{
						case 0:
							printf("소지하고 있는 돈: %d\n", money);
							printf("판돈을 입력하세요: ");
							scanf_s("%s", stringmoney, sizeof(stringmoney));
							if (moneyCheck(&money, stringmoney, &insertmoney, 100000)) {
								system("cls");
								money -= insertmoney;
								printf("사용자의 접속을 기다리는 중...\n이전으로 가려면 q를 입력하세요.\n");
								money += poker_server(insertmoney);
								update_money(fp, &money);
							}
							break;
						case 1:
							poker_client(&money);
							update_money(fp, &money);
							break;
						case 2:
							break;
						}
					} while (menu != 2);
					sel = 0;
					break;
				case 1:
					printf("블랙잭 멀티\n");
					system("pause");
					system("cls");
					break;
				case 2:
					break;
				}
			} while (menu != 2);
			menu = 0;
			sel = 1; // 메인 메뉴로 갈시 멀티플레이 메뉴 선택되게
			break;
		case 2:
			break;
		}
	} while (menu != 2);
	PlaySound(TEXT("sound\\poweroff.wav"), NULL, SND_ASYNC);
	quit_message();
	return 0;
}

int pullDownMenu(int max_menu, char** menulist,int x,int y)
{
	char ch;
	while (1) {
		for (int i = 0; i < max_menu; i++) {
			if (sel == i)
				textcolor(12);
			else
				textcolor(15);
			if (max_menu % 2 == 1) {
				gotoxy(20 * i + x, y);
				printf("%d.%s", i + 1, menulist[i]);
			}
			else {
				if (i < max_menu / 2) {
					gotoxy(20 * i + x, y);
					printf("%d.%s", i + 1, menulist[i]);
				}
				else {
					gotoxy(20 * (i - max_menu / 2) +x, 3+y);
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
int pullDownMenu_yesorno(char** menulist,int x, int y)
{
	char ch;
	int sel = 0;
	while (1) {
		for (int i = 0; i < 2; i++) {
			if (sel == i)
				textcolor(12);
			else
				textcolor(15);
			gotoxy(20 * i + x, y);
			printf("%s", menulist[i]);
		}
		textcolor(15);
		ch = _getch();
		if (ch == KEY_LEFT) {
			PlaySound(TEXT("sound\\button2.wav"), NULL, SND_ASYNC);
			sel = ((sel - 1) + 2) % 2;
		}
		else if (ch == KEY_RIGHT) {
			PlaySound(TEXT("sound\\button2.wav"), NULL, SND_ASYNC);
			sel = (sel + 1) % 2;
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
int moneyCheck_borrow(int* money, char* stringmoney, int *insertmoney,int* borrowmoney,int* gugeolUpgrade) {
	rewind(stdin);
	for (int i = 0; stringmoney[i] != '\0'; i++)
	{
		if (!isdigit(stringmoney[i])) {
			PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
			printf("숫자만 넣어주세요!\n");
			system("pause");
			system("cls");
			return 0;
		}
	}
	*insertmoney = atoi(stringmoney);
	if (*insertmoney > *borrowmoney) {
		PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
		printf("빚보다 많이 갚을 수 없습니다!\n");
		system("pause");
		system("cls");
		return 0;
	}
	if (*insertmoney > *money) {
		PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
		printf("가지고 있는 돈이 적습니다!\n");
		system("pause");
		system("cls");
		return 0;
	}
	if (*insertmoney <= 1000+*gugeolUpgrade*1000) {
		PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
		printf("%d원 보다는 많아야 합니다!\n", 1000 + *gugeolUpgrade * 1000);
		system("pause");
		system("cls");
		return 0;
	}
	return 1;
}
int moneyCheck(int *money,char*stringmoney, int* insertmoney, int maxmoney) {
	rewind(stdin);
	for (int i = 0; stringmoney[i] != '\0'; i++)
	{
		if (!isdigit(stringmoney[i])) {
			PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
			printf("숫자만 넣어주세요!\n");
			system("pause");
			system("cls");
			return 0;
		}
	}
	*insertmoney = atoi(stringmoney);
	if (maxmoney != 0) { // 0으로 설정시 무제한
		if (*insertmoney > maxmoney) {
			PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
			printf("%d원 이하만 가능합니다!\n", maxmoney);
			system("pause");
			system("cls");
			return 0;
		}
	}
	if (*insertmoney > *money) {
		PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
		printf("가지고 있는 돈이 적습니다!\n");
		system("pause");
		system("cls");
		return 0;
	}
	if (*insertmoney <= 0) {
		PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
		printf("1원 이상 넣어주세요!\n");
		system("pause");
		system("cls");
		return 0;
	}
	return 1;
}
void login_menu(char* id, char* password) {
	int num = 0;
	unsigned char plain[32] = {0};
	unsigned char encrypt[32];
	memset(plain, 0x00, sizeof(plain));
	memset(encrypt, 0x00, sizeof(encrypt));
	gotoxy(4, 1); printf("LOGIN");
	gotoxy(3, 2); printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	gotoxy(3, 3); printf("┃");
	gotoxy(36, 3); printf("┃");
	gotoxy(3, 4); printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
	gotoxy(4, 6); printf("PASSWORD");
	gotoxy(3, 7); printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	gotoxy(3, 8); printf("┃");
	gotoxy(36, 8); printf("┃");
	gotoxy(3, 9); printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
	gotoxy(5, 3); printf("_"); gotoxy(5, 3);
	while ((id[num] = _getch()) != '\r')
	{
		if (id[num] == '\b' && num != 0) {
			printf("\b \b");
			id[num] = '\0';
			num--;
		}
		else {
			if ((id[num] == '\b' && num == 0) || num >= ID_SIZE - 1)
				continue;
			if ((id[num]) == '\t')
				continue;
			if (plain[num] == 32) // 스페이스바
				continue;
			else
				_putch(id[num]);
			num++;
		}
	}
	id[num] = '\0';
	gotoxy(5, 8); printf("_"); gotoxy(5, 8);
	num = 0;
	PlaySound(TEXT("sound\\button.wav"), NULL, SND_ASYNC);
	do
	{
		while ((plain[num] = _getch()) != '\r')
		{
			if (plain[num] == '\b' && num != 0) {
				printf("\b \b");
				plain[num] = '\0';
				num--;
			}
			else {
				if ((plain[num] == '\b' && num == 0) || num >= ID_SIZE - 1)
					continue;
				if ((plain[num]) == '\t')
					continue;
				if (plain[num] == 32) // 스페이스바
					continue;
				else
					_putch('*');
				num++;
			}
		}
	} while (plain[0] == '\r');
	
	
	
	plain[num] = '\0';
	mySHA(plain, encrypt);
	for (int i = 0; i < 32; i++)
		sprintf(password + 2 * i, "%02x", *(encrypt+i));
	gotoxy(0, 11);
}
void update_money(FILE* fp, int* money)
{
	char tempmoney[MONEY_SIZE] = { 0 };
	fopen_s(fp, "user.dat", "r+");
	fseek(fp, startadd - MONEY_SIZE, SEEK_SET);
	sprintf_s(tempmoney, MONEY_SIZE,"%d",*money);
	fwrite(tempmoney, MONEY_SIZE, 1, fp);
	fclose(fp);
}
void update_gugeolUpgrade(FILE* fp, int* gugeolUpgrade)
{
	char tempupgrade[MONEY_SIZE] = { 0 };
	fopen_s(fp, "user.dat", "r+");
	fseek(fp, startadd - MONEY_SIZE*2, SEEK_SET);
	sprintf_s(tempupgrade, MONEY_SIZE,"%d", *gugeolUpgrade);
	fwrite(tempupgrade, MONEY_SIZE, 1, fp);
	fclose(fp);
}
void update_borrowmoney(FILE* fp, int* borrowmoney)
{
	char tempborrowmoney[MONEY_SIZE] = { 0 };
	fopen_s(fp, "user.dat", "r+");
	fseek(fp, startadd - MONEY_SIZE * 3, SEEK_SET);
	sprintf_s(tempborrowmoney, MONEY_SIZE, "%d", *borrowmoney);
	fwrite(tempborrowmoney, MONEY_SIZE, 1, fp);
	fclose(fp);
}
int login_record(FILE* fp, int* money, int* gugeolUpgrade,int *borrowmoney)
{
	char id[ID_SIZE] = { '\0' };
	char password[PASS_SIZE] = { '\0' };
	USER data;
	fseek(fp, 0, SEEK_SET);	// 파일의 처음으로 간다
	login_menu(id, password);
	while (!feof(fp)) {		// 파일의 끝까지 반복한다
		fread(&data, sizeof(data), 1, fp);
		if ((strcmp(data.id, id) == 0) && (strcmp(data.password, password) == 0)) {	// 이름을 비교한다
			startadd = ftell(fp);
			*borrowmoney = atoi(data.savedborrowmoney);
			*gugeolUpgrade = atoi(data.savedGugeolUpgrade);
			*money = atoi(data.savedUserMoney);
			PlaySound(TEXT("sound\\button.wav"), NULL, SND_ASYNC);
			return 0;
		}
	}
	PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
	printf("해당되는 계정이 없거나 비밀번호가 맞지 않습니다.\n");
	return 1;
}
void add_record(FILE* fp)
{
	USER data;
	data = get_record(fp);	// 사용자로부터 데이터를 받아서 구조체에 저장
	if (id_check(fp, data.id)) {
		PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
		printf("중복된 아이디 입니다!\n");
		system("pause");
		return;
	}
	fseek(fp, 0, SEEK_END);	// 파일의 끝으로 간다	
	fwrite(&data, sizeof(data), 1, fp);	// 구조체 데이터를 파일에 쓴다
}

USER get_record(FILE* fp)
{
	USER data;
	for (int i = 0; i < ID_SIZE; i++)
	{
		data.id[i] = '\0';
	}
	for (int i = 0; i < PASS_SIZE; i++) {
		data.password[i] = '\0';
	}
	for (int i = 0; i < MONEY_SIZE-1; i++)
	{
		data.savedUserMoney[i] = '0';
		data.savedGugeolUpgrade[i] = '0';
		data.savedborrowmoney[i] = '0';
	}
	data.savedUserMoney[MONEY_SIZE-1] = '\0';
	data.savedGugeolUpgrade[MONEY_SIZE-1] = '\0';
	data.savedborrowmoney[MONEY_SIZE - 1] = '\0';
	fflush(stdin);		// 표준 입력의 버퍼를 비운다
	do {
		login_menu(data.id,data.password);
		printf("\n");
		if (data.id[0] == '\0' || data.password[0] == '\0') {
			PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
			printf("공백을 입력할 수 없습니다.\n");
			system("pause");
			system("cls");
			continue;
		}
		break;
	} while (1);
	PlaySound(TEXT("sound\\button.wav"), NULL, SND_ASYNC);
	data.savedGugeolUpgrade[9] = '1'; // 1
	data.savedUserMoney[5] = '1'; // 1000
	data.savedborrowmoney[2] = '1'; // 10000000
	return data;
}
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
void quit_message() {
	printf("종료중입니다.");
	for (int i = 0; i < 3; i++)
	{
		Sleep(300);
		printf(".");
	}
}
void timeprocess(char * str) {
	for (int i = 0; i < 5; i++)
	{
		printf("%s",str);
		Sleep(250);
		printf(".");
		Sleep(250);
		printf(".");
		Sleep(250);
		printf(".");
		Sleep(250);
		system("cls");
	}
}

void ending() {
	mciOpen.lpstrElementName = "sound\\bgm.mp3"; // 파일 경로 입력
	mciOpen.lpstrDeviceType = "mpegvideo";

	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE,
		(DWORD)(LPVOID)&mciOpen);

	dwID = mciOpen.wDeviceID;

	mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, // play & repeat
		(DWORD)(LPVOID)&m_mciPlayParms);
	system("cls");
	for (int i = 1; i < 92; i++)
	{
		system("cls");
		if (i <= 35) {
			gotoxy(14, 37 - i); printf("♠Yeungjin Casino♠");
		}
		if (i <= 47) {
			textcolor(12);
			gotoxy(17, 47 - i); printf("PM, 포커, 룰렛");
			textcolor(15);
		}
		if (i <= 49) {
			gotoxy(20, 49 - i); printf("전 석 진");
		}
		if (i <= 54) {
			textcolor(12);
			gotoxy(21, 54 - i); printf("블랙잭");
			textcolor(15);
		}
		if (i <= 56) {
			gotoxy(20, 56 - i); printf("김 재 현");
		}
		if (i <= 61) {
			textcolor(12);
			gotoxy(22, 61 - i); printf("경마");
			textcolor(15);
		}
		if (i <= 63) {
			gotoxy(20, 63 - i); printf("권 오 윤");
		}
		if (i <= 68) {
			textcolor(12);
			gotoxy(20, 68 - i); printf("슬릇머신");
			textcolor(15);
		}
		if (i <= 70) {
			gotoxy(20, 70 - i); printf("전 태 웅");
		}
		if (i <= 75) {
			textcolor(12);
			gotoxy(21, 75 - i); printf("디자인");
			textcolor(15);
		}
		if (i <= 77) {
			gotoxy(20, 77 - i); printf("최 진 영");
		}

		if (i <= 82) {
			textcolor(12);
			gotoxy(20, 82 - i); printf("제작기간");
			textcolor(15);
		}
		if (i <= 84) {
			gotoxy(20, 84 - i); printf("2021/05/06~2021/06/13");
		}

		if (i <= 87) {
			textcolor(12);
			gotoxy(13, 87 - i); printf("♠Thanks For Playing!♠");
			textcolor(15);
		}
		
		gotoxy(0, 0);
		Sleep(400);


	}
	
	system("pause");
	mciSendCommandW(dwID, MCI_CLOSE, 0, NULL);
	system("cls");
}