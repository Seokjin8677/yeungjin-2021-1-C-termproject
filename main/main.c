#include <stdio.h>
#include <Windows.h>
#include <conio.h>

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

extern void textcolor(int);
extern int poker();
extern int pokersingle(int, int);
extern int poker_server(int);
extern void poker_client(int*);
void gotoxy(int, int);
int pullDownMenu(int,char[][MAX_MENU_CHAR]);
int sel = 0;
int main(void) {
	int menu;
	int money = 10000;
	int insertmoney;
	char mainmenulist[MAIN_MENU][MAX_MENU_CHAR] = { "�̱��÷���","��Ƽ�÷���","����" };
	char singlemenulist[SINGLE_MENU][MAX_MENU_CHAR] = { "��Ŀ","����","�����ӽ�","�귿","�渶","�ܾ���ȸ","������","����" };
	char multimenulist[MULTI_MENU][MAX_MENU_CHAR] = { "��Ŀ","����","�ܾ���ȸ","����" };
	char multimenu_pokerlist[MULTI_SEL_MENU][MAX_MENU_CHAR] = { "���� ����","���� ����","����" };
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
					system("cls");
					money -= insertmoney;
					money += pokersingle(insertmoney,poker());
					_getch();
					system("cls");
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
							system("cls");
							money -= insertmoney;
							printf("������� ������ ��ٸ��� ��...\n�������� ������ q�� �Է��ϼ���.\n");
							money += poker_server(insertmoney);
							break;
						case 1:
							poker_client(&money);
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
	return 0;
}

int pullDownMenu(int max_menu, char menulist[][MAX_MENU_CHAR])
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
		if (ch == KEY_LEFT)
			sel = ((sel - 1) + max_menu) % max_menu;
		else if (ch == KEY_RIGHT)
			sel = (sel + 1) % max_menu;
		else if (ch == KEY_UP && max_menu % 2 == 0)
			sel = ((sel + max_menu / 2) + max_menu) % max_menu;
		else if (ch == KEY_DOWN && max_menu % 2 == 0)
			sel = ((sel - max_menu / 2) + max_menu) % max_menu;
		else if (ch == KEY_RETURN)
			break;
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