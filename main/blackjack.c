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


int playerCard[8] = { 0 }; //player가 게임중 가질수있는 카드의 배열
int dealerCard[8] = { 0 }; ////dealer가 게임중 가질수있는 카드의 배열
 
/*
struct pokerStruct // 구조체로 바꾸면 코드량이 줄것같음
{
	int rank[5];
	int suit[5];
	int sum;
};
*/

int blackjack(int money) {
		
	//Card_deck 52장

	int card_deck[52]; //카드를 담을 배열
	
	makingCard(card_deck); //없어도 되긴함
	
	//printArray(card_deck, DECK); //카드배열 출력

	shuffle(card_deck, DECK);  //카드셔플

	int player_index = 0;//플레이어 카드배열 인덱스값
	int dealer_index = 0;////딜러 카드배열 인덱스값

	int game_money = money;  //보유머니
	int bating_money; //배팅머니


	while (1) {
		
		player_index = 0; //게임시작시 딜러와 플레이어 카드배열 인덱스 초기화.
		dealer_index = 0;
		bating_money = 0; //배팅머니 초기화
		
		while (1)
		{

			printf("1.게임시작\n"); 
			printf("2.도움말\n");
			printf("3.뒤로가기\n");
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
				printf("(대충 블랙잭 설명하는 내용)\n");
				printf("(뒤로가러면 아무키 입력)\n");
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
		

		printf("배팅금액을 정해주세요(최소 1000원) / 잔고 : %d\n",game_money); //배팅머니 입력받기
		
		scanf_s("%d", &bating_money);

		if (bating_money < 1000) { //배팅머니은 최소 1000원
			continue;
		}
		else{
			game_money -= bating_money; //게임머니에서 배팅머니를 빼준다.

		}
		system("cls");

		//Start

		/*
		if (count > 46) { //카드를 전부사용했을시
			count = -1;
			shuffle(card_deck, DECK);
		}
		*/

		//Start
		printf("카드를 두장씩 가집니다(아무키나 입력).\n"); 
		_getch();
		system("cls");
		for (int i = 0; i < 2; i++) {
			 //딜러와 플레이어 모두 카드2장씩을 받는다.
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
		*인덱스 , 카운트 확인용
		printf("딜러 인덱스 값 :%d 카운트값 :%d\n", dealer_index, count);
		printf("플레이어 인덱스 값 :%d 카운트값 :%d\n", player_index, count);
		_getch();
		*/
	


		//2장뽑았을때 21이 나오면 blackjack(배팅머니 2배)
		if (card_sum(dealerCard, dealer_index)==21) { //딜러가 21일때
			card_table(dealerCard, dealer_index, playerCard, player_index, game_money, bating_money);
			printf("\nblack Jack\n");
			_getch();
			system("cls");
			continue;
		
		}
		else if(card_sum(playerCard, player_index)==21){ //플레이어 21일때
			game_money += bating_money * 3; //배팅금의 3배
			card_table(dealerCard, dealer_index, playerCard, player_index, game_money, bating_money);
			printf("\nblack Jack\n");
			_getch();
			system("cls");
			continue;
		}

		int flag = 0; //bust 또는 surrender 확인 flag 


		//Stay(Stand) or Hit

		while (1) { //플레이어가 stay or -1 잘못입력했을때 반복문 종료. -1 이 나오면 Stay.
			card_table(dealerCard, dealer_index, playerCard, player_index, game_money, bating_money); //현재 게임정보


			int temp = 0; //선택값을 담기위한 tmep 변수
			temp = choice(); //Stay or Hit 선택
			
			
			system("cls");

			if (temp == 1||temp==-1) {//1또는 잘못입력시 
				
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
				flag = 2;//21이 넘으면 Bust 체크를 위해 flag 변수에 1대입
				break;

			}
			else{   //Hit 선택시 21 이 넘으면 Bust
				
				get_playingCard(card_deck, playerCard,player_index); //Hit시 카드한장을 더 배열에 추기한다.
				player_index += 1;  //카드지급 후 다음 카드를 받기위해 인덱스를 1증가 시킨다.

				
				card_table(dealerCard, dealer_index, playerCard, player_index, game_money, bating_money);
				printf("Hit\n");
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

		
		
		
		card_table(dealerCard, dealer_index, playerCard, player_index, game_money, bating_money);
		_getch();
		system("cls");

		if (flag == 1) { //Bust 확인
			printf("Bust (player)\n");
			_getch();
			system("cls");
			continue;
		}
		else if (flag == 2) {//Surrender 확인
			printf("Surrender\n");
			_getch();
			system("cls");
			game_money += bating_money * 0.5; //배팅금의 0.5배만 차감
			continue;
		}

		//Stay 시에
		//
		while (card_sum(dealerCard, dealer_index)<17) {//딜러는 카드의 합이 17이상이 될때까지 카드를 뽑는다. 21이 넘으면 Bust
			

			get_playingCard(card_deck, dealerCard, dealer_index);
			dealer_index += 1;
			card_table(dealerCard, dealer_index, playerCard, player_index, game_money, bating_money);
			_getch();
			system("cls");

			if (card_sum(dealerCard, dealer_index) > 21) { //21이 넘으면 Bust
				flag = 1;//21이 넘으면 Bust 체크를 위해 flag 변수에 1대입
				break;
			}
			
		}

		card_table(dealerCard, dealer_index, playerCard, player_index, game_money, bating_money);
		_getch();
	

		if (flag == 1) { //Bust 확인
			printf("Bust (Dealer)\n");
			game_money += bating_money * 2; //player 승리로 배팅금액 2배 휙득
			_getch();
			system("cls");
			continue;
		}

		printf("딜러합 : %d\n", card_sum(dealerCard, dealer_index));
		printf("플레이어합 : %d\n", card_sum(playerCard, player_index));

		if (card_sum(dealerCard, dealer_index) == card_sum(playerCard, player_index)){ //비길시
			game_money += bating_money; //배팅금액 
			printf("Push(동점)\n");
		}else if (card_sum(playerCard, player_index) < card_sum(dealerCard, dealer_index)) { //딜러가 높을시
			printf("딜러 승\n");
		}
		else {
			game_money += bating_money*2;
			printf("플레이어 승\n");
		}


		

		_getch();
		system("cls");


	}

	return 0;

}
void card_table(int *dealerCard, int dealer_index, int *playerCard, int player_index,int money, int batMoney) { //딜러카드 배열 과 플레이어 카드배열 출력(현재 게임정보)

	printf("딜러카드 : ");
	printDealerCardArray(dealerCard, dealer_index);
	printf("\n");
	printf("플레이어카드 : ");
	printPlayerCardArray(playerCard, player_index);
	printf("\n");
	printf("보유자금 : %d  현재 배팅금액 :%d",money,batMoney);
	printf("\n");

}
int choice( ) { //배팅후 다음행동을 정한다. 

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
		return -1; //오류방어

	}

}

int card_sum(int* cardlist, int size) {//카드배열의 합을 구하는 함수, 합이 21보다 낮을시 A(1)은 10으로 계산, 높을시 1로 계산, J,Q,K는 10으로 계산

  //A(1)가 있을시 나온순서에 상관없이 카드배열의합이 21 이하면 11로 계산, 넘으면 1로계산
	// * A(1) 두번나오거나 뒤쪽에 나오면 계산하는데 오류가있음


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

void printPlayerCardArray(int *arr, int size) { //가지고 있는 카드배열을 출력하는 함수 , J, Q , K 도 표현하기
	int temp = 0;
	int suite = 0; //문양
	for (int i = 0; i < size; i++) {
		temp = (arr[i]%13) + 1;
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
			else if(temp ==13){
				printf("♣K ");
			}
			else
				printf("출력오류 ");
			break;
		case 2 : //다이아 
			if (temp == 1) {
				printf("◆A ");
			}
			else if (temp  < 11) {
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
			else if (temp  < 11) {
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
			if (temp  ==1) {
				printf("♣A ");
			}
			else if (temp  < 11) {
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

void printDealerCardArray(int *arr, int size) { //딜러 카드배열 , 1장은 안보이게 출력
	
	int temp = 0;
	int suite = 0; //문양
	for (int i = 0; i < size; i++) {
		temp = (arr[i] % 13) + 1; //13으로 나눈값의 나머지
		suite = temp / 13; //13으로 나눈값
		
		/*
		if (i == 0) { //1번째카드는 보여주지않는다. (승패가 결정되면 무시)  
			printf("[?] ");
		}

		else
		*/
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

void makingCard(int card_deck[]) { //카드덱을 만드는 함수
	for (int i = 0; i <52; i++) {
		card_deck[i] = playingCard[i];
	}


}


void swap(int arr[], int i, int j) //셔플할떄 쓰이는 함수
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

		rn = rand() % (n - i - 1) + i + 1; //난수의 범위 :  i + 1 ~  arr[n-1]

		swap(arr, i, rn);
	}

}



void get_playingCard(int *deck,int *cardArray,int index) { //게임 끝나면 베열을 비우고 카운터값을 초기화 시켜야함.
	
	static int count = -1;
	if (count > DECK)
		count= -1;  //반환할 카드가 없으면 오류방어를 위해 -1을 반환한다.

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