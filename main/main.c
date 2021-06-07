#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#define LOGIN_SIZE 32
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
	char id[LOGIN_SIZE];		// ���̵�
	char password[LOGIN_SIZE];	// ��й�ȣ
	unsigned int userMoney;
} USER;
extern void textcolor(int);
extern int poker();
extern int pokersingle(int, int);
extern int poker_server(int);
extern void poker_client(int*);
void gotoxy(int, int);
int moneyCheck(int, int);
void quit_message();
void CursorView() // Ŀ�� ����� �Լ�
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //Ŀ�� ���� (1 ~ 100)
	cursorInfo.bVisible = FALSE; //Ŀ�� Visible TRUE(����) FALSE(����)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
int pullDownMenu(int,char**); // �޸� ������ ���� ���׵� �迭 ���
int sel = 0;
long startadd; // �� �ҷ����� ���� ��ġ�� ����
int id_check(FILE*, char*);
USER get_record(FILE*);
void add_record(FILE*);
int login_record(FILE*, int*);
void update_money(FILE*, int*);
void login_menu(char*, char*);

int main(void) {
	int menu;
	unsigned int money = 0;
	int insertmoney;
	char *loginmenulist[MAIN_MENU] = {"�α���","��������","����"};
	char *mainmenulist[MAIN_MENU] = { "�̱��÷���","��Ƽ�÷���","����" };
	char *singlemenulist[SINGLE_MENU] = { "��Ŀ","����","�����ӽ�","�귿","�渶","�ܾ���ȸ","������","����" };
	char *multimenulist[MULTI_MENU] = { "��Ŀ","����","�ܾ���ȸ","����" };
	char *multimenu_pokerlist[MULTI_SEL_MENU] = { "���� ����","���� ����","����" };
	CursorView(); // Ŀ�� �����
	FILE* fp = NULL;
	int loginStatus = 0;
	// ���� ������ �߰� ���� �����Ѵ�. 
	if (fopen_s(&fp,"user.dat", "a+")) {
		//printf(stderr, "�Է��� ���� ������ �� �� �����ϴ�");
		exit(1);
	}
	do {
		menu = pullDownMenu(MAIN_MENU, loginmenulist);
		switch (menu)
		{
		case 0:
			printf("���� �α���");
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
		menu = pullDownMenu(MAIN_MENU, mainmenulist);
		switch (menu)
		{
		case 0:
			do {
				menu = pullDownMenu(SINGLE_MENU, singlemenulist);
				switch (menu)
				{
				case 0:
					printf("�ǵ��� �Է��ϼ���: ");
					scanf_s("%d", &insertmoney);
					if (moneyCheck(money,insertmoney)) {
						system("cls");
						money -= insertmoney;
						money += pokersingle(insertmoney, poker());
						system("pause");
						system("cls");
					}
					update_money(fp, &money);
					break;
				case 1:
					//printf("�غ����Դϴ�.\n");
					_getch();
					system("cls");
					break;
				case 2:
					printf("�غ����Դϴ�.\n");
					_getch();
					system("cls");
					break;
				case 3:
					printf("�غ����Դϴ�.\n");
					_getch();
					system("cls");
					break;
				case 4:
					printf("�غ����Դϴ�.\n");
					_getch();
					system("cls");
					break;
				case 5:
					printf("�ܾ�: %d\n", money);
					_getch();
					system("cls");
					break;
				case 6:
					money += 1000;
					update_money(fp, &money);
					printf("1000���� �������ϴ�.\n");
					_getch();
					system("cls");
					break;
				case 7:
					break;
				}
			} while (menu != 7);
			sel = 0; // ���� �޴��� ���� �̱��÷��� �޴� ���õǰ�
			break;
		case 1:
			sel = 0; // ��Ƽ�÷��� �޴� ���� �� 1�� �޴����� ���õǰ�
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
							printf("�ǵ��� �Է��ϼ���: ");
							scanf_s("%d", &insertmoney);
							if (moneyCheck(money, insertmoney)) {
								system("cls");
								money -= insertmoney;
								printf("������� ������ ��ٸ��� ��...\n�������� ������ q�� �Է��ϼ���.\n");
								money += poker_server(insertmoney);
							}
							update_money(fp, &money);
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
					printf("�غ����Դϴ�.\n");
					_getch();
					system("cls");
					break;
				case 2:
					printf("�غ����Դϴ�.\n");
					_getch();
					system("cls");
					break;
				case 3:
					break;
				}
			} while (menu != 3);
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
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos); //������Ÿ���� ����� ��ġ�̵�
}

int moneyCheck(int money, int insertmoney) {
	if (insertmoney > money) {
		PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
		printf("������ �ִ� ���� �����ϴ�...\n");
		system("pause");
		system("cls");
		return 0;
	}
	if (insertmoney <= 0) {
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
			if ((id[num] == '\b' && num == 0) || num >= LOGIN_SIZE - 1)
				continue;
			if ((id[num]) == '\t')
				break;
			else
				_putch(id[num]);
			num++;
		}
	}
	id[num] = '\0';
	gotoxy(5, 8); printf("_"); gotoxy(5, 8);
	num = 0;
	PlaySound(TEXT("sound\\button.wav"), NULL, SND_ASYNC);
	while ((password[num] = _getch()) != '\r')
	{
		if (password[num] == '\b' && num != 0) {
			printf("\b \b");
			password[num] = '\0';
			num--;
		}
		else {
			if ((password[num] == '\b' && num == 0) || num >= LOGIN_SIZE - 1)
				continue;
			if ((password[num]) == '\t')
				continue;
			else
				_putch('*');
			num++;
		}
	}
	password[num] = '\0';
	gotoxy(0, 11);
}
void update_money(FILE* fp, int* money)
{
	fopen_s(&fp, "user.dat", "r+");
	fseek(fp, startadd, SEEK_SET);
	fwrite(money, sizeof(money), 1, fp);
	fclose(fp);
}
int login_record(FILE* fp, int* money)
{
	char id[LOGIN_SIZE] = { 0 };
	char password[LOGIN_SIZE] = { 0 };
	int num = 0;
	USER data;
	fseek(fp, 0, SEEK_SET);	// ������ ó������ ����
	login_menu(id, password);
	while (!feof(fp)) {		// ������ ������ �ݺ��Ѵ�
		fread(&data, sizeof(data), 1, fp);
		if ((strcmp(data.id, id) == 0) && (strcmp(data.password, password) == 0)) {	// �̸��� ���Ѵ�
			*money = data.userMoney;
			startadd = ftell(fp) - sizeof(money);
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
	int num = 0;
	for (int i = 0; i < LOGIN_SIZE; i++) {
		data.id[i] = '\0';
		data.password[i] = '\0';
	}
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
	data.userMoney = 10000;
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