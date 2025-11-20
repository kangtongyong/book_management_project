#ifndef STRUCTS_H
#define STRUCTS_H
#pragma once

#include <stdint.h>
#include <stdbool.h>

/*
* 프로젝트 전역 상수 길이 정의
*/

enum {
	MAX_BOOK_ID_LENGTH = 30,
	MAX_BOOK_NAME_LENGTH = 255,
	MAX_WRITER_LENGTH = 255,
	MAX_TRANSLATOR_LENGTH = 255,
	MAX_BOOK_OX_LENGTH = 20,
	MAX_MAKER_LENGTH = 255,
	MAX_USER_ID_LENGTH = 30,
	MAX_USER_NAME_LENGTH = 50,
	MAX_USER_PASSWORD_LENGHTH = 50,
	MAX_BORROWED_BOOKS = 3,
	MAX_PHONE_LENGTH = 30
};

/*
* 프로젝트 식별자 정의
*/

typedef char BookId[MAX_BOOK_ID_LENGTH];
typedef char UserId[MAX_USER_ID_LENGTH];

/*
* 공통 열거형 정의
*/

typedef enum accounttype{
	ACCOUNT_TYPE_ADMIN = 1,
	ACCOUNT_TYPE_USER = 0
} ACCOUNTTYPE;

typedef enum bookstatus {
	BOOK_AVAILABLE = 1,
	BOOK_NOT_AVAILABLE = 0
} BOOKSTATUS;

typedef enum {
	TRUE = 1,
	FALSE = 0
}booltype;

typedef enum req {
	REQUESTED = 1,				//요청관련
	NOT_REQUESTED = 0		
}REQ;

/*
* DB 에러용 열거형 정의
*/

typedef enum dberror{
	DB_SUCCESS = 0,
	DB_FILE_NOT_FOUND = -1,
	DB_READ_ERROR = -2,
	DB_WRITE_ERROR = -3,
	DB_RECORD_NOT_FOUND = -4,
	DB_DUPLICATE_RECORD = -5
} DBERROR;

typedef struct date{
	uint16_t year;					//년도 4바이트
	uint8_t month;					//월 1바이트
	uint8_t day;					//일 1바이트
}Date;

/*
* 공통 구조체 정의
*/

typedef struct book {
	BookId bookID;																//책 고유 아이디 ex) 4301
	char bookName[MAX_BOOK_NAME_LENGTH];										//책 제목
	char writer[MAX_WRITER_LENGTH];												//저자
	char translator[MAX_TRANSLATOR_LENGTH];										//번역가, 옮긴이
	BOOKSTATUS bookStatus;														//Available 과 No Available 로 대여상태 구분
	char maker[MAX_MAKER_LENGTH];												//출판사
}BOOK;

typedef struct user{																				
	char userName[MAX_USER_NAME_LENGTH];										//사용자 이름
	char phoneNum[MAX_PHONE_LENGTH];
	ACCOUNTTYPE accountType;													//사용자 타입 ADMIN, USER 중 하나
	uint8_t borrowedBookCount;													//현재 대여한 책 권 수
	BookId borrowedBooks[MAX_BORROWED_BOOKS];									//현재 대여한 책 ID 목록
}USER;

typedef struct login {
	ACCOUNTTYPE accountType;												//사용자 타입 ADMIN, USER 중 하나
	UserId loginID;															//사용자 아이디
	char loginPW[MAX_USER_PASSWORD_LENGHTH];								//사용자의 비밀번호
}LOGIN;

typedef struct borrow {
	BOOK bookID;																		//책 고유 아이디
	LOGIN userID;																		//사용자 아이디
	Date borrowDate;																	//책 대여 날짜
	Date dueDate;																		//책 반납 마감 날짜
	Date returnDate;																	//책 반납 예정 날짜
	uint16_t overdueDay;																//반납 시점 기준 계산 결과
}BORROW;

typedef struct request {
	BOOK bookID;																		//책 고유 아이디
	LOGIN userID;																		//사용자 아이디
	booltype extendRequest;																//대여 일 수 연장 요청 TRUE / FALSE 로 구분해 요청 확인
	booltype clearRequest;																//연체 해제 요청 TRUE / FALSE 로 구분해 요청 확인
}REQUEST;

/*
* 날짜 구조체 유틸리티 함수 (빈 날짜 확인)
* 반환값 : 날짜가 비어있다면 true, 아니면 false
*/
static inline bool date_is_null(Date d) {
	return d.year == 0 || d.month == 0 || d.day == 0;
}

#endif