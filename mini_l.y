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

	int errorCount = 0;

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
		errorCount++;
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
		char* name; // Useful for code generation
		char* code;
		int t;
		int size;
	} typeNode;	
}

%error-verbose
%token FUNCTION BEGIN_PARAMS END_PARAMS BEGIN_LOCALS END_LOCALS BEGIN_BODY END_BODY TYPE_INTEGER ARRAY OF IF THEN ENDIF ELSE WHILE DO BEGINLOOP ENDLOOP CONTINUE READ WRITE AND OR NOT TRUE FALSE RETURN SUB ADD MULT DIV MOD EQ NEQ LT GT LTE GTE SEMICOLON COLON COMMA L_PAREN R_PAREN L_SQUARE_BRACKET R_SQUARE_BRACKET ASSIGN
%start input
%token <dval> INTEGER
%token <string_list> IDENT
%type <string_list> identifier identifiers comp
%type <typeNode> declaration declaration_prime var expression boolexpr term relation_expr expressions multiplicative_expr 
%type <typeNode> declarations function vars relation_and_expr statement statements
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

function: FUNCTION IDENT { sprintf(codestr, "func %s", $2); emitCode(codestr); insert($2, m_void); } SEMICOLON BEGIN_PARAMS declarations END_PARAMS BEGIN_LOCALS declarations END_LOCALS BEGIN_BODY statements END_BODY { sprintf(codestr, "endfunc\n"); emitCode(codestr); }
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

statement: var ASSIGN expression { 
		 	if (fetch($1.name)) if (!checkType($1.t, $3.t)) reg_type_error("Mismatched assignment"); 
			sprintf(codestr, "= %s, %s", $1.name, $3.name); emitCode(codestr);
		 }
		 | RETURN expression { 
			if (!checkType($2.t, m_int)) reg_type_error("Trying to return a non int type");
			sprintf(codestr, "ret %s", $2.name); emitCode(codestr);
		 }
		 | CONTINUE { }
		 | IF boolexpr {
			char* label = newlabel();
			$$.name = label;
			sprintf(codestr, "?:= %s, %s", label, $2.name);	emitCode(codestr);
		 } THEN statements else_prime ENDIF { if ($2.t != m_bool) reg_type_error("If statement does not contain a boolean expression"); }
		 | WHILE boolexpr BEGINLOOP statements ENDLOOP {}
		 | DO BEGINLOOP statements ENDLOOP WHILE boolexpr {}
		 | READ vars { sprintf(codestr, ".< %s", $2.name); emitCode(codestr); }
		 | WRITE vars { sprintf(codestr, ".> %s", $2.name); emitCode(codestr); }
		 ;

else_prime:		{} 
		  |	ELSE statements	{}		
		  ;

vars: 	var {}
	|	var COMMA vars {}
	;

comp: EQ	{$$ = "==";}
	| NEQ 	{$$ = "!=";}
	| LT 	{$$ = "<";}
	| GT	{$$ = ">";}
	| LTE	{$$ = "<=";}
	| GTE	{$$ = ">=";}
	;

var: identifier { 
   $$.name = $1; $$.t = m_int; 
}
   | identifier L_SQUARE_BRACKET expression R_SQUARE_BRACKET { 
	if (!checkType($3.t, m_int)) reg_type_error("Array access expression is not of type int"); 
	else { $$.name = $1; $$.t = m_int; }
};

expression: multiplicative_expr {}
		  | expression ADD multiplicative_expr {
			if (!(checkType($1.t, $3.t) && checkType($1.t, m_int)))
				reg_type_error("Expression uses non int types");
			$$.name = newtemp();
			sprintf(codestr, ". %s", $$.name); emitCode(codestr);
			sprintf(codestr, "+ %s, %s, %s", $$.name, $1.name, $3.name); emitCode(codestr);
		  }
		  | expression SUB multiplicative_expr {
		  	if (!(checkType($1.t, $3.t) && checkType($1.t, m_int)))
				reg_type_error("Expression uses non int types");
			$$.name = newtemp();
			sprintf(codestr, ". %s", $$.name); emitCode(codestr);
			sprintf(codestr, "- %s, %s, %s", $$.name, $1.name, $3.name); emitCode(codestr);
		  }
		  ;

