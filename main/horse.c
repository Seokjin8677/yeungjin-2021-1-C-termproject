#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void race(int x, int y);

int horse(int money)
{
    int horse_num = 5, rank[10] = { 0 }, i; //���� ���� �� �� 5, ��������
    int horse[10] = { 0 }, race, number = 0, r = 0; 
    int chose_horse; //����ڰ� ������ ��
    
    srand(time(NULL));

    printf("���ָ�����\n\n");
   
    printf("\n\n");
    printf("�ڽ��� ������ ���� ��ȣ�� �Է��Ͻÿ�: \n");
    scanf("%d", &chose_horse);

    system("cls");

    //���ָ� ����� ȭ�� ����
    printf("\n");
    printf("\t\t\t\t\t\t���ָ� ����� \n\n");
    printf("start                                                                                      end  ���\n");
    printf("====================================================================================================\n");
    for (i = 1; i < horse_num+1; i++)
        printf("%d\t��\n\n", i);
    printf("====================================================================================================\n");
    printf("�ƹ�Ű�� ������ ���ָ� �����մϴ�.\n");


    getch(); //����
    fflush(stdin);
    
    while (horse_num != r) //����� ������ �������� �������
    {
        number = rand() % horse_num; // �����ϰ� ������ �� ����

        if (rank[number] != 0) //������ ���� ����� 0�� �ƴϸ� while ������
            continue;

        race = rand() % 4 + 1; 

        if (race % 4 == 0)
            if (horse[number] < 1)  race = rand() %  + 1;
            else    race = 0;
        else
            race = rand() % 4 + 1;


        horse[number] += race; 
        Sleep(100);

        if (horse[number] >= 80) //����� �����ϸ� ���ǥ��
        {
            horse[number] = 80;
            if (!rank[number]) 
            {
                r++; //����� ���� ����
                rank[number] = r; //������� ������ �ش� ���� ����� ����
                //��������ǥ�� �� ��� ǥ��
                gotoxy(10, 5 + number * 2);
                for (i = 0; i < horse[number]; i++) {
                    printf(" ");
                }
                if (horse[number]) printf("->");
                printf("\t  %d", r);
            }
        }

        else //������� �����ϱ� �����̸�
        {
            gotoxy(10, 5 + number * 2);
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
    gotoxy(20, 24);
    printf("\n\n��������!\n"); //��� ���Ḧ ǥ���Ѵ�.
    
    if (rank[chose_horse-1] == 1) {
        printf("����� ���ָ��� ����߽��ϴ�! �ǵ��� 5�谡 ���޵˴ϴ�.");
        return money * 5;
    } else {
        printf("����� ���ָ��� ������� ���߽��ϴ�.");
    return 0;
    }
}

void race(int x, int y)
{
    COORD Pos = { x - 1, y - 1 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}