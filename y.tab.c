/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "mini_l.y" /* yacc.c:339  */

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

#line 209 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    FUNCTION = 258,
    BEGIN_PARAMS = 259,
    END_PARAMS = 260,
    BEGIN_LOCALS = 261,
    END_LOCALS = 262,
    BEGIN_BODY = 263,
    END_BODY = 264,
    TYPE_INTEGER = 265,
    ARRAY = 266,
    OF = 267,
    IF = 268,
    THEN = 269,
    ENDIF = 270,
    ELSE = 271,
    WHILE = 272,
    DO = 273,
    BEGINLOOP = 274,
    ENDLOOP = 275,
    CONTINUE = 276,
    READ = 277,
    WRITE = 278,
    AND = 279,
    OR = 280,
    NOT = 281,
    TRUE = 282,
    FALSE = 283,
    RETURN = 284,
    SUB = 285,
    ADD = 286,
    MULT = 287,
    DIV = 288,
    MOD = 289,
    EQ = 290,
    NEQ = 291,
    LT = 292,
    GT = 293,
    LTE = 294,
    GTE = 295,
    SEMICOLON = 296,
    COLON = 297,
    COMMA = 298,
    L_PAREN = 299,
    R_PAREN = 300,
    L_SQUARE_BRACKET = 301,
    R_SQUARE_BRACKET = 302,
    ASSIGN = 303,
    INTEGER = 304,
    IDENT = 305,
    UMINUS = 306
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 144 "mini_l.y" /* yacc.c:355  */

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

#line 328 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 345 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   185

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  152

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   306

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   185,   185,   186,   189,   192,   193,   196,   200,   196,
     210,   211,   214,   220,   221,   226,   227,   230,   232,   237,
     240,   257,   261,   270,   278,   280,   269,   287,   292,   297,
     299,   287,   306,   308,   306,   316,   325,   336,   337,   340,
     341,   344,   345,   346,   347,   348,   349,   352,   355,   361,
     362,   369,   378,   379,   386,   393,   402,   403,   410,   411,
     418,   427,   431,   435,   439,   452,   456,   460,   467,   494,
     500,   505,   511,   517,   526,   540,   542
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "FUNCTION", "BEGIN_PARAMS", "END_PARAMS",
  "BEGIN_LOCALS", "END_LOCALS", "BEGIN_BODY", "END_BODY", "TYPE_INTEGER",
  "ARRAY", "OF", "IF", "THEN", "ENDIF", "ELSE", "WHILE", "DO", "BEGINLOOP",
  "ENDLOOP", "CONTINUE", "READ", "WRITE", "AND", "OR", "NOT", "TRUE",
  "FALSE", "RETURN", "SUB", "ADD", "MULT", "DIV", "MOD", "EQ", "NEQ", "LT",
  "GT", "LTE", "GTE", "SEMICOLON", "COLON", "COMMA", "L_PAREN", "R_PAREN",
  "L_SQUARE_BRACKET", "R_SQUARE_BRACKET", "ASSIGN", "INTEGER", "IDENT",
  "UMINUS", "$accept", "input", "program", "functions", "function", "$@1",
  "$@2", "declarations", "declaration", "declaration_prime", "identifiers",
  "identifier", "statements", "statement", "@3", "$@4", "$@5", "@6", "$@7",
  "$@8", "$@9", "@10", "$@11", "else_prime", "vars", "comp", "var",
  "expression", "multiplicative_expr", "boolexpr", "relation_and_expr",
  "relation_expr", "term", "expressions", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306
};
# endif

#define YYPACT_NINF -70

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-70)))

