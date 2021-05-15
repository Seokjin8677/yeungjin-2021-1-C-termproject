#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

void textcolor(int color_number)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}
struct pokerStruct // 패 확인을 위한 패 구조체
{
	int rank;
	int suit;
};
void cardPrint(struct pokerStruct* card);
void bubbleSort(struct pokerStruct* card);
int checkCard(struct pokerStruct* card);
int card_select(int cardlist[]);

int poker(int money) {
	srand(time(NULL));
	int cardlist[52] = {
	0,1,2,3,4,5,6,7,8,9,10,11,12,	// CLOVER
	13,14,15,16,17,18,19,20,21,22,23,24,25,	// DIAMOND
	26,27,28,29,30,31,32,33,34,35,36,37,38,	// HEART
	39,40,41,42,43,44,45,46,47,48,49,50,51	// SPADE
	};

	struct pokerStruct card[5]; // 5장 카드 구조체 생성

	int tempcard;
	int selects, selects_temp;

	for (int i = 0; i < 5; i++) // 카드 5장 고르기
	{
		tempcard = card_select(cardlist);
		card[i].rank = tempcard % 13;
		card[i].suit = tempcard / 13;
	}

	cardPrint(card);

	do // 바꿀 카드 선택
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
	} while (selects_temp != 0);

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
	bubbleSort(card); // 내림차순 정렬

	int handtype = checkCard(card);
	switch (handtype)
	{
	case 2:
		printf("One Pair\n원금만 회수했다...\n");
		return money;
	case 3:
		printf("Two Pair\n%d원을 벌었다!\n", money * 2);
		return money * 2;
	case 4:
		printf("Three Of A Kind\n%d원을 벌었다!\n", money * 3);
		return money * 3;
	case 5:
		printf("Straight\n%d원을 벌었다!\n", money * 5);
		return money * 5;
	case 6:
		printf("Flush\n%d원을 벌었다!\n", money * 10);
		return money * 10;
	case 7:
		printf("Full House\n%d원을 벌었다!\n", money * 15);
		return money * 15;
	case 8:
		printf("Four Of A kind\n%d원을 벌었다!\n", money * 20);
		return money * 20;
	case 9:
		printf("Straight Flush\n%d원을 벌었다!\n", money * 100);
		return money * 100;
	case 10:
		printf("Royal Straight Flush\n%d원을 벌었다!\n", money * 500);
		return money * 500;
	default:
		printf("High Card\n돈을 잃었다...\n");
		return 0;
	}

}

void cardPrint(struct pokerStruct* card) { // 포커 패 출력
	for (int i = 0; i < 5; i++)
	{
		switch (card[i].suit)
		{
		case 0:
			textcolor(15);
			printf("♣");
			break;
		case 1:
			textcolor(12);
			printf("♥");
			break;
		case 2:
			textcolor(12);
			printf("◆");
			break;
		case 3:
			textcolor(15);
			printf("♠");
			break;
		default:
			break;
		}
		textcolor(15);
		switch (card[i].rank)
		{
		case 9:
			printf("Jack ");
			break;
		case 10:
			printf("Queen ");
			break;
		case 11:
			printf("King ");
			break;
		case 12:
			printf("ACE ");
			break;
		default:
			printf("%d ", card[i].rank % 13 + 2);
			break;
		}
	}
	printf("\n");
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