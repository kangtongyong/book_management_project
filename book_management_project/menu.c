/** 메뉴 출력 함수 파일*/
#define _CRT_SECURE_NO_WARNINGS
#include "menu.h"
#include "ui.h"
#include "structs.h"
#include "assistant.h"
#include "color.h"
#include "login.h"
#include "book.h"
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
			{
				// 로그인 화면으로 이동
				DisplayLogin();
				choose++;
				
				break;

			}


			case MENU_SIGNUP:
			{
				// 회원가입 화면으로 이동
				MenuSignUp();
				choose++;
				
				break;
			}


			case MENU_EXIT:
				// 프로그램 종료
				DisplayExit(0);
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

	char buffid[MAX_USER_ID_LENGTH] = { 0 };		//	아이디 입력 버퍼
	char buffpw[MAX_USER_PASSWORD_LENGHTH] = { 0 };		// 비밀번호 입력 버퍼
	int wrongcount = 0;								// 잘못된 로그인 시도 횟수

	ClearConsole();

	while (1)
	{
		//	로그인 화면 출력
		DisplayLoginScreen();

		//	커서 보이기
		Cursor(1);
		ch = _getch();
		if(ch == 27)
		{
			break;
		}


		//	ID 입력
		MoveCursor(35 + (int)strlen("ID :"), 18);
		printf("                              ");	//	기존 입력 지우기
		MoveCursor(35 + (int)strlen("ID :"), 18);
		scanf("%29s", buffid);	//	최대 29글자 (널 포함 30)

		//	PW 입력
		MoveCursor(35 + (int)strlen("PW :"), 21);
		printf("                              ");
		MoveCursor(35 + (int)strlen("PW :"), 21);
		InputStarPW(buffpw, MAX_USER_PASSWORD_LENGHTH);	// 최대 29글자 (널 포함 30)

		//	커서 숨기기
		Cursor(0);
		

		//	로그인 검사 호출 (login.c의 testlogin 사용)
		int result = testlogin(buffid, buffpw);

		//	결과에 따른 처리
		if (result == ACCOUNT_TYPE_ADMIN)
		{
			system("cls");
			DrawSquare(100, 30, 0, 0);
			MoveCursor(40, 14);
			printf("관리자 %s님 환영합니다.\n", buffid);
			_getch();   //	콘솔에서 관리자 %s님 환영합니다. 읽을 시간 주기
			AdminMenu();

			//	관리자 / 사용자 메뉴로 분기
			return;     // 로그인 화면 종료
		}
		else if (result == ACCOUNT_TYPE_USER)
		{
			UserMenu(buffid);
			//	사용자 / 사용자 메뉴로 분기

			
		}

		else if (result == DB_FILE_NOT_FOUND)
		{
			// DB 문제 (user.txt 읽기 실패 등)
			MoveCursor(36, 24);
			printf("사용자 DB 파일을 열 수 없습니다.");
			MoveCursor(32, 26);
			printf("(아무 키나 누르면 메인으로 돌아갑니다.)");
			_getch();
			return;     // 메인 메뉴로 복귀
		}

		else if (result == DB_RECORD_NOT_FOUND)
		{
			//	로그인 실패
			wrongcount++;
			MoveCursor(31, 24);
			printf("아이디 또는 비밀번호가 잘못되었습니다. (%d/%d)", wrongcount, WRONGCOUNT_FAIL);

			//	일정 횟수 이상 실패 시 종료
			if (wrongcount >= WRONGCOUNT_FAIL)
			{
				MoveCursor(31, 26);
				printf("%d이상 로그인 시도로 프로그램을 종료합니다.", wrongcount);
				_getch();
				DisplayExit(0);
			}

			MoveCursor(34, 26);
			printf("다시 시도하려면 아무 키나 누르세요. (ESC: 종료)");

			ch = _getch();
			if (ch == 27) // ESC
			{
				DisplayExit(0);
			}
			// ESC가 아니면 처음으로 돌아가서 재시도
		}

		else
		{
			//	기타 에러
			MoveCursor(35, 24);
			printf("알 수 없는 DB 에러가 발생했습니다.");
			MoveCursor(33, 26);
			printf("(코드: %d)\n", result);
			_getch();
			DisplayExit(0);
		}
	}
}

/*
* 회원가입 메뉴 출력 함수
* 매개변수 : 없음
* 반환값 : 없음
*/

