#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>


extern void gotoxy(int x, int y);
void draw_check02(int c, int r);
void reel_series(int r[][3]);
void display_reel(char rc[][3], int r[][3]);
void game_control(char reel[][3], int reel_num[][3], int money);
int return_money(int r[][3], int betting);



int thank;
int slot(money)
{

    char reel[6][3] = { "★", "♠", "◆", "♥", "♣", "○" };
    int i, reel_num[3][3];


    // printf("\t슬롯머신 게임\n\n");
    PlaySound(TEXT("sound\\shot.wav"), NULL, SND_ASYNC);
    gotoxy(7, 3);

    printf("┌──슬롯머신─┐");

    gotoxy(7, 4);

    draw_check02(6, 3); //바둑판생성

    for (i = 0; i < 3; i++)
        reel_num[0][i] = rand() % 5; //난수생성
    //gotoxy(3, 20);
    reel_series(reel_num);      //기호순서 reel_num에다 순서를정함
    game_control(reel, reel_num, money);
    gotoxy(2, 16);
    system("pause");
    return thank;
}


/*

확장된 바둑판 그리기 함수 draw_check02

*/

void draw_check02(int c, int r)
{
    gotoxy(7, 4); printf("├───┬───┬───┤");
    gotoxy(7, 5); printf("│   │   │   │");
    gotoxy(7, 6); printf("│   │   │   │");
    gotoxy(7, 7); printf("│   │   │   │");
    gotoxy(7, 8); printf("│   │   │   │");
    gotoxy(7, 9); printf("│   │   │   │");
    gotoxy(7, 10); printf("├───┴───┴───┤");
    gotoxy(7, 11); printf("│           │");
    gotoxy(7, 12); printf("└───────────┘");
}

/*

화면에 표시된 지시어들을 지우는 함수 clear_text

*/


/*

화면에 표시된 사례 지우기 함수 clear case

*/




/*

각 릴에 대한 기호의 순서를 결정하는 함수 reel_series

*/

void reel_series(int r[][3])

{

    int i, j;

    for (i = 0; i < 3; i++)

        for (j = 0; j < 3; j++)

            r[j][i] = (r[0][i] + j) % 6; //세개의 릴에 대한 기호 순서

}



/*

회전 순서에 따라 릴을 화면에 출력하는 함수 display_reel

*/

void display_reel(char rc[][3], int r[][3])

{

    int i, j;

    for (i = 0; i < 3; i++)

        for (j = 0; j < 3; j++)

        {

            gotoxy(9 + j * 4, 5 + i * 2);

            printf("%s", rc[r[i][j]]);

        }

}



/*

슬롯 머신 게임을 제어하는 함수 game_control

*/

void game_control(char reel[][3], int reel_num[][3], int money)

{

    int i, j, num[3];

    double pst;

    int random[3]; //임의의 릴을 먼저 멈추게 하도록 난수 발생

    clock_t start, end;



    display_reel(reel, reel_num);

    //bet = game_progress(money);



    //겹치지 않도록

    random[0] = rand() % 3;

    do

    {

        random[1] = rand() % 3;

    } while (random[1] == random[0]);

    do

    {

        random[2] = rand() % 3;

    } while (random[2] == random[1] || random[2] == random[0]);



    for (i = 0; i < 3; i++)

    {

        /*

        gotoxy(1, 24);

        for (j = 0; j < 3; j++)

                printf("%d ", random[j]);

                */

        start = clock();

        do

        {
            Sleep(50);
            for (j = i; j < 3; j++) //릴을 돌리는 함수

                reel_num[0][random[j]] = reel_num[1][random[j]];

            reel_series(reel_num);

            display_reel(reel, reel_num);

            end = clock();

            pst = (double)(end - start) / CLK_TCK;

        } while (pst < 1); //1초안에

        num[i] = reel_num[1][i]; //가운데만 보기때문에

    }

    //num[i] = reel_num[0][i];
    gotoxy(7, 13);
    thank = return_money(reel_num, money);
    gotoxy(7, 14);
    printf(" 상금: %d", thank);
}



/*

당첨 사례 따라 배팅 금액과 사례금을 계산하는 함수 return_money

*/

int return_money(int r[][3], int money)

{
    if (r[1][0] == r[1][1] && r[1][1] == r[1][2] && r[1][0] == r[1][2]) //문양이 세개 동일할경우(★, ♠, ◆)
    {
        printf(" 돈을 얻었다!!");
        PlaySound(TEXT("sound\\win.wav"), NULL, SND_ASYNC);
        return money * 2;
    }
    printf(" 돈을 잃었다..");
    PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
    return 0;

}
