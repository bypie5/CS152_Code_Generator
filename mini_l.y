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
	void reg_type_error(char* msg) {
		errorCount++;
		printf("SEMANTIC ERROR (line %d): %s\n", curr_line, msg);
	}

	char* concat(const char *s1, const char *s2) {
		char* result = malloc(strlen(s1) + strlen(s2) + 1);
		strcpy(result, s1);
		strcat(result, s2);
		return result;
	}


	int stackTop = -1;
	char* loopStack[BUFFER_SIZE];
	void pushLoopStack(char* val) {
		stackTop++;
		//printf("Pushing: %s...\n", val);
		loopStack[stackTop] = val;
	}

	int isEmpty() {
   		if(stackTop == -1)
      		return 1;
   		else
      		return 0;
	}

	char* popLoopStack() {
		if (isEmpty()) {
			return 0;
		}

		char* data = loopStack[stackTop];
		stackTop--;

		//printf("%s\n", data);

		return data;
	}

	// Handles declarations that were split by commas
	void split_insert(const char* list, M_TYPE type) {
		char* ref = malloc(strlen(list) + 1);
		strcpy(ref, list);
		char* pch = strtok(ref, ",");
		while(pch != NULL) {
			if(!insert(pch, type)) reg_type_error("Variable multiply defined");
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

	void split_read(char* list, M_TYPE type, char* index) {
		/*if ($2.t == m_int) {
			sprintf(codestr, ".< %s", $2.name); emitCode(codestr); 
	 	} else {
			sprintf(codestr, ".[]< %s, %s", $2.name, $2.index); emitCode(codestr);			
		}*/
		char* ref = malloc(strlen(list) + 1);
		strcpy(ref, list);
		char * pch = strtok(ref, ",");
		while(pch != NULL) {
			if (type == m_int) {
				sprintf(codestr, ".< %s", pch);
				emitCode(codestr);
			} else {
				sprintf(codestr, ".[]< %s, %s", pch, index);
				emitCode(codestr);
			}
			pch = strtok(NULL, ",");
		}
	}
	
	void split_write(char* list, M_TYPE type, char* index) {
		/*if ($2.t == m_int) {
			sprintf(codestr, ".< %s", $2.name); emitCode(codestr); 
	 	} else {
			sprintf(codestr, ".[]< %s, %s", $2.name, $2.index); emitCode(codestr);			
		}*/
		char* ref = malloc(strlen(list) + 1);
		strcpy(ref, list);
		char * pch = strtok(ref, ",");
		while(pch != NULL) {
			if (type == m_int) {
				sprintf(codestr, ".> %s", pch);
				emitCode(codestr);
			} else {
				sprintf(codestr, ".[]> %s, %s", pch, index);
				emitCode(codestr);
			}
			pch = strtok(NULL, ",");
		}
	}
	void split_param(char* list) {
		int param_count = 0;
		char* ref = malloc(strlen(list) + 1);
		strcpy(ref, list);
		char* pch = strtok(ref, ",");
		while(pch != NULL) {
			sprintf(codestr, "= %s, $%d", pch, param_count);
			emitCode(codestr);
			pch = strtok(NULL, ",");
			param_count++;
		}
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
		char* index;
	} typeNode;

	struct elseif {
		char* then_label;
		char* else_label;
	} elseif;

	struct whileloop {
		char* then_label;
		char* else_label;
		char* begin_label;
		char* exit_label;
		char* start_label;
		char* continue_to;
	} whileloop;
}

%error-verbose
%token FUNCTION BEGIN_PARAMS END_PARAMS BEGIN_LOCALS END_LOCALS BEGIN_BODY END_BODY TYPE_INTEGER ARRAY OF IF THEN ENDIF ELSE WHILE DO BEGINLOOP ENDLOOP CONTINUE READ WRITE AND OR NOT TRUE FALSE RETURN SUB ADD MULT DIV MOD EQ NEQ LT GT LTE GTE SEMICOLON COLON COMMA L_PAREN R_PAREN L_SQUARE_BRACKET R_SQUARE_BRACKET ASSIGN
%start input
%token <dval> INTEGER
%token <string_list> IDENT
%type <string_list> identifier identifiers comp 
%type <typeNode> var expression boolexpr term relation_expr expressions multiplicative_expr declaration declarations declaration_prime
%type <typeNode> function vars relation_and_expr 
%type <whileloop> statement statements
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

function: FUNCTION IDENT { 
		sprintf(codestr, "func %s", $2); 
		emitCode(codestr); 
		if (!insert($2, m_void)) {reg_type_error("Variable multiply defined");} 
		} SEMICOLON BEGIN_PARAMS declarations {
		if ($6.code) {
			split_param($6.code);
		}
		} END_PARAMS BEGIN_LOCALS declarations END_LOCALS BEGIN_BODY statements END_BODY { 
		sprintf(codestr, "endfunc\n"); 
		emitCode(codestr); 
		}
		;

declarations: {$$.code = 0;}
				| declaration SEMICOLON declarations {$$ = $1;} 
				;

declaration: identifiers COLON declaration_prime { 
		   	$$.code = $1;
			split_insert($1, $3.t); 
			split_emit($1, $3.t, $3.size); 
		  };

declaration_prime: TYPE_INTEGER { $$.t = m_int; }
				 | ARRAY L_SQUARE_BRACKET INTEGER R_SQUARE_BRACKET OF TYPE_INTEGER { 
					$$.t = m_array; $$.size = (int) $3;
 				 	if ($$.size <= 0) reg_type_error("Invalid array size");
				 };

identifiers: identifier { $$ = $1; }
		   | identifier COMMA identifiers { $$ = concat($$, concat(",", $3)); } 
		   ;

identifier: IDENT { $$ = $1; };

statements:		statement SEMICOLON {
		  		/*if ($1.continue_to) {
		  			sprintf(codestr, ":= %s", $1.continue_to); emitCode(codestr);
				}*/
				}
		  		| statement SEMICOLON statements {}
				;

statement: var ASSIGN expression { 
		 	if (fetch($1.name)) {
				if (!( (checkType($1.t, m_int) && checkType($1.t, m_int)) || (checkType($1.t, m_array) && checkType($3.t, m_int)) )) 
					reg_type_error("Mismatched assignment"); 
			} else {
				reg_type_error("Symbol does not exist in the symbol table");
			}
			if (checkType($1.t, m_int) && checkType($3.t, m_int)) {
				sprintf(codestr, "= %s, %s", $1.name, $3.name); emitCode(codestr);
			}
		 	else if (checkType($1.t, m_array)) {
				sprintf(codestr, "[]= %s, %s, %s", $1.name, $1.index, $3.name) ; emitCode(codestr);
			}
			else {
				sprintf(codestr, "=[] %s, %s, %s", $1.name, $3.name, $3.index); emitCode(codestr);
			}
	     }
		 | RETURN expression { 
			if (!checkType($2.t, m_int)) reg_type_error("Trying to return a non int type");
			sprintf(codestr, "ret %s", $2.name); emitCode(codestr);
		 }
		 | CONTINUE {
			char* target = popLoopStack();
			if (!target)
				reg_type_error("Continue statement outside of a loop statement");
			else {
				sprintf(codestr, ":= %s", target); emitCode(codestr);		
		 	}
		 }
		 | IF boolexpr 
		 {
			char* else_label = newlabel();
			$<whileloop>$.else_label = else_label;
			sprintf(codestr, "?:= %s, %s", else_label, $2.name); emitCode(codestr);
		 	char* then_label = newlabel();
			$<whileloop>$.then_label = then_label;
			sprintf(codestr, ":= %s", then_label); emitCode(codestr);
		 } 
		 THEN {
			sprintf(codestr, ": %s", $<whileloop>3.else_label); emitCode(codestr);
		 } statements {
		 	sprintf(codestr, ": %s", $<whileloop>3.then_label); emitCode(codestr);
		 } else_prime ENDIF { 
			if ($2.t != m_bool) 
				reg_type_error("If statement does not contain a boolean expression"); 
		 	$$ = $6;
		 }
		 | {
			$<whileloop>$.start_label = newlabel(); 
			pushLoopStack($<whileloop>$.start_label);
			sprintf(codestr, ": %s", $<whileloop>$.start_label); emitCode(codestr);
		 } WHILE boolexpr
		 { 
			$<whileloop>1.begin_label = newlabel();
			sprintf(codestr, "?:= %s, %s", $<whileloop>1.begin_label, $3.name); emitCode(codestr);
			$<whileloop>1.exit_label = newlabel();
			sprintf(codestr, ":= %s", $<whileloop>1.exit_label); emitCode(codestr);
		 } BEGINLOOP {
			sprintf(codestr, ": %s", $<whileloop>1.begin_label); emitCode(codestr);
		 } statements {
		 	sprintf(codestr, ":= %s", $<whileloop>1.start_label); emitCode(codestr);
		 } ENDLOOP {
		 	$$ = $<whileloop>1;
			$$.continue_to = $<whileloop>1.begin_label;
			sprintf(codestr, ": %s", $<whileloop>1.exit_label); emitCode(codestr);
		 }
		 | {
			$<whileloop>$.continue_to = newlabel();
			pushLoopStack($<whileloop>$.continue_to);
			$<whileloop>$.begin_label = newlabel();
		 } DO BEGINLOOP {
			sprintf(codestr, ": %s", $<whileloop>1.begin_label); emitCode(codestr);
		 } statements ENDLOOP WHILE {
		 	sprintf(codestr, ": %s", $<whileloop>1.continue_to); emitCode(codestr);
		 } boolexpr {
			sprintf(codestr, "?:= %s, %s", $<whileloop>1.begin_label, $9.name); emitCode(codestr);
		 	$$ = $<whileloop>1;
		 }
		 | READ vars { 
			split_read($2.name, $2.t, $2.index);
		 }
		 | WRITE vars { 
			split_write($2.name, $2.t, $2.index);
		 }
		 ;

else_prime:		{} 
		  |	ELSE statements	{}		
		  ;

vars: 	var { $$ = $1; }
	|	var COMMA vars { $$.name = concat($$.name, concat(",", $3.name)); }
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
	if (fetch($1)) if (!checkType(fetch($1)->type, m_array)) reg_type_error("Attempting to use an integer like an array");
	$$.name = $1; $$.t = m_array; $$.index = $3.name;
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
						sprintf(codestr, "%% %s, %s, %s", $$.name, $1.name, $3.name); emitCode(codestr);
				   }
				   ;

