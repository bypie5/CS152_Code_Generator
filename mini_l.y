%{
	#include <stdio.h>
	#include <stdlib.h>
	void yyerror(const char* msg);
	extern int curr_line;
	extern int curr_pos;
	FILE * yyin;
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
input:			  {printf("input -> epsilon\n");}
	 	| program {printf("input -> program\n");}
		;

program: functions {printf("program -> functions\n");};

functions: 	function {printf("functions -> function\n");}
		 	| function functions {printf("functions -> function function\n");}
			;

function: FUNCTION IDENT SEMICOLON BEGIN_PARAMS declarations END_PARAMS BEGIN_LOCALS declarations END_LOCALS BEGIN_BODY statements END_BODY {printf("function -> FUNCTION IDENT SEMICOLON BEGIN_PARAMS declarations END_PARAMS BEGIN_LOCALS declarations END_LOCALS BEGIN_BODY statements END_BODY\n");}
		;

declarations: 		{printf("declarations -> epsilon\n");}
				| declaration SEMICOLON declarations {printf("declarations -> declaration SEMICOLON declarations\n");}
				;

declaration: identifiers COLON declaration_prime {printf("declaration -> identifiers COLON declaration_prime\n");};

declaration_prime: INTEGER {printf("declaration_prime -> INTEGER\n");}
				 | ARRAY L_SQUARE_BRACKET NUMBER R_SQUARE_BRACKET OF INTEGER {printf("declaration_prime -> ARRAY L_SQUARE_BRACKET NUMBER R_SQUARE_BRACKET OF INTEGER\n");};

identifiers: identifier {printf("identifiers -> identifier\n");}
		   | identifier COMMA identifiers {printf("identifiers -> identifier COMMA identifiers\n");}
		   ;

identifier: IDENT {printf("identifier -> IDENT_%s\n", $1);};

statements:		statement SEMICOLON {printf("statements -> statement SEMICOLON\n");}
		  		| statement SEMICOLON statements {printf("statements -> statement SEMICOLON statements\n");}
				;

statement: var ASSIGN expression {printf("statement -> var ASSIGN expression\n");}
		 | RETURN expression {printf("statement -> RETURN expression\n");}
		 | CONTINUE {printf("statement -> CONTINUE\n");}
		 | IF boolexpr THEN statements else_prime ENDIF {printf("statement -> IF boolexpr THEN statements else_prime ENDIF\n");}
		 | WHILE boolexpr BEGINLOOP statements ENDLOOP {printf("statement -> WHILE boolexpr BEGINLOOP statements ENDLOOP\n");}
		 | DO BEGINLOOP statements ENDLOOP WHILE boolexpr {printf("statement -> DO BEGINLOOP statements ENDLOOP WHILE boolexpr\n");}
		 | READ vars {printf("statement -> READ vars\n");}
		 | WRITE vars {printf("statement -> WRITE vars\n");}
		 ;

else_prime:		{printf("else_prime -> epsilon\n");} 
		  |	ELSE statements	{printf("else_prime -> ELSE statements\n");}		
		  ;

vars: 	var {printf("vars -> var\n");}
	|	var COMMA vars {printf("vars -> var COMMA vars\n");}
	;

comp: EQ	{printf("comp -> EQ\n");}
	| NEQ 	{printf("comp -> NEQ\n");}
	| LT 	{printf("comp -> LT\n");}
	| GT	{printf("comp -> GT\n");}
	| LTE	{printf("comp -> LTE\n");}
	| GTE	{printf("comp -> GTE\n");}
	;

var: identifier {printf("var -> identifier\n");}
   	| identifier L_SQUARE_BRACKET expression R_SQUARE_BRACKET {printf("var -> identifier L_SQUARE_BRACKET expression R_SQUARE_BRACKET\n");};

expression: multiplicative_expr multiplicative_exprs {printf("expression -> multiplicative_expr multiplicative_exprs\n");}
		  ;

multiplicative_exprs:	{printf("multiplicative_exprs -> epsilon\n");} 
					| SUB multiplicative_expr multiplicative_exprs {printf("multiplicative_exprs -> SUB multiplicative_expr multiplicative_exprs\n");} 
					| ADD multiplicative_expr multiplicative_exprs {printf("multiplicative_exprs -> ADD multiplicative_expr multiplicative_exprs\n");} 

					;

multiplicative_expr: term terms {printf("multiplicative_expr -> term terms\n");}
					;

terms:	{printf("terms -> epsilon\n");} 
	 | MULT term terms {printf("terms -> MULT term terms\n");}
	 | DIV term terms {printf("terms -> DIV term terms\n");}
	 | MOD term terms {printf("terms -> MOD term terms\n");} 
	 ;

boolexpr: relation_and_expr r_a_es {printf("boolexpr -> relation_and_expr r_a_es\n");}
			;

r_a_es: 	{printf("r_a_es -> epsilon\n");}
	  |  OR relation_and_expr r_a_es {printf("r_a_es -> OR relation_and_expr r_a_es\n");}
	  ;

relation_and_expr: relation_expr r_es {printf("relation_and_expr -> relation_expr r_es\n");} 
				 ;

r_es: 	{printf("r_es -> epsilon\n");}
	| AND relation_expr r_es {printf("r_es -> AND relation_expr r_es\n");}
	;

relation_expr:  expression comp expression {printf("relation_expr -> expression comp expression\n");}
			 | TRUE {printf("relation_expr -> TRUE\n");}
			 | FALSE {printf("relation_expr -> FALSE\n");}
			 | L_PAREN boolexpr R_PAREN {printf("relation_expr -> L_PAREN boolexpr R_PAREN\n");}
			 | NOT expression comp expression {printf("relation_expr -> NOT expression comp expression\n");}
			 | NOT TRUE {printf("relation_expr -> NOT TRUE\n");}
			 | NOT FALSE {printf("relation_expr -> NOT FALSE\n");}
			 | NOT L_PAREN boolexpr R_PAREN {printf("relation_expr -> NOT L_PAREN boolexpr R_PAREN\n");}
			 ;

term: var  {printf("term -> var\n");}
	| NUMBER {printf("term -> NUMBER\n");}
	| L_PAREN expression R_PAREN {printf("term -> L_PAREN expression R_PAREN\n");}
	| SUB var %prec UMINUS {printf("term -> SUB var\n");}
	| SUB NUMBER %prec UMINUS {printf("term -> SUB NUMBER\n");}
	| SUB L_PAREN expression R_PAREN %prec UMINUS {printf("term -> SUB L_PAREN expression R_PAREN\n");}
	| identifier L_PAREN expressions R_PAREN {printf("term -> identifier L_PAREN expressions R_PAREN\n");}
	;

expressions: expression {printf("expressions -> expression\n");}
		   | expression expressions COMMA {printf("expressions -> expression expressions COMMA\n");}
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

