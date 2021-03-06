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
void timeprocess(char *);
void gotoxy(int, int);
void quit_message();
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
extern void gotoxy(int, int);
extern void textcolor(int);
extern void init();
extern void background();
extern int pokersingle(int, int);
extern int poker();
extern int blackjack(int, int*);
extern int slot(int);
extern int roulette(int);
extern int horse(int);
extern int lotto();
extern void story_explain();
extern void poker_explain();
extern void blackjack_explain();
extern void slot_explain();
extern void roulette_explain();
extern void horse_explain();
extern void shop_explain();
extern int poker_server(int);
extern void poker_client(int*);
extern void mySHA(unsigned char*, unsigned char*);


int main(void) {
	int menu;
	int insertmoney;
	char* loginmenulist[MAIN_MENU] = { "로그인","계정생성","종료" };
	char* mainmenulist[MAIN_MENU] = { "싱글플레이","멀티플레이","종료" };
	char* singlemenulist[SINGLE_MENU] = { "포커","블랙잭","슬릇머신","룰렛","경마","은행","구걸하기","상점","설명","이전" };
	char* shopmenulist[SHOP_MENU] = { "구걸 UP","로또","이전" };
	char* multimenulist[MULTI_MENU] = { "포커","이전" };
	char* multimenu_pokerlist[MULTI_SEL_MENU] = { "게임 생성","게임 참가","이전" };
	char* bankmenulist[BANK_MENU] = { "잔액조회","대출금 확인","대출상환","이전" };
	char* explainmenulist[EXPLAIN_MENU] = { "스토리","포커","블랙잭","슬릇머신","룰렛","경마","상점","이전" };
	char* yesornomenulist[2] = { "예","아니오" };

	unsigned char plain[32] = { 0 };
	unsigned char encrypt[32] = { 0 };
	char stringmoney[10] = { 0 };


	init(); // 콘솔창 세팅
	//background();




	/*start_screen();

	



	
	Sleep(3000);
	system("cls");
	*/
	
	background();
	

	FILE* fp = NULL;
	int loginStatus = 0;
	srand((unsigned)time(NULL));
	// 이진 파일을 추가 모드로 오픈한다. 
	if (fopen_s(&fp,"user.dat", "a+")) {
		//printf(stderr, "입력을 위한 파일을 열 수 없습니다");
		exit(1);
	}

	do {
		background();
		menu = pullDownMenu(MAIN_MENU, loginmenulist,MENU_X-2, MENU_Y);
		switch (menu)
		{
		case 0:
			printf("계정 로그인");
			system("cls");
			background();
			if (login_record(fp,&money,&gugeolUpgrade,&borrowmoney)) {
				_getch();
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
			background();
			add_record(fp);
			break;
		case 2:
			fclose(fp);
			background();
			PlaySound(TEXT("sound\\poweroff.wav"), NULL, SND_ASYNC);
			quit_message();
			return 0;
		}
		system("cls");
	} while (loginStatus != 1);
	do {
		background();
		menu = pullDownMenu(MAIN_MENU, mainmenulist, MENU_X-3, MENU_Y);
		switch (menu)
		{
		case 0:
			do {
				background();
				menu = pullDownMenu(SINGLE_MENU, singlemenulist, MENU_X-17, MENU_Y);
				switch (menu)
				{
				case 0:
					background();
					gotoxy(60,37);
					printf("소지하고 있는 돈: %d", money); // 포커
					gotoxy(60, 38);
					printf("판돈을 입력하세요(최대 10만원)");
					gotoxy(90, 39);
					printf("원");
					gotoxy(78, 39);
					scanf_s("%s", stringmoney,sizeof(stringmoney));
					if (moneyCheck(&money, stringmoney,&insertmoney,100000)) {
						background();
						system("cls");
						money -= insertmoney;
						money += pokersingle(insertmoney, poker());
						update_money(fp, &money);
						_getch();
						system("cls");
					}
					break;
				case 1:
					background();
					gotoxy(60, 37);
					printf("소지하고 있는 돈: %d", money); // 블랙잭
					gotoxy(60, 38);
					printf("판돈을 입력하세요(최대 10만원)");
					gotoxy(90, 39);
					printf("원");
					gotoxy(78, 39);
					scanf_s("%s", stringmoney, sizeof(stringmoney));
					if (moneyCheck(&money, stringmoney, &insertmoney, 100000)) {
						system("cls");
						background();
						money -= insertmoney;
						PlaySound(TEXT("sound\\button.wav"), NULL, SND_ASYNC);
						money += blackjack(insertmoney,&money);
						update_money(fp, &money);
						//_getch();
						system("cls");
					}
					break;
				case 2:
					background();
					gotoxy(60, 37);
					printf("소지하고 있는 돈: %d", money); // 슬롯머신
					gotoxy(60, 38);
					printf("판돈을 입력하세요(최대 10만원)");
					gotoxy(90, 39);
					printf("원");
					gotoxy(78, 39);
					scanf_s("%s", stringmoney, sizeof(stringmoney));
					if (moneyCheck(&money, stringmoney, &insertmoney, 100000)) {
						system("cls");
						background();
						money -= insertmoney;
						money += slot(insertmoney);
						update_money(fp, &money);
						//system("pause");
						_getch();
						system("cls");
					}
					break;
					system("cls");
					break;
				case 3: // 룰렛
					background();
					gotoxy(60, 37);
					printf("소지하고 있는 돈: %d", money); // 룰렛
					gotoxy(60, 38);
					printf("판돈을 입력하세요(최대 10만원)");
					gotoxy(90, 39);
					printf("원");
					gotoxy(78, 39);
					scanf_s("%s", stringmoney, sizeof(stringmoney));
					if (moneyCheck(&money, stringmoney, &insertmoney, 100000)) {
						system("cls");
						money -= insertmoney;
						PlaySound(TEXT("sound\\button.wav"), NULL, SND_ASYNC);
						money += roulette(insertmoney);
						update_money(fp, &money);
						//_getch();
						system("cls");
					}
					break;
				case 4:
					background();
					gotoxy(60, 37);
					printf("소지하고 있는 돈: %d", money); // 경마
					gotoxy(60, 38);
					printf("판돈을 입력하세요(최대 10만원)");
					gotoxy(90, 39);
					printf("원");
					gotoxy(78, 39);
					scanf_s("%s", stringmoney, sizeof(stringmoney));
					if (moneyCheck(&money, stringmoney, &insertmoney, 100000)) {
						system("cls");
						money -= insertmoney;
						money += horse(insertmoney);
						update_money(fp, &money);
						_getch();
						system("cls");
					}
					break;
					
				case 5:
					sel = 0; // 상점 메뉴 접속 시 1번 메뉴부터 선택되게
					do
					{
						background();
						menu = pullDownMenu(BANK_MENU, bankmenulist, MENU_X-3, MENU_Y);
						switch (menu)
						{
						case 0:
							background();
							gotoxy(39, 17);
							printf("소지금: %d\n", money);
							_getch();
							system("cls");
							break;
						case 1:
							background();
							gotoxy(39, 17);
							printf("남은 대출금: %d\n",borrowmoney);
							_getch();
							system("cls");
							break;
						case 2:
							background();
							if (borrowmoney <= 0) {
								gotoxy(36, 17);
								printf("이미 대출금을 모두 갚았습니다!\n");
								_getch();
								system("cls");
								break;
							}
							background();
							gotoxy(25, 17);
							printf("상환할 대출금을 입력하세요:\n");
							gotoxy(56, 17);
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
					background();
					if (money < 1000) {
						timeprocess("구걸중");
						money += 1000 * gugeolUpgrade;
						update_money(fp, &money);
						printf("%d원을 벌었습니다.\n", 1000 * gugeolUpgrade);
						PlaySound(TEXT("sound\\coin.wav"), NULL, SND_ASYNC);
					}
					else {
						gotoxy(32, 18);
						printf("1000원 미만일때만 구걸이 가능합니다!\n");
						PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
					}
					_getch();
					system("cls");
					break;
				case 7:
					background();
					sel = 0; // 상점 메뉴 접속 시 1번 메뉴부터 선택되게
					do
					{
						background();
						menu = pullDownMenu(SHOP_MENU, shopmenulist, MENU_X, MENU_Y);
						switch (menu)
						{
						case 0:
							background();
							gotoxy(30, 17);
							printf("구걸시 얻는 돈이 증가합니다.(Max Level 10)\n");
							if (gugeolUpgrade >= 10) {
								gotoxy(30, 17);
								printf("현재 스킬 Lv.MAX\n");
								gotoxy(25, 18);
								printf("이미 최대 레벨에 도달해서 구매할 수 없습니다!\n");
								PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
								_getch();
								system("cls");
								break;
							}
							background();
							gotoxy(30, 17);
							printf("현재 스킬 Lv.%d\n",gugeolUpgrade);
							gotoxy(30, 18);
							printf("소지하고 있는 돈: %d\n", money);
							gotoxy(30, 19);
							printf("구매 하시겠습니까?(10,000원)\n");
							if (pullDownMenu_yesorno(yesornomenulist, 30, 20) == 0) {
								if (moneyCheck(&money, "10000", &insertmoney,100000)) {
									money -= insertmoney;
									update_money(fp, &money);
									gugeolUpgrade++;
									update_gugeolUpgrade(fp, &gugeolUpgrade);
									background();
									gotoxy(30, 18);
									printf("구매완료!\n");
									_getch();
								}
								else 
									break;
							}
							
							system("cls");
							break;
						case 1:
							background();
							gotoxy(30, 17);
							printf("로또를 구매합니다.\n");
							gotoxy(30, 18);
							printf("소지하고 있는 돈: %d\n", money);
							gotoxy(30, 19);
							printf("구매 하시겠습니까?(1,000원)\n");
							if (pullDownMenu_yesorno(yesornomenulist, 30, 20) == 0) {
								if (money < 1000) {
									gotoxy(30, 18);
									printf("돈이 모자랍니다!");
									PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
									_getch();
									system("cls");
									break;
								}
								if (money  <= 1000+ gugeolUpgrade * 1000) {
									background();
									gotoxy(30, 18);
									printf("%d원 보다 많아야 구매가 가능합니다!\n", 1000 + gugeolUpgrade * 1000);
									PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
									_getch();
									system("cls");
									break;
								}
								money -= 1000;
								money += lotto();
								gotoxy(0, 18);
								update_money(fp, &money);
								_getch();
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
						background();
						menu = pullDownMenu(EXPLAIN_MENU, explainmenulist, MENU_X-11, MENU_Y);
						switch (menu)
						{
						case 0: // 스토리
							background();
							gotoxy(55,10);
							story_explain();
							_getch();
							system("cls");
							break;
						case 1: // 포커
							background();
							gotoxy(55, 5);
							poker_explain();
							_getch();
							system("cls");
							break;
						case 2: // 블랙잭
							background();
							gotoxy(55, 3);
							blackjack_explain();
							_getch();
							system("cls");
							break;
						case 3: // 슬릇머신
							background();
							gotoxy(55, 10);
							slot_explain();
							_getch();
							system("cls");
							break;
						case 4: // 룰렛
							background();
							gotoxy(55, 10);
							roulette_explain();
							_getch();
							system("cls");
							break;
						case 5: // 경마
							background();
							gotoxy(55, 10);
							horse_explain();
							_getch();
							system("cls");
							break;
						case 6: // 상점
							background();
							gotoxy(53, 10);
							shop_explain();
							_getch();
							system("cls");
							break;
						case 7: //이전
							break;
						}
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
				background();
				menu = pullDownMenu(MULTI_MENU, multimenulist, MENU_X, MENU_Y);
				switch (menu)
				{
				case 0:
					sel = 0;
					do
					{
						background();
						menu = pullDownMenu(MULTI_SEL_MENU, multimenu_pokerlist, MENU_X - 3, MENU_Y);
						switch (menu)
						{
						case 0:
							background();
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
							background();
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
					break;
				}
			} while (menu != 1);
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
				gotoxy(15 * i + x, y);
				printf("%d.%s", i + 1, menulist[i]);
			}
			else {
				if (i < max_menu / 2) {
					gotoxy(15 * i + x, y);
					printf("%d.%s", i + 1, menulist[i]);
				}
				else {
					gotoxy(15 * (i - max_menu / 2) +x, 3+y);
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

int moneyCheck_borrow(int* money, char* stringmoney, int *insertmoney,int* borrowmoney,int* gugeolUpgrade) {
	rewind(stdin);
	for (int i = 0; stringmoney[i] != '\0'; i++)
	{
		if (!isdigit(stringmoney[i])) {
			PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
			gotoxy(40, 15);
			printf("숫자만 넣어주세요!\n");
			_getch();
			system("cls");
			return 0;
		}
	}
	*insertmoney = atoi(stringmoney);
	if (*insertmoney > *borrowmoney) {
		PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
		gotoxy(40, 15);
		printf("빚보다 많이 갚을 수 없습니다!\n");
		_getch();
		system("cls");
		return 0;
	}
	if (*insertmoney > *money) {
		PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
		gotoxy(40, 15);
		printf("가지고 있는 돈이 적습니다!\n");
		_getch();
		system("cls");
		return 0;
	}
	if (*insertmoney <= 1000+*gugeolUpgrade*1000) {
		PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
		gotoxy(40, 15);
		printf("%d원 보다는 많아야 합니다!\n", 1000 + *gugeolUpgrade * 1000);
		_getch();
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
			background();
			gotoxy(40, 15);
			printf("숫자만 넣어주세요!\n");
			_getch();
			system("cls");
			return 0;
		}
	}
	*insertmoney = atoi(stringmoney);
	if (maxmoney != 0) { // 0으로 설정시 무제한
		if (*insertmoney > maxmoney) {
			PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
			background();
			gotoxy(40, 15);
			printf("%d원 이하만 가능합니다!\n", maxmoney);
			_getch();
			system("cls");
			return 0;
		}
	}
	if (*insertmoney > *money) {
		PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
		background();
		gotoxy(40, 15);
		printf("가지고 있는 돈이 적습니다!\n");
		_getch();
		system("cls");
		return 0;
	}
	if (*insertmoney <= 0) {
		PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
		background();
		gotoxy(40, 15);
		printf("1원 이상 넣어주세요!\n");
		_getch();
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
	gotoxy(33, 20-7); printf("ID");
	gotoxy(32, 21 - 7); printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	gotoxy(32, 22 - 7); printf("┃");
	gotoxy(65, 22 - 7); printf("┃");
	gotoxy(32, 23 - 7); printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
	gotoxy(33, 25 - 7); printf("PASSWORD");
	gotoxy(32, 26 - 7); printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	gotoxy(32, 27 - 7); printf("┃");
	gotoxy(65, 27 - 7); printf("┃");
	gotoxy(32, 28 - 7); printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
	gotoxy(34, 22 - 7); printf("_"); gotoxy(34, 22- 7);
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
	gotoxy(34, 27 - 7); printf("_"); gotoxy(34, 27 - 7);
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
	fopen_s(&fp, "user.dat", "r+");
	fseek(fp, startadd - MONEY_SIZE, SEEK_SET);
	sprintf_s(tempmoney, MONEY_SIZE,"%d",*money);
	fwrite(tempmoney, MONEY_SIZE, 1, fp);
	fclose(fp);
}
void update_gugeolUpgrade(FILE* fp, int* gugeolUpgrade)
{
	char tempupgrade[MONEY_SIZE] = { 0 };
	fopen_s(&fp, "user.dat", "r+");
	fseek(fp, startadd - MONEY_SIZE*2, SEEK_SET);
	sprintf_s(tempupgrade, MONEY_SIZE,"%d", *gugeolUpgrade);
	fwrite(tempupgrade, MONEY_SIZE, 1, fp);
	fclose(fp);
}
void update_borrowmoney(FILE* fp, int* borrowmoney)
{
	char tempborrowmoney[MONEY_SIZE] = { 0 };
	fopen_s(&fp, "user.dat", "r+");
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
	gotoxy(27, 25);
	printf("해당되는 계정이 없거나 비밀번호가 맞지 않습니다.\n");
	return 1;
}
void add_record(FILE* fp)
{
	USER data;
	data = get_record(fp);	// 사용자로부터 데이터를 받아서 구조체에 저장
	if (id_check(fp, data.id)) {
		PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
		background();
		gotoxy(27, 25);
		printf("중복된 아이디 입니다!\n");
		_getch();
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
			background();
			PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
			gotoxy(27, 25);
			printf("공백을 입력할 수 없습니다.\n");
			_getch();
			system("cls");
			continue;
		}
		break;
	} while (1);
	PlaySound(TEXT("sound\\button.wav"), NULL, SND_ASYNC);
	data.savedGugeolUpgrade[9] = '1'; // 1
	data.savedUserMoney[2] = '1'; // 1000
	data.savedborrowmoney[3] = '1'; // 10000000
	return data;
}
int id_check(FILE* fp, char* id) {
	USER data;
	fseek(fp, 0, SEEK_END);
	if (ftell(fp) <= 0) {
		return 0;
	}
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
	background();
	gotoxy(40, 18);
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
		background();
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
	background();
	Sleep(1000);
	gotoxy(40, 4); printf("♠Yeungjin Casino♠");
	textcolor(12);
	Sleep(1000);
	gotoxy(43, 6); printf("PM, 포커, 룰렛");
	textcolor(15);
	Sleep(1000);
	gotoxy(46, 8); printf("전 석 진");
	textcolor(12);
	Sleep(1000);
	gotoxy(47, 10); printf("블랙잭");
	textcolor(15);
	Sleep(1000);
	gotoxy(46, 12); printf("김 재 현");
	textcolor(12);
	Sleep(1000);
	gotoxy(48, 14); printf("경마");
	textcolor(15);
	Sleep(1000);
	gotoxy(46, 16); printf("권 오 윤");
	textcolor(12);
	Sleep(1000);
	gotoxy(46, 18); printf("슬릇머신");
	textcolor(15);
	Sleep(1000);
	gotoxy(46, 20); printf("전 태 웅");
	textcolor(12);
	Sleep(1000);
	gotoxy(47, 22); printf("디자인");
	textcolor(15);
	Sleep(1000);
	gotoxy(46, 24); printf("최 진 영");
	textcolor(12);
	Sleep(1000);
	gotoxy(46, 26); printf("제작기간");
	textcolor(15);
	Sleep(1000);
	gotoxy(40, 28); printf("2021/05/06~2021/06/13");
	textcolor(12);
	Sleep(1000);
	gotoxy(39, 30); printf("♠Thanks For Playing!♠");
	textcolor(15);
	_getch();
	mciSendCommandW(dwID, MCI_CLOSE, 0, NULL);
	system("cls");
}