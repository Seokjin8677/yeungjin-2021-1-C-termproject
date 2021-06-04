#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#include <conio.h>

#include <Windows.h>




void draw_check02(int c, int r);

void reel_series(int r[][3]);

void gotoxys(int x, int y);

void display_reel(char rc[][3], int r[][3]);

void clear_text(void);

void game_control(char reel[][3], int reel_num[][3], int money);

int return_money(int r[], int betting);

void clear_case(void);


int thank;
int slot(money)
{

    char reel[6][3] = { "★", "♠", "◆", "♥", "♣", "○" };
    int i, reel_num[3][3];
    srand((unsigned)time(NULL));

    printf("\t슬롯머신 게임\n\n");

    gotoxys(1, 5);

    printf("┌──슬롯머신─┐");

    gotoxys(1, 6);

    draw_check02(6, 3); //바둑판생성

    for (i = 0; i < 3; i++)
        reel_num[0][i] = rand() % 5; //난수생성

    reel_series(reel_num);      //기호순서 reel_num에다 순서를정함
    game_control(reel, reel_num, money);
    gotoxy(3, 20);
    return thank;
}



void gotoxys(int x, int y)

{

    COORD Pos = { x - 1, y - 1 };

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

}



/*

확장된 바둑판 그리기 함수 draw_check02

*/

void draw_check02(int c, int r)

{

    int i, j;

    unsigned char a = 0xa6;

    unsigned char b[12];

    for (i = 1; i < 12; i++)
        b[i] = 0xa0 + i;

    printf("%c%c", a, b[2]);

    for (i = 0; i < c - 1; i++)

    {

        printf("%c%c", a, b[1]);

        printf("%c%c", a, b[8]);

    }

    printf("%c%c", a, b[1]);

    printf("%c%c", a, b[2]);

    printf("\n");

    for (i = 0; i < r - 1; i++)

    {

        printf("%c%c", a, b[2]);;

        for (j = 0; j < c; j++)

        {

            printf("  ");

            printf("%c%c", a, b[2]);

        }

        printf("\n");

        printf("%c%c", a, b[7]);

        for (j = 0; j < c - 1; j++)

        {

            printf("%c%c", a, b[1]);

            printf("%c%c", a, b[11]);

        }

        printf("%c%c", a, b[1]);

        printf("%c%c", a, b[9]);
        printf("<----------------");
        printf("\n");

    }

    printf("%c%c", a, b[2]);

    for (j = 0; j < c; j++)

    {

        printf("  ");

        printf("%c%c", a, b[2]);

    }

    printf("\n");

    printf("%c%c", a, b[6]);

    for (i = 0; i < c - 1; i++)

    {

        printf("%c%c", a, b[1]);

        printf("%c%c", a, b[10]);

    }

    printf("%c%c", a, b[1]);

    printf("%c%c", a, b[5]);

    printf("\n");

}

/*

화면에 표시된 지시어들을 지우는 함수 clear_text

*/

void clear_text(void)

{

    int i, j;

    for (i = 17; i < 20; i++)

    {

        gotoxys(1, i);

        for (j = 0; j < 42; j++)

            printf(" ");

    }

}



/*

화면에 표시된 사례 지우기 함수 clear case

*/

void clear_case(void)

{

    gotoxys(43, 18);

    printf("                                             ");

}



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

            gotoxys(3 + j * 4, 7 + i * 2);

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

    thank = return_money(num, money);
    printf("\t 상금: %d", thank);

}



/*

당첨 사례 따라 배팅 금액과 사례금을 계산하는 함수 return_money

*/

int return_money(int r[], int money)

{
    if (r[0] == r[1] && r[1] == r[2] && r[0] == r[2]) //문양이 세개 동일할경우(★, ♠, ◆)

    {

        if (r[0] == 0)

        {
            printf("\t돈을 얻었다");
            return money * 2;
        }

        else if (r[0] == 1)

        {
            printf("\t돈을 얻었다");
            return money * 2;
        }

        else if (r[0] == 2)

        {
            printf("\t돈을 얻었다");
            return money * 2;
        }

    }

    //그 외 두개가 동일할 경우
    /*
    else if ((r[0] == 0 && r[1] == 0) || (r[1] == 0 && r[2] == 0) || (r[0] == 0 && r[2] == 0))

    {
        printf("lose money");
        return money * 2;
    }

    else if ((r[0] == 1 && r[1] == 1) || (r[1] == 1 && r[2] == 1) || (r[0] == 1 && r[2] == 1))

    {
        printf("lose money");
        return money * 2;
    }

    else if ((r[0] == 2 && r[1] == 2) || (r[1] == 2 && r[2] == 2) || (r[0] == 2 && r[2] == 2))

    {
        printf("lose money");
        return money * 2;
    }

    else if ((r[0] == 3 && r[1] == 3) || (r[1] == 3 || r[2] == 3) || (r[0] == 3 && r[2] == 3))

    {
        printf("lose money");
        return money * 2;
    }

    else if ((r[0] == 4 && r[1] == 4) || (r[1] == 4 && r[2] == 4) || (r[0] == 4 && r[2] == 4))

    {
        printf("lose money");
        return money * 2;
    }

    else if ((r[0] == 5 && r[1] == 5) || (r[1] == 5 && r[2] == 5) || (r[0] == 5 && r[2] == 5))

    {
        printf("lose money");
        return money * 2;
    }
    */
    else //당첨 사례가 없을 경우
        printf("\t돈을 읽었다");  return 0;

}