multiplicative_expr: term {}
				   | multiplicative_expr MULT term {
				   		if (!(checkType($1.t, $3.t) && checkType($1.t, m_int)))
							reg_type_error("Expression uses non int types");
						$$.name = newtemp();
						sprintf(codestr, ". %s", $$.name); emitCode(codestr);
						sprintf(codestr, "* %s, %s, %s", $$.name, $1.name, $3.name); emitCode(codestr);
				   }
				   | multiplicative_expr DIV term {
						if (!(checkType($1.t, $3.t) && checkType($1.t, m_int)))
							reg_type_error("Expression uses non int types");
						$$.name = newtemp();
						sprintf(codestr, ". %s", $$.name); emitCode(codestr);
						sprintf(codestr, "/ %s, %s, %s", $$.name, $1.name, $3.name); emitCode(codestr);
				   }
				   | multiplicative_expr MOD term {
						if (!(checkType($1.t, $3.t) && checkType($1.t, m_int)))
							reg_type_error("Expression uses non int types");
						$$.name = newtemp();
						sprintf(codestr, ". %s", $$.name); emitCode(codestr);
						sprintf(codestr, "% %s, %s, %s", $$.name, $1.name, $3.name); emitCode(codestr);
				   }
				   ;

boolexpr: relation_and_expr r_a_es { $$ = $1; }
		;

r_a_es: 	{}
	  |  OR relation_and_expr r_a_es {}
	  ;

relation_and_expr: relation_expr r_es { $$ = $1; }  
				 ;

r_es: 	{}
	| AND relation_expr r_es {}
	;

relation_expr:  expression comp expression { 
	if (!(checkType($1.t, $3.t) && checkType($1.t, m_int))) 
		reg_type_error("Comparison does not compare two int expressions"); 
	else $$.t = m_bool; 
	char* temp_c = newtemp();
	sprintf(codestr, ". %s", temp_c); emitCode(codestr);
	sprintf(codestr, "%s %s, %s, %s", $2, temp_c, $1.name, $3.name); emitCode(codestr);
	
	$$.name = temp_c;
	} 
			 | TRUE { $$.t = m_bool; }
			 | FALSE { $$.t = m_bool; }
			 | L_PAREN boolexpr R_PAREN { $$.t = m_bool; $$.name = $2.name; }
			 | NOT expression comp expression { 
	if (!(checkType($2.t, $4.t) && checkType($2.t, m_int))) reg_type_error("Comparison does not compare two int expressions"); else $$.t = m_bool;}
			 | NOT TRUE { $$.t = m_bool; }
			 | NOT FALSE { $$.t = m_bool; }
			 | NOT L_PAREN boolexpr R_PAREN { $$.t = m_bool; }
			 ;

term: var  { 
	if (fetch($1.name)) $$ = $1; 
	$$.name = newtemp(); 
	sprintf(codestr, ". %s", $$.name); emitCode(codestr); 
	sprintf(codestr, "= %s, %s", $$.name, $1.name); emitCode(codestr);
	}
	| INTEGER { 
	$$.t = m_int; 
	$$.name = newtemp();	
	sprintf(codestr, ". %s", $$.name); emitCode(codestr); 
	sprintf(codestr, "= %s, %d", $$.name, (int)$1); emitCode(codestr);
	}
	| L_PAREN expression R_PAREN { 
	if (!checkType($2.t, m_int)) 
		reg_type_error("Expression is not an int type"); 
	else 
		$$ = $2; 
	}
	| SUB var %prec UMINUS { 
	$$ = $2; $$.name = "subtest2";
	}
	| SUB INTEGER %prec UMINUS { 
	$$.t = m_int; $$.name = "a"; 
	}
	| SUB L_PAREN expression R_PAREN %prec UMINUS { 
	if (!checkType($3.t, m_int)) 
		reg_type_error("Expression is not an int type"); 
	else 
		$$.t = m_int; 
	$$.name = "subtest";
	}
	| identifier L_PAREN expressions R_PAREN { 
		$$.t = m_int;
		$$.name = newtemp();	
		sprintf(codestr, "param %s", $3.name); emitCode(codestr);
		/*NOTE WILL PROBABLY NEED TO IMPLEMENT SPLIT EMIT FOR PARAMS*/
		sprintf(codestr, ". %s", $$.name); emitCode(codestr);
		sprintf(codestr, "call %s, %s", $1, $$.name); emitCode(codestr);
	}
	;

expressions: expression { 
		   /*$$.name = newtemp(); 
		   sprintf(codestr, ". %s", $$.name); emitCode(codestr);
		   sprintf(codestr, "= %s, %s", $$.name, $1.name); emitCode(codestr);*/
		   }
		   | expression expressions COMMA {}
		   ;

%%

int main(int argc, char** argv) {
	if (argc > 1) {
		yyin = fopen(argv[1], "r");
		if (yyin == NULL) {
			printf("usage: %s filename\n", argv[0]);
			return 1;
		}
	}
	yyparse();
	if (errorCount > 0) {
		printf("WARNING: %d error(s) in the above contexts.", errorCount);
	}
	return 0;
}

void yyerror(const char* msg) {
	printf("Syntax error at line %d: %s\n", curr_line, msg);
}

