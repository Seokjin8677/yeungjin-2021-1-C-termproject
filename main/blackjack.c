#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#define DECK 52


void makingCard(int card_deck[]);
void swap(int arr[], int i, int j);
void shuffle(int *arr, int n);
void get_playingCard(int* deck, int* cardArray, int index);
void card_table(int* dealerCard, int dealer_index, int* playerCard, int player_index, int money, int batMoney);
void printDealerCardArray(int* arr, int size);
void printPlayerCardArray(int* arr, int size);

int playingCard[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,	// CLOVER
					13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,	// DIAMOND
					26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,	// HEART
					39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51	// SPADE
					};


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
	
	makingCard(card_deck); //��� �Ǳ���
	
	//printArray(card_deck, DECK); //ī��迭 ���

	shuffle(card_deck, DECK);  //ī�����

	int player_index = 0;//�÷��̾� ī��迭 �ε�����
	int dealer_index = 0;////���� ī��迭 �ε�����

	int game_money = money;  //�����Ӵ�
	int bating_money; //���øӴ�


	while (1) {
		
		player_index = 0; //���ӽ��۽� ������ �÷��̾� ī��迭 �ε��� �ʱ�ȭ.
		dealer_index = 0;
		bating_money = 0; //���øӴ� �ʱ�ȭ
		
		while (1)
		{

			printf("1.���ӽ���\n"); 
			printf("2.����\n");
			printf("3.�ڷΰ���\n");
			int temp;
			scanf_s("%d", &temp);
			if (temp<0||temp>4) {
				system("cls");
				continue;
			}
			else if (temp == 1) {
				system("cls");
				break;
			}
			else if (temp == 2) {
				system("cls");
				printf("(���� ���� �����ϴ� ����)\n");
				printf("(�ڷΰ����� �ƹ�Ű �Է�)\n");
				_getch();
				system("cls");
				continue;
			}
			else
			{
				system("cls");
				return money;
			}
		}
		

		printf("���ñݾ��� �����ּ���(�ּ� 1000��) / �ܰ� : %d\n",game_money); //���øӴ� �Է¹ޱ�
		
		scanf_s("%d", &bating_money);

		if (bating_money < 1000) { //���øӴ��� �ּ� 1000��
			continue;
		}
		else{
			game_money -= bating_money; //���ӸӴϿ��� ���øӴϸ� ���ش�.

		}
		system("cls");

		//Start

		/*
		if (count > 46) { //ī�带 ���λ��������
			count = -1;
			shuffle(card_deck, DECK);
		}
		*/

		//Start
		printf("ī�带 ���徿 �����ϴ�(�ƹ�Ű�� �Է�).\n"); 
		_getch();
		system("cls");
		for (int i = 0; i < 2; i++) {
			 //������ �÷��̾� ��� ī��2�徿�� �޴´�.
			card_table(dealerCard, dealer_index, playerCard, player_index, game_money, bating_money);
			_getch();
			system("cls");
			get_playingCard(card_deck, dealerCard,dealer_index);
			dealer_index+=1;
			card_table(dealerCard, dealer_index, playerCard, player_index, game_money, bating_money);
			_getch();
			system("cls");
			get_playingCard(card_deck, playerCard, player_index);
			player_index += 1;
			
			

			}
		/*
		*�ε��� , ī��Ʈ Ȯ�ο�
		printf("���� �ε��� �� :%d ī��Ʈ�� :%d\n", dealer_index, count);
		printf("�÷��̾� �ε��� �� :%d ī��Ʈ�� :%d\n", player_index, count);
		_getch();
		*/
	


		//2��̾����� 21�� ������ blackjack(���øӴ� 2��)
		if (card_sum(dealerCard, dealer_index)==21) { //������ 21�϶�
			card_table(dealerCard, dealer_index, playerCard, player_index, game_money, bating_money);
			printf("\nblack Jack\n");
			_getch();
			system("cls");
			continue;
		
		}
		else if(card_sum(playerCard, player_index)==21){ //�÷��̾� 21�϶�
			game_money += bating_money * 3; //���ñ��� 3��
			card_table(dealerCard, dealer_index, playerCard, player_index, game_money, bating_money);
			printf("\nblack Jack\n");
			_getch();
			system("cls");
			continue;
		}

		int flag = 0; //bust �Ǵ� surrender Ȯ�� flag 


		//Stay(Stand) or Hit

		while (1) { //�÷��̾ stay or -1 �߸��Է������� �ݺ��� ����. -1 �� ������ Stay.
			card_table(dealerCard, dealer_index, playerCard, player_index, game_money, bating_money); //���� ��������


			int temp = 0; //���ð��� ������� tmep ����
			temp = choice(); //Stay or Hit ����
			
			
			system("cls");

			if (temp == 1||temp==-1) {//1�Ǵ� �߸��Է½� 
				
				card_table(dealerCard, dealer_index, playerCard, player_index, game_money, bating_money);
				printf("Stay\n");
				_getch();
				system("cls");
				break;

			}
			else if (temp==3) {
				card_table(dealerCard, dealer_index, playerCard, player_index, game_money, bating_money);
				printf("Surrender\n");
				_getch();
				system("cls");
				flag = 2;//21�� ������ Bust üũ�� ���� flag ������ 1����
				break;

			}
			else{   //Hit ���ý� 21 �� ������ Bust
				
				get_playingCard(card_deck, playerCard,player_index); //Hit�� ī�������� �� �迭�� �߱��Ѵ�.
				player_index += 1;  //ī������ �� ���� ī�带 �ޱ����� �ε����� 1���� ��Ų��.

				
				card_table(dealerCard, dealer_index, playerCard, player_index, game_money, bating_money);
				printf("Hit\n");
				_getch();
				system("cls");

				if (card_sum(playerCard, player_index) > 21) { //21�� ������ Bust
					flag = 1;//21�� ������ Bust üũ�� ���� flag ������ 1����
					break;
				}
				else if (card_sum(playerCard, player_index) == 21) { //21�� �Ǿ������ Stay
					break;
				}

			}
		}

		
		
		
		card_table(dealerCard, dealer_index, playerCard, player_index, game_money, bating_money);
		_getch();
		system("cls");

		if (flag == 1) { //Bust Ȯ��
			printf("Bust (player)\n");
			_getch();
			system("cls");
			continue;
		}
		else if (flag == 2) {//Surrender Ȯ��
			printf("Surrender\n");
			_getch();
			system("cls");
			game_money += bating_money * 0.5; //���ñ��� 0.5�踸 ����
			continue;
		}

		//Stay �ÿ�
		//
		while (card_sum(dealerCard, dealer_index)<17) {//������ ī���� ���� 17�̻��� �ɶ����� ī�带 �̴´�. 21�� ������ Bust
			

			get_playingCard(card_deck, dealerCard, dealer_index);
			dealer_index += 1;
			card_table(dealerCard, dealer_index, playerCard, player_index, game_money, bating_money);
			_getch();
			system("cls");

			if (card_sum(dealerCard, dealer_index) > 21) { //21�� ������ Bust
				flag = 1;//21�� ������ Bust üũ�� ���� flag ������ 1����
				break;
			}
			
		}

		card_table(dealerCard, dealer_index, playerCard, player_index, game_money, bating_money);
		_getch();
	

		if (flag == 1) { //Bust Ȯ��
			printf("Bust (Dealer)\n");
			game_money += bating_money * 2; //player �¸��� ���ñݾ� 2�� �׵�
			_getch();
			system("cls");
			continue;
		}

		printf("������ : %d\n", card_sum(dealerCard, dealer_index));
		printf("�÷��̾��� : %d\n", card_sum(playerCard, player_index));

		if (card_sum(dealerCard, dealer_index) == card_sum(playerCard, player_index)){ //����
			game_money += bating_money; //���ñݾ� 
			printf("Push(����)\n");
		}else if (card_sum(playerCard, player_index) < card_sum(dealerCard, dealer_index)) { //������ ������
			printf("���� ��\n");
		}
		else {
			game_money += bating_money*2;
			printf("�÷��̾� ��\n");
		}


		

		_getch();
		system("cls");


	}

	return 0;

}
void card_table(int *dealerCard, int dealer_index, int *playerCard, int player_index,int money, int batMoney) { //����ī�� �迭 �� �÷��̾� ī��迭 ���(���� ��������)

	printf("����ī�� : ");
	printDealerCardArray(dealerCard, dealer_index);
	printf("\n");
	printf("�÷��̾�ī�� : ");
	printPlayerCardArray(playerCard, player_index);
	printf("\n");
	printf("�����ڱ� : %d  ���� ���ñݾ� :%d",money,batMoney);
	printf("\n");

}
int choice( ) { //������ �����ൿ�� ���Ѵ�. 

	int temp;
	printf("1.Stay 2.Hit 3.Surrender 4.DoubleDown\n");
	scanf_s("%d", &temp);

	if (temp == 1) {
		return 1;
	}
	else if (temp == 2) {
		return 2;
	}
	else if (temp == 3) {
		return 3;
	}
	else if (temp == 4) {
		return 4;
	}
	else{
		return -1; //�������

	}

}

