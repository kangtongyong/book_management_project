#define	_CRT_SECURE_NO_WARNINGS
#include "database.h"
#include "structs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//데이터 베이스 관련 함수 작성

USER* users = NULL;
LOGIN* logins = NULL;
int userCount = 0;

BOOK* books = NULL;
int bookCount = 0;

BORROW* borrows = NULL;
int borrowCount = 0;

REQUEST* requests = NULL;


/*
* 함수명 : InitDatabase()
* 기능 : 데이터베이스 초기화(동적 메모리 할당)
* 매개변수 : 없음
* 반환값 : 없음
*/

void InitDatabase(void)
{
	int Ucount = countlines("user.txt");
	int Bcount = countlines("book.txt");
	int Brcount = countlines("borrow.txt");
	
	//user 동적 메모리 할당
	users = (USER*)malloc(sizeof(USER) * Ucount);
	if (users == NULL)
	{
		return;
	}

	//login 동적 메모리 할당
	logins = (LOGIN*)malloc(sizeof(LOGIN) * Ucount);
	if (logins == NULL)
	{
		free(users);
		return;
	}

	//book 동적 메모리 할당
	books = (BOOK*)malloc(sizeof(BOOK) * Bcount);
	if (books == NULL)
	{
		free(users);
		free(logins);
		return;
	}

	//borrow 동적 메모리 할당
	borrows = (BORROW*)malloc(sizeof(BORROW) * Brcount);
	if (borrows == NULL)
	{
		free(users);
		free(logins);
		free(books);
		return;
	}
	userCount = Ucount;				//전역 변수에 개수 저장
	bookCount = Bcount;
	borrowCount = Brcount;

}

/*
* 함수명 : FreeDatabase()
* 기능 : 데이터베이스 해제(동적 메모리 해제)
* 매개변수 : 없음
* 반환값 : 없음
*/

void FreeDatabase(void)	//데이터베이스 해제(동적 메모리 해제)
{
	if (users != NULL)
	{
		free(users);
		users = NULL;
	}
	if (logins != NULL)
	{
		free(logins);
		logins = NULL;
	}
	if (books != NULL)
	{
		free(books);
		books = NULL;
	}
	if (borrows != NULL)
	{
		free(borrows);
		borrows = NULL;
	}
}

/*
* 함수명 : UserDatabaseSave()
* 기능 : user login 구조체 배열 전체 user.txt 파일에 저장
* 매개변수 : 배열의 마지막 인덱스
* 반환 값 : DBERROR
*/

//user.txt 형식 : accountType|ID|PW|name|phone|borrowedBookCount|borrowedBook1|borrowedBook2|borrowedBook3
DBERROR UserDatabaseSave(int lastnum)
{
	

	FILE* userfp = fopen("user.txt", "w");
	if (userfp == NULL)
	{
		return DB_FILE_NOT_FOUND;
	}

	for (int i = 0; i <= lastnum; i++)
	{
		fprintf(userfp, "%d|%s|%s|%s|%s|%u",
			(int)users[i].accountType,
			logins[i].loginID,
			logins[i].loginPW,
			users[i].userName,
			users[i].phoneNum,
			users[i].borrowedBookCount
		);

		//최대 3권
		for (int j = 0; j < MAX_BORROWED_BOOKS; j++)
		{
			fprintf(userfp, "|%s", users[i].borrowedBooks[j]);
		}

		fprintf(userfp, "\n");
	}

	fclose(userfp);
	return DB_SUCCESS;
}

/*
* 함수명 : UserDatabaseAppend()
* 기능 : user.txt에 사용자 한명 추가
* 매개변수 : 배열의 마지막 인덱스
* 반환 값 : DBERROR
*/

DBERROR UserDatabaseAppend()
{
	FILE* userfp = fopen("user.txt", "a");
	if (userfp == NULL)
	{
		return DB_FILE_NOT_FOUND;
	}

	fprintf(userfp, "%d|%s|%s|%s|%s|%u",
		(int)users->accountType,
		logins->loginID,
		logins->loginPW,
		users->userName,
		users->phoneNum,
		users->borrowedBookCount
	);

	for(int j = 0; j < MAX_BORROWED_BOOKS; j++)
	{
		fprintf(userfp, "|%s", users->borrowedBooks[j]);
	}

	fprintf(userfp, "\n");
	fclose(userfp);
	return DB_SUCCESS;
}

