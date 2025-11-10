//ui 보조를 위한 헤더 파일 포함
#define _CRT_SECURE_NO_WARNINGS
#include "color.h"
#include "assistant.h"
#include <string.h>
#include <stdio.h>
#include <Windows.h>

/*
* 콘솔 화면 지우기 함수
* 매개변수 : 없음
* 반환값 : 없음
*/

void ClearConsole(void) 
{
	system("cls");

	return;
}

/*
* 커서 위치 이동 함수
* 매개변수 : int x - 이동할 X 좌표
* 		     int y - 이동할 Y 좌표
* 반환값 : 없음
*/

void MoveCursor(int x, int y) 
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x, y };
	SetConsoleCursorPosition(hConsole, pos);

	return;
}

/*
* 처음 화면 설정 함수
* 매개변수 : 없음
* 반환값 : 없음
*/

void InitConsole(char title[])
{
	SetColorBG(COLOR_BLACK);
	SetColorFont(COLOR_WHITE);
	system("mode con:cols = 100, lines = 30");
	SetConsoleTitleA(title);
	ClearConsole();

	return;
}

/*
* 프로그램 종료 화면 함수
* 매개변수 : 없음
* 반환값 : 없음
*/

void DisplayExit(int n)
{
	ClearConsole();
	printf("프로그램을 종료합니다. 이용해 주셔서 감사합니다.\n");
	exit(n);
}

/*
* 사각형 출력 함수
* 매개변수 : int width - 테두리 가로 길이
* 		     int height - 테두리 세로 길이
* 		     int x - 출력할 X 좌표
* 		     int y - 출력할 Y 좌표
* 반환값 : 없음
*/

void DrawSquare(int width, int height, int x, int y)
{
	MoveCursor(x, y);
	//상단 테두리 출력
	printf("┌");
	for (int i = 0; i < width; i++)
	{
		printf("─");
	}
	printf("┐\n");

	//측면 테두리 출력
	for (int j = 0; j < height; j++)
	{
		MoveCursor(x, y + 1 + j);
		printf("│%*s│\n",width,"");
	}

	//하단 테두리 출력
	MoveCursor(x, y + height);
	printf("└");
	for (int i = 0; i < width; i++)
	{
		printf("─");
	}
	printf("┘\n");

	return;
}

/*
* 커서 보이기 / 숨기기 함수
* 매개변수 : int n - 0: 숨기기, 1: 보이기
* 반환값 : 없음
*/
void Cursor(int n)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = n;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);

	return;
}