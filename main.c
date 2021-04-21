/*
main.c - �� token�� ���� ���
programmer - �����Ϸ� ��13
date - 2021.04.19
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tn.h"
//#include "global.h"
extern yylex();
extern char *yytext; // &yytext[0]

#define STsize 1000 // size of string table

typedef enum _boolean {
	FALSE,
	TRUE
} boolean;
#define FALSE 0
#define TRUE 1

enum errorTypes { noerror, illsp, illid, overst, notallowed, toolong }; //errortype �߰�
typedef enum errorTypes ERRORtypes;
ERRORtypes err; // ����Ÿ�� ���������� ����

int nextid = 0; // identifier�� ù���ڰ� �ִ� string table �ε���
int nextfree = 0; // identifier ���� ����ִ� string table �ε���
int notallowed_i = -1; // notallowedpositon[] �ε���
int notallowedposition[12] = { -1 }; // identifier���� ������ ���� character�� string table�� �ε����� ����

char seperators[] = ".,;:?!\t\n "; // ���� �߰�
char ST[STsize]; // string table

int cErrors = 0; // detected Error�� ����
int lineNum = 1; // Line Number�� ����


/*
PrintError - ���� ��� �Լ�
*/
void PrintError() {
	printf("...Error...\t\t\t\t");
	cErrors++;
	switch (err)
	{
	case overst: // string table�� �����÷ο�
		// ���� characters ���ڸ� ������ ���� ������ ������ �ٲ۴�.
		nextfree = nextid - 1;
		printf("String table OVERFLOW");
		exit(0);
		break;
	case notallowed:  // ���������� character�� ������� ��
		nextfree = nextid; // �ε����� string table���� ������ ��ó�� ó��
		for (int i = 0; i <= notallowed_i; i++) {
			printf("%c ", ST[notallowedposition[i]]);
		}
		printf("is not allowed");
		break;
	case illid: // identifier�� ���ڷ� ������ ��
		printf("%s is illegal seperator\n", yytext);
		break;
	case toolong: // identifier�� 12�ڸ� �Ѿ ��
		nextfree = nextid; // �ε����� string table���� ������ ��ó�� ó��
		printf("too long identifier");
		break;
	case illsp: // ���� seperator�� ��
		printf("%s is illegal seperator\n", yytext);
		break;
	default:
		break;
	}
	err = noerror;
}

/*
isSeperator - seperator���� �������ִ� �Լ�,  seperator�� TRUE�� ��ȯ
*/
int isSeperator(char c) {
	for (int i = 0; i < strlen(seperators); i++) {
		if (c == seperators[i])
			return TRUE;
	}
	return FALSE;
}

/*
* checkIdentifier - string table�� �� identifier �˻�
������ ���� character�� ������ notallowed, err ����
*/
void checkIdentifier() {
	for (int i = nextid; i < nextfree; i++) {
		// ������ ���� character�� �ε����� notallowedposition[]�� ����
		if (!isSeperator(ST[i])) {
			notallowed_i++;
			notallowedposition[notallowed_i] = i;
		}
	}
	if (notallowed_i > -1) { // ������ ���� character�� �ϳ��� ������ notallowed ���� �߻�
		err = notallowed;
		PrintError(err);
	}
}

/*
printtoken() - token type ���� ���
Line number, Type, ST index, Token
*/
void printtoken(enum tnumber tn) {
	boolean STindex = TRUE; // ST index�� ����ϴ� Identifier�� TRUE
	if (isSeperator(yytext)) STindex = FALSE;
	// print Token type
	switch (tn) {
		// comments
	case TSCOM: printf("small comment"); break;
	case TLCOM: printf("left comment"); break;
	case TRCOM: printf("rignt comment"); break;
		// indentifiers
	case TLETTER: printf("letter"); break;
	case TDIGIT: printf("digit"); break;
	case TIDENT: printf("identifier"); break;
		// numbers
	case TDECIMAL: printf("demimal number"); break;
	case TFIXNUM: printf("fixed-point number"); break;
		// operators
	case TPLUS: printf("plus"); break;
	case TMINUS: printf("minus"); break;
	case TSTAR: printf("multifly"); break;
	case TSLASH: printf("divide"); break;
	case TMOD: printf("remainder"); break;
	case TASSIGN: printf("assign"); break;
	case TPLUSAS: printf("plus assign"); break;
	case TMINUSAS: printf("minus assign"); break;
	case TSTARAS: printf("multifly assign"); break;
	case TSLASHAS: printf("divide assign"); break;
	case TMODAS: printf("remainder assign"); break;
	case TNOT: printf("not"); break;
	case TAND: printf("and"); break;
	case TOR: printf("or"); break;
	case TEQUAL: printf("equal"); break;
	case TNOTEQU: printf("not equal"); break;
	case TRIGHTBIG: printf("rignt big"); break;
	case TLEFTBIG: printf("left big"); break;
	case TRIGHTBEQ: printf("rignt big equal"); break;
	case TLEFTBEQ: printf("left big equal"); break;
	case TINC: printf("increase"); break;
	case TDEC: printf("decrease"); break;
		// keywords
	case TCONST: printf("const"); break;
	case TELSE: printf("else"); break;
	case TIF: printf("if"); break;
	case TINT: printf("int"); break;
	case TRETURN: printf("return"); break;
	case TVOID: printf("void"); break;
	case TWHILE: printf("while"); break;
		// Special Symbols
	case TLPARE: printf("left parenthesis"); break;
	case TRPARE: printf("rignt parenthesis"); break;
	case TCOMMA: printf("comma"); break;
	case TLCURLY: printf("left curly brace"); break;
	case TRCURLY: printf("rignt curly brace"); break;
	case TLSQUARE: printf("left square bracket"); break;
	case TRSQUARE: printf("rignt square bracket"); break;
	case TSEMICOL: printf("semicolon"); break;
		// White spaces
	case TBLANK: printf("blank"); break;
	case TTAB: printf("tab"); break;
	case TNEWLINE: printf("new line"); lineNum++;  break;
	default: printf("default"); break;
	}
	// print ST-index
	if (STindex) printf("\t\t%d\t\t", nextfree);
	else printf("\t\t\t\t");
	// print Token
	printf("%s \n", yytext); // %d, atoi(yytext)
}

/*
ReadID() - identifier�� �д� �Լ�
*/
void ReadID() {
	nextid = nextfree;
	int slen = strlen(yytext);
	// Error detection - toolong
	if (slen > 12) {
		err = toolong;
		PrintError();
		return;
	}
	// Error detection - Overflow
	if (nextfree >= STsize) {
		err = overst;
		PrintError();
		return;
	}
	// String table �Է�
	for (int i = 0; i < slen; i++) {
		ST[nextfree++] = &yytext[i];
	}
	// \0�� ST�� �Է�x �̸�
	ST[nextfree++] = '\0';

	checkIdentifier();
}

void main()
{ 
	enum tnumber tn; /* token number */

	// print header
	printf("\n\n-------------------\n");
	printf("Index in ST\tidentifier");
	printf("\n-------------------\n\n");
	printf("Line number\t\tToken type\t\tST-index\t\tToken\n");

	while( (tn = yylex()) != TEOF) {
		// print Line number
		printf("%d\t\t\t", lineNum);
		// detect Error...
		// skip seperators...
		// Save to ST...
		ReadID();
		// ���� �ʱ�ȭ
		err = noerror;
		notallowed_i = -1;
		// Print token...
		printtoken(tn);
	}

	// print footer
	printf("\n\n*****\n\n");
	if (cErrors == 0) printf("No errors detected");
	else printf("%d errors detected", cErrors);

	return;
}