boolexpr: relation_and_expr { $$ = $1; }
		| boolexpr OR relation_and_expr {
			$$.name = newtemp();
			sprintf(codestr, ". %s", $$.name); emitCode(codestr);
			sprintf(codestr, "|| %s, %s, %s", $$.name, $1.name, $3.name); emitCode(codestr);
		}
		;

relation_and_expr: relation_expr { $$ = $1; }  
				 | relation_and_expr AND relation_expr {
					$$.name = newtemp();
				 	sprintf(codestr, ". %s", $$.name); emitCode(codestr);
				 	sprintf(codestr, "&& %s, %s, %s", $$.name, $1.name, $3.name); emitCode(codestr);
	 		     }
				 ;

relation_expr:  expression comp expression { 
	if (!(checkType($1.t, $3.t) && checkType($1.t, m_int))) 
		reg_type_error("Comparison does not compare two int expressions"); 
	$$.t = m_bool; 
	char* temp_c = newtemp();
	sprintf(codestr, ". %s", temp_c); emitCode(codestr);
	sprintf(codestr, "%s %s, %s, %s", $2, temp_c, $1.name, $3.name); emitCode(codestr);
	$$.name = temp_c;
	} 
			 | TRUE { 
	$$.t = m_bool; 
	$$.name = "1";
	}
			 | FALSE {
	$$.t = m_bool;
	$$.name = "0"; 
	}
			 | L_PAREN boolexpr R_PAREN { 
	$$.t = m_bool; 
	$$.name = $2.name; 
	}
			 | NOT expression comp expression { 
	if (!(checkType($2.t, $4.t) && checkType($2.t, m_int))) 
		reg_type_error("Comparison does not compare two int expressions"); 
	$$.t = m_bool;

	$$.name = newtemp();
	sprintf(codestr, ". %s", $$.name); emitCode(codestr);
	
	char* temp = newtemp();
	sprintf(temp, ". %s", temp); emitCode(codestr);
	sprintf(codestr, "%s %s, %s, %s", $3, temp, $2.name, $4.name); emitCode(codestr);
	sprintf(codestr, "! %s, %s", $$.name, temp); emitCode(codestr);
	}
			 | NOT TRUE { 
	$$.t = m_bool; 
	$$.name = "0";
	}
			 | NOT FALSE { 
	$$.t = m_bool; 
	$$.name = "1";
	}
			 | NOT L_PAREN boolexpr R_PAREN { 
	$$.t = m_bool; 
	$$.name = newtemp();
	sprintf(codestr, "! %s, %s", $$.name, $3.name); emitCode(codestr);
	}
			 ;

