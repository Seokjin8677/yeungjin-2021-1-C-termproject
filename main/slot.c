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

    char reel[6][3] = { "��", "��", "��", "��", "��", "��" };
    int i, reel_num[3][3];


    // printf("\t���Ըӽ� ����\n\n");
    PlaySound(TEXT("sound\\shot.wav"), NULL, SND_ASYNC);
    gotoxy(7, 3);

    printf("���������ԸӽŦ���");

    gotoxy(7, 4);

    draw_check02(6, 3); //�ٵ��ǻ���

    for (i = 0; i < 3; i++)
        reel_num[0][i] = rand() % 5; //��������
    //gotoxy(3, 20);
    reel_series(reel_num);      //��ȣ���� reel_num���� ����������
    game_control(reel, reel_num, money);
    gotoxy(2, 16);
    system("pause");
    return thank;
}


/*

Ȯ��� �ٵ��� �׸��� �Լ� draw_check02

*/

void draw_check02(int c, int r)
{
    gotoxy(7, 4); printf("��������������������������");
    gotoxy(7, 5); printf("��   ��   ��   ��");
    gotoxy(7, 6); printf("��   ��   ��   ��");
    gotoxy(7, 7); printf("��   ��   ��   ��");
    gotoxy(7, 8); printf("��   ��   ��   ��");
    gotoxy(7, 9); printf("��   ��   ��   ��");
    gotoxy(7, 10); printf("��������������������������");
    gotoxy(7, 11); printf("��           ��");
    gotoxy(7, 12); printf("��������������������������");
}

/*

ȭ�鿡 ǥ�õ� ���þ���� ����� �Լ� clear_text

*/


/*

ȭ�鿡 ǥ�õ� ��� ����� �Լ� clear case

*/




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

            gotoxy(9 + j * 4, 5 + i * 2);

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

    //num[i] = reel_num[0][i];
    gotoxy(7, 13);
    thank = return_money(reel_num, money);
    gotoxy(7, 14);
    printf(" ���: %d", thank);
}



/*

��÷ ��� ���� ���� �ݾװ� ��ʱ��� ����ϴ� �Լ� return_money

*/

int return_money(int r[][3], int money)

{
    if (r[1][0] == r[1][1] && r[1][1] == r[1][2] && r[1][0] == r[1][2]) //������ ���� �����Ұ��(��, ��, ��)
    {
        printf(" ���� �����!!");
        PlaySound(TEXT("sound\\win.wav"), NULL, SND_ASYNC);
        return money * 2;
    }
    printf(" ���� �Ҿ���..");
    PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
    return 0;

}
