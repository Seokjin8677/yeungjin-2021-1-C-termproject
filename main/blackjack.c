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

int playingCard_number[] = { 1,2,3,4,5,6,7,8,9,10,JACK,QUEEN,KING }; //카드의 숫자 배열 J Q K 는 각각 11 , 12, 13, 으로 나타냄
int playingCard_suite[] = { SPADE , DIA , HEART , CLOVER };
int used_playingCard[52]; //사용된 카드를 담는 배열
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
	
	makingCard(card_deck);
	
	//printArray(card_deck, DECK); //카드배열 출력

	shuffle(card_deck, DECK);

	printArray(card_deck, DECK); //셔플된 카드덱 출력(확인용, 주석처리가능)
	printf("\n");//
	

	//카드지급 테스트

	int player_index = 0; //get함수에서 같이 처리할지 생각
	int dealer_index = 0;


	int game_money = money; //매개변수로 입력받는 금액
	int bating_money; 
	/*
	게임머니 / 배팅머니 / 
	
	*/

	while (1) {
		
		
		player_index = 0; //게임시작시 딜러와 플레이어 카드배열 인덱스 초기화.
		dealer_index = 0;
		bating_money = 0; 

		printf("배팅금액을 정해주세요(최소 1000원) / 잔고 : %d\n",game_money); //배팅머니 입력받기
		scanf_s("%d", &bating_money);

		if (bating_money < 1000) { //배팅머니은 최소 1000원
			continue;
		}
		else{
			game_money -= bating_money; //게임머니에서 배팅머니를 빼준다.

		}
		system("cls");

		//첫시작
		if (count > 46) { //카드를 전부사용했을시
			count = -1;
			shuffle(card_deck, DECK);
		}

		printf("카드를 두장씩 가집니다(아무키나 입력).\n"); //*한장씩나오게 바꾸기.
		
		while (dealer_index < 2 && player_index<2) { //딜러와 플레이어 모두 카드2장씩을 받는다.

			_getch();
			system("cls");

			dealerCard[dealer_index] = get_playingCard(card_deck);
			dealer_index++;
			printf("딜러카드 : ");
			printArray(dealerCard, dealer_index);
			printf("\n");
			/*
			if (dealer_index == 1) { //*딜러의 첫장은 보여주지않는다.
				printf("[?]\n");
			}
			*/

			printf("플레이어카드 : ");
			
		
			playerCard[player_index] = get_playingCard(card_deck);
			player_index++;  //카드지급 후 다음 카드를 받기위해 인덱스를 1증가 시킨다.	

			printArray(playerCard, player_index);
			
		}

		card_table(dealerCard, dealer_index, playerCard, player_index);

		//2장뽑았을때 21이 나오면 blackjack(배팅머니 2배)
		if (card_dsum(dealerCard, dealer_index)==21) { //딜러가 21일때
		
			printf("black Jack\n");
			continue;
		
		}
		else if(card_dsum(playerCard, player_index)==21){ //플레이어 21일때
			game_money += bating_money * 3; //
			printf("black Jack\n");
			continue;
		}

		int flag = 0;

		//Stay or Hit
		while (1) { //플레이어가 stay or -1 잘못입력했을때 반복문 종료. -1 이 나오면 Stay.
			
			int temp = 0; //선택값을 담기위한 tmep 변수
			temp = choice(); //Stay or Hit 선택

			printf("\n");
			if (temp == 1||temp==-1) {
				printf("Stay\n");
				break;

			}
			else{   //Hit 선택시 21 이 넘으면 Bust
				printf("Hit\n");
				playerCard[player_index] = get_playingCard(card_deck);
				player_index++;  //카드지급 후 다음 카드를 받기위해 인덱스를 1증가 시킨다.	
				card_table(dealerCard, dealer_index, playerCard, player_index);

				if (card_dsum(playerCard, player_index) > 21) { //21이 넘으면 Bust
					flag = 1;//21이 넘으면 Bust 체크를 위해 flag 변수에 1대입
					break;
				}
				else if (card_dsum(playerCard, player_index) == 21) { //21이 되었을경우 Stay
					break;
				}

			}
		}

		card_dsum(playerCard, player_index);
		_getch();

		card_table(dealerCard, dealer_index, playerCard, player_index);
		
		

		if (flag == 1) { //Bust 확인
			printf("Bust (player)\n");
			continue;
		}

		//Stay 시에
		

		/*
		* system("cls");
		printf("딜러카드 : ");
		printArray(dealerCard, dealer_index);
		printf("\n");
		printf("플레이어카드 : ");
		printArray(playerCard, player_index);
		_getch();
		*/
		
		//
		while (card_dsum(dealerCard, dealer_index)<17) {//딜러는 카드의 합이 17이상이 될때까지 카드를 뽑는다. 21이 넘으면 Bust
			

			dealerCard[dealer_index] = get_playingCard(card_deck);
			dealer_index++;
			card_table(dealerCard, dealer_index, playerCard, player_index);
			
			if (card_dsum(dealerCard, dealer_index) > 21) { //21이 넘으면 Bust
				game_money += bating_money * 2; //player 승리로 배팅금액 2배 휙득
				flag = 1;//21이 넘으면 Bust 체크를 위해 flag 변수에 1대입
				break;
			}
			
		}
		
		if (flag == 1) { //Bust 확인
			printf("Bust (Dealer)\n");
			continue;
		}

		card_table(dealerCard, dealer_index, playerCard, player_index);


		printf("딜러합 : %d\n", card_dsum(dealerCard, dealer_index));
		printf("플레이어합 : %d\n", card_dsum(playerCard, player_index));

		
		if (card_dsum(dealerCard, dealer_index) == card_dsum(playerCard, player_index)){ //비길시
			game_money += bating_money; //배팅금액 
			printf("Push(동점)\n");


		}else if (card_dsum(playerCard, player_index) < card_dsum(dealerCard, dealer_index)) { //딜러가 높을시
			
			printf("딜러 승\n");
			
		}
		else {
			game_money += bating_money*2;
			printf("플레이어 승\n");
		
		}


		printf("\n남은카드 갯수 :%d\n", DECK - (count + 1));

		_getch();
		


	}

	return 0;

}
void card_table(int dealerCard[], int dealer_index, int playerCard[], int player_index) { //딜러카드 배열 과 플레이어 카드배열 출력

	system("cls");
	printf("딜러카드 : ");
	printArray(dealerCard, dealer_index);
	printf("\n");
	printf("플레이어카드 : ");
	printArray(playerCard, player_index);
	_getch();

}
int choice( ) { //배팅후 카드2장씩을 받으면 다음행동을 정한다.

	int temp;
	printf("1.Stay 2.Hit\n");
	scanf_s("%d", &temp);

	if (!(temp == 1 || temp == 2)) {
		return -1; //오류방어

	}
	else if (temp == 1) {
		return 1;
	}
	else
		return 2;

}