term: var  { 
	if (fetch($1.name)) {
		$$ = $1; 
	} else {
		reg_type_error("Symbol does not exist in the symbol table");
	}
	int curr_type;
	if (fetch($1.name)) {
		curr_type = fetch($1.name)->type;
	} else {
		curr_type = $1.t;
	}
	if (curr_type == m_int) {
		$$.name = newtemp(); 
		sprintf(codestr, ". %s", $$.name); emitCode(codestr); 
		sprintf(codestr, "= %s, %s", $$.name, $1.name); emitCode(codestr);
	} else {
		$$.name = newtemp();
		sprintf(codestr, ". %s", $$.name); emitCode(codestr);
		
		if (!$1.index) 
			reg_type_error("Used array variable missing a specified index");
		
		sprintf(codestr, "=[] %s, %s, %s", $$.name, $1.name, $1.index); emitCode(codestr);	
		$$.t = m_int;
	}
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
	$$ = $2;
	$$.name = newtemp();
	sprintf(codestr, ". %s", $$.name); emitCode(codestr);
	sprintf(codestr, "= %s, %s", $$.name, $2.name); emitCode(codestr);;
	}
	| SUB var %prec UMINUS { 
	$$ = $2;
	$$.name = newtemp();
	sprintf(codestr, ". %s", $$.name); emitCode(codestr);
	sprintf(codestr, "* %s, %s, -1", $$.name, $2.name); emitCode(codestr);
	}
	| SUB INTEGER %prec UMINUS { 
	$$.t = m_int;	
	$$.name = newtemp();
	sprintf(codestr, ". %s", $$.name); emitCode(codestr);
	sprintf(codestr, "* %s, %d, -1", $$.name, (int)$2); emitCode(codestr);
	}
	| SUB L_PAREN expression R_PAREN %prec UMINUS { 
	if (!checkType($3.t, m_int)) 
		reg_type_error("Expression is not an int type"); 
	$$.t = m_int; 
	
	$$.name = newtemp();
	sprintf(codestr, ". %s", $$.name); emitCode(codestr);
	sprintf(codestr, "* %s, %s, -1", $$.name, $3.name); emitCode(codestr);
    }
	| identifier L_PAREN expressions R_PAREN { 
		$$.t = m_int;
		$$.name = newtemp();	
		sprintf(codestr, "param %s", $3.name); emitCode(codestr);
		/*NOTE WILL PROBABLY NEED TO IMPLEMENT SPLIT EMIT FOR PARAMS*/
		sprintf(codestr, ". %s", $$.name); emitCode(codestr);

		if (!fetch($1)) {
			reg_type_error("Function being called was not defined");
		}
		sprintf(codestr, "call %s, %s", $1, $$.name); emitCode(codestr);
	}
	;

expressions: expression { 
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

	// Check errors
	if (!fetch("main")) {
		printf("ERROR: \'main\' function is not defined\n");
	} else if (errorCount > 0) {
		printf("ERROR: %d error(s) in the above contexts.\n", errorCount);
	} else {
		printCode();
	}
	return 0;
}

void yyerror(const char* msg) {
	printf("Syntax error at line %d: %s\n", curr_line, msg);
}

