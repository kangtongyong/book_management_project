#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include "database.h"
#include "structs.h"
#include "assistant.h"
#include "borrow.h"

//대여 관련 함수

/*
* 함수명 : returnBook()
* 기능 : 책 반납 함수
* 매개변수 : 구조체 포인터
* 반환값 : 없음
*/
void returnBook(BORROW* b) {
    setToday(&b->returnDate);

    // 연체일 계산
    b->overdueDay = calculateOverdue(&b->dueDate, &b->returnDate);
}

/*
* 함수명 : toDays()
* 기능 : 날짜를 일수로 변환하는 함수
* 매개변수 : 날짜 구조체 포인터
* 반환값 : 일수
*/

int toDays(Date* d) {
    return d->year * 365 + d->month * 30 + d->day;
    // 단순 계산 (정확히 하려면 실제 달력 계산 사용)
}

/*
* 함수명 : calculateOverdue()
* 기능 : 연체일 계산 함수
* 매개변수 : 반납일, 대여일 구조체 포인터
* 반환값 : 연체일 수
*/

uint16_t calculateOverdue(Date* due, Date* returned) {
    int dueDays = toDays(due);
    int retDays = toDays(returned);

    if (retDays > dueDays)
        return retDays - dueDays;

    return 0;
}
