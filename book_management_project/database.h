#ifndef DATABASE_H
#define DATABASE_H
#pragma once
#include "structs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
* 데이터 베이스(DB .txt파일) 관련 함수를 정의하는 헤더 파일
*/

void InitDatabase(void);														//데이터베이스 초기화(동적 메모리 할당)
void FreeDatabase(void);														//데이터베이스 해제(동적 메모리 해제)
int countlines(const char* filename);											//파일에서 구조체 개수를 세는 함수
DBERROR UserDatabaseSave( int lastnum);											//user login 구조체 배열 전체 user.txt 파일에 저장
DBERROR UserDatabaseAppend(int idx);											//user.txt에 사용자 한명 추가
DBERROR UserDatabaseLoad(int max, int* count);									//user login 구조체 배열 전체 user.txt에서 불러오기
DBERROR BookDatabaseSave(int lastnum);											//book.txt에 구조체 전체를 저장하는 함수
DBERROR BookDatabaseAppend(int idx);											//book.txt에 구조체 한개 추가하는 함수
DBERROR BookDatabaseLoad(int max, int* count);									//book.txt에서 구조체 전체를 불러오는 함수
DBERROR BorrowDatabaseSave(int lastnum);										//borrow.txt에 구조체 전체를 저장하는 함수
DBERROR BorrowDatabaseAppend(int idx);											//borrow.txt에 구조체 한개 추가하는 함수 
DBERROR BorrowDatabaseLoad(int max, int* count);								//borrow.txt에서 구조체 전체를 불러오는 함수
void AddUser(USER newUser, LOGIN newLogin);										//사용자 추가 함수 (users, logins 배열 동적 재할당 및 추가)
void AddBook(BOOK newBook);														//책 추가 함수 (books 배열 동적 재할당 및 추가)
void AddBorrow(BORROW newBorrow);												//대여 기록 추가 함수 (borrows 배열 동적 재할당 및 추가)

#endif