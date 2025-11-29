//UI 관련 함수 구현 파일
#define _CRT_SECURE_NO_WARNINGS
#include "color.h"
#include "assistant.h"
#include <conio.h>				// _getch() 함수 사용을 위한 헤더 파일 포함
#include <stdio.h>
#include <Windows.h>

/*
* ─│┌ ┐┘└├ ┤┬ ┴ ┼
*/

/*
* 메인 화면 출력 함수
* 매개변수 : 없음
* 반환값 : 없음
*/

void DisplayMainScreen(void)
{
	DrawSquare(100, 30, 0, 0);
	
	//타이틀 테두리
	DrawSquare(25, 4, 37, 5);
	MoveCursor(41, 7);
	printf("도서관 관리 프로그램");
	
	//메뉴 테두리
	DrawSquare(25, 15, 37, 13);
	
	//로그인 버튼
	DrawSquare(11, 2, 44, 17);
	MoveCursor(48, 18);
	printf("로그인");
	
	//회원가입 버튼
	DrawSquare(11, 2, 44, 20);
	MoveCursor(47, 21);
	printf("회원가입");

	//종료 버튼
	DrawSquare(11, 2, 44, 23);
	MoveCursor(49, 24);
	printf("종료");

	return;
}

/*
* 로그인 화면 출력 함수
* 매개변수 : 없음
* 반환값 : 없음
*/

void DisplayLoginScreen(void)
{
	ClearConsole();
	//화면 테두리
	DrawSquare(100, 30, 0, 0);
	DrawSquare(50, 28, 25, 1);

	//타이틀 테두리
	DrawSquare(25, 4, 37, 5);
	MoveCursor(41, 7);
	printf("도서관 관리 프로그램");


	//로그인 박스 테두리
	MoveCursor(42, 16);//11
	printf("로그인을 해주세요.");

	DrawSquare(36, 2, 32, 17);
	MoveCursor(34, 18);
	printf("ID :");

	DrawSquare(36, 2, 32, 20);
	MoveCursor(34, 21);
	printf("PW :");

	return;
}

/*
* 버튼 화면 출력 함수 (비활성)
* 매개변수 : int x - 버튼 X 좌표
* 		     int y - 버튼 Y 좌표
* 반환값 : 없음
*/

void DisplayButton(int x, int y, ColorType BG, ColorType FONT)
{
	SetColorBG(BG);
	SetColorFont(FONT);
	MoveCursor(x, y);
	printf("□");

	return;
}

void DisplayButtonAct(int x, int y, ColorType BG, ColorType FONT)
{
	SetColorBG(BG);
	SetColorFont(FONT);
	MoveCursor(x, y);
	printf("■");

	return;
}