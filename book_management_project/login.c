#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "login.h"
#include "structs.h"
#include "database.h"
#include "assistant.h"


//  로그인 관련 함수


/*
    함수명   :   testlogin()
    기능 :  DisplayLogin()에서 전달받은 ID, PW를 DB에서 검사,
            로그인 성공 여부 및 계정 타입/에러 코드를 반환하는 함수
    매개변수 :  const char* id  - 입력받은 아이디
                const char* pw  - 입력받은 비밀번호
    반환값:     ACCOUNT_TYPE_ADMIN (1)      관리자 로그인 성공
                ACCOUNT_TYPE_USER  (0)      사용자 로그인 성공
                DB_FILE_NOT_FOUND  (-1)     DB 파일을 열 수 없음
                DB_RECORD_NOT_FOUND(-4)     로그인 실패
*/
int testlogin(const char* id, const char* pw)
{
    int usercount = 0;       // 실제로 로드된 사용자 수

    //  user.txt 에서 로그인 정보 로드
    DBERROR err = UserDatabaseLoad(userCount, &usercount);
    if (err != DB_SUCCESS || usercount <= 0)
    {
        // 파일이 없거나, 유저 데이터가 없는 경우
        return DB_FILE_NOT_FOUND;           //  -1 반환
    }

    //  ID / PW 비교
    for (int i = 0; i < usercount; i++)
    {
        if (strcmp(id, logins[i].loginID) == 0 &&
            strcmp(pw, logins[i].loginPW) == 0)
        {
            MoveCursor(31, 24);
            printf("                                                    ");
            MoveCursor(31, 24);

            //  관리자
            if (logins[i].accountType == ACCOUNT_TYPE_ADMIN)
            {
                printf("\n관리자 %s님 환영합니다.\n", logins[i].loginID);
                return logins[i].accountType;    // 1 반환
            }
            //  사용자
            else
            {
                printf("\n사용자 %s님 환영합니다.\n", logins[i].loginID);
                return logins[i].accountType;    // 0 반환
            }
        }
    }

    //  로그인 실패
    return DB_RECORD_NOT_FOUND;                 // -4
}
