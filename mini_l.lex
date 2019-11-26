%{
	#include "y.tab.h"
	#include "stdlib.h"
	int curr_line = 1;
	int curr_col = 0;
%}

LETTER [a-z]|[A-Z]
NUMBER [0-9]
CHARS [_]


%%
function {curr_col += yyleng; return FUNCTION;}
beginparams {curr_col += yyleng; return BEGIN_PARAMS;}
endparams {curr_col += yyleng; return END_PARAMS;}
beginlocals {curr_col += yyleng; return BEGIN_LOCALS;}
endlocals {curr_col += yyleng; return END_LOCALS;}
beginbody {curr_col += yyleng; return BEGIN_BODY;}
endbody {curr_col += yyleng; return END_BODY;}
integer {curr_col += yyleng; return TYPE_INTEGER;}
array {curr_col += yyleng; return ARRAY;}
of {curr_col += yyleng; return OF;}
if {curr_col += yyleng; return IF;}
then {curr_col += yyleng; return THEN;}
endif {curr_col += yyleng; return ENDIF;}
else {curr_col += yyleng; return ELSE;}
while {curr_col += yyleng; return WHILE;}
do {curr_col += yyleng; return DO;}
beginloop {curr_col += yyleng; return BEGINLOOP;}
endloop {curr_col += yyleng; return ENDLOOP;}
continue {curr_col += yyleng; return CONTINUE;}
read {curr_col += yyleng; return READ;}
write {curr_col += yyleng; return WRITE;}
and {curr_col += yyleng; return AND;}
or {curr_col += yyleng; return OR;}
not {curr_col += yyleng; return NOT;}
true {curr_col += yyleng; return TRUE;}
false {curr_col += yyleng; return FALSE;}
return {curr_col += yyleng; return RETURN;}

\- {curr_col += yyleng; return SUB;}
\+ {curr_col += yyleng; return ADD;}
\* {curr_col += yyleng; return MULT;}
\/ {curr_col += yyleng; return DIV;}
% {curr_col += yyleng; return MOD;}

\=\= {curr_col += yyleng; return EQ;}
\<\> {curr_col += yyleng; return NEQ;}
\< {curr_col += yyleng; return LT;}
\> {curr_col += yyleng; return GT;}
\<\= {curr_col += yyleng; return LTE;}
\>\= {curr_col += yyleng; return GTE;}

{NUMBER}+ {yylval.dval = atoi(yytext); curr_col += yyleng; return INTEGER;}

{LETTER}({LETTER}|{NUMBER}|{CHARS})*_ {printf("Error at line %d, column %d: identifier \"%s\" cannot end with an underscore\n", curr_line, curr_col, yytext); return 1;} 

{LETTER}({LETTER}|{NUMBER}|{CHARS})* {yylval.string_list = strndup(yytext, yyleng); curr_col += yyleng; return IDENT;}

{NUMBER}({LETTER}|{NUMBER}|{CHARS})+ {printf("Error at line %d, column %d: identifier \"%s\" must begin with a letter\n", curr_line, curr_col, yytext); return 1;}


";" {curr_col += yyleng; return SEMICOLON;}
\: {curr_col += yyleng; return COLON;}
\, {curr_col += yyleng; return COMMA;}
\( {curr_col += yyleng; return L_PAREN;}
\) {curr_col += yyleng; return R_PAREN;}
"\[" {curr_col += yyleng; return L_SQUARE_BRACKET;}
"\]" {curr_col += yyleng; return R_SQUARE_BRACKET;}
\:\= {curr_col += yyleng; return ASSIGN;}

##.*\n {curr_col += yyleng; curr_line++;}

[ \t] {curr_col += yyleng;}

"\n" {curr_col = 0; curr_line++;}

. {printf("Error at line %d, column %d: unrecognized symbol \"%s\"\n", curr_line, curr_col, yytext); return 1;}
%%

