#ifndef ASSISTANT_H
#define ASSISTANT_H
#pragma once
#include "color.h"
#include "structs.h"
#include <conio.h>						// _getch() 함수 사용을 위한 헤더 파일 포함
#include <stdio.h>
#include <Windows.h>

/*
* UI 보조 함수 헤더 파일
*/

void ClearConsole(void);											// 콘솔 화면 지우기 함수 원형
void MoveCursor(int x, int y);										// 커서 위치 이동 함수 원형
void InitConsole(char title[]);										// 처음 화면 설정 함수 원형
void DisplayExit(int n);											// 프로그램 종료 화면 함수 원형
void DrawSquare(int width, int height, int x, int y);				// 사각형 그리기 함수 원형
void Cursor(int n);													// 커서 보이기/숨기기 함수 원형
void setToday(Date* d);												// 현재 날짜를 넣어주는 공통 함수 원형
int daysInMonth(int year, int month);								// 해당 월의 일 수를 반환하는 함수 원형
void addDays(Date* d, int days);									// 날짜에 일 수를 더하는 함수 원형
void InputStarPW(char* buffer, int maxLen);							// 비밀번호 * 변환 함수 원형

#endif