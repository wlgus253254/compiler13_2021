/*
 * main.c - �� token�� ���� ���
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

extern yylex();
extern char* yytext;

void printtoken(enum tnumber tn) {

	// print Token type
	switch (tn) {
	case TIDENT: printf("identifier\t"); break;
	// numbers
	case TINTEGER: printf("demimal number\t"); break;
	case TFLOAT: printf("fixed-point number"); break;
	// operators
	case TPLUS: printf("plus\t\t"); break;
	case TMINUS: printf("minus\t\t"); break;
	case TSTAR: printf("multifly\t"); break;
	case TSLASH: printf("divide\t\t"); break;
	case TMOD: printf("remainder\t"); break;
	case TASSIGN: printf("assign\t\t"); break;
	case TADDASSIGN: printf("plus assign\t"); break;
	case TSUBASSIGN: printf("minus assign\t"); break;
	case TMULASSIGN: printf("multifly assign\t"); break;
	case TDIVASSIGN: printf("divide assign\t"); break;
	case TMODASSIGN: printf("remainder assign\t"); break;
	case TNOT: printf("not\t\t"); break;
	case TAND: printf("and\t\t"); break;
	case TOR: printf("or\t\t"); break;
	case TEQUAL: printf("equal\t\t"); break;
	case TNOTEQU: printf("not equal\t"); break;
	case TLESS: printf("rignt big\t"); break;
	case TGREAT: printf("left big\t"); break;
	case TLESSE: printf("rignt big equal\t"); break;
	case TGREATE: printf("left big equal\t"); break;
	case TINC: printf("increase\t"); break;
	case TDEC: printf("decrease\t"); break;
		// keywords
	case TCONST: printf("const\t\t"); break;
	case TELSE: printf("else\t\t"); break;
	case TIF: printf("if\t\t"); break;
	case TINT: printf("int\t\t"); break;
	case TRETURN: printf("return\t\t"); break;
	case TVOID: printf("void\t\t"); break;
	case TWHILE: printf("while\t\t"); break;
		// Special Symbols
	case TLPARE: printf("left parenthesis"); break;
	case TRPARE: printf("rignt parenthesis"); break;
	case TCOMMA: printf("comma\t\t"); break;
	case TLCURLY: printf("left curly brace"); break;
	case TRCURLY: printf("rignt curly brace"); break;
	case TLSQUARE: printf("left square bracket"); break;
	case TRSQUARE: printf("rignt square bracket"); break;
	case TSEMI: printf("semicolon\t"); break;
	}
	// print ST-index
	if (STindex) { printf("\t\t%d\t\t", nextid); nextid = nextfree + 1; }
	else printf("\t\t\t\t");
	// print Token
	printf("%s \n", yytext); // %d, atoi(yytext)
} 

void main() {
	// ���� �ʱ�ȭ
	for (int i = 0; i < 12; i++) { 
		notallowedposition[i] = -1;
	}
	STindex = FALSE;
	lineNum = 1;

	printf("Line number\tToken type\t\t\tST-index\tToken\n"); // ��� ���

	while ((tn = yylex()) != TEOF) {
		printf("%d\t\t", lineNum);
		printtoken(tn);
		STindex = FALSE;
	}

	if (cErrors == 0) printf("No erros detected\n");
	else printf("%d errors detected\n", cErrors);
}

/*
	1 a#a�� ��� ��� ���� ������ ����ؾߵǴ���
	2 ST�� �����÷ο찡 �߻��ϸ� �����ؾ��ϴ���
	3 "�� '�� ��ū���� �߰��ؾ��ϴ��� (testdata5.dat)
	4 �ּ��� ��ū���� ���������ϴ���
	5 �� �߰��� ��ū�̳� ������ �ִ���
	6 �� �� �ּ� date,, ����׾�� 8��8..
*/