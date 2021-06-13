#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#define DECK 52
#define KEY_UP  0x48
#define KEY_DOWN 0x50
#define KEY_LEFT  0x4B
#define KEY_RIGHT 0x4D
#define KEY_RETURN 0x0D

extern void textcolor(int);
extern void gotoxy(int, int);
void makingCard(int*);
void swap(int *, int , int );
void shuffle(int* , int );
void get_playingCard(int* , int* , int );
void card_table(int* , int , int* , int , int* , int );
void printDealerCardArray(int* , int );
void printPlayerCardArray(int* , int );
void blackjackDealerPrint(int* , int );
void blackjackPlayerPrint(int* , int );
int choiceBlackjack(int , char** );
int pullDownMenuBlackjack(int, char**);
int card_sum(int*, int);
int hideFlag = 0;

int playingCard[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,	// CLOVER
					13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,	// DIAMOND
					26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,	// HEART
					39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51	// SPADE
};


int playerCard[15] = { 0 }; //player�� ������ �������ִ� ī���� �迭
int dealerCard[15] = { 0 }; ////dealer�� ������ �������ִ� ī���� �迭



int blackjack(int insertmoney,int* money) {
	gotoxy(0, 0);
	char* blackjackChoiceList[] = { "Stay", "Hit", "Surrender", "DoubleDown" };
	char* blackMenuList[] = { "���ӽ���","����","�ڷΰ���" };
	char* blackFinMenuList[] = { "����ϱ�","�ڷΰ���" };

	//Card_deck 52��
	int menu = 0;
	int card_deck[52]; //ī�带 ���� �迭

	makingCard(card_deck); //��� �Ǳ���

	//printArray(card_deck, DECK); //ī��迭 ���

	shuffle(card_deck, DECK);  //ī�����

	int player_index = 0;//�÷��̾� ī��迭 �ε�����
	int dealer_index = 0;////���� ī��迭 �ε�����

	//int game_money = money;  //�����Ӵ�
	//int bating_money; //���øӴ�

	while (1)
	{
		gotoxy(0, 0);
		rewind(stdin);
		/*int temp = 0; //���ð��� ������� tmep ����
		temp = pullDownMenuBlackjack(3, blackMenuList); // �޴��Ǽ��ð� ��ȯ
		if (temp < 0 || temp>4) {
			system("cls");
			continue;
		}
		else if (temp == 0) {//���ӽ���*/

			while (1) {
				system("cls");
				int temp = 0; //blackjack �޴������� ���� ����
				/*if (*money <= 0) {
					printf("�������� 0���Դϴ�");
					_getch();
					break;

				}*/

				player_index = 0; //���ӽ��۽� ������ �÷��̾� ī��迭 �ε��� �ʱ�ȭ.
				dealer_index = 0;
				//bating_money = 0; //���øӴ� �ʱ�ȭ
				hideFlag = 1;


				//int test = 25 / 13;
				//printf(" ���ñݾ��� �����ּ���(�ּ� 1000��) / �ܰ� : %d\n", game_money); //���øӴ� �Է¹ޱ�
				//printf(" ���ñݾ��� �����ּ���(�ּ� 1000��) / �ܰ� : %d\n", *money); //���øӴ� �Է¹ޱ�

				//scanf_s("%d", &bating_money);

				/*rewind(stdin);
				if (bating_money < 1000 || game_money - bating_money < 0) { //���øӴ��� �ּ� 1000��
					system("cls");
					rewind(stdin);
					continue;
				} 
				else {
					game_money -= bating_money; //���ӸӴϿ��� ���øӴϸ� ���ش�.

				}
				system("cls");*/

				//Start

				/*
				if (count > 46) { //ī�带 ���λ��������
					count = -1;
					shuffle(card_deck, DECK);
				}
				*/

				//Start
				printf(" ī�带 ���徿 �����ϴ�(�ƹ�Ű�� �Է�).\n");
				_getch();
				system("cls");
				for (int i = 0; i < 2; i++) {
					//������ �÷��̾� ��� ī��2�徿�� �޴´�.
					card_table(dealerCard, dealer_index, playerCard, player_index,money, insertmoney);
					_getch();
					system("cls");
					get_playingCard(card_deck, dealerCard, dealer_index);
					dealer_index += 1;
					card_table(dealerCard, dealer_index, playerCard, player_index, money, insertmoney);
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
				if (card_sum(dealerCard, dealer_index) == 21) { //������ 21�϶�
					hideFlag = 0;
					card_table(dealerCard, dealer_index, playerCard, player_index, money, insertmoney);
					gotoxy(0, 21);
					printf("\n black Jack\n");
					system("pause");
					system("cls");
					return 0;
					/*_getch();
					temp = choiceBlackjack(2, blackFinMenuList); // �޴��Ǽ��ð� ��ȯ
					if (temp == 0) {
						//����ϱ�
						system("cls");
						continue;

					}
					else if (temp == 1) {
						//�޴��ΰ���
						break;
					}*/
				}
				else if (card_sum(playerCard, player_index) == 21) { //�÷��̾� 21�϶�
					hideFlag = 0;
					//*money += insertmoney * 3; //���ñ��� 3��
					card_table(dealerCard, dealer_index, playerCard, player_index, money, insertmoney);
					gotoxy(0, 21);
					printf("\n black Jack\n");
					/*_getch();
					temp = choiceBlackjack(2, blackFinMenuList); // �޴��Ǽ��ð� ��ȯ
					if (temp == 0) {
						//����ϱ�
						system("cls");
						continue;

					}
					else if (temp == 1) {
						//�޴��ΰ���
						break;
					}*/
					system("pause");
					system("cls");
					return insertmoney * 3;
				}

				int flag = 0; //bust �Ǵ� surrender Ȯ�� flag 



				//choice
				while (1) { //�÷��̾ stay or -1 �߸��Է������� �ݺ��� ����. -1 �� ������ Stay.
					card_table(dealerCard, dealer_index, playerCard, player_index, money, insertmoney); //���� ��������
					int temp = 0; //���ð��� ������� tmep ����
					temp = choiceBlackjack(4, blackjackChoiceList); // �޴��Ǽ��ð� ��ȯ
					if (temp == 0 || temp == -1) {//1�Ǵ� �߸��Է½� 

						card_table(dealerCard, dealer_index, playerCard, player_index, money, insertmoney);
						gotoxy(0, 21);
						printf(" Stay\n");
						_getch();
						system("cls");
						break;

					}
					else if (temp == 2) {
						card_table(dealerCard, dealer_index, playerCard, player_index, money, insertmoney);
						gotoxy(0, 21);
						printf(" Surrender\n");
						_getch();
						system("cls");
						flag = 2;//21�� ������ Bust üũ�� ���� flag ������ 1����
						break;

					}
					else if (temp == 3) { //DoubleDown 
					//���� ��ο� �� �ݺ��� ����
						card_table(dealerCard, dealer_index, playerCard, player_index, money, insertmoney);

						int temp_money;
						gotoxy(0, 21);
						printf(" �߰� ���ñݾ��� �����ּ���(�ּ� 1000��) / �ܰ� : %d\n", *money); //�߰� ���øӴ� �Է¹ޱ�
						scanf_s("%d", &temp_money);

						if (temp_money < 1000 || *money - insertmoney < 0) { //�߰� ���øӴ��� �ּ� 1000��
							continue;
						}
						else {
							insertmoney += temp_money; //���� ���øӴϿ� �߰��Էµ� ���øӴϸ� �����ش�.
							*money -= temp_money; //���ӸӴϿ��� ���øӴϸ� ���ش�.
							system("cls");
						}

						get_playingCard(card_deck, playerCard, player_index); //Hit�� ī�������� �� �迭�� �߱��Ѵ�.
						player_index += 1;  //ī������ �� ���� ī�带 �ޱ����� �ε����� 1���� ��Ų��.

						card_table(dealerCard, dealer_index, playerCard, player_index, money, insertmoney);
						gotoxy(0, 21);
						printf(" DoubleDown\n");
						_getch();
						system("cls");

						if (card_sum(playerCard, player_index) > 21) { //21�� ������ Bust
							flag = 1;//21�� ������ Bust üũ�� ���� flag ������ 1����	
						}
						break;

					}
					else {   //Hit ���ý� 21 �� ������ Bust / temp==2

						get_playingCard(card_deck, playerCard, player_index); //Hit�� ī�������� �� �迭�� �߱��Ѵ�.
						player_index += 1;  //ī������ �� ���� ī�带 �ޱ����� �ε����� 1���� ��Ų��.	
						card_table(dealerCard, dealer_index, playerCard, player_index, money, insertmoney);
						gotoxy(0, 21);
						printf(" Hit\n");
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




				card_table(dealerCard, dealer_index, playerCard, player_index, money, insertmoney);
				_getch();
				system("cls");


				if (flag == 1) { //Bust Ȯ��
					card_table(dealerCard, dealer_index, playerCard, player_index, money, insertmoney);
					gotoxy(0, 21);
					printf(" Bust (player)\n");
					system("pause");
					system("cls");
					return 0;
					/*_getch();
					temp = choiceBlackjack(2, blackFinMenuList); // �޴��Ǽ��ð� ��ȯ
					if (temp == 0) {
						//����ϱ�
						system("cls");
						continue;
					}
					else if (temp == 1) {
						//�޴��ΰ���
						system("cls");
						break;
					}*/
				}
				else if (flag == 2) {//Surrender Ȯ��
					card_table(dealerCard, dealer_index, playerCard, player_index, money, insertmoney);
					gotoxy(0, 21);
					printf(" Surrender\n");
					system("pause");
					system("cls");
					return insertmoney/2;
					/*_getch();
					*money += insertmoney * 0.5; //���ñ��� 0.5�踸 ����
					temp = choiceBlackjack(2, blackFinMenuList); // �޴��Ǽ��ð� ��ȯ
					if (temp == 0) {
						//����ϱ�
						system("cls");
						continue;
					}
					else if (temp == 1) {
						//�޴��ΰ���
						system("cls");
						break;
					}*/

				}

				//Stay �ÿ�
				//����ī�� ����
				hideFlag = 0;
				while (card_sum(dealerCard, dealer_index) < 17) {//������ ī���� ���� 17�̻��� �ɶ����� ī�带 �̴´�. 21�� ������ Bust

					get_playingCard(card_deck, dealerCard, dealer_index);
					dealer_index += 1;
					card_table(dealerCard, dealer_index, playerCard, player_index, money, insertmoney);
					_getch();
					system("cls");

					if (card_sum(dealerCard, dealer_index) > 21)
					{ //21�� ������ Bust
						flag = 1;//21�� ������ Bust üũ�� ���� flag ������ 1����
						break;
					}

				}

				card_table(dealerCard, dealer_index, playerCard, player_index, money, insertmoney);
				_getch();


				if (flag == 1) { //Bust Ȯ��
					gotoxy(0, 21);
					printf(" Bust (Dealer)\n");
					system("pause");
					system("cls");
					return insertmoney * 2;
					/* *money += insertmoney * 2; //player �¸��� ���ñݾ� 2�� �׵�
					temp = choiceBlackjack(2, blackFinMenuList); // �޴��Ǽ��ð� ��ȯ
					if (temp == 0) {
						//����ϱ�
						system("cls");
						continue;
					}
					else if (temp == 1) {
						//�޴��ΰ���
						system("cls");
						break;
					}*/
				}

				gotoxy(0, 21);
				printf(" ������ : %d\n", card_sum(dealerCard, dealer_index));
				printf(" �÷��̾��� : %d\n", card_sum(playerCard, player_index));

				if (card_sum(dealerCard, dealer_index) == card_sum(playerCard, player_index)) { //����
					//*money += insertmoney; //���ñݾ� 
					gotoxy(0, 23);
					printf(" Push(����)\n");
					system("pause");
					system("cls");
					return insertmoney;
				}
				else if (card_sum(playerCard, player_index) < card_sum(dealerCard, dealer_index)) { //������ ������
					gotoxy(0, 23);
					printf(" ���� ��\n");
					system("pause");
					system("cls");
					return 0;
				}
				else {
					//*money += insertmoney * 2;
					gotoxy(0, 23);
					printf(" �÷��̾� ��\n");
					system("pause");
					system("cls");
					return insertmoney * 2;
				}
				/*
				_getch();

				temp = choiceBlackjack(2, blackFinMenuList); // �޴��Ǽ��ð� ��ȯ
				if (temp == 0) {
					//����ϱ�
					system("cls");
					continue;
				}
				else if (temp == 1) {
					//�޴��ΰ���
					system("cls");
					break;
				}*/
			}

		/*}
		else if (temp == 1) {//����
			system("cls");
			printf("*******����*******\n");
			printf("***�������� ���***\n");
			printf("* ���ñݾ��� ������ ������ ���۵˴ϴ�.\n");
			printf("* ù���ۿ� ������ �÷��̾ ���� ī�� 2�徿�� �޽��ϴ�.\n");
			printf("* ������ �ڽ��� ī�� �� ù��° �� ���� �����մϴ�.\n");
			printf("* �÷��̾�� �ڽ��� ī�尡 21 �����ʴ� ���� ������ �߰��ൿ�� �Ҽ��ֽ��ϴ�.\n");
			printf("* �÷��̾��� ���� ����Ǹ� ������ ī�� 2���� ���� �մϴ�.\n"); \
				printf("* ������ ī������ 17�� ���������� �߰�ī�带 �̾ƾ��մϴ�.\n"); \
				printf("* ������ ���� ����Ǹ� 21���������� ���� ����� ����� �¸��ϰ� �˴ϴ�..\n");
			printf("\n***���ӱ�Ģ***\n");
			printf("* Bust : ī�������� 21�� �ѰԵǸ� �й��ϰԵ˴ϴ�.\n");
			printf("* BlackJack : ù���� ī���� ���� 21�϶� ���ñ��� 3�踦 �ްԵ˴ϴ�.\n");
			printf("* Aceī�� : Aacī��� 1 �Ǵ� 11�� ���˴ϴ�.\n");
			printf("* J Q K ī�� : J Q K ī��� 10 ���� ���˴ϴ�.\n");
			printf("\n***�߰��ൿ***\n");
			printf("* Stay : ī�带 ���̻� �����ʰ� ������ ������ �ѱ�ϴ�.\n* Hit : ī�������� �� �޽��ϴ�.\n* Surrender : �ڽ��� �й踦 �����ϰ� ���ñ��� ������ �޽��ϴ�.\n* DoubleDown : �߰������� �ϴ´�� ī�带 ���� ���ް� ������ ������ �ѱ�ϴ�."); \
				printf("(�ڷΰ����� �ƹ�Ű �Է�)\n");
			_getch();
			system("cls");
			continue;
		}
		else
		{
			system("cls");
			return insertmoney;
		}*/
	}
	return insertmoney;

}
void card_table(int* dealerCard, int dealer_index, int* playerCard, int player_index, int* money, int batMoney) { //����ī�� �迭 �� �÷��̾� ī��迭 ���(���� ��������)


	printf("           �����ڱ� : %d  ���� ���ñݾ� :%d", *money, batMoney);
	blackjackDealerPrint(dealerCard, dealer_index);
	//printf("\n\n\n");
	//printDealerCardArray(playerCard, player_index);
	blackjackPlayerPrint(playerCard, player_index);
	
	


}


int pullDownMenuBlackjack(int max_menu, char** menulist)
{
	gotoxy(0, 0);
	char ch;
	int sel = 0;
	while (1) {
		for (int i = 0; i < max_menu; i++) {
			if (sel == i)
				textcolor(12);
			else
				textcolor(15);
			if (max_menu % 2 == 1) {
				gotoxy(20 * i + 1, 3 + 4);
				printf("%s",  menulist[i]);
			}
			else {
				if (i < max_menu / 2) {
					gotoxy(20 * i + 1, 3 + 4);
					printf("%s", menulist[i]);
				}
				else {
					gotoxy(20 * (i - max_menu / 2) + 1, 6 + 4);
					printf("%s", menulist[i]);
				}
			}
		}
		textcolor(15);
		ch = _getch();
		if (ch == KEY_LEFT) {
			//PlaySound(TEXT("sound\\button2.wav"), NULL, SND_ASYNC);
			sel = ((sel - 1) + max_menu) % max_menu;
		}
		else if (ch == KEY_RIGHT) {
			//PlaySound(TEXT("sound\\button2.wav"), NULL, SND_ASYNC);
			sel = (sel + 1) % max_menu;
		}
		else if (ch == KEY_UP && max_menu % 2 == 0) {
			//PlaySound(TEXT("sound\\button2.wav"), NULL, SND_ASYNC);
			sel = ((sel + max_menu / 2) + max_menu) % max_menu;
		}
		else if (ch == KEY_DOWN && max_menu % 2 == 0) {
			//PlaySound(TEXT("sound\\button2.wav"), NULL, SND_ASYNC);
			sel = ((sel - max_menu / 2) + max_menu) % max_menu;
		}
		else if (ch == KEY_RETURN) {
			//PlaySound(TEXT("sound\\button.wav"), NULL, SND_ASYNC);
			break;
		}
		Sleep(1);
	}
	system("cls");
	return sel;
}

int choiceBlackjack(int max_menu, char** menulist)
{
	gotoxy(0, 0);
	char ch;
	int sel = 0;
	while (1) {
		for (int i = 0; i < max_menu; i++) {
			if (sel == i)
				textcolor(12);
			else
				textcolor(15);
			
			gotoxy(15 * (i - max_menu / 2) + 45,22);
			printf("%s", menulist[i]);
		
		}
		textcolor(15);
		ch = _getch();
		if (ch == KEY_LEFT) {
			//PlaySound(TEXT("sound\\button2.wav"), NULL, SND_ASYNC);
			sel = ((sel - 1) + max_menu) % max_menu;
		}
		else if (ch == KEY_RIGHT) {
			//PlaySound(TEXT("sound\\button2.wav"), NULL, SND_ASYNC);
			sel = (sel + 1) % max_menu;
		}
		else if (ch == KEY_UP && max_menu % 2 == 0) {
			//PlaySound(TEXT("sound\\button2.wav"), NULL, SND_ASYNC);
			sel = ((sel + max_menu / 2) + max_menu) % max_menu;
		}
		else if (ch == KEY_DOWN && max_menu % 2 == 0) {
			//PlaySound(TEXT("sound\\button2.wav"), NULL, SND_ASYNC);
			sel = ((sel - max_menu / 2) + max_menu) % max_menu;
		}
		else if (ch == KEY_RETURN) {
			//PlaySound(TEXT("sound\\button.wav"), NULL, SND_ASYNC);
			break;
		}
		Sleep(1);
	}
	system("cls");
	return sel;
}

int card_sum(int* cardlist, int size) {//ī��迭�� ���� ���ϴ� �Լ�, ���� 21���� ������ A(1)�� 10���� ���, ������ 1�� ���, J,Q,K�� 10���� ���

  //A(1)�� ������ ���¼����� ������� ī��迭������ 21 ���ϸ� 11�� ���, ������ 1�ΰ��
	


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

void printPlayerCardArray(int* arr, int size) { //������ �ִ� ī��迭�� ����ϴ� �Լ� , J, Q , K �� ǥ���ϱ�
	int temp = 0;
	int suite = 0; //����
	for (int i = 0; i < size; i++) {
		temp = (arr[i] % 13) + 1;
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
	printf("\n");


}


void printDealerCardArray(int* arr, int size) { //���� ī��迭 , 1���� �Ⱥ��̰� ���

	int temp = 0;
	int suite = 0; //����
	for (int i = 0; i < size; i++) {
		temp = (arr[i] % 13) + 1; //13���� �������� ������
		suite = temp / 13; //13���� ������


		if (i == 0 && hideFlag == 1) { //1��°ī��� ���������ʴ´�. (���а� �����Ǹ� ����)  
			printf("[?] ");
		}

		else

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

void blackjackDealerPrint(int* arr, int size) { // ��Ŀ �� ���
	
	int temp = 0;
	int suite = 0; //����
	printf("\n ����ī�� : ");
	gotoxy(0, 0);
	for (int i = 0; i < size; i++)
	{
		temp = (arr[i] % 13) + 1; //13���� �������� ������
		suite = arr[i] / 13; //13���� ������

	   //PlaySound(TEXT("sound\\paper.wav"), NULL, SND_ASYNC);

		gotoxy(3 + i * 15, 2);
		printf("������������������"); // ī�� ��� ���

		for (int j = 2; j < 9; j++)
		{
			gotoxy(3 + i * 15, j+1);
			printf("��       �� "); // ī�� ��� ���
		}

		gotoxy(3 + i * 15, 10);
		printf("������������������ "); // ī�� ��� ���
		if (i == 0 && hideFlag == 1)
		{
			gotoxy(7 + i * 15, 6);
			printf("?");
			gotoxy(5 + i * 15, 3);
			printf("?");
			gotoxy(10 + i * 15, 9);
			printf("?");
		}
		else {
			switch (suite) // ī�� ���� ���
			{
			case 0:
				gotoxy(7 + i * 15, 6); printf("��");
				break;
			case 1:
				gotoxy(7 + i * 15, 6); printf("��");
				break;
			case 2:
				gotoxy(7 + i * 15, 6); printf("��");
				break;
			case 3:
				gotoxy(7 + i * 15, 6); printf("��");
				break;
			default:
				gotoxy(7 + i * 15, 6); printf("����");
				break;
			}
			switch (temp) // ī�� ���� ���
			{
			case 11:
				gotoxy(5 + i * 15, 3); printf("J");
				gotoxy(10 + i * 15, 9); printf("J");
				break;
			case 12:
				gotoxy(5 + i * 15, 3); printf("Q");
				gotoxy(10 + i * 15, 9); printf("Q");
				break;
			case 13:
				gotoxy(5 + i * 15, 3); printf("K");
				gotoxy(10 + i * 15, 9); printf("K");
				break;
			case 1:
				gotoxy(5 + i * 15, 3); printf("A");
				gotoxy(10 + i * 15, 9); printf("A");
				break;
			default:
				gotoxy(5 + i * 15, 3); printf("%d", temp);
				gotoxy(9 + i * 15, 9); printf("%2d", temp);
				break;
			}
			textcolor(15);
		}
	}
	gotoxy(0, 0);

}

void blackjackPlayerPrint(int* arr, int size) { // ��Ŀ �� ���
	gotoxy(0, 0);
	int temp = 0;
	int suite = 0; //����
	printf("\n\n\n\n\n\n\n\n\n\n\n �÷��̾�ī�� : ");
	for (int i = 0; i < size; i++)
	{
		temp = (arr[i] % 13) + 1; //13���� �������� ������
		suite = arr[i] / 13; //13���� ������

	   //PlaySound(TEXT("sound\\paper.wav"), NULL, SND_ASYNC);

		gotoxy(3 + i * 15, 1 + 11);
		printf("������������������"); // ī�� ��� ���

		for (int j = 2; j < 9; j++)
		{
			gotoxy(3 + i * 15, j + 11);
			printf("��       �� "); // ī�� ��� ���
		}

		gotoxy(3 + i * 15, 20);
		printf("������������������ "); // ī�� ��� ���
		switch (suite) // ī�� ���� ���
		{
		case 0:
			gotoxy(7 + i * 15, 16);
			printf("��");
			break;
		case 1:
			gotoxy(7 + i * 15, 16);
			printf("��");
			break;
		case 2:
			gotoxy(7 + i * 15, 16);
			printf("��");
			break;
		case 3:
			gotoxy(7 + i * 15, 16);
			printf("��");
			break;
		default:
			gotoxy(7 + i * 15, 16);
			printf("����");
			break;
		}
		switch (temp) // ī�� ���� ���
		{
		case 11:
			gotoxy(5 + i * 15, 13); printf("J");
			gotoxy(10 + i * 15, 19); printf("J");
			break;
		case 12:
			gotoxy(5 + i * 15, 13); printf("Q");
			gotoxy(10 + i * 15, 19); printf("Q");
			break;
		case 13:
			gotoxy(5 + i * 15, 13); printf("K");
			gotoxy(10 + i * 15, 19); printf("K");
			break;
		case 1:
			gotoxy(5 + i * 15, 13); printf("A");
			gotoxy(10 + i * 15, 19); printf("A");
			break;
		default:
			gotoxy(5 + i * 15, 13); printf("%d", temp);
			gotoxy(9 + i * 15, 19); printf("%2d", temp);
			break;
		}
		textcolor(15);

	}
	gotoxy(0, 0);
	

}

void makingCard(int* card_deck) { //ī�嵦�� ����� �Լ�
	for (int i = 0; i < 52; i++) {
		card_deck[i] = playingCard[i];
	}


}


void swap(int* arr, int i, int j) //�����ҋ� ���̴� �Լ�
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void shuffle(int* arr, int n)
{
	int temp = 0;
	int rn;

	for (int i = 0; i < n - 1; i++) {

		rn = rand() % (n - i - 1) + i + 1; //������ ���� :  i + 1 ~  arr[n-1]

		swap(arr, i, rn);
	}

}



void get_playingCard(int* deck, int* cardArray, int index) { //���� ������ ������ ���� ī���Ͱ��� �ʱ�ȭ ���Ѿ���.

	static int count = 0;
	if (count >= DECK) {
		count = 0;  //-1�� �ʱ�ȭ
		shuffle(deck, DECK);  //ī�����
	}
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