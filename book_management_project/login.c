#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "login.h"
#include "structs.h"
#define MEMBER_NUMBER 3
#define WRONGCOUNT_FAIL 10

//	로그인 관련 함수



//	testlogin 테스트용
int main()
{

	// 함수 출력 테스트 용
	int result = testlogin();

	if (result == ACCOUNT_TYPE_ADMIN)
	{
		printf("[시스템 접근 권한: 관리자 모드]\n");
	}

	else if (result == ACCOUNT_TYPE_USER)
	{
		printf("[시스템 접근 권한: 사용자 모드]\n");
	}

	else if (result == -1)
	{
		printf("[너무 많은 로그인 실패로 접속 차단 되었습니다.]\n");
	}

	else
	{
		printf("\n[UNKNOWN ERRER !!]\n");
	}

	return 0;
}


//	로그인 함수
int testlogin(void)
{

	//	보안코드 생성용 초기화
	srand((unsigned int)time(NULL));


	//	임시 로그인 정보
	LOGIN logininfo[MEMBER_NUMBER] =
	{
		{ACCOUNT_TYPE_ADMIN, "admin", "adminpass"},
		{ACCOUNT_TYPE_ADMIN, "9999", "99999999"},
		{ACCOUNT_TYPE_USER, "user1", "12345678"}
	};

	//	id와 pw 저장 변수
	char id[MAX_USER_ID_LENGTH];
	char pw[MAX_USER_PASSWORD_LENGHTH];

	//	잘못된 로그인 시도 저장 
	int wrongcount = 0;


	//	무한루프를 돌면서 아이디와 비밀번호를 입력받고 확인
	while (1)
	{

		if (wrongcount < 3)
		{
			//	아이디와 비밀번호 입력
			printf("\n아이디와 비밀번호를 입력하세요.\n");

			printf("ID: ");
			scanf("%28s", id);

			printf("Password: ");
			scanf("%48s", pw);
		}
		else
		{
			// 일정 시도 초과
			if (WRONGCOUNT_FAIL <= wrongcount)
			{
				printf("\n너무 많은 잘못된 로그인 시도입니다.\n프로그램을 종료합니다.\n");
				return -1;
			}


			//	랜덤 난수 보안 코드 생성
			int secret_code = rand() % 10000;

			//	코드 입력 변수
			int input_code = 0;

			printf("\n--%d회 이상 로그인을 실패하셨습니다.--\n10회 이상 로그인 실패시 로그인이 금지됩니다.\n", wrongcount);

			printf("ID: ");
			scanf("%28s", id);

			printf("Password: ");
			scanf("%48s", pw);

			// 보안 코드 제시 및 입력
			printf("다음 보안 코드를 입력하세요: %04d\n", secret_code);
			printf("보안 코드 네자리 입력: ");
			scanf("%4d", &input_code);


			// 보안 코드 검사 불일치
			if (input_code != secret_code)
			{

				printf("\n보안 코드가 일치하지 않습니다. 다시 시도하세요.\n\n");
				wrongcount++;
				continue;

			}

			// 보안 코드 검사 일치
			else
			{
				printf("\n보안 코드 일치.\n");
			}

		}

		//	반복문을 통한 비교
		for (int i = 0; i < MEMBER_NUMBER; i++)
		{

			//	아이디, 비밀번호 확인
			if (strcmp(id, logininfo[i].loginID) == 0 && strcmp(pw, logininfo[i].loginPW) == 0)
			{
				//	관리자
				if (logininfo[i].accountType == ACCOUNT_TYPE_ADMIN)
				{
					printf("\n관리자 %s님 환영합니다.\n", logininfo[i].loginID);
					wrongcount = 0;
					return logininfo[i].accountType;
				}

				//	사용자
				else
				{
					printf("\n사용자 %s님 환영합니다.\n", logininfo[i].loginID);
					wrongcount = 0;
					return logininfo[i].accountType;
				}
			}

		}

		//	로그인 실패
		printf("로그인 실패 : 아이디 또는 비밀번호가 잘못되었습니다.\n\n");
		wrongcount++;
	}
}