#define YYTABLE_NINF -33

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      14,   -38,    31,   -70,   -70,    14,   -70,   -70,   -70,    23,
      64,    -6,   -70,   -70,    46,    50,    57,    98,    -6,   115,
      -6,   108,   -70,   -70,    72,   -70,   -70,    -6,    74,   128,
      90,   131,   130,    86,   143,    94,   -70,    -6,    -6,     2,
     116,   145,   122,   147,   148,   117,   -70,    33,   -70,   -70,
      61,    94,   -70,     9,   -70,   121,    96,   142,   144,   -70,
     -70,   -70,   126,   -70,     2,    41,     2,   -70,    67,    94,
     151,     2,   -70,   -70,    94,   121,     2,   -70,   -70,   110,
      -4,     2,     2,     2,   -70,   -70,   -70,   -70,   -70,   -70,
       2,     2,     2,     2,    94,   157,    94,    -6,    17,     3,
     -70,   142,   -70,    41,     4,     2,    48,   -70,   -70,    -7,
     127,    96,    96,    41,   -70,   -70,   -70,   144,   -70,   -70,
     -70,   -70,   154,    86,   -70,    41,   -70,    26,   132,   -70,
      86,   -70,   156,     2,   -70,   -70,   -70,   -70,    86,   160,
      71,   158,   -70,    94,   -70,    86,   163,   159,   142,   -70,
     -70,   -70
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     3,     4,     5,     7,     1,     6,     0,
       0,    10,    17,     8,     0,     0,    15,     0,    10,     0,
       0,     0,    11,    13,     0,    12,    16,    10,     0,     0,
       0,     0,     0,    27,     0,     0,    22,     0,     0,     0,
      47,     0,     0,     0,     0,     0,    14,     0,    61,    62,
       0,     0,    69,    47,    68,     0,    49,    23,    56,    58,
      52,    35,    39,    36,     0,    21,     0,     9,    18,     0,
       0,     0,    65,    66,     0,     0,     0,    72,    71,     0,
       0,     0,     0,     0,    41,    42,    43,    44,    45,    46,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      19,    28,    33,    20,     0,     0,     0,    70,    63,    75,
       0,    51,    50,    60,    53,    54,    55,    57,    24,    59,
      40,    48,     0,    27,    67,    64,    73,     0,     0,    74,
      27,    29,     0,     0,    69,    68,    76,    25,    27,     0,
       0,    37,    30,     0,    70,    27,     0,     0,    34,    38,
      26,    31
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -70,   -70,   -70,   175,   -70,   -70,   -70,    -8,   -70,   -70,
     161,   -11,   -64,   -70,   -70,   -70,   -70,   -70,   -70,   -70,
     -70,   -70,   -70,   -70,   -30,   107,   -32,   -36,   -69,   -49,
      89,    88,    40,    76
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,     5,     9,    17,    13,    14,    25,
      15,    53,    41,    42,    95,   130,   141,    43,   122,   138,
     147,    44,   123,   146,    61,    90,    54,    55,    56,    57,
      58,    59,    60,   110
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      16,    45,    80,    65,   100,    62,    62,    16,    63,    16,
      22,    75,     6,   111,   112,    79,    16,     1,    78,    29,
     101,    94,    40,   127,    83,   104,    40,    40,    98,    94,
      99,     7,    50,    82,    83,   103,    45,    64,    79,    40,
     106,   108,    52,    12,    12,   109,    64,    82,    83,   124,
     121,    52,    12,    81,   113,    66,    50,    40,   111,   132,
      72,    73,   107,    50,    10,    62,   137,   120,    11,   125,
     133,    82,    83,   109,   142,   134,    12,    74,    82,    83,
      35,   149,    52,    12,   -27,   -32,    40,    18,    36,    37,
      38,    45,    19,   126,   148,   135,    39,   140,    45,    35,
      20,    82,    83,    21,   -32,    76,    45,    36,    37,    38,
      77,    12,    40,    45,    27,    39,   144,    12,    28,    40,
      47,    48,    49,    30,    50,    23,    24,    40,    91,    92,
      93,   114,   115,   116,    40,    31,    12,    32,    51,    33,
      82,    83,    34,    52,    12,    84,    85,    86,    87,    88,
      89,    82,    83,    46,    67,   107,    84,    85,    86,    87,
      88,    89,    66,    68,    69,    71,    70,    94,    96,    97,
     102,   118,   129,   131,   145,   136,   139,   143,   150,   151,
       8,    26,   105,   117,   119,   128
};

