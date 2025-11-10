/** 메뉴 출력 함수 파일*/
#include "menu.h"
#include "ui.h"
#include "structs.h"
#include "assistant.h"
#include "color.h"
#include <stdio.h>
#include <conio.h>
#include <Windows.h>

/** 처음 메인 메뉴 출력 */
void DisplayMain(void)
{
	int choose = 0;
	int currentIndex = MENU_LOGIN; // 현재 선택된 메뉴 인덱스
	int ch;
	InitConsole("도서관 관리 프로그램");
	while (1)
	{
		// 메인 화면 출력
		DisplayMainScreen();

		//커서 숨기기
		Cursor(0);

		//각 버튼을 현재 선택에 따라 다른색상으로 표시
		for (int i = 0; i < MENU_COUNT; i++)
		{
			int y = MENU_Y0 + (i * MENU_GAP);

			int bg = COLOR_BLACK;
			int font = COLOR_WHITE;

			if (i == currentIndex)
			{
				bg = COLOR_WHITE;
				font = COLOR_WHITE;
				DisplayButtonAct(MENU_X, y, bg, font);
			}
			else
			{
				bg = COLOR_BLACK;
				font = COLOR_WHITE;
				DisplayButton(MENU_X, y, bg, font);
			}
		}

		//키 1개 입력 대기
		ch = _getch();

		//ESC 키 입력 시 프로그램 종료
		if (ch == 27)
		{
			DisplayExit(0);
		}

		//방향키 입력 처리
		if (ch == 224 || ch == 0) // 방향키는 2바이트
		{
			ch = _getch(); // 방향키의 두 번째 바이트 읽기
			switch (ch)
			{
			case UP:
				if (currentIndex > 0)
					currentIndex--;
				break;
			case DOWN:
				if (currentIndex < MENU_COUNT - 1)
					currentIndex++;
				break;

			default:
				break;
			}
		}

		//엔터키 입력 시 메뉴 확정
		else if (ch == 13)
		{
			switch (currentIndex)
			{
			case MENU_LOGIN:
				// 로그인 화면으로 이동
				DisplayLogin();
				choose++;
				break;

			case MENU_SIGNUP:
				// 회원가입 화면으로 이동
				//DisplaySignupScreen();
				choose++;
				break;
			case MENU_EXIT:
				// 프로그램 종료
				DisplayExit(0);
				break;
			}
		}

		if (choose > 0)
		{
			break;
		}
	}
}

/*
* 로그인 메뉴 출력 함수
* 매개변수 : 없음
* 반환값 : 없음
*/
void DisplayLogin(void)
{
	int currentIndex = LOGIN_ID; // 현재 선택된 메뉴 인덱스
	int ch;
	char id[MAX_USER_ID_LENGTH] = { 0 };
	char pw[MAX_USER_PASSWORD_LENGHTH] = { 0 };

	while (1)
	{
		// 로그인 화면 출력 함수 구현
		DisplayLoginScreen();

		MoveCursor(37 + strlen("ID :"), 18);
		//scanf("%s", id);

		MoveCursor(37 + strlen("PW :"), 21);
		//scanf("%s", pw);

		//키 1개 입력 대기
		ch = _getch();

		//ESC 키 입력 시 프로그램 종료
		if (ch == 27)
		{
			DisplayExit(0);
		}

	}
}

/*
* 회원가입 메뉴 출력 함수
* 매개변수 : 없음
* 반환값 : 없음
*/