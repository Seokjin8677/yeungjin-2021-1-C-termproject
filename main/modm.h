//��� ���� .. ��Ƽ���Ͽ��� ���� �ȵǴµ� ���� ������ �𸣰���

#ifndef __STDIO_H__ // __STDIO_H__ ��� ��ũ�ΰ� ���ǵǾ����� ������ ����   
#define __STDIO_H__ // __STDIO_H__ ��ũ�� ����  

#include <stdio.h> 

#endif // �������  

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

#ifndef __WINMM_LIB__
#define __WINMM_LIB__

#pragma comment(lib, "winmm.lib")

#endif



// Ű���� ��  
#ifndef KEY_CODE
#define KEY_CODE

#define KEY_UP  0x48
#define KEY_DOWN 0x50
#define KEY_LEFT  0x4B
#define KEY_RIGHT 0x4D
#define KEY_RETURN 0x0D

#endif

//�޴� ��
#ifndef MENU_CODE
#define MENU_CODE

#define MAIN_MENU 3
#define SINGLE_MENU 8
#define MULTI_MENU 4
#define MULTI_SEL_MENU 3
#define MAX_MENU_CHAR 20

#endif


void start();