/*
* 함수명 : UserDatabaseLoad()
* 기능 : user login 구조체 배열 전체 user.txt에서 불러오기
* 매개변수 : max, count
* 반환 값 : DBERROR
*/

DBERROR UserDatabaseLoad(int max, int* count)	//max에 userCount 넣어서 호출
{
	FILE* userfp = fopen("user.txt", "r");
	if (userfp == NULL)
	{
		*count = 0;
		return DB_FILE_NOT_FOUND;
	}

	char line[512];		//한 줄을 저장할 버퍼
	int idx = 0;			//현재 인덱스

	while (idx < max && fgets(line, sizeof(line), userfp) != NULL)
	{
		//줄 끝 제거
		line[strcspn(line, "\r\n")] = '\0';

		//파싱
		char* token;
		int field = 0;

		//토큰화
		token = strtok(line, "|");

		while (token != NULL)
		{
			while (*token == ' ') token++; //앞 공백 제거
			char* end = token + strlen(token) - 1;
			while (end > token && (*end == ' ')) { *end = '\0'; end--; } //뒤 공백 제거
			
			switch (field)
			{
			case 0: //accountType
				logins[idx].accountType = (ACCOUNTTYPE)atoi(token);
				users[idx].accountType = logins[idx].accountType;
				break;
			case 1: //loginID
				strncpy(logins[idx].loginID, token, MAX_USER_ID_LENGTH);
				logins[idx].loginID[MAX_USER_ID_LENGTH - 1] = '\0';
				break;
			case 2: //loginPW
				strncpy(logins[idx].loginPW, token, MAX_USER_PASSWORD_LENGHTH);
				logins[idx].loginPW[MAX_USER_PASSWORD_LENGHTH - 1] = '\0';
				break;
			case 3: //userName
				strncpy(users[idx].userName, token, MAX_USER_NAME_LENGTH);
				users[idx].userName[MAX_USER_NAME_LENGTH - 1] = '\0';
				break;
			case 4: //phoneNum
				strncpy(users[idx].phoneNum, token, MAX_PHONE_LENGTH);
				users[idx].phoneNum[MAX_PHONE_LENGTH - 1] = '\0';
				break;
			case 5: //borrowedBookCount
				users[idx].borrowedBookCount = (uint8_t)atoi(token);
				break;
			default: //borrowedBooks
				{
					int bookIndex = field - 6;
					if (0 <= bookIndex && bookIndex < MAX_BORROWED_BOOKS)
					{
						strncpy(users[idx].borrowedBooks[bookIndex], token, MAX_BOOK_ID_LENGTH);
						users[idx].borrowedBooks[bookIndex][MAX_BOOK_ID_LENGTH - 1] = '\0';
					}
					break;
				}

			field++;
			token = strtok(NULL, "|");
			}
		}

		idx++;
	}

	fclose(userfp);
	*count = idx;
	return DB_SUCCESS;
}

/*
* 함수명 : BookDatabaseSave()
* 기능 : book.txt에 구조체 전체를 저장하는 함수
* 매개변수 : book 구조체 배열, 배열 마지막 인덱스
* 반환값 : 정수값
*/

//book.txt 형식 : bookID|bookName|writer|translator|bookStatus|maker
DBERROR BookDatabaseSave(int lastnum)
{
	FILE* bookfp = fopen("book.txt","w");
	if (bookfp == NULL)
	{
		return DB_FILE_NOT_FOUND;
	}

	for(int i = 0; i <= lastnum; i++)
	{
		fprintf(bookfp,"%s|%s|%s|%s|%d|%s\n",
			books[i].bookID,
			books[i].bookName,
			books[i].writer,
			books[i].translator,
			books[i].bookStatus,
			books[i].maker);
	}
	
	fclose(bookfp);
	return DB_SUCCESS;
}

