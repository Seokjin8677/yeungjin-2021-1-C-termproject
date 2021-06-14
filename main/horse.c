#include "modm.h"

extern void gotoxy(int, int);
extern void background();
void printhorsefield();
int horse(int insertmoney)
{
    int horse_num = 5, rank[5] = { 0 }, i; //경주 참여 말 수 5, 순위저장
    int horse[5] = { 0 }, race, number = 0, r = 0; 
    int chose_horse; //사용자가 선택할 말
    char select_horse[2];


    /*printf("경주마게임\n\n");
   
    printf("\n\n");*/
    

    //경주마 경기장 화면 설계
    printf("\n");
    do {
        printhorsefield();
        //printf("아무키나 누르면 경주를 시작합니다.");
        gotoxy(55, 38);
        printf("배팅할 말의 번호를 입력하시오(1~5): ");
        fflush(stdin);
        scanf_s("%s", &select_horse,2);
        PlaySound(TEXT("sound\\button.wav"), NULL, SND_ASYNC);
        switch (select_horse[0])
		{
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
			break;
        default:
            gotoxy(63, 39);
            printf("1~5 까지만 입력해주세요!\n");
            fflush(stdin);
            system("pause");
            system("cls");
            break;
		}
        
        
    } while (select_horse[0] <'1' || select_horse[0]>'5');
    chose_horse = select_horse[0] - 48;
    printhorsefield();
    PlaySound(TEXT("sound\\shot.wav"), NULL, SND_ASYNC);
    /*gotoxy(0, 16); printf("                                                       ");
    gotoxy(0, 16);
    //system("pause");
    fflush(stdin);
    gotoxy(0, 16); printf("                                        ");*/
    while (horse_num != r) //등수가 말수와 같아지면 경기종료
    {
        number = rand() % horse_num; // 랜덤하게 움직일 말 선택

        if (rank[number] != 0) //선택한 말의 등수가 0이 아니면 while 문으로
            continue;

        race = rand() % 4 + 1; 

        if (race % 4 == 0)
            if (horse[number] < 1)  race = rand() %  + 1;
            else    race = 0;
        else
            race = rand() % 4 + 1;


        horse[number] += race; 
        Sleep(50);

        if (horse[number] >= 70) //결승점 도착하면 등수표시
        {
            horse[number] = 70;
            if (!rank[number]) 
            {
                r++; //등수를 위한 변수

                rank[number] = r; //결승점에 도착한 해당 말의 등수을 저장

                //도착지점표시 및 등수 표기
                gotoxy(10, 13 + number * 2);
                for (i = 0; i < horse[number]; i++) {
                    printf(" ");
                }
                if (horse[number]) printf("->");
                printf("\t  %d", r);
            }
        }

        else //결승점을 도착하기 이전이면
        {
            gotoxy(10, 13 + number * 2);
            for (i = 0; i < horse[number]; i++) {
                printf(" ");
            }
            if (horse[number] && race >= 0)
                printf("->");
            else if (race < 0) {
                for (i = 80; i >= 0; i--)
                    printf(" ");
                gotoxy(10 + horse[number], 5 + number * 2);
            }
        }
    }
    gotoxy(65, 39);
    printf("게임종료!"); //경기 종료를 표시한다.
    
    if (rank[chose_horse-1] == 1) {
        gotoxy(55, 37);
        printf("당신의 경주마가 우승했습니다!");
        gotoxy(65, 38);
        printf("%d원을 벌었다!", insertmoney * 5);
        PlaySound(TEXT("sound\\win.wav"), NULL, SND_ASYNC);
        return insertmoney * 5;
    } 
    else {
        gotoxy(55, 37);
        printf("당신의 경주마가 우승하지 못했습니다...");
        gotoxy(65, 38);
        printf("돈을 잃었다...");
        PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
        return 0;
    }
}
void printhorsefield() {
    system("cls");
    background();

    gotoxy(7, 9); 
    printf("영진 경마장");

    gotoxy(7, 26);
    printf("START                                                                    END      등수");
    
    gotoxy(7, 10);
    printf("======================================================================================");
    

    gotoxy(7, 25);
    printf("======================================================================================");
}