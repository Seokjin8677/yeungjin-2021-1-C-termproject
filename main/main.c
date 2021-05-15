#include <stdio.h>
#include <Windows.h>
#include <conio.h>

#define MAIN_MENU 3
#define SINGLE_MENU 8
#define MULTI_MENU 4
#define KEY_UP  0x48
#define KEY_DOWN 0x50
#define KEY_LEFT  0x4B
#define KEY_RIGHT 0x4D
#define KEY_RETURN 0x0D

extern void textcolor(int);
extern int poker(int);
void gotoxy(int, int);
int pullDownMenu();
int sel = 0;
int main(void) {
	int menu;
	int money = 10000;
	int insertmoney;
	char mainmenulist[MAIN_MENU][20] = { "싱글플레이","멀티플레이","종료" };
	char singlemenulist[SINGLE_MENU][20] = { "포커","블랙잭","슬릇머신","룰렛","경마","잔액조회","돈벌기","이전" };
	char multimenulist[MULTI_MENU][20] = { "포커","블랙잭","잔액조회","이전" };
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
					system("cls");
					money -= insertmoney;
					money += poker(insertmoney);
					_getch();
					system("cls");
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
					printf("1000원을 벌었습니다.\n");
					_getch();
					system("cls");
					break;
				case 7:
					break;
				}
			} while (menu != 7);
			sel = 0;
			break;
		case 1:
			do
			{
				menu = pullDownMenu(MULTI_MENU, multimenulist);
				switch (menu)
				{
				case 0:
					printf("준비중입니다.\n");
					_getch();
					system("cls");
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
			sel = 1;
			break;
		case 2:
			break;
		}
	} while (menu != 2);
	return 0;
}

int pullDownMenu(int max_menu, char menulist[][20])
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
		else if (ch == KEY_UP && max_menu % 2 == 0 && max_menu > 4)
			sel = ((sel + max_menu / 2) + max_menu) % max_menu;
		else if (ch == KEY_DOWN && max_menu % 2 == 0 && max_menu > 4)
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
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos); //프로토타입의 값대로 위치이동
}