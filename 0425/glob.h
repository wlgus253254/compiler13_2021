/*
 * glob.h - global variable for the project
 * programmer - 김지현, 김하연, 정혜민
 * date -
 */

 // Symbol table 정의
#define STsize 1000 // size of string table

int nextid; // identifier의 첫글자가 있는 string table 인덱스
int nextfree; // identifier 직후 비어있는 string table 인덱스

char ST[STsize]; // string table

// 그 외 global 변수들
typedef enum _boolean {
	FALSE,
	TRUE
} boolean;
#define FALSE 0
#define TRUE 1

int lineNum; // line수를 세어주는 변수
enum tokentypes tn;
boolean STindex; // ST index를 출력하는 Identifier면 TRUE

enum errorTypes { illsp, illid, overst, notallowed, toolong }; //errortype 추가
typedef enum errorTypes ERRORtypes;
ERRORtypes err; // 에러타입 전역변수로 선언
int cErrors; // 에러 세는 변수

int notallowed_i; // notallowedpositon[] 인덱스
int notallowedposition[12]; // identifier에서 허용되지 않은 character의 string table의 인덱스를 저장