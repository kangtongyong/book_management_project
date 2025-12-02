#ifndef LOGIN_H
#define LOGIN_H
#pragma once
#include "structs.h"
#define WRONGCOUNT_FAIL 10

/*
    *   로그인 관련 함수 선언 헤더 파일
    *
    *  반환값 :
    *      ACCOUNT_TYPE_ADMIN (1)      - 관리자 로그인 성공
    *      ACCOUNT_TYPE_USER  (0)      - 사용자 로그인 성공
    *      DB_FILE_NOT_FOUND  (-1)     - DB 파일을 열 수 없음(user.txt 등)
    *      DB_RECORD_NOT_FOUND(-4)     - 로그인 실패 (ID/PW 불일치)
*/

int testlogin(const char* id, const char* pw);
int signup(const char* id, const char* pw,
    const char* name, const char* phone);

#endif