int card_dsum(int* cardlist, int size) {//카드배열의 합을 구하는 함수, 합이 21보다 낮을시 A(1)은 10으로 계산, 높을시 1로 계산, J,Q,K는 10으로 계산

  //A(1)가 있을시 나온순서에 상관없이 카드배열의합이 21 이하면 11로 계산, 넘으면 1로계산
	// * A(1) 두번나오거나 뒤쪽에 나오면 계산하는데 오류가있음


	int sum = 0; //카드배열의 합
	int arr_sum[8] = { 0 }; // A(1) 을 10 또는 1로 바꾸기 위해 만듬

	int temp = 0;
	int count_ace = 0; // ace 갯수를 세는 변수

	for (int i = 0; i < size; i++) {
		temp = cardlist[i]; //index  i번째 값을 temp에 담는다.

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
int change_jqk(int value) { //배열의 카드가  J Q K 인지 확인하고 10으로 바꿔주는 함수
	return value < 11 ? value : 10;

}
int change_ace(int* arr_sum, int sum, int size) { //배열의합이 21을 초과할때 A(1)을 1로 게산하는 함수
	//카드 배열의 값을 내림차순 후 더한다.

	
	for (int i = 0; i < size; i++) {
		if (arr_sum[i] == 1) {
			sum -= 10;
		}
	}	
	return sum;
}




void printArray(int arr[], int size) { //가지고 있는 카드배열을 출력하는 함수 , J, Q , K 도 표현하기
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



int get_playingCard(int arr[]) { //게임 끝나면 베열을 비우고 카운터값을 초기화 시켜야함.
	


	if (count > DECK)
		return -1;  //반환할 카드가 없으면 오류방어를 위해 -1을 반환한다.

	else {
		count++;
		return arr[count]; //현재 인덱스의 카드를 반환
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