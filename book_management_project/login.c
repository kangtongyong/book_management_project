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
    
    int max = userCount;
    int count = 0;
    //  user.txt 에서 로그인 정보 로드

    DBERROR err = UserDatabaseLoad(max, &count);
    if (err != DB_SUCCESS || count <= 0)
    {
        // 파일이 없거나, 유저 데이터가 없는 경우
        return DB_FILE_NOT_FOUND;           //  -1 반환
    }

    //  ID / PW 비교
    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(id, logins[i].loginID) == 0 &&
            strcmp(pw, logins[i].loginPW) == 0)
        {
            MoveCursor(31, 24);

            //  관리자
            if (logins[i].accountType == ACCOUNT_TYPE_ADMIN)
            {
                return logins[i].accountType;    // 1 반환
            }
            //  사용자
            else
            {
                return logins[i].accountType;    // 0 반환
            }
        }
    }

    //  로그인 실패
    return DB_RECORD_NOT_FOUND;                 // -4
}

/*
* 함수명 : signup()
* 기능 : 회원가입 기능
* 매개변수 : 없음
* 반환값 : 없음
*/

int signup(const char * id, const char * pw,
            const char * name, const char * phone)
{
    FILE* fp;
    char line[512];
    
    //ID 중복 검사

    fp = fopen("user.txt", "r");
    if (fp != NULL)
    {
        while (fgets(line, sizeof(line), fp) != NULL)
        {
            char* token;
            int field = 0;
            char existId[MAX_USER_ID_LENGTH] = { 0 };

            // 줄 끝 개행 제거
            line[strcspn(line, "\r\n")] = '\0';

            token = strtok(line, "|");
            while (token != NULL)
            {
                // 앞뒤 공백 제거 (database.c와 동일 스타일)
                while (*token == ' ') token++;
                char* end = token + strlen(token) - 1;
                while (end > token && (*end == ' '))
                {
                    *end = '\0';
                    end--;
                }

                if (field == 1)   // 두 번째 필드가 ID
                {
                    strncpy(existId, token, MAX_USER_ID_LENGTH - 1);
                    existId[MAX_USER_ID_LENGTH - 1] = '\0';
                    break;
                }

                field++;
                token = strtok(NULL, "|");
            }

            if (strcmp(existId, id) == 0)
            {
                // 이미 같은 ID가 존재
                fclose(fp);
                return DB_DUPLICATE_RECORD;
            }

        }
        fclose(fp);
    }
    //fp == NULL 일 경우 user.txt 없기에 검사 생략

    fp = fopen("user.txt", "a");
    if (fp == NULL)
    {
        return DB_FILE_NOT_FOUND;
    }

    fprintf(fp, "%d|%s|%s|%s|%s|0|||\n",
        (int)ACCOUNT_TYPE_USER,
        id,
        pw,
        name,
        phone
    );

    fclose(fp);

    return DB_SUCCESS;
}