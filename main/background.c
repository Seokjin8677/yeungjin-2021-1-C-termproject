#include "modm.h"

void background()
{


    int i;


    //모니터 상판
    gotoxy(0, 0);
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");

    // 디스플레이 상판
    gotoxy(5, 3);
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");

    // 모니터 옆구리 1
    for (i = 1; i < 35; i++)

    {

        gotoxy(0, i);
        printf("┃");

        gotoxy(98, i);
        printf("┃");

    }

    gotoxy(20, 20);
    /*  printf("안녕");*/

      // 디스플레이 옆구리
    for (i = 4; i < 4 + 27; i++)

    {

        gotoxy(5, i);
        printf("┃");

        gotoxy(93, i);
        printf("┃");

    }

    //디스플레이 하판
    gotoxy(5, 31);
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");

    //모니터 중판(?)
    gotoxy(0, 35);
    printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫");


    //모니터 환기구1
    for (int j = 0; j <= 2; j++)
    {
        for (i = 7; i < 7 + 25; i++)
        {
            gotoxy(i, 32 + j);
            printf("┃");
        }
    }

    //전원버튼
    gotoxy(87, 32);
    printf("┏━━━┓");

    gotoxy(87, 33);
    printf("┃ ⊙┃");

    gotoxy(87, 34);
    printf("┗━━━┛");



    // 모니터 옆구리 2
    for (i = 36; i < 36 + 7; i++)

    {

        gotoxy(0, i);
        printf("┃");

        gotoxy(98, i);
        printf("┃");

    }


    //모니터 환기구2-2
    for (int j = 0; j <= 1; j++)
    {
        for (i = 4; i < 4 + 40; i++)
        {
            gotoxy(i, 37 + j);
            printf("┃");
        }
    }


    //모니터 환기구2-2
    for (int j = 0; j <= 1; j++)
    {
        for (i = 4; i < 4 + 40; i++)
        {
            gotoxy(i, 40 + j);
            printf("┃");
        }
    }

    //환기구2 옆 댕그라미
    gotoxy(47, 41);
    printf("○");


    //플로피 디스크
    gotoxy(53, 36);
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");

    for (i = 37; i < 37 + 4; i++)
    {

        gotoxy(53, i);
        printf("┃");

        gotoxy(93, i);
        printf("┃");

    }

    //// 디스크 입구
    //gotoxy(54, 37);
    //printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");

    //gotoxy(54, 38);
    //printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");


    gotoxy(53, 40);
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");


    //몲
    gotoxy(53, 41);
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");

    gotoxy(53, 42);
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");


    //모니터 하판
    gotoxy(0, 43);
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");


}