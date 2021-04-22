/*
 * reporterror.c - 에러 출력
 * programmer - 김지현, 김하연, 정혜민
 * date - 
 */


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tn.h"
#include "glob.h"

extern char* yytext;

void reporterror() {
	cErrors++;
	notallowed_i = -1;
	printf("%d\t\t", lineNum);
	printf("**ERROR**\t\t\t\t\t");

	switch (err) {
	case illsp : // 허용되지 않은 문자가 들어간 경우
		printf("%s Illegal Character", yytext);
		break;
	case illid : // 숫자로 시작하는 IDENT의 경우
		printf("%s Illegal IDENT", yytext);
		break;
	case toolong : // 13자가 넘어가는 IDENT의 경우
		printf("%s Too Long IDENT", yytext);
		break;
	case notallowed : // 중간에 허용되지 않은 문자가 들어간 IDENT의 경우...
		for (int i = 0; i <= notallowed_i; i++) {
			printf("%c ", ST[notallowedposition[i]]);
		}
		printf("is not allowed");
		break;
	case overst : // String Table이 오버플로우 된 경우
		printf("String Table OVERFLOW\n");
		exit(1); // 종료??
	}

	printf("\n");
}