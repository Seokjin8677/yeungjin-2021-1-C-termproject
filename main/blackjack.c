#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SPADE 0
#define DIA 100
#define HEART 200
#define CLOVER 300
#define KING 13
#define QUEEN 12
#define JACK 11
#define DECK 52

static int count = -1;

void makingCard(int card_deck[]);
void swap(int arr[], int i, int j);
void printArray(int arr[], int n);
void shuffle(int arr[], int n);
int get_playingCard(int arr[]);

int playingCard_number[] = { 1,2,3,4,5,6,7,8,9,10,JACK,QUEEN,KING }; //카드의 숫자 배열 J Q K 는 각각 11 , 12, 13, 으로 나타냄
int playingCard_suite[] = { SPADE , DIA , HEART , CLOVER };
int used_playingCard[52]; //사용된 카드를 담는 배열
int playerCard[5] = { 0 }; //player가 게임중 가질수있는 카드의 배열
int dealerCard[5] = { 0 }; ////dealer가 게임중 가질수있는 카드의 배열

/*
struct pokerStruct // 구조체로 바꿀까 고민중
{
	int rank[5];
	int suit[5];
	int sum;
};
*/

int blackjack(int money) {


	//Card_deck 52장



	int card_deck[52]; //카드를 담을 배열

	
	makingCard(card_deck);
	
	printArray(card_deck, DECK);

	shuffle(card_deck, DECK);

	//printArray(card_deck, DECK);


	printf("\n\n\n\n\n");


	//카드지급 테스트

	int player_index = 0;
	int dealer_index = 0;


	while (1) {
	
	printArray(card_deck, DECK);
		
		
	if (card_sum(playerCard, player_index) <= 17) {  //딜러카드의 합이 17 이 넘을때까지 무조건 드로우 한다.
		dealerCard[dealer_index] = get_playingCard(card_deck);
		dealer_index++;
		
	}
	printArray(dealerCard, dealer_index);
	playerCard[player_index] = get_playingCard(card_deck);
	player_index++;  //카드지급 후 다음 카드를 받기위해 인덱스를 1증가 시킨다.	
	printArray(playerCard, player_index); //현재 인덱스(받는 카드숫자)만큼 출력

	printf("\n");

	printf("%d", card_sum(playerCard, player_index));

	printf("\n");

	

	printf("\n");
	printf("남은카드 갯수 :%d",DECK-(count+1));
	_getch();
	system("cls");


	}

	//


	return 0;

}


int winner_check(int player, int dealer) {

	if ((dealer==21&&player==21)||(player<21&&dealer<21)) {
		return 0;
	}
	else if (dealer > 21) {
		return 1; //player 승리
	}
	else
		return 2;

}
int card_sum(int* player, int index) {

	int sum = 0; //카드배열의 합
	

	for (int i = 0; i < index; i++) {
		if(player[i]<14)
			sum += player[i];
		else if(player[i]<114)
			sum += player[i]-100;
		else if (player[i] < 214)
			sum += player[i]-200;
		else
			sum += player[i]-300;

	}
	
	return sum; 
}

void printArray(int arr[], int size) { //가지고 있는 카드배열을 출력하는 함수
	int count = 0;
	for (int i = 0; i <size; i++) {
		if (arr[i] < 14) {
			printf("♠%d ", arr[i]);
		}
		else if (arr[i] < 114) {
			printf("◆%d ", arr[i]-100);
		}
		else if (arr[i] < 214) {
			printf("♥%d ", arr[i] - 200);

		}
		else {
			printf("♣%d ", arr[i] - 300);
		}
		count++;
		if (count % 13 == 0)
			printf("\n");
	}

	printf("\n");


}
void makingCard(int card_deck[]) { //카드덱을 만드는 함수

	int index = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			card_deck[index] = playingCard_suite[i] + playingCard_number[j];
			index++;
		}

	}


}


void swap(int arr[], int i, int j) //셔플할떄 쓰이는 함수
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void shuffle(int arr[], int n)  //DECK 상수가 아닌 현재 남아있는 카드를 셔플
{

	srand(time(NULL));


	int temp = 0;
	int rn;


	for (int i = 0; i < n - 1; i++) {

		rn = rand() % (n - i - 1) + i + 1; //난수의 범위 :  i + 1 ~  arr[n-1]

		swap(arr, i, rn);
	}

}



int card_drow() { //현재 카드덱의 첫번째 카드를  가지고있는 카드 배열에 반환

	return 0;
}


int get_playingCard(int arr[]) { //게임 끝나면 베열을 비우고 카운터값을 초기화 시켜야함.
	


	if (count > DECK)
		return -1;  //반환할 카드가 없으면 오류방어를 위해 -1을 반환한다.

	else {
		count++;
		return arr[count]; //현재 인덱스의 카드를 반환
	}

	//게임도중 카드가부족할시 쓰인카드를 다가져와 셔플해야한다.


}
