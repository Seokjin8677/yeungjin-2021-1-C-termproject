#include "modm.h"

void textcolor(int color_number)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}
struct pokerStruct // 패 확인을 위한 패 구조체
{
	int rank;
	int suit;
};
extern void gotoxy(int, int);
extern void background();
void cardPrint(struct pokerStruct* card);
void bubbleSort(struct pokerStruct* card);
int checkCard(struct pokerStruct* card);
int card_select(int cardlist[]);
int pokersingle(int, int);
void card_print2(int , int);
void pullDownMenu_poker(int*);
int poker() {
	int handtype;
	int selcard2[5] = { 0 }; // 카드를 바꾸기 위한 배열
	int cardlist[52] = {
	0,1,2,3,4,5,6,7,8,9,10,11,12,	// CLOVER
	13,14,15,16,17,18,19,20,21,22,23,24,25,	// DIAMOND
	26,27,28,29,30,31,32,33,34,35,36,37,38,	// HEART
	39,40,41,42,43,44,45,46,47,48,49,50,51	// SPADE
	};

	struct pokerStruct card[5]; // 5장 카드 구조체 생성

	int tempcard;
	int selects=0, selects_temp;

	for (int i = 0; i < 5; i++) // 카드 5장 고르기
	{
		tempcard = card_select(cardlist);
		card[i].rank = tempcard % 13;
		card[i].suit = tempcard / 13;
	}
	gotoxy(65, 37); printf("<-,->: 화살표 이동"); // 오른쪽 상단에 설명 출력
	gotoxy(65, 38); printf("  Space: 카드선택");
	gotoxy(65, 39); printf("  Enter: 선택확정");
	cardPrint(card);

	/*do // 바꿀 카드 선택
	{
		printf("바꿀 카드를 선택: ");
		scanf_s("%d", &selects);
		selects_temp = selects;
		while (selects_temp != 0)
		{
			if (selects_temp % 10 > 5) // 각 자리 숫자가 6이 넘을때
			{
				printf("6이 넘는 숫자는 입력할 수 없습니다.\n");
				break;
			}
			selects_temp /= 10;
		}
	} while (selects_temp != 0);*/

	pullDownMenu_poker(selcard2); // 포커 카드를 키보드로 선택하게 하는 메뉴 출력

	for (int i = 0; i < 5; i++)
	{
		selects += *(selcard2 + i);
	}
	while (selects != 0) // 원하는 카드 바꾸기
	{
		selects_temp = selects;
		selects /= 10;
		if (selects_temp % 10 == 0) // 바꾸는 숫자 중 0이 있으면 생략
			continue;
		tempcard = card_select(cardlist);
		card[selects_temp % 10 - 1].rank = tempcard % 13;
		card[selects_temp % 10 - 1].suit = tempcard / 13;

	}
	system("cls");
	cardPrint(card);
	/* int score = 0; 1:1 경기 시 같은 패가 나왔을때 승부를 위한 점수
	for (int i = 0; i < 5; i++)
	{
		if (card[i].rank == 12) // ACE = 1점
			score += 1 * (card[i].suit + 1);
		else
			score += 2 + card[i].rank * (card[i].suit + 1);
	}
	printf("YOUR SCORE: %d\n", score); */
	bubbleSort(card); // 포커패 확인을 위한 내림차순 정렬

	handtype = checkCard(card);
	return handtype;
}
void pokermulti(int handtype) {
	switch (handtype)
	{
	case 2:
		printf("One Pair\n");
		return;
	case 3:
		printf("Two Pair\n");
		return;
	case 4:
		printf("Three Of A Kind\n");
		return;
	case 5:
		printf("Straight\n");
		return;
	case 6:
		printf("Flush\n");
		return;
	case 7:
		printf("Full House\n");
		return;
	case 8:
		printf("Four Of A kind\n");
		return;
	case 9:
		printf("Straight Flush\n");
		return;
	case 10:
		printf("Royal Straight Flush\n");
		return;
	default:
		printf("High Card\n");
		return;
	}
}
int pokersingle(int money,int handtype) {
	PlaySound(TEXT("sound\\coin.wav"), NULL, SND_ASYNC);
	switch (handtype)
	{
	case 2:
		gotoxy(65, 38);
		printf("One Pair");
		gotoxy(65, 39);
		printf("절반만 회수했다...");
		return money * 0.5;
	case 3:
		gotoxy(65, 38);
		printf("Two Pair");
		gotoxy(65, 39);
		printf("%d원을 벌었다!",money * 3);
		return money * 3;
	case 4:
		gotoxy(65, 38);
		printf("Three Of A Kind");
		gotoxy(65, 39);
		printf("%d원을 벌었다!", money * 5);
		return money * 5;
	case 5:
		gotoxy(65, 38);
		printf("Straight");
		gotoxy(65, 39);
		printf("%d원을 벌었다!", money * 10);
		return money * 10;
	case 6:
		gotoxy(65, 38);
		printf("Flush");
		gotoxy(65, 39);
		printf("%d원을 벌었다!", money * 15);
		return money * 15;
	case 7:
		gotoxy(65, 38);
		printf("Full House");
		gotoxy(65, 39);
		printf("%d원을 벌었다!", money * 30);
		return money * 30;
	case 8:
		gotoxy(65, 38);
		printf("Four Of A Kind");
		gotoxy(65, 39);
		printf("%d원을 벌었다!", money * 50);
		return money * 50;
	case 9:
		gotoxy(65, 38);
		printf("Straight Flush");
		gotoxy(65, 39);
		printf("%d원을 벌었다!", money * 100);
		return money * 100;
	case 10:
		gotoxy(65, 38);
		printf("Royal Straight Flush");
		gotoxy(65, 39);
		printf("%d원을 벌었다!", money * 500);
		return money * 500;
	default:
		gotoxy(65, 38);
		printf("High Card");
		gotoxy(65, 39);
		printf("돈을 잃었다...");
		return 0;
	}
}

