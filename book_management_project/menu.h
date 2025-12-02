#ifndef MENU_H
#define MENU_H
#pragma once

typedef enum {
	MENU_LOGIN = 0,
	MENU_SIGNUP,
	MENU_EXIT,
	MENU_COUNT
}MENU_INDEX;

typedef enum {
	LOGIN_ID = 0,
	LOGIN_PW,
	LOGIN_COUNT
}LOGIN_INDEX;

typedef enum {
	LEFT = 75,
	RIGHT = 77,
	UP = 72,
	DOWN = 80
}DIRECTION;

//버튼 위치 상수 정의

#define MENU_X 45
#define MENU_Y0 18
#define MENU_GAP 3

void DisplayMain(void);							//처음 메인 메뉴 출력 함수 원형
void DisplayLogin(void);						//로그인 화면 출력 함수 원형
void MenuSignUp(void)							//	회원가입 화면 출력 함수 원형

#endif