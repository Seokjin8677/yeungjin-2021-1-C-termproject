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


int playerCard[15] = { 0 }; //player가 게임중 가질수있는 카드의 배열
int dealerCard[15] = { 0 }; ////dealer가 게임중 가질수있는 카드의 배열



int blackjack(int insertmoney,int* money) {
	gotoxy(0, 0);
	char* blackjackChoiceList[] = { "Stay", "Hit", "Surrender", "DoubleDown" };
	char* blackMenuList[] = { "게임시작","도움말","뒤로가기" };
	char* blackFinMenuList[] = { "계속하기","뒤로가기" };

	//Card_deck 52장
	int menu = 0;
	int card_deck[52]; //카드를 담을 배열

	makingCard(card_deck); //없어도 되긴함

	//printArray(card_deck, DECK); //카드배열 출력

	shuffle(card_deck, DECK);  //카드셔플

	int player_index = 0;//플레이어 카드배열 인덱스값
	int dealer_index = 0;////딜러 카드배열 인덱스값

	//int game_money = money;  //보유머니
	//int bating_money; //배팅머니

	while (1)
	{
		gotoxy(0, 0);
		rewind(stdin);
		/*int temp = 0; //선택값을 담기위한 tmep 변수
		temp = pullDownMenuBlackjack(3, blackMenuList); // 메뉴의선택값 반환
		if (temp < 0 || temp>4) {
			system("cls");
			continue;
		}
		else if (temp == 0) {//게임시작*/

			while (1) {
				system("cls");
				int temp = 0; //blackjack 메뉴선택을 위한 변수
				/*if (*money <= 0) {
					printf("보유금이 0원입니다");
					_getch();
					break;

				}*/

				player_index = 0; //게임시작시 딜러와 플레이어 카드배열 인덱스 초기화.
				dealer_index = 0;
				//bating_money = 0; //배팅머니 초기화
				hideFlag = 1;


				//int test = 25 / 13;
				//printf(" 배팅금액을 정해주세요(최소 1000원) / 잔고 : %d\n", game_money); //배팅머니 입력받기
				//printf(" 배팅금액을 정해주세요(최소 1000원) / 잔고 : %d\n", *money); //배팅머니 입력받기

				//scanf_s("%d", &bating_money);

				/*rewind(stdin);
				if (bating_money < 1000 || game_money - bating_money < 0) { //배팅머니은 최소 1000원
					system("cls");
					rewind(stdin);
					continue;
				} 
				else {
					game_money -= bating_money; //게임머니에서 배팅머니를 빼준다.

				}
				system("cls");*/

				//Start

				/*
				if (count > 46) { //카드를 전부사용했을시
					count = -1;
					shuffle(card_deck, DECK);
				}
				*/

				//Start
				printf(" 카드를 두장씩 가집니다(아무키나 입력).\n");
				_getch();
				system("cls");
				for (int i = 0; i < 2; i++) {
					//딜러와 플레이어 모두 카드2장씩을 받는다.
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
				*인덱스 , 카운트 확인용
				printf("딜러 인덱스 값 :%d 카운트값 :%d\n", dealer_index, count);
				printf("플레이어 인덱스 값 :%d 카운트값 :%d\n", player_index, count);
				_getch();
				*/



				//2장뽑았을때 21이 나오면 blackjack(배팅머니 2배)
				if (card_sum(dealerCard, dealer_index) == 21) { //딜러가 21일때
					hideFlag = 0;
					card_table(dealerCard, dealer_index, playerCard, player_index, money, insertmoney);
					gotoxy(0, 21);
					printf("\n black Jack\n");
					system("pause");
					system("cls");
					return 0;
					/*_getch();
					temp = choiceBlackjack(2, blackFinMenuList); // 메뉴의선택값 반환
					if (temp == 0) {
						//계속하기
						system("cls");
						continue;

					}
					else if (temp == 1) {
						//메뉴로가기
						break;
					}*/
				}
				else if (card_sum(playerCard, player_index) == 21) { //플레이어 21일때
					hideFlag = 0;
					//*money += insertmoney * 3; //배팅금의 3배
					card_table(dealerCard, dealer_index, playerCard, player_index, money, insertmoney);
					gotoxy(0, 21);
					printf("\n black Jack\n");
					/*_getch();
					temp = choiceBlackjack(2, blackFinMenuList); // 메뉴의선택값 반환
					if (temp == 0) {
						//계속하기
						system("cls");
						continue;

					}
					else if (temp == 1) {
						//메뉴로가기
						break;
					}*/
					system("pause");
					system("cls");
					return insertmoney * 3;
				}

				int flag = 0; //bust 또는 surrender 확인 flag 



				//choice
				while (1) { //플레이어가 stay or -1 잘못입력했을때 반복문 종료. -1 이 나오면 Stay.
					card_table(dealerCard, dealer_index, playerCard, player_index, money, insertmoney); //현재 게임정보
					int temp = 0; //선택값을 담기위한 tmep 변수
					temp = choiceBlackjack(4, blackjackChoiceList); // 메뉴의선택값 반환
					if (temp == 0 || temp == -1) {//1또는 잘못입력시 

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
						flag = 2;//21이 넘으면 Bust 체크를 위해 flag 변수에 1대입
						break;

					}
					else if (temp == 3) { //DoubleDown 
					//한장 드로우 후 반복문 종료
						card_table(dealerCard, dealer_index, playerCard, player_index, money, insertmoney);

						int temp_money;
						gotoxy(0, 21);
						printf(" 추가 배팅금액을 정해주세요(최소 1000원) / 잔고 : %d\n", *money); //추가 배팅머니 입력받기
						scanf_s("%d", &temp_money);

						if (temp_money < 1000 || *money - insertmoney < 0) { //추가 배팅머니은 최소 1000원
							continue;
						}
						else {
							insertmoney += temp_money; //기존 배팅머니에 추가입력된 배팅머니를 더해준다.
							*money -= temp_money; //게임머니에서 배팅머니를 빼준다.
							system("cls");
						}

						get_playingCard(card_deck, playerCard, player_index); //Hit시 카드한장을 더 배열에 추기한다.
						player_index += 1;  //카드지급 후 다음 카드를 받기위해 인덱스를 1증가 시킨다.

						card_table(dealerCard, dealer_index, playerCard, player_index, money, insertmoney);
						gotoxy(0, 21);
						printf(" DoubleDown\n");
						_getch();
						system("cls");

						if (card_sum(playerCard, player_index) > 21) { //21이 넘으면 Bust
							flag = 1;//21이 넘으면 Bust 체크를 위해 flag 변수에 1대입	
						}
						break;

					}
					else {   //Hit 선택시 21 이 넘으면 Bust / temp==2

						get_playingCard(card_deck, playerCard, player_index); //Hit시 카드한장을 더 배열에 추기한다.
						player_index += 1;  //카드지급 후 다음 카드를 받기위해 인덱스를 1증가 시킨다.	
						card_table(dealerCard, dealer_index, playerCard, player_index, money, insertmoney);
						gotoxy(0, 21);
						printf(" Hit\n");
						_getch();
						system("cls");

						if (card_sum(playerCard, player_index) > 21) { //21이 넘으면 Bust
							flag = 1;//21이 넘으면 Bust 체크를 위해 flag 변수에 1대입
							break;
						}
						else if (card_sum(playerCard, player_index) == 21) { //21이 되었을경우 Stay
							break;
						}

					}
				}




				card_table(dealerCard, dealer_index, playerCard, player_index, money, insertmoney);
				_getch();
				system("cls");


				if (flag == 1) { //Bust 확인
					card_table(dealerCard, dealer_index, playerCard, player_index, money, insertmoney);
					gotoxy(0, 21);
					printf(" Bust (player)\n");
					system("pause");
					system("cls");
					return 0;
					/*_getch();
					temp = choiceBlackjack(2, blackFinMenuList); // 메뉴의선택값 반환
					if (temp == 0) {
						//계속하기
						system("cls");
						continue;
					}
					else if (temp == 1) {
						//메뉴로가기
						system("cls");
						break;
					}*/
				}
				else if (flag == 2) {//Surrender 확인
					card_table(dealerCard, dealer_index, playerCard, player_index, money, insertmoney);
					gotoxy(0, 21);
					printf(" Surrender\n");
					system("pause");
					system("cls");
					return insertmoney/2;
					/*_getch();
					*money += insertmoney * 0.5; //배팅금의 0.5배만 차감
					temp = choiceBlackjack(2, blackFinMenuList); // 메뉴의선택값 반환
					if (temp == 0) {
						//계속하기
						system("cls");
						continue;
					}
					else if (temp == 1) {
						//메뉴로가기
						system("cls");
						break;
					}*/

				}

				//Stay 시에
				//딜러카드 공개
				hideFlag = 0;
				while (card_sum(dealerCard, dealer_index) < 17) {//딜러는 카드의 합이 17이상이 될때까지 카드를 뽑는다. 21이 넘으면 Bust

					get_playingCard(card_deck, dealerCard, dealer_index);
					dealer_index += 1;
					card_table(dealerCard, dealer_index, playerCard, player_index, money, insertmoney);
					_getch();
					system("cls");

					if (card_sum(dealerCard, dealer_index) > 21)
					{ //21이 넘으면 Bust
						flag = 1;//21이 넘으면 Bust 체크를 위해 flag 변수에 1대입
						break;
					}

				}

				card_table(dealerCard, dealer_index, playerCard, player_index, money, insertmoney);
				_getch();


				if (flag == 1) { //Bust 확인
					gotoxy(0, 21);
					printf(" Bust (Dealer)\n");
					system("pause");
					system("cls");
					return insertmoney * 2;
					/* *money += insertmoney * 2; //player 승리로 배팅금액 2배 휙득
					temp = choiceBlackjack(2, blackFinMenuList); // 메뉴의선택값 반환
					if (temp == 0) {
						//계속하기
						system("cls");
						continue;
					}
					else if (temp == 1) {
						//메뉴로가기
						system("cls");
						break;
					}*/
				}

				gotoxy(0, 21);
				printf(" 딜러합 : %d\n", card_sum(dealerCard, dealer_index));
				printf(" 플레이어합 : %d\n", card_sum(playerCard, player_index));

				if (card_sum(dealerCard, dealer_index) == card_sum(playerCard, player_index)) { //비길시
					//*money += insertmoney; //배팅금액 
					gotoxy(0, 23);
					printf(" Push(동점)\n");
					system("pause");
					system("cls");
					return insertmoney;
				}
				else if (card_sum(playerCard, player_index) < card_sum(dealerCard, dealer_index)) { //딜러가 높을시
					gotoxy(0, 23);
					printf(" 딜러 승\n");
					system("pause");
					system("cls");
					return 0;
				}
				else {
					//*money += insertmoney * 2;
					gotoxy(0, 23);
					printf(" 플레이어 승\n");
					system("pause");
					system("cls");
					return insertmoney * 2;
				}
				/*
				_getch();

				temp = choiceBlackjack(2, blackFinMenuList); // 메뉴의선택값 반환
				if (temp == 0) {
					//계속하기
					system("cls");
					continue;
				}
				else if (temp == 1) {
					//메뉴로가기
					system("cls");
					break;
				}*/
			}

		/*}
		else if (temp == 1) {//도움말
			system("cls");
			printf("*******도움말*******\n");
			printf("***게임진행 방식***\n");
			printf("* 배팅금액을 정한후 게임이 시작됩니다.\n");
			printf("* 첫시작에 딜러와 플레이어가 각각 카드 2장씩을 받습니다.\n");
			printf("* 딜러는 자신의 카드 중 첫번째 한 장을 오픈합니다.\n");
			printf("* 플레이어는 자신의 카드가 21 넘지않는 범위 내에서 추가행동을 할수있습니다.\n");
			printf("* 플레이어의 턴이 종료되면 딜러의 카드 2장을 오픈 합니다.\n"); \
				printf("* 딜러의 카드합이 17을 넘을때까지 추가카드를 뽑아야합니다.\n"); \
				printf("* 딜러의 턴이 종료되면 21범위내에서 가장 가까운 사람이 승리하게 됩니다..\n");
			printf("\n***게임규칙***\n");
			printf("* Bust : 카드의합이 21이 넘게되면 패배하게됩니다.\n");
			printf("* BlackJack : 첫턴의 카드의 합이 21일때 배팅금의 3배를 받게됩니다.\n");
			printf("* Ace카드 : Aac카드는 1 또는 11로 계산됩니다.\n");
			printf("* J Q K 카드 : J Q K 카드는 10 으로 계산됩니다.\n");
			printf("\n***추가행동***\n");
			printf("* Stay : 카드를 더이상 받지않고 딜러의 턴으로 넘깁니다.\n* Hit : 카드한장을 더 받습니다.\n* Surrender : 자신의 패배를 인정하고 배팅금의 절반을 받습니다.\n* DoubleDown : 추가배팅을 하는대신 카드를 한장 더받고 딜러의 턴으론 넘깁니다."); \
				printf("(뒤로가려면 아무키 입력)\n");
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
void card_table(int* dealerCard, int dealer_index, int* playerCard, int player_index, int* money, int batMoney) { //딜러카드 배열 과 플레이어 카드배열 출력(현재 게임정보)


	printf("           보유자금 : %d  현재 배팅금액 :%d", *money, batMoney);
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

int card_sum(int* cardlist, int size) {//카드배열의 합을 구하는 함수, 합이 21보다 낮을시 A(1)은 10으로 계산, 높을시 1로 계산, J,Q,K는 10으로 계산

  //A(1)가 있을시 나온순서에 상관없이 카드배열의합이 21 이하면 11로 계산, 넘으면 1로계산
	


	int sum = 0; //카드배열의 합
	int temp = 0;
	int count_ace = 0; // ace 갯수를 세는 변수



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

void printPlayerCardArray(int* arr, int size) { //가지고 있는 카드배열을 출력하는 함수 , J, Q , K 도 표현하기
	int temp = 0;
	int suite = 0; //문양
	for (int i = 0; i < size; i++) {
		temp = (arr[i] % 13) + 1;
		suite = temp / 13;
		switch (suite)
		{
		case 1: //클로버
			if (temp == 1) {
				printf("♣A ");
			}
			else if (temp < 11) {
				printf("♣%d ", temp);
			}
			else if (temp == 11) {
				printf("♣J ");
			}
			else if (temp == 12) {
				printf("♣Q ");
			}
			else if (temp == 13) {
				printf("♣K ");
			}
			else
				printf("출력오류 ");
			break;
		case 2: //다이아 
			if (temp == 1) {
				printf("◆A ");
			}
			else if (temp < 11) {
				printf("◆%d ", temp);
			}
			else if (temp == 11) {
				printf("◆J ");
			}
			else if (temp == 12) {
				printf("◆Q ");
			}
			else if (temp == 13) {
				printf("◆K ");
			}
			else
				printf("출력오류 ");
			break;

		case 3: //하트
			if (temp == 1) {
				printf("♥A ");
			}
			else if (temp < 11) {
				printf("♥%d ", temp);
			}
			else if (temp == 11) {
				printf("♥J ");
			}
			else if (temp == 12) {
				printf("♥Q ");
			}
			else if (temp == 13) {
				printf("♥K ");
			}
			else
				printf("출력오류 ");
			break;
		default: //스페이스
			if (temp == 1) {
				printf("♣A ");
			}
			else if (temp < 11) {
				printf("♠%d ", temp);
			}
			else if (temp == 11) {
				printf("♠J ");
			}
			else if (temp == 12) {
				printf("♠Q ");
			}
			else if (temp == 13) {
				printf("♠K ");
			}
			else
				printf("출력오류 ");
			break;
		}

	}
	printf("\n");


}


void printDealerCardArray(int* arr, int size) { //딜러 카드배열 , 1장은 안보이게 출력

	int temp = 0;
	int suite = 0; //문양
	for (int i = 0; i < size; i++) {
		temp = (arr[i] % 13) + 1; //13으로 나눈값의 나머지
		suite = temp / 13; //13으로 나눈값


		if (i == 0 && hideFlag == 1) { //1번째카드는 보여주지않는다. (승패가 결정되면 무시)  
			printf("[?] ");
		}

		else

		{
			switch (suite)
			{
			case 1: //클로버
				if (temp == 1) {
					printf("♣A ");
				}
				else if (temp < 11) {
					printf("♣%d ", temp);
				}
				else if (temp == 11) {
					printf("♣J ");
				}
				else if (temp == 12) {
					printf("♣Q ");
				}
				else if (temp == 13) {
					printf("♣K ");
				}
				else
					printf("출력오류 ");
				break;
			case 2: //다이아 
				if (temp == 1) {
					printf("◆A ");
				}
				else if (temp < 11) {
					printf("◆%d ", temp);
				}
				else if (temp == 11) {
					printf("◆J ");
				}
				else if (temp == 12) {
					printf("◆Q ");
				}
				else if (temp == 13) {
					printf("◆K ");
				}
				else
					printf("출력오류 ");
				break;

			case 3: //하트
				if (temp == 1) {
					printf("♥A ");
				}
				else if (temp < 11) {
					printf("♥%d ", temp);
				}
				else if (temp == 11) {
					printf("♥J ");
				}
				else if (temp == 12) {
					printf("♥Q ");
				}
				else if (temp == 13) {
					printf("♥K ");
				}
				else
					printf("출력오류 ");
				break;
			default: //스페이스
				if (temp == 1) {
					printf("♣A ");
				}
				else if (temp < 11) {
					printf("♠%d ", temp);
				}
				else if (temp == 11) {
					printf("♠J ");
				}
				else if (temp == 12) {
					printf("♠Q ");
				}
				else if (temp == 13) {
					printf("♠K ");
				}
				else
					printf("출력오류 ");
				break;
			}
		}




	}
	printf("\n");


}

void blackjackDealerPrint(int* arr, int size) { // 포커 패 출력
	
	int temp = 0;
	int suite = 0; //문양
	printf("\n 딜러카드 : ");
	gotoxy(0, 0);
	for (int i = 0; i < size; i++)
	{
		temp = (arr[i] % 13) + 1; //13으로 나눈값의 나머지
		suite = arr[i] / 13; //13으로 나눈값

	   //PlaySound(TEXT("sound\\paper.wav"), NULL, SND_ASYNC);

		gotoxy(3 + i * 15, 2);
		printf("┏━━━━━━━┓"); // 카드 모양 출력

		for (int j = 2; j < 9; j++)
		{
			gotoxy(3 + i * 15, j+1);
			printf("┃       ┃ "); // 카드 모양 출력
		}

		gotoxy(3 + i * 15, 10);
		printf("┗━━━━━━━┛ "); // 카드 모양 출력
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
			switch (suite) // 카드 문양 출력
			{
			case 0:
				gotoxy(7 + i * 15, 6); printf("♣");
				break;
			case 1:
				gotoxy(7 + i * 15, 6); printf("♥");
				break;
			case 2:
				gotoxy(7 + i * 15, 6); printf("◆");
				break;
			case 3:
				gotoxy(7 + i * 15, 6); printf("♠");
				break;
			default:
				gotoxy(7 + i * 15, 6); printf("에러");
				break;
			}
			switch (temp) // 카드 숫자 출력
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

void blackjackPlayerPrint(int* arr, int size) { // 포커 패 출력
	gotoxy(0, 0);
	int temp = 0;
	int suite = 0; //문양
	printf("\n\n\n\n\n\n\n\n\n\n\n 플레이어카드 : ");
	for (int i = 0; i < size; i++)
	{
		temp = (arr[i] % 13) + 1; //13으로 나눈값의 나머지
		suite = arr[i] / 13; //13으로 나눈값

	   //PlaySound(TEXT("sound\\paper.wav"), NULL, SND_ASYNC);

		gotoxy(3 + i * 15, 1 + 11);
		printf("┏━━━━━━━┓"); // 카드 모양 출력

		for (int j = 2; j < 9; j++)
		{
			gotoxy(3 + i * 15, j + 11);
			printf("┃       ┃ "); // 카드 모양 출력
		}

		gotoxy(3 + i * 15, 20);
		printf("┗━━━━━━━┛ "); // 카드 모양 출력
		switch (suite) // 카드 문양 출력
		{
		case 0:
			gotoxy(7 + i * 15, 16);
			printf("♣");
			break;
		case 1:
			gotoxy(7 + i * 15, 16);
			printf("♥");
			break;
		case 2:
			gotoxy(7 + i * 15, 16);
			printf("◆");
			break;
		case 3:
			gotoxy(7 + i * 15, 16);
			printf("♠");
			break;
		default:
			gotoxy(7 + i * 15, 16);
			printf("에러");
			break;
		}
		switch (temp) // 카드 숫자 출력
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

void makingCard(int* card_deck) { //카드덱을 만드는 함수
	for (int i = 0; i < 52; i++) {
		card_deck[i] = playingCard[i];
	}


}


void swap(int* arr, int i, int j) //셔플할떄 쓰이는 함수
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

		rn = rand() % (n - i - 1) + i + 1; //난수의 범위 :  i + 1 ~  arr[n-1]

		swap(arr, i, rn);
	}

}



void get_playingCard(int* deck, int* cardArray, int index) { //게임 끝나면 베열을 비우고 카운터값을 초기화 시켜야함.

	static int count = 0;
	if (count >= DECK) {
		count = 0;  //-1로 초기화
		shuffle(deck, DECK);  //카드셔플
	}
	else {
		cardArray[index] = deck[count];

		count++;
		int temp = count;
		//printf("남은카드 수 : %d", DECK - (temp+1));
	}
	//게임도중 카드가부족할시 쓰인카드를 다가져와 셔플해야한다.
}
/*
void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos); //프로토타입의 값대로 위치이동
}
*/