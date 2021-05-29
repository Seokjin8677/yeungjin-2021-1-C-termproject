#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
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
void printArray(int arr[], int size);
void card_table(int dealerCard[], int dealer_index, int playerCard[], int player_index);

int playingCard_number[] = { 1,2,3,4,5,6,7,8,9,10,JACK,QUEEN,KING }; //ī���� ���� �迭 J Q K �� ���� 11 , 12, 13, ���� ��Ÿ��
int playingCard_suite[] = { SPADE , DIA , HEART , CLOVER };
int used_playingCard[52]; //���� ī�带 ��� �迭
int playerCard[8] = { 0 }; //player�� ������ �������ִ� ī���� �迭
int dealerCard[8] = { 0 }; ////dealer�� ������ �������ִ� ī���� �迭
 
/*
struct pokerStruct // ����ü�� �ٲٸ� �ڵ差�� �ٰͰ���
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
	
	//printArray(card_deck, DECK); //ī��迭 ���

	shuffle(card_deck, DECK);

	printArray(card_deck, DECK); //���õ� ī�嵦 ���(Ȯ�ο�, �ּ�ó������)
	printf("\n");//
	

	//ī������ �׽�Ʈ

	int player_index = 0; //get�Լ����� ���� ó������ ����
	int dealer_index = 0;


	int game_money = money; //�Ű������� �Է¹޴� �ݾ�
	int bating_money; 
	/*
	���ӸӴ� / ���øӴ� / 
	
	*/

	while (1) {
		
		
		player_index = 0; //���ӽ��۽� ������ �÷��̾� ī��迭 �ε��� �ʱ�ȭ.
		dealer_index = 0;
		bating_money = 0; 

		printf("���ñݾ��� �����ּ���(�ּ� 1000��) / �ܰ� : %d\n",game_money); //���øӴ� �Է¹ޱ�
		scanf_s("%d", &bating_money);

		if (bating_money < 1000) { //���øӴ��� �ּ� 1000��
			continue;
		}
		else{
			game_money -= bating_money; //���ӸӴϿ��� ���øӴϸ� ���ش�.

		}
		system("cls");

		//ù����
		if (count > 46) { //ī�带 ���λ��������
			count = -1;
			shuffle(card_deck, DECK);
		}

		printf("ī�带 ���徿 �����ϴ�(�ƹ�Ű�� �Է�).\n"); //*���徿������ �ٲٱ�.
		
		while (dealer_index < 2 && player_index<2) { //������ �÷��̾� ��� ī��2�徿�� �޴´�.

			_getch();
			system("cls");

			dealerCard[dealer_index] = get_playingCard(card_deck);
			dealer_index++;
			printf("����ī�� : ");
			printArray(dealerCard, dealer_index);
			printf("\n");
			/*
			if (dealer_index == 1) { //*������ ù���� ���������ʴ´�.
				printf("[?]\n");
			}
			*/

			printf("�÷��̾�ī�� : ");
			
		
			playerCard[player_index] = get_playingCard(card_deck);
			player_index++;  //ī������ �� ���� ī�带 �ޱ����� �ε����� 1���� ��Ų��.	

			printArray(playerCard, player_index);
			
		}

		card_table(dealerCard, dealer_index, playerCard, player_index);

		//2��̾����� 21�� ������ blackjack(���øӴ� 2��)
		if (card_dsum(dealerCard, dealer_index)==21) { //������ 21�϶�
		
			printf("black Jack\n");
			continue;
		
		}
		else if(card_dsum(playerCard, player_index)==21){ //�÷��̾� 21�϶�
			game_money += bating_money * 3; //
			printf("black Jack\n");
			continue;
		}

		int flag = 0;

		//Stay or Hit
		while (1) { //�÷��̾ stay or -1 �߸��Է������� �ݺ��� ����. -1 �� ������ Stay.
			
			int temp = 0; //���ð��� ������� tmep ����
			temp = choice(); //Stay or Hit ����

			printf("\n");
			if (temp == 1||temp==-1) {
				printf("Stay\n");
				break;

			}
			else{   //Hit ���ý� 21 �� ������ Bust
				printf("Hit\n");
				playerCard[player_index] = get_playingCard(card_deck);
				player_index++;  //ī������ �� ���� ī�带 �ޱ����� �ε����� 1���� ��Ų��.	
				card_table(dealerCard, dealer_index, playerCard, player_index);

				if (card_dsum(playerCard, player_index) > 21) { //21�� ������ Bust
					flag = 1;//21�� ������ Bust üũ�� ���� flag ������ 1����
					break;
				}
				else if (card_dsum(playerCard, player_index) == 21) { //21�� �Ǿ������ Stay
					break;
				}

			}
		}

		card_dsum(playerCard, player_index);
		_getch();

		card_table(dealerCard, dealer_index, playerCard, player_index);
		
		

		if (flag == 1) { //Bust Ȯ��
			printf("Bust (player)\n");
			continue;
		}

		//Stay �ÿ�
		

		/*
		* system("cls");
		printf("����ī�� : ");
		printArray(dealerCard, dealer_index);
		printf("\n");
		printf("�÷��̾�ī�� : ");
		printArray(playerCard, player_index);
		_getch();
		*/
		
		//
		while (card_dsum(dealerCard, dealer_index)<17) {//������ ī���� ���� 17�̻��� �ɶ����� ī�带 �̴´�. 21�� ������ Bust
			

			dealerCard[dealer_index] = get_playingCard(card_deck);
			dealer_index++;
			card_table(dealerCard, dealer_index, playerCard, player_index);
			
			if (card_dsum(dealerCard, dealer_index) > 21) { //21�� ������ Bust
				game_money += bating_money * 2; //player �¸��� ���ñݾ� 2�� �׵�
				flag = 1;//21�� ������ Bust üũ�� ���� flag ������ 1����
				break;
			}
			
		}
		
		if (flag == 1) { //Bust Ȯ��
			printf("Bust (Dealer)\n");
			continue;
		}

		card_table(dealerCard, dealer_index, playerCard, player_index);


		printf("������ : %d\n", card_dsum(dealerCard, dealer_index));
		printf("�÷��̾��� : %d\n", card_dsum(playerCard, player_index));

		
		if (card_dsum(dealerCard, dealer_index) == card_dsum(playerCard, player_index)){ //����
			game_money += bating_money; //���ñݾ� 
			printf("Push(����)\n");


		}else if (card_dsum(playerCard, player_index) < card_dsum(dealerCard, dealer_index)) { //������ ������
			
			printf("���� ��\n");
			
		}
		else {
			game_money += bating_money*2;
			printf("�÷��̾� ��\n");
		
		}


		printf("\n����ī�� ���� :%d\n", DECK - (count + 1));

		_getch();
		


	}

	return 0;

}
void card_table(int dealerCard[], int dealer_index, int playerCard[], int player_index) { //����ī�� �迭 �� �÷��̾� ī��迭 ���

	system("cls");
	printf("����ī�� : ");
	printArray(dealerCard, dealer_index);
	printf("\n");
	printf("�÷��̾�ī�� : ");
	printArray(playerCard, player_index);
	_getch();

}
int choice( ) { //������ ī��2�徿�� ������ �����ൿ�� ���Ѵ�.

	int temp;
	printf("1.Stay 2.Hit\n");
	scanf_s("%d", &temp);

	if (!(temp == 1 || temp == 2)) {
		return -1; //�������

	}
	else if (temp == 1) {
		return 1;
	}
	else
		return 2;

}

