#include "database.h"
#include "structs.h"
#include <stdio.h>
#include <string.h>

//데이터 베이스 관련 함수 작성

/*
* 함수명 : UserDatabaseSave()
* 기능 : user login 구조체 배열 전체 user.txt 파일에 저장
* 매개변수 : 사용자 구조체 배열, 로그인 구조체 배열, 배열의 마지막 인덱스
* 반환 값 : DBERROR
*/

//user.txt 형식 : accountType | ID | PW | name | phone | borrowedBookCount | borrowedBook1 | borrowedBook2 | borrowedBook3
DBERROR UserDatabaseSave(USER user[],LOGIN login[], int lastnum)
{
	FILE* userfp = fopen("user.txt", "w");
	if (userfp == NULL)
	{
		return DB_FILE_NOT_FOUND;
	}

	for (int i = 0; i <= lastnum; i++)
	{
		fprintf(userfp, "%d|%s|%s|%s|%s|%u",
			(int)user[i].accountType,
			login[i].loginID,
			login[i].loginPW,
			user[i].userName,
			user[i].phoneNum,
			user[i].borrowedBookCount
		);

		//최대 3권
		for (int j = 0; j < MAX_BORROWED_BOOKS; j++)
		{
			fprintf(userfp, "|%s", user[i].borrowedBooks[j]);
		}

		fprintf("userfp", "\n");
	}

	fclose(userfp);
	return DB_SUCCESS;
}

/*
* 함수명 : UserDatabaseAppend()
* 기능 : user.txt에 사용자 한명 추가
* 매개변수 : 사용자 구조체 배열, 로그인 구조체 배열, 배열의 마지막 인덱스
* 반환 값 : DBERROR
*/

DBERROR UserDatabaseAppend(const USER* user, const LOGIN* login)
{
	FILE* userfp = fopen("user.txt", "a");
	if (userfp == NULL)
	{
		return DB_FILE_NOT_FOUND;
	}

	fprintf(userfp, "%d|%s|%s|%s|%s|%u",
		(int)user->accountType,
		login->loginID,
		login->loginPW,
		user->userName,
		user->phoneNum,
		user->borrowedBookCount
	);

	for(int j = 0; j < MAX_BORROWED_BOOKS; j++)
	{
		fprintf(userfp, "|%s", user->borrowedBooks[j]);
	}

	fprintf(userfp, "\n");
	fclose(userfp);
	return DB_SUCCESS;
}

/*
* 함수명 : UserDatabaseLoad()
* 기능 : user login 구조체 배열 전체 user.txt에서 불러오기
* 매개변수 : 사용자 구조체 배열, 로그인 구조체 배열, max, count
* 반환 값 : DBERROR
*/

DBERROR UserDatabaseLoad(USER user[], LOGIN login[], int max, int* count)
{
	FILE* userfp = fopen("user.txt", "r");
	if (userfp == NULL)
	{
		*count = 0;
		return DB_FILE_NOT_FOUND;
	}

	char line[1024];
	int idx = 0;

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
				login[idx].accountType = (ACCOUNTTYPE)atoi(token);
				user[idx].accountType = login[idx].accountType;
				break;
			case 1: //loginID
				strncpy(login[idx].loginID, token, MAX_USER_ID_LENGTH);
				login[idx].loginID[MAX_USER_ID_LENGTH - 1] = '\0';
				break;
			case 2: //loginPW
				strncpy(login[idx].loginPW, token, MAX_USER_PASSWORD_LENGHTH);
				login[idx].loginPW[MAX_USER_PASSWORD_LENGHTH - 1] = '\0';
				break;
			case 3: //userName
				strncpy(user[idx].userName, token, MAX_USER_NAME_LENGTH);
				user[idx].userName[MAX_USER_NAME_LENGTH - 1] = '\0';
				break;
			case 4: //phoneNum
				strncpy(user[idx].phoneNum, token, MAX_PHONE_LENGTH);
				user[idx].phoneNum[MAX_PHONE_LENGTH - 1] = '\0';
				break;
			case 5: //borrowedBookCount
				user[idx].borrowedBookCount = (uint8_t)atoi(token);
				break;
			default: //borrowedBooks
				{
					int bookIndex = field - 6;
					if (0 <= bookIndex && bookIndex < MAX_BORROWED_BOOKS)
					{
						strncpy(user[idx].borrowedBooks[bookIndex], token, MAX_BOOK_ID_LENGTH);
						user[idx].borrowedBooks[bookIndex][MAX_BOOK_ID_LENGTH - 1] = '\0';
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
* 기능 : book.txt에 저장하는 함수
* 매개변수 : book 구조체 배열, 배열 마지막 인덱스
* 반환값 : 정수값
*/

//book.txt 형식 : bookID | bookName | writer | translator | bookStatus | maker
DBERROR BookDatabaseSave(BOOK book[],int lastnum)
{
	FILE* bookfp = fopen("book.txt","w");
	if (bookfp == NULL)
	{
		return DB_FILE_NOT_FOUND;
	}

	//파일 커서 옮기기
	fseek(bookfp, 0, SEEK_END);

	fprintf("%s | %s | %s | %s | %s | %s | %s\n",
		book[lastnum].bookID,
		book[lastnum].bookName,
		book[lastnum].writer,
		book[lastnum].translator,
		book[lastnum].bookStatus,
		book[lastnum].maker);

	printf("책 추가 완료.");
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
//borrow.txt 형식 : bookID | userID | borrowY | borrowM | borrowD | dueY | dueM | dueD | returnY | returnM | returnD | overdueDay


