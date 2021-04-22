/*
 * reporterror.c - ���� ���
 * programmer - ������, ���Ͽ�, ������
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
	case illsp : // ������ ���� ���ڰ� �� ���
		printf("%s Illegal Character", yytext);
		break;
	case illid : // ���ڷ� �����ϴ� IDENT�� ���
		printf("%s Illegal IDENT", yytext);
		break;
	case toolong : // 13�ڰ� �Ѿ�� IDENT�� ���
		printf("%s Too Long IDENT", yytext);
		break;
	case notallowed : // �߰��� ������ ���� ���ڰ� �� IDENT�� ���...
		for (int i = 0; i <= notallowed_i; i++) {
			printf("%c ", ST[notallowedposition[i]]);
		}
		printf("is not allowed");
		break;
	case overst : // String Table�� �����÷ο� �� ���
		printf("String Table OVERFLOW\n");
		exit(1); // ����??
	}

	printf("\n");
}