int card_dsum(int* cardlist, int size) {//ī��迭�� ���� ���ϴ� �Լ�, ���� 21���� ������ A(1)�� 10���� ���, ������ 1�� ���, J,Q,K�� 10���� ���

  //A(1)�� ������ ���¼����� ������� ī��迭������ 21 ���ϸ� 11�� ���, ������ 1�ΰ��
	// * A(1) �ι������ų� ���ʿ� ������ ����ϴµ� ����������


	int sum = 0; //ī��迭�� ��
	int arr_sum[8] = { 0 }; // A(1) �� 10 �Ǵ� 1�� �ٲٱ� ���� ����

	int temp = 0;
	int count_ace = 0; // ace ������ ���� ����

	for (int i = 0; i < size; i++) {
		temp = cardlist[i]; //index  i��° ���� temp�� ��´�.

		if (cardlist[i] < 14) {
			if (temp == 1) {
				count_ace++;
				arr_sum[i] = 11;
			}
			else{
				arr_sum[i] = change_jqk(temp);
			}
		}else if (cardlist[i] < 114) {
			temp -= 100;
			if (temp == 1) {
				count_ace++;
				arr_sum[i] = 11;
			}
			else {
				arr_sum[i] = change_jqk(temp);
			}

		}else if (cardlist[i] < 214) {
			temp -= 200;
			if (temp == 1) {
				count_ace++;
				arr_sum[i] = 11;
			}
			else {
				arr_sum[i] = change_jqk(temp);
			}
		}else {
			temp -= 300;
			if (temp == 1) {
				count_ace++;
				arr_sum[i] = 11;
			}
			else {
				arr_sum[i] = change_jqk(temp);
			}
		}
	}
	for (int i = 0; i < size; i++) {
		sum += arr_sum[i];
	}

	if (sum > 21) {
		for (int i = 0; i < count_ace; i++) {
			if (sum <= 21) {
				break;
			}
			else {
				sum -= 10;
			}

		}
	}

	return sum;

}
int change_jqk(int value) { //�迭�� ī�尡  J Q K ���� Ȯ���ϰ� 10���� �ٲ��ִ� �Լ�
	return value < 11 ? value : 10;

}
int change_ace(int* arr_sum, int sum, int size) { //�迭������ 21�� �ʰ��Ҷ� A(1)�� 1�� �Ի��ϴ� �Լ�
	//ī�� �迭�� ���� �������� �� ���Ѵ�.

	
	for (int i = 0; i < size; i++) {
		if (arr_sum[i] == 1) {
			sum -= 10;
		}
	}	
	return sum;
}




void printArray(int arr[], int size) { //������ �ִ� ī��迭�� ����ϴ� �Լ� , J, Q , K �� ǥ���ϱ�
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



int get_playingCard(int arr[]) { //���� ������ ������ ���� ī���Ͱ��� �ʱ�ȭ ���Ѿ���.
	


	if (count > DECK)
		return -1;  //��ȯ�� ī�尡 ������ ������ ���� -1�� ��ȯ�Ѵ�.

	else {
		count++;
		return arr[count]; //���� �ε����� ī�带 ��ȯ
	}

	//���ӵ��� ī�尡�����ҽ� ����ī�带 �ٰ����� �����ؾ��Ѵ�.


}
/*
void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos); //������Ÿ���� ����� ��ġ�̵�
}
*/