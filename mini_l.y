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
	int type;	
}

%error-verbose
%token FUNCTION BEGIN_PARAMS END_PARAMS BEGIN_LOCALS END_LOCALS BEGIN_BODY END_BODY TYPE_INTEGER ARRAY OF IF THEN ENDIF ELSE WHILE DO BEGINLOOP ENDLOOP CONTINUE READ WRITE AND OR NOT TRUE FALSE RETURN SUB ADD MULT DIV MOD EQ NEQ LT GT LTE GTE SEMICOLON COLON COMMA L_PAREN R_PAREN L_SQUARE_BRACKET R_SQUARE_BRACKET ASSIGN
%start input
%token <dval> INTEGER
%token <string_list> IDENT
%type <string_list> identifier identifiers 
%type <type> declaration_prime term terms var expression expressions relation_expr multiplicative_expr multiplicative_exprs
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

declaration: identifiers COLON declaration_prime { modify_attr_type(stringify($1), $3); };

declaration_prime: TYPE_INTEGER { $$ = m_int; }
				 | ARRAY L_SQUARE_BRACKET INTEGER R_SQUARE_BRACKET OF TYPE_INTEGER { $$ = m_array; };

identifiers: identifier { insert(stringify($1)); }
		   | identifier COMMA identifiers { insert(stringify($1)); } 
		   ;

identifier: IDENT { $$ = stringify($1); };

statements:		statement SEMICOLON {}
		  		| statement SEMICOLON statements {}
				;

statement: var ASSIGN expression { if ($1 != $3) printf("TYPE ERROR line %d\n", curr_line); }
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

var: identifier { if (fetch($1)) $$ = fetch($1)->type; else printf("UNDEFINED SYMBOL line %d: %s\n", curr_line, $1); }
   	| identifier L_SQUARE_BRACKET expression R_SQUARE_BRACKET { if(fetch($1)) $$ = fetch($1)->type; else printf("UNDEFINED SYMBOL line %d: %s\n", curr_line, $1); };

expression:  multiplicative_expr multiplicative_exprs { $$ = $1; }
		  ;

multiplicative_exprs:  {}					
					| SUB multiplicative_expr multiplicative_exprs { $$ = $2; if ($2 != m_int) printf("TYPE ERROR line %d\n", curr_line); } 
					| ADD multiplicative_expr multiplicative_exprs { $$ = $2; if ($2 != m_int) printf("TYPE ERROR line %d\n", curr_line); }  
					;

multiplicative_expr: term terms { $$ = $1; }
					;

terms:	 {} 
	 | MULT term terms { $$ = $2; if ($2 != m_int) printf("TYPE ERROR line %d\n", curr_line); } 
	 | DIV term terms { $$ = $2; if ($2 != m_int) printf("TYPE ERROR line %d\n", curr_line); }
	 | MOD term terms { $$ = $2; if ($2 != m_int) printf("TYPE ERROR line %d\n", curr_line); }
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

relation_expr:  expression comp expression { if ($1 != $3) printf("TYPE ERROR line %d\n", curr_line);}
			 | TRUE {}
			 | FALSE {}
			 | L_PAREN boolexpr R_PAREN {}
			 | NOT expression comp expression {}
			 | NOT TRUE {}
			 | NOT FALSE {}
			 | NOT L_PAREN boolexpr R_PAREN {}
			 ;

term: var  { $$ = $1; }
	| INTEGER { $$ = m_int; }
	| L_PAREN expression R_PAREN { $$ = $2; }
	| SUB var %prec UMINUS { $$ = $2; }
	| SUB INTEGER %prec UMINUS { $$ = m_int; }
	| SUB L_PAREN expression R_PAREN %prec UMINUS { $$ = $3; }
	| identifier L_PAREN expressions R_PAREN { $$ = m_int; }
	;

expressions: expression { $$ = $1; }
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
	return 0;
}

void yyerror(const char* msg) {
	printf("Syntax error at line %d: %s\n", curr_line, msg);
}