/*
* 함수명 : BookDatabaseLoad()
* 기능 : book.txt에서 구조체 전체를 불러오는 함수
* 매개변수 : 배열 최대 크기, 불러온 개수 포인터
* 반환값 : 정수값
*/
DBERROR BookDatabaseLoad(int max, int* count) //max에 bookCount 넣어서 호출
{
	FILE* bookfp = fopen("book.txt", "r");
	if (bookfp == NULL)
	{
		*count = 0;
		return DB_FILE_NOT_FOUND;
	}
	char line[512];			//한 줄을 저장할 버퍼
	int idx = 0;			//현재 인덱스

	while (idx < max && fgets(line, sizeof(line), bookfp) != NULL)
	{
		//줄 끝 제거
		line[strcspn(line, "\r\n")] = '\0';

		//파싱
		char* token;
		int field = 0;

		//토큰화
		token = strtok(line, "|");

		while (token != NULL)
		{
			while (*token == ' ') token++; //앞 공백 제거
			char* end = token + strlen(token) - 1;
			while (end > token && (*end == ' ')) { *end = '\0'; end--; } //뒤 공백 제거
			switch (field)
			{
			case 0: //bookID
				strncpy(books[idx].bookID, token, MAX_BOOK_ID_LENGTH);
				books[idx].bookID[MAX_BOOK_ID_LENGTH - 1] = '\0';
				break;
			case 1: //bookName
				strncpy(books[idx].bookName, token, MAX_BOOK_NAME_LENGTH);
				books[idx].bookName[MAX_BOOK_NAME_LENGTH - 1] = '\0';
				break;
			case 2: //writer
				strncpy(books[idx].writer, token, MAX_WRITER_LENGTH);
				books[idx].writer[MAX_WRITER_LENGTH - 1] = '\0';
				break;
			case 3: //translator
				strncpy(books[idx].translator, token, MAX_TRANSLATOR_LENGTH);
				books[idx].translator[MAX_TRANSLATOR_LENGTH - 1] = '\0';
				break;
			case 4: //bookStatus
				books[idx].bookStatus = (BOOKSTATUS)atoi(token);
				break;
			case 5: //maker
				strncpy(books[idx].maker, token, MAX_MAKER_LENGTH);
				books[idx].maker[MAX_MAKER_LENGTH - 1] = '\0';
				break;
			}
			field++;
			token = strtok(NULL, "|");
		}

		idx++;
	}
	fclose(bookfp);
	*count = idx;
	return DB_SUCCESS;
}

/*
* 함수명 : BookDatabaseAppend()
* 기능 : book.txt에 책 한권 추가하는 함수
* 매개변수 : 없음
* 반환값 : 정수값
*/
DBERROR BookDatabaseAppend()
{
	FILE* bookfp = fopen("book.txt", "a");
	if (bookfp == NULL)
	{
		return DB_FILE_NOT_FOUND;
	}

	fprintf(bookfp, "%s|%s|%s|%s|%d|%s\n",
		books->bookID,
		books->bookName,
		books->writer,
		books->translator,
		books->bookStatus,
		books->maker);


	fclose(bookfp);
	return DB_SUCCESS;
}


/*
* 함수명 : borrowDataSave()
* 기능 : 대여 저장 함수
* 매개변수 : 
* 반환값 : 정수값
*/
//대출 기록은 제대로 구조를 짜지 못해 여러분께서 수정해주시면 감사하겠습니다.^^;
//borrow.txt 형식 : bookID|userID|borrowY|borrowM|borrowD|returnY|returnM|returnD|overdueDay

DBERROR BorrowDatabaseSave(int lastnum)
{
	FILE* borrowfp = fopen("borrow.txt", "w");
	if (borrowfp == NULL)
	{
		return DB_FILE_NOT_FOUND;
	}
	for (int i = 0; i <= lastnum; i++)
	{
		fprintf(borrowfp, "%s|%s|%u|%u|%u|%u|%u|%u|%u\n",
			borrows[i].bookID.bookID,
			borrows[i].userID.loginID,
			borrows[i].borrowDate.year,
			borrows[i].borrowDate.month,
			borrows[i].borrowDate.day,
			borrows[i].returnDate.year,
			borrows[i].returnDate.month,
			borrows[i].returnDate.day,
			borrows[i].overdueDay
		);
	}
	fclose(borrowfp);
	return DB_SUCCESS;
}

