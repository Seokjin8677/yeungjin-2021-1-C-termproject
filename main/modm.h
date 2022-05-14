//헤더 모음 .. 멀티파일에는 적용 안되는데 아직 이유를 모르겠음

#ifndef __STDIO_H__ // __STDIO_H__ 라는 매크로가 정의되어있지 않으면 진행   
#define __STDIO_H__ // __STDIO_H__ 매크로 정의  

#include <stdio.h> 

#endif // 여기까지  

#ifndef __STDLIB_H__
#define __STDLIB_H__

#include <stdlib.h>

#endif

#ifndef __WINDOWS_H__
#define __WINDOWS_H__

#include <windows.h>

#endif

#ifndef __TIME_H__
#define __TIME_H__

#include <time.h>

#endif

#ifndef __CONIO_H__
#define __CONIO_H__

#include <conio.h>

#endif

#ifndef __MMSYSTEM_H__
#define __MMSYSTEM_H__

#include <mmsystem.h>

#endif

#ifndef __DIGITALV_H__
#define __DIGITALV_H__

#include <Digitalv.h>

#endif


#ifndef __WINMM_LIB__
#define __WINMM_LIB__

#pragma comment(lib, "winmm.lib")

#endif



// 키보드 값  
#ifndef CODE
#define CODE

#define ID_SIZE 32
#define PASS_SIZE 65
#define MAIN_MENU 3
#define SINGLE_MENU 10
#define MULTI_MENU 2
#define MULTI_SEL_MENU 3
#define SHOP_MENU 3
#define BANK_MENU 4
#define KEY_UP  0x48
#define KEY_DOWN 0x50
#define KEY_LEFT  0x4B
#define KEY_RIGHT 0x4D
#define KEY_RETURN 0x0D
#define MAX_MENU_CHAR 20
#define EXPLAIN_MENU 8
#define MONEY_SIZE 11
#define DECK 52
#define ROULETTE_MENU 3
#define MENU_X	33
#define MENU_Y	17
#endif

/*
gotoxy(4, 1); printf("LOGIN");
	gotoxy(3, 2); printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	gotoxy(3, 3); printf("┃");
	gotoxy(36, 3); printf("┃");
	gotoxy(3, 4); printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
	gotoxy(4, 6); printf("PASSWORD");
	gotoxy(3, 7); printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	gotoxy(3, 8); printf("┃");
	gotoxy(36, 8); printf("┃");
	gotoxy(3, 9); printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
	gotoxy(5, 3); printf("_"); gotoxy(5, 3);
*/