void cardPrint(struct pokerStruct* card) { // 포커 패 출력
	background();
	for (int i = 0; i < 5; i++)
	{
		PlaySound(TEXT("sound\\paper.wav"), NULL, SND_ASYNC);
		int temp = card[i].suit;
		gotoxy(10+5 + i * 15, 1+19); printf("┏━━━━━━━┓ "); // 카드 모양 출력
		for (int j = 2; j < 9; j++)
		{
			gotoxy(10 + 5 + i * 15, j+19); printf("┃       ┃ "); // 카드 모양 출력
		}
		gotoxy(10 + 5 + i * 15, 9+19); printf("┗━━━━━━━┛ "); // 카드 모양 출력
		if(temp == 1 || temp == 2)
			textcolor(12);
		else
			textcolor(15);
		switch (card[i].suit) // 카드 문양 출력
		{
		case 0:
			gotoxy(14 + 5 + i * 15, 5 + 19); printf("♣");
			break;
		case 1:
			gotoxy(14 + 5 + i * 15, 5 + 19); printf("♥");
			break;
		case 2:
			gotoxy(14 + 5 + i * 15, 5 + 19); printf("◆");
			break;
		case 3:
			gotoxy(14 + 5 + i * 15, 5 + 19); printf("♠");
			break;
		default:
			break;
		}
		switch (card[i].rank) // 카드 숫자 출력
		{
		case 9:
			gotoxy(12 + 5 + i * 15, 2 + 19); printf("J");
			gotoxy(17 + 5 + i * 15, 8 + 19); printf("J");
			break;
		case 10:
			gotoxy(12 + 5 + i * 15, 2 + 19); printf("Q");
			gotoxy(17 + 5 + i * 15, 8 + 19); printf("Q");
			break;
		case 11:
			gotoxy(12 + 5 + i * 15, 2 + 19); printf("K");
			gotoxy(17 + 5 + i * 15, 8 + 19); printf("K");
			break;
		case 12:
			gotoxy(12 + 5 + i * 15, 2 + 19); printf("A");
			gotoxy(17 + 5 + i * 15, 8 + 19); printf("A");
			break;
		default:
			gotoxy(12 + 5 + i * 15, 2 + 19); printf("%d", card[i].rank % 13 + 2);
			gotoxy(16 + 5 + i * 15, 8 + 19); printf("%2d", card[i].rank % 13 + 2);
			break;
		}
		Sleep(500);
		textcolor(15);
	}
	printf("\n\n");
}

int checkCard(struct pokerStruct* card) { // 포커의 패 확인
	int straight = 0, royal = 0, flush = 0, ToK = 0, FoK = 0, numPair = 0;

	int j;
	int straightCounter = 0;
	for (j = 1; j < 5; ++j)
		if (card[j].rank == card[j - 1].rank - 1)
			++straightCounter;

	if (straightCounter == 4)
	{
		straight = 1;
		if (card[0].rank == 12)
			royal = 1;
	}

	else if (straightCounter == 3 && card[0].rank == 12 && card[1].rank == 3)
		straight = 1;

	for (j = 1; j < 5; ++j)
		if (card[j].suit != card[j - 1].suit)
			break;
	if (j == 5)
		flush = 1;

	int numRanks[13] = { 0 };
	for (j = 0; j < 5; ++j)
		++numRanks[card[j].rank];
	for (j = 0; j < 13; ++j)
		switch (numRanks[j])
		{
		case 2:
			++numPair;
			break;
		case 3:
			ToK = 1;
			break;
		case 4:
			FoK = 1;
			break;
		}

	if (royal && flush)
		return 10;
	else if (straight && flush)
		return 9;
	else if (FoK)
		return 8;
	else if (ToK && numPair == 1)
		return 7;
	else if (flush)
		return 6;
	else if (straight)
		return 5;
	else if (ToK)
		return 4;
	else if (numPair == 2)
		return 3;
	else if (numPair == 1)
		return 2;
	return 1;
}