int card_sum(int* cardlist, int size) {//ī��迭�� ���� ���ϴ� �Լ�, ���� 21���� ������ A(1)�� 10���� ���, ������ 1�� ���, J,Q,K�� 10���� ���

  //A(1)�� ������ ���¼����� ������� ī��迭������ 21 ���ϸ� 11�� ���, ������ 1�ΰ��
	// * A(1) �ι������ų� ���ʿ� ������ ����ϴµ� ����������


	int sum = 0; //ī��迭�� ��
	int temp = 0;
	int count_ace = 0; // ace ������ ���� ����



	for (int i = 0; i < size; i++) {
		temp = (cardlist[i] % 13) + 1;
		if (temp == 1) {
			sum += 11;
			count_ace++;
		}
		else if (temp > 10) {
			sum += 10;
		}
		else
			sum += temp;

	}
	if (sum > 21) {
		for (int i = 0; i < count_ace; i++) {
			if (sum <= 21) {
				break;
			}
			else
				sum -= 10;

		}
	}	return sum;
}

void printPlayerCardArray(int *arr, int size) { //������ �ִ� ī��迭�� ����ϴ� �Լ� , J, Q , K �� ǥ���ϱ�
	int temp = 0;
	int suite = 0; //����
	for (int i = 0; i < size; i++) {
		temp = (arr[i]%13) + 1;
		suite = temp / 13;
		switch (suite)
		{
		case 1: //Ŭ�ι�
			if (temp == 1) {
				printf("��A ");
			}
			else if (temp < 11) {
				printf("��%d ", temp);
			}
			else if (temp == 11) {
				printf("��J ");
			}
			else if (temp == 12) {
				printf("��Q ");
			}
			else if(temp ==13){
				printf("��K ");
			}
			else
				printf("��¿��� ");
			break;
		case 2 : //���̾� 
			if (temp == 1) {
				printf("��A ");
			}
			else if (temp  < 11) {
				printf("��%d ", temp);
			}
			else if (temp == 11) {
				printf("��J ");
			}
			else if (temp == 12) {
				printf("��Q ");
			}
			else if (temp == 13) {
				printf("��K ");
			}
			else
				printf("��¿��� ");
			break;

		case 3: //��Ʈ
			if (temp == 1) {
				printf("��A ");
			}
			else if (temp  < 11) {
				printf("��%d ", temp);
			}
			else if (temp == 11) {
				printf("��J ");
			}
			else if (temp == 12) {
				printf("��Q ");
			}
			else if (temp == 13) {
				printf("��K ");
			}
			else
				printf("��¿��� ");
			break;
		default: //�����̽�
			if (temp  ==1) {
				printf("��A ");
			}
			else if (temp  < 11) {
				printf("��%d ", temp);
			}
			else if (temp == 11) {
				printf("��J ");
			}
			else if (temp == 12) {
				printf("��Q ");
			}
			else if (temp == 13) {
				printf("��K ");
			}
			else
				printf("��¿��� ");
			break;
		}

	}
	printf("\n");


}

