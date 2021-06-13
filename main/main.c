#define _CRT_SECURE_NO_WARNINGS
#include "modm.h"





typedef struct user {
	char id[ID_SIZE];		// ���̵�
	char password[PASS_SIZE];	// ��й�ȣ
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
void CursorView() // Ŀ�� ����� �Լ�
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //Ŀ�� ���� (1 ~ 100)
	cursorInfo.bVisible = FALSE; //Ŀ�� Visible TRUE(����) FALSE(����)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
int pullDownMenu(int,char**,int x, int y); // �޸� ������ ���� ���׵� �迭 ���
int pullDownMenu_yesorno(char** menulist, int x, int y);
int id_check(FILE*, char*);
int sel = 0;
long startadd; // �� �ҷ����� ���� ��ġ�� ����
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
	char *loginmenulist[MAIN_MENU] = {"�α���","��������","����"};
	char *mainmenulist[MAIN_MENU] = { "�̱��÷���","��Ƽ�÷���","����" };
	char *singlemenulist[SINGLE_MENU] = { "��Ŀ","����","�����ӽ�","�귿","�渶","����","�����ϱ�","����","����","����" };
	char* shopmenulist[SHOP_MENU] = { "���� ���׷��̵�","�ζ�","����"};
	char *multimenulist[MULTI_MENU] = { "��Ŀ","����","����" };
	char *multimenu_pokerlist[MULTI_SEL_MENU] = { "���� ����","���� ����","����" };
	char* bankmenulist[BANK_MENU] = {"�ܾ���ȸ","����� Ȯ��","�����ȯ","����"};
	char* explainmenulist[EXPLAIN_MENU] = { "���丮","��Ŀ","����","�����ӽ�","�귿","�渶","����","����" };
	char* yesornomenulist[2] = {"��","�ƴϿ�"};
	unsigned char plain[32] = { 0 };
	unsigned char encrypt[32] = { 0 };
	char stringmoney[10] = { 0 };
	CursorView(); // Ŀ�� �����
	FILE* fp = NULL;
	int loginStatus = 0;
	srand(time(NULL));
	// ���� ������ �߰� ���� �����Ѵ�. 
	if (fopen_s(&fp,"user.dat", "a+")) {
		//printf(stderr, "�Է��� ���� ������ �� �� �����ϴ�");
		exit(1);
	}
	
	do {
		menu = pullDownMenu(MAIN_MENU, loginmenulist,1,3);
		switch (menu)
		{
		case 0:
			printf("���� �α���");
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
			printf("���� ����");
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
					printf("�����ϰ� �ִ� ��: %d\n", money); // ��Ŀ
					printf("�ǵ��� �Է��ϼ���(�ִ� 10����): ");
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
					printf("�����ϰ� �ִ� ��: %d\n", money); // ����
					printf("�ǵ��� �Է��ϼ���(�ִ� 10����): ");
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
					printf("�����ϰ� �ִ� ��: %d\n", money); // �����ӽ�
					printf("�ǵ��� �Է��ϼ���(�ִ� 10����): ");
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
				case 3: // �귿
					printf("�����ϰ� �ִ� ��: %d\n",money);
					printf("�ǵ��� �Է��ϼ���(�ִ� 10����): ");
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
					printf("�����ϰ� �ִ� ��: %d\n", money); // �渶
					printf("�ǵ��� �Է��ϼ���(�ִ� 10����): ");
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
					sel = 0; // ���� �޴� ���� �� 1�� �޴����� ���õǰ�
					do
					{
						menu = pullDownMenu(BANK_MENU, bankmenulist, 1, 3);
						switch (menu)
						{
						case 0:
							printf("������: %d\n", money);
							system("pause");
							system("cls");
							break;
						case 1:
							printf("���� �����: %d\n",borrowmoney);
							system("pause");
							system("cls");
							break;
						case 2:
							if (borrowmoney <= 0) {
								printf("�̹� ������� ��� ���ҽ��ϴ�!\n");
								system("pause");
								system("cls");
								break;
							}
							printf("��ȯ�� ������� �Է��ϼ���: ");
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
					sel = 5; // ���� �޴��� ���� ���� �޴� ���õǰ�
					break;
				case 6:
					if (money < 1000) {
						timeprocess("������");
						money += 1000 * gugeolUpgrade;
						update_money(fp, &money);
						printf("%d���� �������ϴ�.\n", 1000 * gugeolUpgrade);
						PlaySound(TEXT("sound\\coin.wav"), NULL, SND_ASYNC);
					}
					else {
						printf("1000�� �̸��϶��� ������ �����մϴ�!\n");
						PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
					}
						
					system("pause");
					system("cls");
					break;
				case 7:
					sel = 0; // ���� �޴� ���� �� 1�� �޴����� ���õǰ�
					do
					{
						menu = pullDownMenu(SHOP_MENU, shopmenulist,1,3);
						switch (menu)
						{
						case 0:
							printf("���ɽ� ��� ���� �����մϴ�.(Max Level 10)\n");
							if (gugeolUpgrade >= 10) {
								printf("���� ��ų Lv.MAX\n");
								printf("�̹� �ִ� ������ �����ؼ� ������ �� �����ϴ�!\n");
								PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
								system("pause");
								system("cls");
								break;
							}
							printf("���� ��ų Lv.%d\n",gugeolUpgrade);
							printf("�����ϰ� �ִ� ��: %d\n", money);
							printf("���� �Ͻðڽ��ϱ�?(10,000��)\n");
							if (pullDownMenu_yesorno(yesornomenulist, 3, 5) == 0) {
								if (moneyCheck(&money, "10000", &insertmoney,100000)) {
									money -= insertmoney;
									update_money(fp, &money);
									gugeolUpgrade++;
									update_gugeolUpgrade(fp, &gugeolUpgrade);
									printf("���ſϷ�!\n");
									system("pause");
								}
								else 
									break;
							}
							
							system("cls");
							break;
						case 1:
							printf("�ζǸ� �����մϴ�.\n");
							printf("�����ϰ� �ִ� ��: %d\n", money);
							printf("���� �Ͻðڽ��ϱ�?(1,000��)\n");
							if (pullDownMenu_yesorno(yesornomenulist, 3, 5) == 0) {
								if (money < 1000) {
									printf("���� ���ڶ��ϴ�!");
									PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
									system("pause");
									system("cls");
									break;
								}
								if (money  <= 1000+ gugeolUpgrade * 1000) {
									printf("%d�� ���� ���ƾ� ���Ű� �����մϴ�!\n", 1000 + gugeolUpgrade * 1000);
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
					sel = 7; // ���� �޴��� ���� ���� �޴� ���õǰ�
					break;
				case 8:
					sel = 0; // ���� �޴� ���� �� 1�� �޴����� ���õǰ�
					do
					{
						menu = pullDownMenu(EXPLAIN_MENU, explainmenulist, 1, 3);
						switch (menu)
						{
						case 0: // ���丮
							story_explain();
							break;
						case 1: // ��Ŀ
							poker_explain();
							break;
						case 2: // ����
							blackjack_explain();
							break;
						case 3: // �����ӽ�
							slot_explain();
							break;
						case 4: // �귿
							roulette_explain();
							break;
						case 5: // �渶
							horse_explain();
							break;
						case 6: // ����
							shop_explain();
							break;
						case 7: //����
							break;
						}
						system("pause");
						system("cls");
					} while (menu != 7);
					sel = 8; // ���� �޴��� ���� �޴� ���õǰ�
					break;
				case 9:
					break;
				}
			} while (menu != 9);
			sel = 0; // ���� �޴��� ���� �̱��÷��� �޴� ���õǰ�
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
							printf("�����ϰ� �ִ� ��: %d\n", money);
							printf("�ǵ��� �Է��ϼ���: ");
							scanf_s("%s", stringmoney, sizeof(stringmoney));
							if (moneyCheck(&money, stringmoney, &insertmoney, 100000)) {
								system("cls");
								money -= insertmoney;
								printf("������� ������ ��ٸ��� ��...\n�������� ������ q�� �Է��ϼ���.\n");
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
					printf("���� ��Ƽ\n");
					system("pause");
					system("cls");
					break;
				case 2:
					break;
				}
			} while (menu != 2);
			menu = 0;
			sel = 1; // ���� �޴��� ���� ��Ƽ�÷��� �޴� ���õǰ�
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
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos); //������Ÿ���� ����� ��ġ�̵�
}
int moneyCheck_borrow(int* money, char* stringmoney, int *insertmoney,int* borrowmoney,int* gugeolUpgrade) {
	rewind(stdin);
	for (int i = 0; stringmoney[i] != '\0'; i++)
	{
		if (!isdigit(stringmoney[i])) {
			PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
			printf("���ڸ� �־��ּ���!\n");
			system("pause");
			system("cls");
			return 0;
		}
	}
	*insertmoney = atoi(stringmoney);
	if (*insertmoney > *borrowmoney) {
		PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
		printf("������ ���� ���� �� �����ϴ�!\n");
		system("pause");
		system("cls");
		return 0;
	}
	if (*insertmoney > *money) {
		PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
		printf("������ �ִ� ���� �����ϴ�!\n");
		system("pause");
		system("cls");
		return 0;
	}
	if (*insertmoney <= 1000+*gugeolUpgrade*1000) {
		PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
		printf("%d�� ���ٴ� ���ƾ� �մϴ�!\n", 1000 + *gugeolUpgrade * 1000);
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
			printf("���ڸ� �־��ּ���!\n");
			system("pause");
			system("cls");
			return 0;
		}
	}
	*insertmoney = atoi(stringmoney);
	if (maxmoney != 0) { // 0���� ������ ������
		if (*insertmoney > maxmoney) {
			PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
			printf("%d�� ���ϸ� �����մϴ�!\n", maxmoney);
			system("pause");
			system("cls");
			return 0;
		}
	}
	if (*insertmoney > *money) {
		PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
		printf("������ �ִ� ���� �����ϴ�!\n");
		system("pause");
		system("cls");
		return 0;
	}
	if (*insertmoney <= 0) {
		PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
		printf("1�� �̻� �־��ּ���!\n");
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
	gotoxy(3, 2); printf("��������������������������������������������������������������������");
	gotoxy(3, 3); printf("��");
	gotoxy(36, 3); printf("��");
	gotoxy(3, 4); printf("��������������������������������������������������������������������");
	gotoxy(4, 6); printf("PASSWORD");
	gotoxy(3, 7); printf("��������������������������������������������������������������������");
	gotoxy(3, 8); printf("��");
	gotoxy(36, 8); printf("��");
	gotoxy(3, 9); printf("��������������������������������������������������������������������");
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
			if (plain[num] == 32) // �����̽���
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
				if (plain[num] == 32) // �����̽���
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
	fseek(fp, 0, SEEK_SET);	// ������ ó������ ����
	login_menu(id, password);
	while (!feof(fp)) {		// ������ ������ �ݺ��Ѵ�
		fread(&data, sizeof(data), 1, fp);
		if ((strcmp(data.id, id) == 0) && (strcmp(data.password, password) == 0)) {	// �̸��� ���Ѵ�
			startadd = ftell(fp);
			*borrowmoney = atoi(data.savedborrowmoney);
			*gugeolUpgrade = atoi(data.savedGugeolUpgrade);
			*money = atoi(data.savedUserMoney);
			PlaySound(TEXT("sound\\button.wav"), NULL, SND_ASYNC);
			return 0;
		}
	}
	PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
	printf("�ش�Ǵ� ������ ���ų� ��й�ȣ�� ���� �ʽ��ϴ�.\n");
	return 1;
}
void add_record(FILE* fp)
{
	USER data;
	data = get_record(fp);	// ����ڷκ��� �����͸� �޾Ƽ� ����ü�� ����
	if (id_check(fp, data.id)) {
		PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
		printf("�ߺ��� ���̵� �Դϴ�!\n");
		system("pause");
		return;
	}
	fseek(fp, 0, SEEK_END);	// ������ ������ ����	
	fwrite(&data, sizeof(data), 1, fp);	// ����ü �����͸� ���Ͽ� ����
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
	fflush(stdin);		// ǥ�� �Է��� ���۸� ����
	do {
		login_menu(data.id,data.password);
		printf("\n");
		if (data.id[0] == '\0' || data.password[0] == '\0') {
			PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
			printf("������ �Է��� �� �����ϴ�.\n");
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
	fseek(fp, 0, SEEK_SET);	// ������ ó������ ����
	while (!feof(fp)) {		// ������ ������ �ݺ��Ѵ�
		fread(&data, sizeof(data), 1, fp);
		if (strcmp(data.id, id) == 0) {	// �̸��� ���Ѵ�
			return 1;
		}
	}
	return 0;
}
void quit_message() {
	printf("�������Դϴ�.");
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
	mciOpen.lpstrElementName = "sound\\bgm.mp3"; // ���� ��� �Է�
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
			gotoxy(14, 37 - i); printf("��Yeungjin Casino��");
		}
		if (i <= 47) {
			textcolor(12);
			gotoxy(17, 47 - i); printf("PM, ��Ŀ, �귿");
			textcolor(15);
		}
		if (i <= 49) {
			gotoxy(20, 49 - i); printf("�� �� ��");
		}
		if (i <= 54) {
			textcolor(12);
			gotoxy(21, 54 - i); printf("����");
			textcolor(15);
		}
		if (i <= 56) {
			gotoxy(20, 56 - i); printf("�� �� ��");
		}
		if (i <= 61) {
			textcolor(12);
			gotoxy(22, 61 - i); printf("�渶");
			textcolor(15);
		}
		if (i <= 63) {
			gotoxy(20, 63 - i); printf("�� �� ��");
		}
		if (i <= 68) {
			textcolor(12);
			gotoxy(20, 68 - i); printf("�����ӽ�");
			textcolor(15);
		}
		if (i <= 70) {
			gotoxy(20, 70 - i); printf("�� �� ��");
		}
		if (i <= 75) {
			textcolor(12);
			gotoxy(21, 75 - i); printf("������");
			textcolor(15);
		}
		if (i <= 77) {
			gotoxy(20, 77 - i); printf("�� �� ��");
		}

		if (i <= 82) {
			textcolor(12);
			gotoxy(20, 82 - i); printf("���۱Ⱓ");
			textcolor(15);
		}
		if (i <= 84) {
			gotoxy(20, 84 - i); printf("2021/05/06~2021/06/13");
		}

		if (i <= 87) {
			textcolor(12);
			gotoxy(13, 87 - i); printf("��Thanks For Playing!��");
			textcolor(15);
		}
		
		gotoxy(0, 0);
		Sleep(400);


	}
	
	system("pause");
	mciSendCommandW(dwID, MCI_CLOSE, 0, NULL);
	system("cls");
}