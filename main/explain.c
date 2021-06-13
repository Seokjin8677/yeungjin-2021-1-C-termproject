#include "modm.h"


void story_explain() {
	textcolor(12);
	printf("\n\n\t* 배경설명\n\n");
	textcolor(15);
	printf("\t* 당신은 무리한 투자로 인해 빚을 가득 안은 빚쟁이 입니다...\n\n");
	printf("\t* 당신에게 유일하게 남은 것은 1000원짜리 지폐와 1000만원 빚 뿐 입니다...\n\n");
	printf("\t* 과연 당신은 빚을 모두 갚아 빚쟁이 인생을 벗어날 수 있을까요?\n\n");
	printf("\t* 행운을 빕니다.\n\n\n");
}
void poker_explain() {
	textcolor(12);
	printf("\n\n\t* 싱글 플레이\n\n");
	textcolor(15);
	printf("\t* 방향키로 원하는 카드를 가르킨 후 스페이스 바를 눌러 바꿀 카드를 선택합니다.\n\n");
	printf("\t* 엔터를 누르면 선택한 카드를 바꿉니다.\n\n");
	printf("\tHigh Card: 0배\t\tOne Pair: 0.5배\n");
	printf("\tTwo Pair: 3배\t\tThree of A Kind: 5배\n");
	printf("\tStraight: 10배\t\tFlush: 15배\n");
	printf("\tFull House: 30배\tFour of A Kind: 50배\n");
	printf("\tStraight Flush: 100배\tRoyal Straigh Flush: 500배\n");
	textcolor(12);
	printf("\n\n\t* 멀티 플레이\n\n");
	textcolor(15);
	printf("\t* 방장이 먼저 카드를 드로우 한 후 참가자가 카드를 드로우 합니다.\n\n");
	printf("\t* 카드의 족보가 높은 사람이 돈을 가져갑니다.\n\n");
	printf("\t* 같은 족보가 나오면 비깁니다.\n\n\n");
}
void blackjack_explain() {
	textcolor(12);
	printf("\n\n\t* 게임진행 방식\n\n");
	textcolor(15);
	printf("\t* 배팅금액을 정한후 게임이 시작됩니다.\n");
	printf("\t* 첫시작에 딜러와 플레이어가 각각 카드 2장씩을 받습니다.\n");
	printf("\t* 딜러는 자신의 카드 중 첫번째 한 장을 오픈합니다.\n");
	printf("\t* 플레이어는 자신의 카드가 21 넘지않는 범위 내에서 추가행동을 할수있습니다.\n");
	printf("\t* 플레이어의 턴이 종료되면 딜러의 카드 2장을 오픈 합니다.\n");
	printf("\t* 딜러의 카드합이 17을 넘을때까지 추가카드를 뽑아야합니다.\n");
	printf("\t* 딜러의 턴이 종료되면 21범위내에서 가장 가까운 사람이 승리하게 됩니다..\n");
	textcolor(12);
	printf("\n\n\t* 게임규칙\n\n");
	textcolor(15);
	printf("\t* Bust : 카드의합이 21이 넘게되면 패배하게됩니다.\n");
	printf("\t* BlackJack : 첫턴의 카드의 합이 21일때 배팅금의 3배를 받게됩니다.\n");
	printf("\t* Ace카드 : Aac카드는 1 또는 11로 계산됩니다.\n");
	printf("\t* J Q K 카드 : J Q K 카드는 10 으로 계산됩니다.\n");
	textcolor(12);
	printf("\n\n\t* 추가행동\n\n");
	textcolor(15);
	printf("\t* Stay : 카드를 더이상 받지않고 딜러의 턴으로 넘깁니다.\n\t* Hit : 카드한장을 더 받습니다.\n\t* Surrender : 자신의 패배를 인정하고 배팅금의 절반을 받습니다.\n\t* DoubleDown : 추가배팅을 하는대신 카드를 한장 더받고 딜러의 턴으론 넘깁니다.\n\n\n");
}
void slot_explain() {
	textcolor(12);
	printf("\n\n\t* 게임진행 방식\n\n");
	textcolor(15);
	printf("\t* 배팅금액을 정한후 게임이 시작됩니다.\n\n");
	printf("\t* 문양이 세개 동일할 경우 배팅금액의 10배를 얻습니다.\n\n");
	printf("\t* 문양이 두개 동일할 경우 배팅금액의 3배를 얻습니다\n\n");
	printf("\t* 문양이 맞지 않다면 판돈을 잃게 됩니다\n\n\n");
}
void roulette_explain() {
	printf("\n\n\t* 세가지 룰 중 하나를 선택합니다.\n\n");
	printf("\t* 숫자 하나는 원하는 숫자를 선택한 뒤 맞으면 35배의 돈을 얻습니다.\n\n");
	printf("\t* 홀짝은 홀짝을 선택한 뒤 맞으면 2배의 돈을 얻습니다.\n\n");
	printf("\t* 1~18/19~36은 원하는 범위를 선택한 뒤 맞으면 2배의 돈을 얻습니다.\n\n");
	printf("\t* 0의 경우 홀수, 짝수도 아니고 범위에 속하지 않으므로 꽝 입니다.\n\n\n");
}
void horse_explain() {
	printf("\n\n\t* 배팅금액을 정한후 게임이 시작됩니다.\n\n");
	printf("\t* 게임 시작전 우승 할 말의 번호를 선택합니다.\n\n");
	printf("\t* 선택한 말이 우승하게 된다면 배팅금액의 5배를 지급 받습니다.\n\n");
	printf("\t* 우승하지 못한다면 판돈을 잃게 됩니다.\n\n\n");
}
void shop_explain() {
	printf("\n\n\t* 구걸 스킬과 복권을 살 수 있습니다.\n\n");
	printf("\t* 구걸 스킬을 올리면 레벨 1당 1000원을 더 얻을 수 있습니다.\n\n");
	printf("\t* 로또는 현실의 복권과 유사합니다.\n\n");
	printf("\t* 3개를 맞을 시 5등, 4개를 맞을 시 4등, 5개를 맞으면 3등\n\n");
	printf("\t* 5개를 맞고 보너스 번호를 맞추면 2등, 6개를 전부 맞으면 1등 입니다.\n\n");
	printf("\n\t5등: 5,000원\t4등: 50,000원\t3등: 1,000,000원\n");
	printf("\t2등: 50,000,000원\t1등: 1,000,000,000원\n\n\n");
}