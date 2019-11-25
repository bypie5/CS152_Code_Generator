%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "symbol_table.h"
	
	#define BUFFER_SIZE 25

	void yyerror(const char* msg);
	extern int curr_line;
	extern int curr_pos;
	FILE * yyin;

	// Used to add a null-terminator to $<n>
	char* stringify(char* s) {
		char* key = malloc(sizeof(char)*BUFFER_SIZE);
		sprintf(key, "%s", s);
		return key;
	}
%}

%union {
	double dval;
	char* string_list;	
}

%error-verbose
%token FUNCTION BEGIN_PARAMS END_PARAMS BEGIN_LOCALS END_LOCALS BEGIN_BODY END_BODY INTEGER ARRAY OF IF THEN ENDIF ELSE WHILE DO BEGINLOOP ENDLOOP CONTINUE READ WRITE AND OR NOT TRUE FALSE RETURN SUB ADD MULT DIV MOD EQ NEQ LT GT LTE GTE SEMICOLON COLON COMMA L_PAREN R_PAREN L_SQUARE_BRACKET R_SQUARE_BRACKET ASSIGN
%start input
%token <dval> NUMBER
%token <string_list> IDENT
%type <string_list> identifier
%left ADD SUB
%left MULT DIV MOD
%nonassoc UMINUS

%%
input:			  {}
	 	| program {}
		;

program: functions {};
	   

functions: 	function {}
		 	| function functions {}			
			;

function: FUNCTION IDENT SEMICOLON BEGIN_PARAMS declarations END_PARAMS BEGIN_LOCALS declarations END_LOCALS BEGIN_BODY statements END_BODY {}
		;

declarations: 		{}
				| declaration SEMICOLON declarations {}
				;

declaration: identifiers COLON declaration_prime {};

declaration_prime: INTEGER { insert(stringify($1), m_int); }
				 | ARRAY L_SQUARE_BRACKET NUMBER R_SQUARE_BRACKET OF INTEGER { insert(stringify($1), m_array); };

identifiers: identifier {}
		   | identifier COMMA identifiers {}
		   ;

identifier: IDENT { };

statements:		statement SEMICOLON {}
		  		| statement SEMICOLON statements {}
				;

statement: var ASSIGN expression {}
		 | RETURN expression {}
		 | CONTINUE {}
		 | IF boolexpr THEN statements else_prime ENDIF {}
		 | WHILE boolexpr BEGINLOOP statements ENDLOOP {}
		 | DO BEGINLOOP statements ENDLOOP WHILE boolexpr {}
		 | READ vars {}
		 | WRITE vars {}
		 ;

else_prime:		{} 
		  |	ELSE statements	{}		
		  ;

vars: 	var {}
	|	var COMMA vars {}
	;

comp: EQ	{}
	| NEQ 	{}
	| LT 	{}
	| GT	{}
	| LTE	{}
	| GTE	{}
	;

var: identifier {}
   	| identifier L_SQUARE_BRACKET expression R_SQUARE_BRACKET {};

expression: multiplicative_expr multiplicative_exprs {}
		  ;

multiplicative_exprs:	{} 
					| SUB multiplicative_expr multiplicative_exprs {} 
					| ADD multiplicative_expr multiplicative_exprs {} 

					;

multiplicative_expr: term terms {}
					;

terms:	{} 
	 | MULT term terms {}
	 | DIV term terms {}
	 | MOD term terms {} 
	 ;

boolexpr: relation_and_expr r_a_es {}
		;

r_a_es: 	{}
	  |  OR relation_and_expr r_a_es {}
	  ;

relation_and_expr: relation_expr r_es {} 
				 ;

r_es: 	{}
	| AND relation_expr r_es {}
	;

relation_expr:  expression comp expression {}
			 | TRUE {}
			 | FALSE {}
			 | L_PAREN boolexpr R_PAREN {}
			 | NOT expression comp expression {}
			 | NOT TRUE {}
			 | NOT FALSE {}
			 | NOT L_PAREN boolexpr R_PAREN {}
			 ;

term: var  {}
	| NUMBER {}
	| L_PAREN expression R_PAREN {}
	| SUB var %prec UMINUS {}
	| SUB NUMBER %prec UMINUS {}
	| SUB L_PAREN expression R_PAREN %prec UMINUS {}
	| identifier L_PAREN expressions R_PAREN {}
	;

expressions: expression {}
		   | expression expressions COMMA {}
		   ;

%%


int main(int argc, char** argv) {
	if (argc > 1) {
		yyin = fopen(argv[1], "r");
		if (yyin == NULL) {
			printf("usage: %s filename\n", argv[0]);
		}
	}
	yyparse();
	print();
	return 0;
}

void yyerror(const char* msg) {
	printf("Syntax error at line %d: %s\n", curr_line, msg);
}

