%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "symbol_table.h"
	#include "code_generation.h"	

	#define BUFFER_SIZE 75

	void yyerror(const char* msg);
	extern int curr_line;
	extern int curr_pos;
	FILE * yyin;

	char* concat(const char *s1, const char *s2) {
		char* result = malloc(strlen(s1) + strlen(s2) + 1);
		strcpy(result, s1);
		strcat(result, s2);
		return result;
	}

	// Handles declarations that were split by commas
	void split_insert(const char* list, M_TYPE type) {
		char* ref = malloc(strlen(list) + 1);
		strcpy(ref, list);
		char* pch = strtok(ref, ",");
		while(pch != NULL) {
			insert(pch, type);
			pch = strtok(NULL, ",");
		}

	}

	void split_emit(char* list, M_TYPE type, int size) {
		char* ref = malloc(strlen(list) + 1);
		strcpy(ref, list);
		char* pch = strtok(ref, ",");
		while(pch != NULL) {
			if (type == m_int) { 
				sprintf(codestr, ". %s", pch);
				emitCode(codestr);
			} else {
				sprintf(codestr, ".[] %s, %d", pch, size);
				emitCode(codestr);
			}
			pch = strtok(NULL, ",");
		}
	}

	void reg_type_error(char* msg) {
		printf("TYPE ERROR (line %d): %s\n", curr_line, msg);
	}

	int checkType(M_TYPE t1, M_TYPE t2) {
		if (t1 == t2) return 1;
		return 0;
	}	
%}

%union {
	double dval;
	char* string_list;

	struct typeNode {
		char* name;
		int t;
		int size;
	} typeNode;	
}

%error-verbose
%token FUNCTION BEGIN_PARAMS END_PARAMS BEGIN_LOCALS END_LOCALS BEGIN_BODY END_BODY TYPE_INTEGER ARRAY OF IF THEN ENDIF ELSE WHILE DO BEGINLOOP ENDLOOP CONTINUE READ WRITE AND OR NOT TRUE FALSE RETURN SUB ADD MULT DIV MOD EQ NEQ LT GT LTE GTE SEMICOLON COLON COMMA L_PAREN R_PAREN L_SQUARE_BRACKET R_SQUARE_BRACKET ASSIGN
%start input
%token <dval> INTEGER
%token <string_list> IDENT
%type <string_list> identifier identifiers
%type <typeNode> declaration declaration_prime var expression boolexpr term relation_expr expressions multiplicative_expr multiplicative_exprs terms
%left ADD SUB
%left MULT DIV MOD
%nonassoc UMINUS
%%

input:			  {}
	 	| program {}
		;

program: functions {};
	   

functions: 	function { }
		 	| function functions {}			
			;

function: FUNCTION IDENT { printf("func %s\n", $2); } SEMICOLON BEGIN_PARAMS declarations END_PARAMS BEGIN_LOCALS declarations END_LOCALS BEGIN_BODY statements END_BODY {}
		;

declarations: 		{}
				| declaration SEMICOLON declarations {} 
				;

declaration: identifiers COLON declaration_prime { split_insert($1, $3.t); split_emit($1, $3.t, $3.size); };

declaration_prime: TYPE_INTEGER { $$.t = m_int; }
				 | ARRAY L_SQUARE_BRACKET INTEGER R_SQUARE_BRACKET OF TYPE_INTEGER { $$.t = m_array; $$.size = (int) $3; };

identifiers: identifier { $$ = $1; }
		   | identifier COMMA identifiers { $$ = concat($$, concat(",", $3)); } 
		   ;

identifier: IDENT { $$ = $1; };

statements:		statement SEMICOLON {}
		  		| statement SEMICOLON statements {}
				;

statement: var ASSIGN expression { if (fetch($1.name)) if (!checkType($1.t, $3.t)) reg_type_error("Mismatched assignment"); }
		 | RETURN expression { if (!checkType($2.t, m_int)) reg_type_error("Trying to return a non int type"); }
		 | CONTINUE { }
		 | IF boolexpr THEN statements else_prime ENDIF { if ($2.t != m_bool) reg_type_error("If statement does not contain a boolean expression"); }
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

var: identifier { $$.name = $1; $$.t = m_int; }
   | identifier L_SQUARE_BRACKET expression R_SQUARE_BRACKET { if (!checkType($3.t, m_int)) reg_type_error("Array access expression is not of type int");  else { $$.name = $1; $$.t = m_int; } };


expression:  multiplicative_expr multiplicative_exprs { if (!checkType($1.t, m_int)) reg_type_error("Expression uses non int types"); else $$.t = m_int; }
		  ;

multiplicative_exprs:  {}					
					| SUB multiplicative_expr multiplicative_exprs { if (!checkType($2.t, m_int)) reg_type_error("Expression uses non int types"); else $$.t = m_int; } 
					| ADD multiplicative_expr multiplicative_exprs { if (!checkType($2.t, m_int)) reg_type_error("Expression uses non int types"); else $$.t = m_int;}  
					;

multiplicative_expr: term terms { $$ = $1; }
					;

terms:	 {} 
	 | MULT term terms { if (!checkType($2.t, m_int)) reg_type_error("Expression uses non int types"); else $$ = $2; } 
	 | DIV term terms  { if (!checkType($2.t, m_int)) reg_type_error("Expression uses non int types"); else $$ = $2; }
	 | MOD term terms  { if (!checkType($2.t, m_int)) reg_type_error("Expression uses non int types"); else $$ = $2; }
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

relation_expr:  expression comp expression { if (!(checkType($1.t, $3.t) && checkType($1.t, m_int))) reg_type_error("Comparison does not compare two int expressions"); else $$.t = m_bool; } 
			 | TRUE { $$.t = m_bool; }
			 | FALSE { $$.t = m_bool; }
			 | L_PAREN boolexpr R_PAREN { $$.t = m_bool; }
			 | NOT expression comp expression { if (!(checkType($2.t, $4.t) && checkType($2.t, m_int))) reg_type_error("Comparison does not compare two int expressions"); else $$.t = m_bool;}
			 | NOT TRUE { $$.t = m_bool; }
			 | NOT FALSE { $$.t = m_bool; }
			 | NOT L_PAREN boolexpr R_PAREN { $$.t = m_bool; }
			 ;

term: var  { if (fetch($1.name)) $$.t = $1.t; }
	| INTEGER { $$.t = m_int; }
	| L_PAREN expression R_PAREN { if (!checkType($2.t, m_int)) reg_type_error("Expression is not an int type"); else $$.t = m_int; }
	| SUB var %prec UMINUS { $$.t = $2.t; }
	| SUB INTEGER %prec UMINUS { $$.t = m_int; }
	| SUB L_PAREN expression R_PAREN %prec UMINUS { if (!checkType($3.t, m_int)) reg_type_error("Expression is not an int type"); else $$.t = m_int; }
	| identifier L_PAREN expressions R_PAREN { $$.t = m_int; }
	;

expressions: expression { }
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

