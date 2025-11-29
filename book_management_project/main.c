#include "structs.h"
#include "assistant.h"
#include "database.h"
#include "ui.h"
#include "menu.h"
#include "color.h"
#include <conio.h>		// _getch() 함수 사용을 위한 헤더 파일 포함
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

int main(void) 
{
	//  데이터베이스 초기화 (동적 메모리 할당)
	InitDatabase();

	DisplayMain();

	////	데이터베이스 해제(동적 메모리 해제)
	//FreeDatabase();
	return 0;
}