void MenuSignUp(void)
{
	int currentIndex = MENU_SIGNUP; // 현재 선택된 메뉴 인덱스
	int ch;

	char buffid[MAX_USER_ID_LENGTH] = { 0 };			//	아이디 입력 버퍼
	char buffpw[MAX_USER_PASSWORD_LENGHTH] = { 0 };		//	비밀번호 입력 버퍼
	char buffname[MAX_USER_NAME_LENGTH] = { 0 };		//	이름 입력 버퍼
	char buffphonenum[MAX_PHONE_LENGTH] = { 0 };		//	전화번호 입력 버퍼

	while (1)
	{
		DisplaySignUpScreen();

		ch = _getch();
		if (ch == 27)
		{
			break;
		}

		//	커서 보이기
		Cursor(1);

		MoveCursor(35 + (int)strlen("ID :"), 15);
		printf("                              ");	//	기존 입력 지우기
		MoveCursor(35 + (int)strlen("ID :"), 15);
		scanf("%29s", buffid);

		//	PW 입력
		MoveCursor(35 + (int)strlen("PW :"), 18);
		printf("                              ");
		MoveCursor(35 + (int)strlen("PW :"), 18);
		scanf("%29s", buffpw);

		//	name 입력
		MoveCursor(35 + (int)strlen("PW :"), 21);
		printf("                              ");
		MoveCursor(35 + (int)strlen("PW :"), 21);
		scanf("%10s", buffname);

		//	phonenum 입력
		MoveCursor(35 + (int)strlen("PW :"), 24);
		printf("                              ");
		MoveCursor(35 + (int)strlen("PW :"), 24);
		scanf("%15s", buffphonenum);

		//	커서 숨기기
		Cursor(0);

		int result = signup(buffid, buffpw, buffname, buffphonenum);

		if (result == DB_DUPLICATE_RECORD)
		{
			//	동일한 아이디 존재
			system("cls");
			MoveCursor(36, 24);
			printf("DB파일 내에 동일한 아이디가 존재합니다.");
			MoveCursor(34, 26);
			printf("다시 시도하려면 아무 키나 누르세요. (ESC: 종료)");

			ch = _getch();
			if (ch == 27) // ESC
			{
				DisplayExit(0);
			}
			else
			{
				continue;
			}
		}
		else if (result == DB_FILE_NOT_FOUND)
		{
			// DB 문제 (user.txt 읽기 실패 등)
			MoveCursor(36, 26);
			printf("사용자 DB 파일을 열 수 없습니다.");
			MoveCursor(32, 28);
			printf("(아무 키나 누르면 메인으로 돌아갑니다.)");
			_getch();
			return;     // 메인 메뉴로 복귀
		}
		else if (result == DB_SUCCESS)
		{
			system("cls");
			DrawSquare(100, 30, 0, 0);
			MoveCursor(35, 18);
			printf("회원가입 완료");
			MoveCursor(32, 20);
			printf("(아무 키나 누르면 메인으로 돌아갑니다.)");

			_getch();
			return;     // 메인 메뉴로 복귀
		}
		else
		{
			//	기타 에러
			MoveCursor(35, 24);
			printf("알 수 없는 DB 에러가 발생했습니다.");
			MoveCursor(33, 26);
			printf("(코드: %d)\n", result);
			_getch();
			DisplayExit(0);
		}
	}
}

/*
* 유저 메뉴	출력 함수
*/

void UserMenu(const char * id)
{
	char strbuff[MAX_BOOK_NAME_LENGTH] = { 0 };
	int ch;
	
	while (1)
	{
		DisplayUserScreen(id);

		DisplayBookListInArea();

		//도서 검색
		MoveCursor(23 + (int)strlen("도서 검색 : "), 3);
		printf("                              ");	//	기존 입력 지우기
		MoveCursor(23 + (int)strlen("도서 검색 : "), 3);
		ch = _getch();
		if (ch == 13)	//	엔터키
		{
			scanf("%79s", strbuff);	//	최대 79글자 (널 제외함 80)
		}
		
		
		if (ch == 27)
		{
			break;
		}

		SearchBook(strbuff);

		
	}

}

void AdminMenu(void)
{
	int ch;

	while (1)
	{
		DisplayAdmin();

		ch = _getch();
		
		switch (ch)
		{
			case 49:
			{
				AddBookInteractive();
				break;
			}
			case 50:
			{
				EditBookInteractive();
				break;
			}
			case 51:
			{
				RemoveBookInteractive();
				break;
			}
			case 52:
			{	
				while (1)
				{
					ch = _getch();

					DisplayUserListInArea();
					if (ch == 27)
					{
						break;
					}
				}
				break;
			}
			case 53:
			{
				while (1)
				{
					ch = _getch();

					DisplayBookListInArea();
					if (ch == 27)
					{
						break;
					}
				}
				break;
			}
			case 27:
			{
				return;
			}
			default:
				break;
		}

	}

}