//ui 보조를 위한 헤더 파일 포함
#define _CRT_SECURE_NO_WARNINGS
#include "color.h"
#include "assistant.h"
#include <string.h>
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <ctype.h> 

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
	system("mode con: cols = 100 lines = 30");
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

/*
* 현재 날짜를 넣어주는 공통 함수
*/

void setToday(Date* d) 
{
	time_t t = time(NULL);
	struct tm* now = localtime(&t);

	d->year = now->tm_year + 1900;
	d->month = now->tm_mon + 1;
	d->day = now->tm_mday;
}

/*
* 날짜 계산 함수
*/

int daysInMonth(int year, int month)
{
	static int mdays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

	if (month == 2) {
		// 윤년 계산
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
			return 29;
	}
	return mdays[month - 1];
}

/*
* 날짜 더하기 함수
*/

void addDays(Date* d, int days) 
{
	d->day += days;

	while (1) {
		int dim = daysInMonth(d->year, d->month);

		if (d->day > dim) {
			d->day -= dim;
			d->month++;

			if (d->month > 12) {
				d->month = 1;
				d->year++;
			}
		}
		else break;
	}
}


/*
* 비밀번호 입력 함수
* - 키보드에서 한 글자씩 읽어서 buffer에 저장
* - 화면에는 실제 글자 대신 '*' 출력
* - Enter를 누르면 입력 종료
* 매개변수 : char* buffer   - PW를 저장할 배열
*           int   maxLen    - 배열 크기 (널문자 포함 최대 길이)
*/
void InputStarPW(char* buffer, int maxLen)
{
	int len = 0;
	int ch;

	// 안전하게 초기화
	if (buffer == NULL || maxLen <= 1)
		return;

	buffer[0] = '\0';

	while (1)
	{
		ch = _getch();   // 키 하나 입력 (화면에 자동 출력 안 됨)

		// Enter 키 → 입력 종료
		if (ch == 13)    // '\r'
		{
			buffer[len] = '\0';
			break;
		}
		// Backspace 처리
		else if (ch == 8)   // '\b'
		{
			if (len > 0)
			{
				// 버퍼에서 한 글자 삭제
				len--;
				buffer[len] = '\0';

				// 화면에서 '*' 한 개 지우기
				printf("\b \b");   // 커서 뒤로, 공백 출력, 다시 뒤로
			}
		}
		// 일반 출력 가능한 문자
		else if (isprint(ch) && len < maxLen - 1)
		{
			buffer[len] = (char)ch;
			len++;
			buffer[len] = '\0';

			// 화면에는 '*'만 출력
			printf("*");
		}
	}
}