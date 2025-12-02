#ifndef BORROW_H
#define BORROW_H
#pragma once
#include "structs.h"

/*
* 대출, 반납 등의 기능 함수를 정의하는 헤더 파일
*/

void returnBook(BORROW* b);
uint16_t calculateOverdue(Date* due, Date* returned);

#endif