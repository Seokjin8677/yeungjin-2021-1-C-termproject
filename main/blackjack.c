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

int playingCard_number[] = { 1,2,3,4,5,6,7,8,9,10,JACK,QUEEN,KING }; //ī���� ���� �迭 J Q K �� ���� 11 , 12, 13, ���� ��Ÿ��
int playingCard_suite[] = { SPADE , DIA , HEART , CLOVER };
int used_playingCard[52]; //���� ī�带 ��� �迭
int playerCard[5] = { 0 }; //player�� ������ �������ִ� ī���� �迭
int dealerCard[5] = { 0 }; ////dealer�� ������ �������ִ� ī���� �迭

/*
struct pokerStruct // ����ü�� �ٲܱ� �����
{
	int rank[5];
	int suit[5];
	int sum;
};
*/

int blackjack(int money) {


	//Card_deck 52��



	int card_deck[52]; //ī�带 ���� �迭

	
	makingCard(card_deck);
	
	printArray(card_deck, DECK);

	shuffle(card_deck, DECK);

	//printArray(card_deck, DECK);


	printf("\n\n\n\n\n");


	//ī������ �׽�Ʈ

	int player_index = 0;
	int dealer_index = 0;


	while (1) {
	
	printArray(card_deck, DECK);
		
		
	if (card_sum(playerCard, player_index) <= 17) {  //����ī���� ���� 17 �� ���������� ������ ��ο� �Ѵ�.
		dealerCard[dealer_index] = get_playingCard(card_deck);
		dealer_index++;
		
	}
	printArray(dealerCard, dealer_index);
	playerCard[player_index] = get_playingCard(card_deck);
	player_index++;  //ī������ �� ���� ī�带 �ޱ����� �ε����� 1���� ��Ų��.	
	printArray(playerCard, player_index); //���� �ε���(�޴� ī�����)��ŭ ���

	printf("\n");

	printf("%d", card_sum(playerCard, player_index));

	printf("\n");

	

	printf("\n");
	printf("����ī�� ���� :%d",DECK-(count+1));
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
		return 1; //player �¸�
	}
	else
		return 2;

}
int card_sum(int* player, int index) {

	int sum = 0; //ī��迭�� ��
	

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

void printArray(int arr[], int size) { //������ �ִ� ī��迭�� ����ϴ� �Լ�
	int count = 0;
	for (int i = 0; i <size; i++) {
		if (arr[i] < 14) {
			printf("��%d ", arr[i]);
		}
		else if (arr[i] < 114) {
			printf("��%d ", arr[i]-100);
		}
		else if (arr[i] < 214) {
			printf("��%d ", arr[i] - 200);

		}
		else {
			printf("��%d ", arr[i] - 300);
		}
		count++;
		if (count % 13 == 0)
			printf("\n");
	}

	printf("\n");


}
void makingCard(int card_deck[]) { //ī�嵦�� ����� �Լ�

	int index = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			card_deck[index] = playingCard_suite[i] + playingCard_number[j];
			index++;
		}

	}


}


void swap(int arr[], int i, int j) //�����ҋ� ���̴� �Լ�
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void shuffle(int arr[], int n)  //DECK ����� �ƴ� ���� �����ִ� ī�带 ����
{

	srand(time(NULL));


	int temp = 0;
	int rn;


	for (int i = 0; i < n - 1; i++) {

		rn = rand() % (n - i - 1) + i + 1; //������ ���� :  i + 1 ~  arr[n-1]

		swap(arr, i, rn);
	}

}



int card_drow() { //���� ī�嵦�� ù��° ī�带  �������ִ� ī�� �迭�� ��ȯ

	return 0;
}


int get_playingCard(int arr[]) { //���� ������ ������ ���� ī���Ͱ��� �ʱ�ȭ ���Ѿ���.
	


	if (count > DECK)
		return -1;  //��ȯ�� ī�尡 ������ ������ ���� -1�� ��ȯ�Ѵ�.

	else {
		count++;
		return arr[count]; //���� �ε����� ī�带 ��ȯ
	}

	//���ӵ��� ī�尡�����ҽ� ����ī�带 �ٰ����� �����ؾ��Ѵ�.


}