int card_select(int cardlist[]) { // 카드 한 장 랜덤으로 고르기
	int card_sel1;
	int temp_card;
	for (int i = 0; i < 1;)
	{
		card_sel1 = rand() % 52;
		if (cardlist[card_sel1] == 52)
			continue;
		temp_card = cardlist[card_sel1];
		cardlist[card_sel1] = 52;
		i++;
	}
	return temp_card;
}
void bubbleSort(struct pokerStruct* card) { // 내림차순 정렬
	int temp, temp2;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4 - i; j++)
		{
			if (card[j].rank < card[j + 1].rank)
			{
				temp = card[j].rank;
				temp2 = card[j].suit;
				card[j].rank = card[j + 1].rank;
				card[j].suit = card[j + 1].suit;
				card[j + 1].rank = temp;
				card[j + 1].suit = temp2;
			}
		}
	}
}
void card_print2(int i, int sel) { // 카드를 선택하면 빨간색, 이미 선택된 카드는 다시 흰색으로
	PlaySound(TEXT("sound\\button.wav"), NULL, SND_ASYNC);
	if (sel != 0)
		textcolor(12);
	else
		textcolor(15);
	gotoxy(10 + 5 + i * 15, 1 + 19); printf("┏━━━━━━━┓ ");
	for (int j = 2; j < 9; j++)
	{
		gotoxy(10 + 5 + i * 15, j + 19); printf("┃");
		gotoxy(18 + 5 + i * 15, j + 19); printf("┃");
	}
	gotoxy(10 + 5 + i * 15, 9 + 19); printf("┗━━━━━━━┛ ");

	textcolor(15);
}
void pullDownMenu_poker(int* selcard2) // 카드를 키보드로 선택하게 하는 함수
{
	char ch;
	int sel = 0;
	int temp = 0;

	gotoxy(14 + 5 + sel * 15, 11 + 19); printf("♠"); // 선택 메뉴 출력 및 초기화
	while (1) {
		ch = _getch();
		if (ch == KEY_LEFT) {
			PlaySound(TEXT("sound\\button2.wav"), NULL, SND_ASYNC);
			sel = ((sel - 1) + 5) % 5;
		}
		else if (ch == KEY_RIGHT) {
			PlaySound(TEXT("sound\\button2.wav"), NULL, SND_ASYNC);
			sel = (sel + 1) % 5;
		}
		else if (ch == 32) { // 스페이스바 입력
			switch (sel)
			{
			case 0:
				if (selcard2[sel] == 0)
					selcard2[sel] = 10000;
				else
					selcard2[sel] = 0;
				card_print2(sel, selcard2[sel]);
				break;
			case 1:
				if (selcard2[sel] == 0)
					selcard2[sel] = 2000;
				else
					selcard2[sel] = 0;
				card_print2(sel, selcard2[sel]);
				break;
			case 2:
				if (selcard2[sel] == 0)
					selcard2[sel] = 300;
				else
					selcard2[sel] = 0;
				card_print2(sel, selcard2[sel]);
				break;
			case 3:
				if (selcard2[sel] == 0)
					selcard2[sel] = 40;
				else
					selcard2[sel] = 0;
				card_print2(sel, selcard2[sel]);
				break;
			case 4:
				if (selcard2[sel] == 0)
					selcard2[sel] = 5;
				else
					selcard2[sel] = 0;
				card_print2(sel, selcard2[sel]);
				break;
			default:
				break;
			}
		}
		else if (ch == KEY_RETURN) // 엔터 누르면 끝
			break;
		gotoxy(14 + 5 + temp * 15, 11 + 19); printf("  "); // 이전 화살표 지우기
		gotoxy(14 + 5 + sel * 15, 11 + 19); printf("♠");
		temp = sel; // 이전 화살표를 위한 temp 설정
		Sleep(1); // 최적화를 위한 Sleep(1)
	}
	system("cls");
}