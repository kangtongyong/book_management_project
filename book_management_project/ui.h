#ifndef UI_H
#define UI_H
#pragma once
#include "color.h"


/*
* UI 관련 함수를 정의하는 헤더 파일
*/
void DisplayMainScreen(void);										// 메인 화면 출력 함수 원형
void DisplayLoginScreen(void);										// 로그인 화면 출력 함수 원형
void DisplayButtonAct(int x, int y, ColorType BG, ColorType FONT);		// 화면에 버튼 생성 함수 원형 (활성)
void DisplayButton(int x, int y, ColorType BG, ColorType FONT);		// 화면에 버튼 생성 함수 원형(비활성)

#endif