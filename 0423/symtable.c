/*
 * symtable.c - symmbol table °ü¸®
 * programmer - ±èÁöÇö, ±èÇÏ¿¬, Á¤Çý¹Î
 * date - 
 */


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tn.h"
#include "glob.h"

extern char *yytext;

void overST() {
	if (nextfree == STsize) {
		err = overst;
		reporterror();
	}
}

void SymbolTable(char* text) {
	overST();
	for (unsigned int i = 0; i < strlen(text); i++) { ST[nextfree++] = text[i]; }
	STindex = TRUE;
}