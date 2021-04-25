%{
/* scanner.l - lexical analyzer for the MiniC
 * programmer - 김지현, 김하연, 정혜민
 * data - 28/04/2021
 */

#include <stdio.h>
#include <stdlib.h>
#include "tn.h"		/*token name definition*/
#include "glob.h"	/* global variable*/
%}

A	[A-Za-z_]
D	[0-9]

%x	CMNT

%%

"+"			return(TPLUS);
"-"			return(TMINUS);
"*"			return(TSTAR);
"/"			return(TSLASH);
"%"			return(TMOD);
"="			return(TASSIGN);
"+="		return(TADDASSIGN);
"-="		return(TSUBASSIGN);
"*="		return(TMULASSIGN);
"/="		return(TDIVASSIGN);
"%="		return(TMODASSIGN);
"=="		return(TEQUAL);
"!="		return(TNOTEQU);
"<"			return(TLESS);
">"			return(TGREAT);
"<="		return(TLESSE);
">="		return(TGREATE);
"!"			return(TNOT);
"&&"		return(TAND);
"||"		return(TOR);
"++"		return(TINC);
"--"		return(TDEC);

"("			return(TLPARE);
")"			return(TRPARE);
"{"			return(TLCURLY);
"}"			return(TRCURLY);
"["			return(TLSQUARE);
"]"			return(TRSQUARE);
";"			return(TSEMI);
","			return(TCOMMA);


"const"		return(TCONST);
"else"		return(TELSE);
"if"		return(TIF);
"int"		return(TINT);
"return"	return(TRETURN);
"void"		return(TVOID);
"while"		return(TWHILE);

{A}({A}|{D})*				{ if (strlen(yytext) >= 13) { err = toolong; reporterror(); } else { SymbolTable(yytext); return(TIDENT); } }
{D}+{A}({A}|{D})*	{ err = illid; reporterror(); }


"//".*"\n"                { lineNum++; }
"/*".*"*/"              ;

"/*"                    { BEGIN CMNT; }
<CMNT>.              ;
<CMNT>"\n"         { lineNum++; }
<CMNT>"*/"           { BEGIN INITIAL; }
<CMNT><<EOF>>        { printf("ERROR!!\n"); }
					
{D}+"."{D}*					return(TFLOAT);
{D}+						return(TINTEGER);

[ \t]		;
"\n"	{ lineNum++; }

.	{ err = illsp; reporterror(); }
%%

int yywrap() { 
	return 1; 
}