/*
* 함수명 : borrowDataLoad()
* 기능 : 대여 불러오기 함수
* 매개변수 : 배열 최대 크기, 불러온 개수 포인터
* 반환값 : 정수값
*/

DBERROR BorrowDatabaseLoad(int max, int* count) //max에 borrowCount 넣어서 호출
{
	FILE* borrowfp = fopen("borrow.txt", "r");
	if (borrowfp == NULL)
	{
		*count = 0;
		return DB_FILE_NOT_FOUND;
	}
	char line[512];			//한 줄을 저장할 버퍼
	int idx = 0;			//현재 인덱스
	while (idx < max && fgets(line, sizeof(line), borrowfp) != NULL)
	{
		//줄 끝 제거
		line[strcspn(line, "\r\n")] = '\0';
		//파싱
		char* token;
		int field = 0;
		//토큰화
		token = strtok(line, "|");
		while (token != NULL)
		{
			while (*token == ' ') token++; //앞 공백 제거
			char* end = token + strlen(token) - 1;
			while (end > token && (*end == ' ')) { *end = '\0'; end--; } //뒤 공백 제거
			switch (field)
			{
			case 0: //bookID
				strncpy(borrows[idx].bookID.bookID, token, MAX_BOOK_ID_LENGTH);
				borrows[idx].bookID.bookID[MAX_BOOK_ID_LENGTH - 1] = '\0';
				break;
			case 1: //userID
				strncpy(borrows[idx].userID.loginID, token, MAX_USER_ID_LENGTH);
				borrows[idx].userID.loginID[MAX_USER_ID_LENGTH - 1] = '\0';
				break;
			case 2: //borrowDate year
				borrows[idx].borrowDate.year = (uint16_t)atoi(token);
				break;
			case 3: //borrowDate month
				borrows[idx].borrowDate.month = (uint8_t)atoi(token);
				break;
			case 4: //borrowDate day
				borrows[idx].borrowDate.day = (uint8_t)atoi(token);
				break;
			case 5: //returnDate year
				borrows[idx].returnDate.year = (uint16_t)atoi(token);
				break;
			case 6: //returnDate month
				borrows[idx].returnDate.month = (uint8_t)atoi(token);
				break;
			case 7: //returnDate day
				borrows[idx].returnDate.day = (uint8_t)atoi(token);
				break;
			case 8: //overdueDay
				borrows[idx].overdueDay = (uint16_t)atoi(token);
				break;
			}
			field++;
			token = strtok(NULL, "|");
		}
		idx++;
	}
	fclose(borrowfp);
	*count = idx;
	return DB_SUCCESS;
}

/*
* 함수명 : borrowDataAppend()
* 기능 : 대여 추가 함수
* 매개변수 : 없음
* 반환값 : 정수값
*/
DBERROR BorrowDatabaseAppend()
{
	FILE* borrowfp = fopen("borrow.txt", "a");
	if (borrowfp == NULL)
	{
		return DB_FILE_NOT_FOUND;
	}
	fprintf(borrowfp, "%s|%s|%u|%u|%u|%u|%u|%u|%u\n",
		borrows->bookID.bookID,
		borrows->userID.loginID,
		borrows->borrowDate.year,
		borrows->borrowDate.month,
		borrows->borrowDate.day,
		borrows->returnDate.year,
		borrows->returnDate.month,
		borrows->returnDate.day,
		borrows->overdueDay
	);
	fclose(borrowfp);
	return DB_SUCCESS;
}

/*
* 함수명 : countlines()
* 기능 : 파일에서 구조체 개수를 세는 함수
* 매개변수 : 파일이름
* 반환값 : 정수값
*/

int countlines(const char* filename)
{
	FILE* fp = fopen(filename, "r");	//파일 읽기 모드로 열기
	if (fp == NULL)
	{
		return -1;
	}

	int count = 0;						//줄 개수를 세기 위한 변수
	char buffer[512];					//한 줄을 저장할 버퍼
		
	while (fgets(buffer, sizeof(buffer), fp) != NULL) //한 줄씩 읽어 줄 개수를 count에 저장
	{
		count++;
	}

	fclose(fp);
	return count;										//파일 닫기 후 줄 개수 반환
}