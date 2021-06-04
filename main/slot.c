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

    char reel[6][3] = { "��", "��", "��", "��", "��", "��" };
    int i, reel_num[3][3];
    srand((unsigned)time(NULL));

    printf("\t���Ըӽ� ����\n\n");

    gotoxys(1, 5);

    printf("���������ԸӽŦ���");

    gotoxys(1, 6);

    draw_check02(6, 3); //�ٵ��ǻ���

    for (i = 0; i < 3; i++)
        reel_num[0][i] = rand() % 5; //��������

    reel_series(reel_num);      //��ȣ���� reel_num���� ����������
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

Ȯ��� �ٵ��� �׸��� �Լ� draw_check02

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

ȭ�鿡 ǥ�õ� ���þ���� ����� �Լ� clear_text

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

ȭ�鿡 ǥ�õ� ��� ����� �Լ� clear case

*/

void clear_case(void)

{

    gotoxys(43, 18);

    printf("                                             ");

}



/*

�� ���� ���� ��ȣ�� ������ �����ϴ� �Լ� reel_series

*/

void reel_series(int r[][3])

{

    int i, j;

    for (i = 0; i < 3; i++)

        for (j = 0; j < 3; j++)

            r[j][i] = (r[0][i] + j) % 6; //������ ���� ���� ��ȣ ����

}



/*

ȸ�� ������ ���� ���� ȭ�鿡 ����ϴ� �Լ� display_reel

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

���� �ӽ� ������ �����ϴ� �Լ� game_control

*/

void game_control(char reel[][3], int reel_num[][3], int money)

{

    int i, j, num[3];

    double pst;

    int random[3]; //������ ���� ���� ���߰� �ϵ��� ���� �߻�

    clock_t start, end;



    display_reel(reel, reel_num);

    //bet = game_progress(money);



    //��ġ�� �ʵ���

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
            for (j = i; j < 3; j++) //���� ������ �Լ�

                reel_num[0][random[j]] = reel_num[1][random[j]];

            reel_series(reel_num);

            display_reel(reel, reel_num);

            end = clock();

            pst = (double)(end - start) / CLK_TCK;

        } while (pst < 1); //1�ʾȿ�

        num[i] = reel_num[1][i]; //����� ���⶧����

    }

    thank = return_money(num, money);
    printf("\t ���: %d", thank);

}



/*

��÷ ��� ���� ���� �ݾװ� ��ʱ��� ����ϴ� �Լ� return_money

*/

int return_money(int r[], int money)

{
    if (r[0] == r[1] && r[1] == r[2] && r[0] == r[2]) //������ ���� �����Ұ��(��, ��, ��)

    {

        if (r[0] == 0)

        {
            printf("\t���� �����");
            return money * 2;
        }

        else if (r[0] == 1)

        {
            printf("\t���� �����");
            return money * 2;
        }

        else if (r[0] == 2)

        {
            printf("\t���� �����");
            return money * 2;
        }

    }

    //�� �� �ΰ��� ������ ���
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
    else //��÷ ��ʰ� ���� ���
        printf("\t���� �о���");  return 0;

}