static const yytype_uint8 yycheck[] =
{
      11,    33,    51,    39,    68,    37,    38,    18,    38,    20,
      18,    47,    50,    82,    83,    51,    27,     3,    50,    27,
      69,    25,    33,    30,    31,    74,    37,    38,    64,    25,
      66,     0,    30,    30,    31,    71,    68,    44,    74,    50,
      76,    45,    49,    50,    50,    81,    44,    30,    31,    45,
      47,    49,    50,    44,    90,    46,    30,    68,   127,   123,
      27,    28,    45,    30,    41,    97,   130,    97,     4,   105,
      44,    30,    31,   109,   138,    49,    50,    44,    30,    31,
      13,   145,    49,    50,    17,    18,    97,    41,    21,    22,
      23,   123,    42,    45,   143,   127,    29,   133,   130,    13,
      43,    30,    31,     5,    18,    44,   138,    21,    22,    23,
      49,    50,   123,   145,     6,    29,    45,    50,    46,   130,
      26,    27,    28,    49,    30,    10,    11,   138,    32,    33,
      34,    91,    92,    93,   145,     7,    50,    47,    44,     8,
      30,    31,    12,    49,    50,    35,    36,    37,    38,    39,
      40,    30,    31,    10,     9,    45,    35,    36,    37,    38,
      39,    40,    46,    41,    17,    48,    18,    25,    24,    43,
      19,    14,    45,    19,    16,    43,    20,    17,    15,    20,
       5,    20,    75,    94,    96,   109
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    53,    54,    55,    56,    50,     0,    55,    57,
      41,     4,    50,    59,    60,    62,    63,    58,    41,    42,
      43,     5,    59,    10,    11,    61,    62,     6,    46,    59,
      49,     7,    47,     8,    12,    13,    21,    22,    23,    29,
      63,    64,    65,    69,    73,    78,    10,    26,    27,    28,
      30,    44,    49,    63,    78,    79,    80,    81,    82,    83,
      84,    76,    78,    76,    44,    79,    46,     9,    41,    17,
      18,    48,    27,    28,    44,    79,    44,    49,    78,    79,
      81,    44,    30,    31,    35,    36,    37,    38,    39,    40,
      77,    32,    33,    34,    25,    66,    24,    43,    79,    79,
      64,    81,    19,    79,    81,    77,    79,    45,    45,    79,
      85,    80,    80,    79,    84,    84,    84,    82,    14,    83,
      76,    47,    70,    74,    45,    79,    45,    30,    85,    45,
      67,    19,    64,    44,    49,    78,    43,    64,    71,    20,
      79,    68,    64,    17,    45,    16,    75,    72,    81,    64,
      15,    20
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    52,    53,    53,    54,    55,    55,    57,    58,    56,
      59,    59,    60,    61,    61,    62,    62,    63,    64,    64,
      65,    65,    65,    66,    67,    68,    65,    69,    70,    71,
      72,    65,    73,    74,    65,    65,    65,    75,    75,    76,
      76,    77,    77,    77,    77,    77,    77,    78,    78,    79,
      79,    79,    80,    80,    80,    80,    81,    81,    82,    82,
      83,    83,    83,    83,    83,    83,    83,    83,    84,    84,
      84,    84,    84,    84,    84,    85,    85
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     1,     1,     2,     0,     0,    14,
       0,     3,     3,     1,     6,     1,     3,     1,     2,     3,
       3,     2,     1,     0,     0,     0,     9,     0,     0,     0,
       0,     9,     0,     0,     8,     2,     2,     0,     2,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     4,     1,
       3,     3,     1,     3,     3,     3,     1,     3,     1,     3,
       3,     1,     1,     3,     4,     2,     2,     4,     1,     1,
       3,     2,     2,     4,     4,     1,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 185 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1539 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 186 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1545 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 189 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1551 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 192 "mini_l.y" /* yacc.c:1646  */
    { }
#line 1557 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 193 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1563 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 196 "mini_l.y" /* yacc.c:1646  */
    { 
		sprintf(codestr, "func %s", (yyvsp[0].string_list)); 
		emitCode(codestr); 
		if (!insert((yyvsp[0].string_list), m_void)) {reg_type_error("Variable multiply defined");} 
		}
#line 1573 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 200 "mini_l.y" /* yacc.c:1646  */
    {
		if ((yyvsp[0].typeNode).code) {
			split_param((yyvsp[0].typeNode).code);
		}
		}
#line 1583 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 204 "mini_l.y" /* yacc.c:1646  */
    { 
		sprintf(codestr, "endfunc\n"); 
		emitCode(codestr); 
		}
#line 1592 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 210 "mini_l.y" /* yacc.c:1646  */
    {(yyval.typeNode).code = 0;}
#line 1598 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 211 "mini_l.y" /* yacc.c:1646  */
    {(yyval.typeNode) = (yyvsp[-2].typeNode);}
#line 1604 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 214 "mini_l.y" /* yacc.c:1646  */
    { 
		   	(yyval.typeNode).code = (yyvsp[-2].string_list);
			split_insert((yyvsp[-2].string_list), (yyvsp[0].typeNode).t); 
			split_emit((yyvsp[-2].string_list), (yyvsp[0].typeNode).t, (yyvsp[0].typeNode).size); 
		  }
#line 1614 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 220 "mini_l.y" /* yacc.c:1646  */
    { (yyval.typeNode).t = m_int; }
#line 1620 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 221 "mini_l.y" /* yacc.c:1646  */
    { 
					(yyval.typeNode).t = m_array; (yyval.typeNode).size = (int) (yyvsp[-3].dval);
 				 	if ((yyval.typeNode).size <= 0) reg_type_error("Invalid array size");
				 }
#line 1629 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 226 "mini_l.y" /* yacc.c:1646  */
    { (yyval.string_list) = (yyvsp[0].string_list); }
#line 1635 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 227 "mini_l.y" /* yacc.c:1646  */
    { (yyval.string_list) = concat((yyval.string_list), concat(",", (yyvsp[0].string_list))); }
#line 1641 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 230 "mini_l.y" /* yacc.c:1646  */
    { (yyval.string_list) = (yyvsp[0].string_list); }
#line 1647 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 232 "mini_l.y" /* yacc.c:1646  */
    {
		  		/*if ($1.continue_to) {
		  			sprintf(codestr, ":= %s", $1.continue_to); emitCode(codestr);
				}*/
				}
#line 1657 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 237 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1663 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 240 "mini_l.y" /* yacc.c:1646  */
    { 
		 	if (fetch((yyvsp[-2].typeNode).name)) {
				if (!( (checkType((yyvsp[-2].typeNode).t, m_int) && checkType((yyvsp[-2].typeNode).t, m_int)) || (checkType((yyvsp[-2].typeNode).t, m_array) && checkType((yyvsp[0].typeNode).t, m_int)) )) 
					reg_type_error("Mismatched assignment"); 
			} else {
				reg_type_error("Symbol does not exist in the symbol table");
			}
			if (checkType((yyvsp[-2].typeNode).t, m_int) && checkType((yyvsp[0].typeNode).t, m_int)) {
				sprintf(codestr, "= %s, %s", (yyvsp[-2].typeNode).name, (yyvsp[0].typeNode).name); emitCode(codestr);
			}
		 	else if (checkType((yyvsp[-2].typeNode).t, m_array)) {
				sprintf(codestr, "[]= %s, %s, %s", (yyvsp[-2].typeNode).name, (yyvsp[-2].typeNode).index, (yyvsp[0].typeNode).name) ; emitCode(codestr);
			}
			else {
				sprintf(codestr, "=[] %s, %s, %s", (yyvsp[-2].typeNode).name, (yyvsp[0].typeNode).name, (yyvsp[0].typeNode).index); emitCode(codestr);
			}
	     }
#line 1685 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 257 "mini_l.y" /* yacc.c:1646  */
    { 
			if (!checkType((yyvsp[0].typeNode).t, m_int)) reg_type_error("Trying to return a non int type");
			sprintf(codestr, "ret %s", (yyvsp[0].typeNode).name); emitCode(codestr);
		 }
#line 1694 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 261 "mini_l.y" /* yacc.c:1646  */
    {
			char* target = popLoopStack();
			if (!target)
				reg_type_error("Continue statement outside of a loop statement");
			else {
			sprintf(codestr, ":= %s", target); emitCode(codestr);		
		 	}
		 }
#line 1707 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 270 "mini_l.y" /* yacc.c:1646  */
    {
			char* else_label = newlabel();
			(yyval.whileloop).else_label = else_label;
			sprintf(codestr, "?:= %s, %s", else_label, (yyvsp[0].typeNode).name); emitCode(codestr);
		 	char* then_label = newlabel();
			(yyval.whileloop).then_label = then_label;
			sprintf(codestr, ":= %s", then_label); emitCode(codestr);
		 }
#line 1720 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 278 "mini_l.y" /* yacc.c:1646  */
    {
			sprintf(codestr, ": %s", (yyvsp[-1].whileloop).else_label); emitCode(codestr);
		 }
#line 1728 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 280 "mini_l.y" /* yacc.c:1646  */
    {
		 	sprintf(codestr, ": %s", (yyvsp[-3].whileloop).then_label); emitCode(codestr);
		 }
#line 1736 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 282 "mini_l.y" /* yacc.c:1646  */
    { 
			if ((yyvsp[-7].typeNode).t != m_bool) 
				reg_type_error("If statement does not contain a boolean expression"); 
		 	(yyval.whileloop) = (yyvsp[-3].whileloop);
		 }
#line 1746 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 287 "mini_l.y" /* yacc.c:1646  */
    {
			(yyval.whileloop).start_label = newlabel(); 
			pushLoopStack((yyval.whileloop).start_label);
			sprintf(codestr, ": %s", (yyval.whileloop).start_label); emitCode(codestr);
		 }
#line 1756 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 292 "mini_l.y" /* yacc.c:1646  */
    { 
			(yyvsp[-2].whileloop).begin_label = newlabel();
			sprintf(codestr, "?:= %s, %s", (yyvsp[-2].whileloop).begin_label, (yyvsp[0].typeNode).name); emitCode(codestr);
			(yyvsp[-2].whileloop).exit_label = newlabel();
			sprintf(codestr, ":= %s", (yyvsp[-2].whileloop).exit_label); emitCode(codestr);
		 }
#line 1767 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 297 "mini_l.y" /* yacc.c:1646  */
    {
			sprintf(codestr, ": %s", (yyvsp[-4].whileloop).begin_label); emitCode(codestr);
		 }
#line 1775 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 299 "mini_l.y" /* yacc.c:1646  */
    {
		 	sprintf(codestr, ":= %s", (yyvsp[-6].whileloop).start_label); emitCode(codestr);
		 }
#line 1783 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 301 "mini_l.y" /* yacc.c:1646  */
    {
		 	(yyval.whileloop) = (yyvsp[-8].whileloop);
			(yyval.whileloop).continue_to = (yyvsp[-8].whileloop).begin_label;
			sprintf(codestr, ": %s", (yyvsp[-8].whileloop).exit_label); emitCode(codestr);
		 }
#line 1793 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 306 "mini_l.y" /* yacc.c:1646  */
    {
		 	(yyval.whileloop).begin_label = newlabel();
		 }
#line 1801 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 308 "mini_l.y" /* yacc.c:1646  */
    {
			pushLoopStack((yyvsp[-2].whileloop).begin_label);
			sprintf(codestr, ": %s", (yyvsp[-2].whileloop).begin_label); emitCode(codestr);
		 }
#line 1810 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 311 "mini_l.y" /* yacc.c:1646  */
    {
			sprintf(codestr, "?:= %s, %s", (yyvsp[-7].whileloop).begin_label, (yyvsp[0].typeNode).name); emitCode(codestr);
		 	(yyval.whileloop) = (yyvsp[-7].whileloop);
			(yyval.whileloop).continue_to = (yyvsp[-7].whileloop).begin_label;
		 }
#line 1820 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 316 "mini_l.y" /* yacc.c:1646  */
    { 
			/*if ($2.t == m_int) {
				sprintf(codestr, ".< %s", $2.name); emitCode(codestr); 
		 	} else {
				sprintf(codestr, ".[]< %s, %s", $2.name, $2.index); emitCode(codestr);
			}*/

			split_read((yyvsp[0].typeNode).name, (yyvsp[0].typeNode).t, (yyvsp[0].typeNode).index);
		 }
#line 1834 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 325 "mini_l.y" /* yacc.c:1646  */
    { 
			/*if ($2.t == m_int) {
				sprintf(codestr, ".> %s", $2.name); emitCode(codestr); 
		 	} else {
				sprintf(codestr, ".[]> %s, %s", $2.name, $2.index); emitCode(codestr);
			}*/

			split_write((yyvsp[0].typeNode).name, (yyvsp[0].typeNode).t, (yyvsp[0].typeNode).index);
		 }
#line 1848 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 336 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1854 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 337 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1860 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 340 "mini_l.y" /* yacc.c:1646  */
    { (yyval.typeNode) = (yyvsp[0].typeNode); }
#line 1866 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 341 "mini_l.y" /* yacc.c:1646  */
    { (yyval.typeNode).name = concat((yyval.typeNode).name, concat(",", (yyvsp[0].typeNode).name)); }
#line 1872 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 344 "mini_l.y" /* yacc.c:1646  */
    {(yyval.string_list) = "==";}
#line 1878 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 345 "mini_l.y" /* yacc.c:1646  */
    {(yyval.string_list) = "!=";}
#line 1884 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 346 "mini_l.y" /* yacc.c:1646  */
    {(yyval.string_list) = "<";}
#line 1890 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 347 "mini_l.y" /* yacc.c:1646  */
    {(yyval.string_list) = ">";}
#line 1896 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 348 "mini_l.y" /* yacc.c:1646  */
    {(yyval.string_list) = "<=";}
#line 1902 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 349 "mini_l.y" /* yacc.c:1646  */
    {(yyval.string_list) = ">=";}
#line 1908 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 352 "mini_l.y" /* yacc.c:1646  */
    { 
	(yyval.typeNode).name = (yyvsp[0].string_list); (yyval.typeNode).t = m_int; 
}
#line 1916 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 355 "mini_l.y" /* yacc.c:1646  */
    { 
	if (!checkType((yyvsp[-1].typeNode).t, m_int)) reg_type_error("Array access expression is not of type int"); 
	if (fetch((yyvsp[-3].string_list))) if (!checkType(fetch((yyvsp[-3].string_list))->type, m_array)) reg_type_error("Attempting to use an integer like an array");
	(yyval.typeNode).name = (yyvsp[-3].string_list); (yyval.typeNode).t = m_array; (yyval.typeNode).index = (yyvsp[-1].typeNode).name;
}
#line 1926 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 361 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1932 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 362 "mini_l.y" /* yacc.c:1646  */
    {
			if (!(checkType((yyvsp[-2].typeNode).t, (yyvsp[0].typeNode).t) && checkType((yyvsp[-2].typeNode).t, m_int)))
				reg_type_error("Expression uses non int types");
			(yyval.typeNode).name = newtemp();
			sprintf(codestr, ". %s", (yyval.typeNode).name); emitCode(codestr);
			sprintf(codestr, "+ %s, %s, %s", (yyval.typeNode).name, (yyvsp[-2].typeNode).name, (yyvsp[0].typeNode).name); emitCode(codestr);
		  }
#line 1944 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 369 "mini_l.y" /* yacc.c:1646  */
    {
		  	if (!(checkType((yyvsp[-2].typeNode).t, (yyvsp[0].typeNode).t) && checkType((yyvsp[-2].typeNode).t, m_int)))
				reg_type_error("Expression uses non int types");
			(yyval.typeNode).name = newtemp();
			sprintf(codestr, ". %s", (yyval.typeNode).name); emitCode(codestr);
			sprintf(codestr, "- %s, %s, %s", (yyval.typeNode).name, (yyvsp[-2].typeNode).name, (yyvsp[0].typeNode).name); emitCode(codestr);
		  }
#line 1956 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 378 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1962 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 379 "mini_l.y" /* yacc.c:1646  */
    {
				   		if (!(checkType((yyvsp[-2].typeNode).t, (yyvsp[0].typeNode).t) && checkType((yyvsp[-2].typeNode).t, m_int)))
							reg_type_error("Expression uses non int types");
						(yyval.typeNode).name = newtemp();
						sprintf(codestr, ". %s", (yyval.typeNode).name); emitCode(codestr);
						sprintf(codestr, "* %s, %s, %s", (yyval.typeNode).name, (yyvsp[-2].typeNode).name, (yyvsp[0].typeNode).name); emitCode(codestr);
				   }
#line 1974 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 386 "mini_l.y" /* yacc.c:1646  */
    {
						if (!(checkType((yyvsp[-2].typeNode).t, (yyvsp[0].typeNode).t) && checkType((yyvsp[-2].typeNode).t, m_int)))
							reg_type_error("Expression uses non int types");
						(yyval.typeNode).name = newtemp();
						sprintf(codestr, ". %s", (yyval.typeNode).name); emitCode(codestr);
						sprintf(codestr, "/ %s, %s, %s", (yyval.typeNode).name, (yyvsp[-2].typeNode).name, (yyvsp[0].typeNode).name); emitCode(codestr);
				   }
#line 1986 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 393 "mini_l.y" /* yacc.c:1646  */
    {
						if (!(checkType((yyvsp[-2].typeNode).t, (yyvsp[0].typeNode).t) && checkType((yyvsp[-2].typeNode).t, m_int)))
							reg_type_error("Expression uses non int types");
						(yyval.typeNode).name = newtemp();
						sprintf(codestr, ". %s", (yyval.typeNode).name); emitCode(codestr);
						sprintf(codestr, "%% %s, %s, %s", (yyval.typeNode).name, (yyvsp[-2].typeNode).name, (yyvsp[0].typeNode).name); emitCode(codestr);
				   }
#line 1998 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 402 "mini_l.y" /* yacc.c:1646  */
    { (yyval.typeNode) = (yyvsp[0].typeNode); }
#line 2004 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 403 "mini_l.y" /* yacc.c:1646  */
    {
			(yyval.typeNode).name = newtemp();
			sprintf(codestr, ". %s", (yyval.typeNode).name); emitCode(codestr);
			sprintf(codestr, "|| %s, %s, %s", (yyval.typeNode).name, (yyvsp[-2].typeNode).name, (yyvsp[0].typeNode).name); emitCode(codestr);
		}
#line 2014 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 410 "mini_l.y" /* yacc.c:1646  */
    { (yyval.typeNode) = (yyvsp[0].typeNode); }
#line 2020 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 411 "mini_l.y" /* yacc.c:1646  */
    {
					(yyval.typeNode).name = newtemp();
				 	sprintf(codestr, ". %s", (yyval.typeNode).name); emitCode(codestr);
				 	sprintf(codestr, "&& %s, %s, %s", (yyval.typeNode).name, (yyvsp[-2].typeNode).name, (yyvsp[0].typeNode).name); emitCode(codestr);
	 		     }
#line 2030 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 418 "mini_l.y" /* yacc.c:1646  */
    { 
	if (!(checkType((yyvsp[-2].typeNode).t, (yyvsp[0].typeNode).t) && checkType((yyvsp[-2].typeNode).t, m_int))) 
		reg_type_error("Comparison does not compare two int expressions"); 
	(yyval.typeNode).t = m_bool; 
	char* temp_c = newtemp();
	sprintf(codestr, ". %s", temp_c); emitCode(codestr);
	sprintf(codestr, "%s %s, %s, %s", (yyvsp[-1].string_list), temp_c, (yyvsp[-2].typeNode).name, (yyvsp[0].typeNode).name); emitCode(codestr);
	(yyval.typeNode).name = temp_c;
	}
#line 2044 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 427 "mini_l.y" /* yacc.c:1646  */
    { 
	(yyval.typeNode).t = m_bool; 
	(yyval.typeNode).name = "1";
	}
#line 2053 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 431 "mini_l.y" /* yacc.c:1646  */
    {
	(yyval.typeNode).t = m_bool;
	(yyval.typeNode).name = "0"; 
	}
#line 2062 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 435 "mini_l.y" /* yacc.c:1646  */
    { 
	(yyval.typeNode).t = m_bool; 
	(yyval.typeNode).name = (yyvsp[-1].typeNode).name; 
	}
#line 2071 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 439 "mini_l.y" /* yacc.c:1646  */
    { 
	if (!(checkType((yyvsp[-2].typeNode).t, (yyvsp[0].typeNode).t) && checkType((yyvsp[-2].typeNode).t, m_int))) 
		reg_type_error("Comparison does not compare two int expressions"); 
	(yyval.typeNode).t = m_bool;

	(yyval.typeNode).name = newtemp();
	sprintf(codestr, ". %s", (yyval.typeNode).name); emitCode(codestr);
	
	char* temp = newtemp();
	sprintf(temp, ". %s", temp); emitCode(codestr);
	sprintf(codestr, "%s %s, %s, %s", (yyvsp[-1].string_list), temp, (yyvsp[-2].typeNode).name, (yyvsp[0].typeNode).name); emitCode(codestr);
	sprintf(codestr, "! %s, %s", (yyval.typeNode).name, temp); emitCode(codestr);
	}
#line 2089 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 452 "mini_l.y" /* yacc.c:1646  */
    { 
	(yyval.typeNode).t = m_bool; 
	(yyval.typeNode).name = "0";
	}
#line 2098 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 456 "mini_l.y" /* yacc.c:1646  */
    { 
	(yyval.typeNode).t = m_bool; 
	(yyval.typeNode).name = "1";
	}
#line 2107 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 460 "mini_l.y" /* yacc.c:1646  */
    { 
	(yyval.typeNode).t = m_bool; 
	(yyval.typeNode).name = newtemp();
	sprintf(codestr, "! %s, %s", (yyval.typeNode).name, (yyvsp[-1].typeNode).name); emitCode(codestr);
	}
#line 2117 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 467 "mini_l.y" /* yacc.c:1646  */
    { 
	if (fetch((yyvsp[0].typeNode).name)) {
		(yyval.typeNode) = (yyvsp[0].typeNode); 
	} else {
		reg_type_error("Symbol does not exist in the symbol table");
	}
	int curr_type;
	if (fetch((yyvsp[0].typeNode).name)) {
		curr_type = fetch((yyvsp[0].typeNode).name)->type;
	} else {
		curr_type = (yyvsp[0].typeNode).t;
	}
	if (curr_type == m_int) {
		(yyval.typeNode).name = newtemp(); 
		sprintf(codestr, ". %s", (yyval.typeNode).name); emitCode(codestr); 
		sprintf(codestr, "= %s, %s", (yyval.typeNode).name, (yyvsp[0].typeNode).name); emitCode(codestr);
	} else {
		(yyval.typeNode).name = newtemp();
		sprintf(codestr, ". %s", (yyval.typeNode).name); emitCode(codestr);
		
		if (!(yyvsp[0].typeNode).index) 
			reg_type_error("Used array variable missing a specified index");
		
		sprintf(codestr, "=[] %s, %s, %s", (yyval.typeNode).name, (yyvsp[0].typeNode).name, (yyvsp[0].typeNode).index); emitCode(codestr);	
		(yyval.typeNode).t = m_int;
	}
	}
#line 2149 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 494 "mini_l.y" /* yacc.c:1646  */
    { 
	(yyval.typeNode).t = m_int; 
	(yyval.typeNode).name = newtemp();	
	sprintf(codestr, ". %s", (yyval.typeNode).name); emitCode(codestr); 
	sprintf(codestr, "= %s, %d", (yyval.typeNode).name, (int)(yyvsp[0].dval)); emitCode(codestr);
	}
#line 2160 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 500 "mini_l.y" /* yacc.c:1646  */
    { 
	if (!checkType((yyvsp[-1].typeNode).t, m_int)) 
		reg_type_error("Expression is not an int type"); 
	(yyval.typeNode) = (yyvsp[-1].typeNode); 
	}
#line 2170 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 505 "mini_l.y" /* yacc.c:1646  */
    { 
	(yyval.typeNode) = (yyvsp[0].typeNode);
	(yyval.typeNode).name = newtemp();
	sprintf(codestr, ". %s", (yyval.typeNode).name); emitCode(codestr);
	sprintf(codestr, "* %s, %s, -1", (yyval.typeNode).name, (yyvsp[0].typeNode).name); emitCode(codestr);
	}
#line 2181 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 511 "mini_l.y" /* yacc.c:1646  */
    { 
	(yyval.typeNode).t = m_int;	
	(yyval.typeNode).name = newtemp();
	sprintf(codestr, ". %s", (yyval.typeNode).name); emitCode(codestr);
	sprintf(codestr, "* %s, %d, -1", (yyval.typeNode).name, (int)(yyvsp[0].dval)); emitCode(codestr);
	}
#line 2192 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 517 "mini_l.y" /* yacc.c:1646  */
    { 
	if (!checkType((yyvsp[-1].typeNode).t, m_int)) 
		reg_type_error("Expression is not an int type"); 
	(yyval.typeNode).t = m_int; 
	
	(yyval.typeNode).name = newtemp();
	sprintf(codestr, ". %s", (yyval.typeNode).name); emitCode(codestr);
	sprintf(codestr, "* %s, %s, -1", (yyval.typeNode).name, (yyvsp[-1].typeNode).name); emitCode(codestr);
    }
#line 2206 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 526 "mini_l.y" /* yacc.c:1646  */
    { 
		(yyval.typeNode).t = m_int;
		(yyval.typeNode).name = newtemp();	
		sprintf(codestr, "param %s", (yyvsp[-1].typeNode).name); emitCode(codestr);
		/*NOTE WILL PROBABLY NEED TO IMPLEMENT SPLIT EMIT FOR PARAMS*/
		sprintf(codestr, ". %s", (yyval.typeNode).name); emitCode(codestr);

		if (!fetch((yyvsp[-3].string_list))) {
			reg_type_error("Function being called was not defined");
		}
		sprintf(codestr, "call %s, %s", (yyvsp[-3].string_list), (yyval.typeNode).name); emitCode(codestr);
	}
#line 2223 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 540 "mini_l.y" /* yacc.c:1646  */
    { 
		   }
#line 2230 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 542 "mini_l.y" /* yacc.c:1646  */
    {}
#line 2236 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2240 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 545 "mini_l.y" /* yacc.c:1906  */


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