void printDealerCardArray(int *arr, int size) { //���� ī��迭 , 1���� �Ⱥ��̰� ���
	
	int temp = 0;
	int suite = 0; //����
	for (int i = 0; i < size; i++) {
		temp = (arr[i] % 13) + 1; //13���� �������� ������
		suite = temp / 13; //13���� ������
		
		/*
		if (i == 0) { //1��°ī��� ���������ʴ´�. (���а� �����Ǹ� ����)  
			printf("[?] ");
		}

		else
		*/
		{
			switch (suite)
			{
			case 1: //Ŭ�ι�
				if (temp == 1) {
					printf("��A ");
				}
				else if (temp < 11) {
					printf("��%d ", temp);
				}
				else if (temp == 11) {
					printf("��J ");
				}
				else if (temp == 12) {
					printf("��Q ");
				}
				else if (temp == 13) {
					printf("��K ");
				}
				else
					printf("��¿��� ");
				break;
			case 2: //���̾� 
				if (temp == 1) {
					printf("��A ");
				}
				else if (temp < 11) {
					printf("��%d ", temp);
				}
				else if (temp == 11) {
					printf("��J ");
				}
				else if (temp == 12) {
					printf("��Q ");
				}
				else if (temp == 13) {
					printf("��K ");
				}
				else
					printf("��¿��� ");
				break;

			case 3: //��Ʈ
				if (temp == 1) {
					printf("��A ");
				}
				else if (temp < 11) {
					printf("��%d ", temp);
				}
				else if (temp == 11) {
					printf("��J ");
				}
				else if (temp == 12) {
					printf("��Q ");
				}
				else if (temp == 13) {
					printf("��K ");
				}
				else
					printf("��¿��� ");
				break;
			default: //�����̽�
				if (temp == 1) {
					printf("��A ");
				}
				else if (temp < 11) {
					printf("��%d ", temp);
				}
				else if (temp == 11) {
					printf("��J ");
				}
				else if (temp == 12) {
					printf("��Q ");
				}
				else if (temp == 13) {
					printf("��K ");
				}
				else
					printf("��¿��� ");
				break;
			}
		}

		

		
	}
	printf("\n");


}

void makingCard(int card_deck[]) { //ī�嵦�� ����� �Լ�
	for (int i = 0; i <52; i++) {
		card_deck[i] = playingCard[i];
	}


}


void swap(int arr[], int i, int j) //�����ҋ� ���̴� �Լ�
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void shuffle(int *arr, int n)  
{
	srand(time(NULL));

	int temp = 0;
	int rn;

	for (int i = 0; i < n - 1; i++) {

		rn = rand() % (n - i - 1) + i + 1; //������ ���� :  i + 1 ~  arr[n-1]

		swap(arr, i, rn);
	}

}



void get_playingCard(int *deck,int *cardArray,int index) { //���� ������ ������ ���� ī���Ͱ��� �ʱ�ȭ ���Ѿ���.
	
	static int count = -1;
	if (count > DECK)
		count= -1;  //��ȯ�� ī�尡 ������ ������ ���� -1�� ��ȯ�Ѵ�.

	else {
		cardArray[index] = deck[count];
	
		count++;
		int temp = count;
		//printf("����ī�� �� : %d", DECK - (temp+1));
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