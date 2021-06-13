#include "modm.h"

extern void gotoxy(int, int);
void printhorsefield();
int horse(int insertmoney)
{
    int horse_num = 5, rank[5] = { 0 }, i; //���� ���� �� �� 5, ��������
    int horse[5] = { 0 }, race, number = 0, r = 0; 
    int chose_horse; //����ڰ� ������ ��
    char select_horse[2];


    /*printf("���ָ�����\n\n");
   
    printf("\n\n");*/
    

    //���ָ� ����� ȭ�� ����
    printf("\n");
    do {
        printhorsefield();
        //printf("�ƹ�Ű�� ������ ���ָ� �����մϴ�.");
        printf("�ڽ��� ������ ���� ��ȣ�� �Է��Ͻÿ�(1~5): ");
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
            gotoxy(0, 17);
            printf("1~5 ������ �Է����ּ���!\n");
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
        Sleep(50);

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
    gotoxy(20, 14);
    printf("\n\n��������!\n"); //��� ���Ḧ ǥ���Ѵ�.
    
    if (rank[chose_horse-1] == 1) {
        printf("����� ���ָ��� ����߽��ϴ�!\n%d���� ������!\n", insertmoney*5);
        PlaySound(TEXT("sound\\win.wav"), NULL, SND_ASYNC);
        return insertmoney * 5;
    } 
    else {
        printf("����� ���ָ��� ������� ���߽��ϴ�...\n���� �Ҿ���...\n");
        PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
        return 0;
    }
}
void printhorsefield() {
    system("cls");
    gotoxy(44, 1); printf("���� �渶��\n\n");
    printf("START                                                                                      END  ���\n");
    printf("====================================================================================================\n");
    for (int i = 1; i <= 5; i++)
        printf("%d\t��\n\n", i);
    printf("====================================================================================================\n");
}