#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define KEY_LEFT  0x4B
#define KEY_RIGHT 0x4D
#define KEY_UP  0x48
#define KEY_DOWN 0x50
#define KEY_RETURN 0x0D
#define ROULETTE_MENU 3
extern void gotoxy(int, int);
extern int pullDownMenu(int, char**, int x, int y);
extern int pullDownMenu_yesorno(char**, int, int);
char* roulettelist[ROULETTE_MENU] = { "���� �ϳ�","Ȧ/¦","1~18/19~36"};
char* oddevenmenulist[2] = { "Ȧ","¦" };
char* lowerbiggermenulist[2] = { "1~18","19~36" };
extern void textcolor(int color_number);
extern int sel;
int roulette(int insertmoney) {
	int user_roulette;
	int roulette = rand() % 37;
	int menu = 0;
	int returnmoney= 0;
	int oddeven = 0;
	sel = 0;
	
	printf("���� �����ϼ���.");
	menu = pullDownMenu(ROULETTE_MENU, roulettelist, 1, 2);
	switch (menu)
	{
	case 0:
		do {
			printf("���ϴ� ���ڸ� �Է��ϼ���(0~36): ");
			scanf_s("%d", &user_roulette);
			if (user_roulette < 0 || user_roulette > 36) {
				printf("0���� 36������ �Է��ϼ���!\n");
				system("pause");
				system("cls");
			}
		} while (user_roulette < 0 || user_roulette > 36);
		break;
	case 1:
		printf("�� �� �ϳ��� �����ϼ���.");
		oddeven = pullDownMenu_yesorno(oddevenmenulist, 1, 2);
		break;
	case 2:
		printf("�� �� �ϳ��� �����ϼ���.");
		oddeven = pullDownMenu_yesorno(lowerbiggermenulist, 1, 2);
		break;
	}
	
	system("cls");
	//PlaySound(TEXT("sound\\scanning.wav"), NULL, SND_ASYNC);
	gotoxy(3, 1); printf("������������������������������������������������������������������������������������������������������������������������������������");
	gotoxy(3, 2); printf("��    ��    ��    ��    ��    ��    ��    ��    ��    ��    ��    ��    ��    ��");
	gotoxy(3, 3); printf("��    ��    ��    ��    ��    ��    ��    ��    ��    ��    ��    ��    ��    ��");
	gotoxy(3, 4); printf("��    ��������������������������������������������������������������������������������������������������������������������������");
	gotoxy(3, 5); printf("��    ��    ��    ��    ��    ��    ��    ��    ��    ��    ��    ��    ��    ��");
	gotoxy(3, 6); printf("��    ��    ��    ��    ��    ��    ��    ��    ��    ��    ��    ��    ��    ��");
	gotoxy(3, 7); printf("��    ��������������������������������������������������������������������������������������������������������������������������");
	gotoxy(3, 8); printf("��    ��    ��    ��    ��    ��    ��    ��    ��    ��    ��    ��    ��    ��");
	gotoxy(3, 9); printf("��    ��    ��    ��    ��    ��    ��    ��    ��    ��    ��    ��    ��    ��");
	gotoxy(3, 10); printf("������������������������������������������������������������������������������������������������������������������������������������");
	//srand(time(NULL));
	int myvalue = rand() % 37;
	int result = 0;
	textcolor(10);
	gotoxy(6, 2); printf("0");
	for (int i = 1; i < 37; i++)
	{
		if (i % 2 == 0)
			textcolor(12);
		else
			textcolor(15);
		gotoxy(((i - 1) - i / 37) % 12 * 5 + 10, (i - 1 - i / 37) / 12 % 3 * 3 + 2); printf("%2d", i);
	}
	textcolor(15);
	for (result = myvalue; result < 50+rand()%50 + myvalue; result++)
	{
		if (result % 37 == 0) {
			gotoxy(6, 6); printf("o");
			Sleep(50);
			gotoxy(6, 6); printf("  ");
		}
		else {
			gotoxy(((result - 1) - result / 37) % 12 * 5 + 11, (result - 1 - result / 37) / 12 % 3 * 3 + 3); printf("o");
			Sleep(50);
			gotoxy(((result - 1) - result / 37) % 12 * 5 + 11, (result - 1 - result / 37) / 12 % 3 * 3 + 3); printf("  ");
		}
	}
	if (result % 37 == 0) {
		gotoxy(6, 4); printf("  ");
	}
	else {
		gotoxy(((result - 1) - result / 37) % 12 * 5 + 11, (result - 1 - result / 37) / 12 % 3 * 3 + 3); printf("o");
	}
	result %=37;
	gotoxy(1, 12);
	switch (menu)
	{
	case 0:
		if (user_roulette == result) {
			printf("Your Win!\n");
			returnmoney = insertmoney * 36;
		}
		else 
			printf("Your Lose..\n");
		break;
	case 1:
		if (result == 0) 
			printf("Your Lose..\n");
		else if (result % 2 == oddeven) 
			printf("Your Lose..\n");
		else {
			printf("Your Win!\n");
			returnmoney = insertmoney * 2;
		}
		break;
	case 2:
		if (result == 0)
			printf("Your Lose..\n");
		else if (result / 19 != oddeven)
			printf("Your Lose..\n");
		else {
			printf("Your Win!\n");
			returnmoney = insertmoney * 2;
			
		}
		break;
	}

	if(returnmoney==0){
		printf("���� �Ҿ���..\n");
		PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
	}
	else {
		printf("%d���� ������!\n", returnmoney);
		PlaySound(TEXT("sound\\coin.wav"), NULL, SND_ASYNC);
	}
		

	system("pause");
	system("cls");
	sel = 3;
	return returnmoney;
}