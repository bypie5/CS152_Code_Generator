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

#line 128 "y.tab.c" /* yacc.c:339  */

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
#line 63 "mini_l.y" /* yacc.c:355  */

	double dval;
	char* string_list;

	struct typeNode {
		char* name; // Useful for code generation
		char* code;
		int t;
		int size;
	} typeNode;	

#line 232 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 249 "y.tab.c" /* yacc.c:358  */

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
#define YYLAST   177

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  147

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
       0,    88,    88,    89,    92,    95,    96,    99,    99,   102,
     103,   106,   108,   109,   111,   112,   115,   117,   118,   121,
     124,   127,   128,   128,   132,   133,   134,   135,   138,   139,
     142,   143,   146,   147,   148,   149,   150,   151,   154,   157,
     162,   163,   170,   179,   180,   187,   194,   203,   206,   207,
     210,   213,   214,   217,   227,   228,   229,   230,   232,   233,
     234,   237,   243,   249,   255,   258,   261,   268,   278,   283
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
  "declarations", "declaration", "declaration_prime", "identifiers",
  "identifier", "statements", "statement", "$@2", "else_prime", "vars",
  "comp", "var", "expression", "multiplicative_expr", "boolexpr", "r_a_es",
  "relation_and_expr", "r_es", "relation_expr", "term", "expressions", YY_NULLPTR
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

#define YYPACT_NINF -67

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-67)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       5,   -29,    36,   -67,   -67,     5,   -67,   -67,   -67,    -9,
      34,    -2,   -67,    38,    14,    16,    30,    78,    -2,    40,
      -2,    -2,   -67,   -67,    42,   -67,   -67,    91,    46,    96,
      65,    88,   113,    41,    41,   108,   -67,    -2,    -2,    31,
      82,   121,    92,    83,   122,     3,   -67,   -67,   -31,    41,
     -67,   -43,   -67,   117,    44,   -67,   110,   125,   -67,   131,
      88,   -67,   115,   -67,    31,    85,    31,   -67,    88,    31,
     -67,   -67,   -67,    41,   117,    31,   -67,   -67,   106,   114,
      31,    31,    31,   -67,   -67,   -67,   -67,   -67,   -67,    31,
      31,    31,    31,   146,    41,   -67,    41,   -67,    88,   141,
      -2,    15,    -7,   -67,    85,   118,    31,    52,   -67,   -67,
      90,   119,    44,    44,    85,   -67,   -67,   -67,    88,   110,
     125,   142,   148,   -67,   -67,   -67,    85,   -67,    69,   123,
     -67,   151,   -67,   -67,   -67,    41,    31,   -67,   -67,   -67,
      88,   153,   -67,    63,   -67,   -67,   -67
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     3,     4,     5,     7,     1,     6,     0,
       0,     9,    16,     0,     0,     0,    14,     0,     9,     0,
       0,     9,    10,    12,     0,    11,    15,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    21,     0,     0,     0,
      38,     0,     0,     0,     0,     0,    54,    55,     0,     0,
      62,    38,    61,     0,    40,    22,    48,    51,    43,     0,
       0,    26,    30,    27,     0,    20,     0,     8,    17,     0,
      13,    58,    59,     0,     0,     0,    65,    64,     0,     0,
       0,     0,     0,    32,    33,    34,    35,    36,    37,     0,
       0,     0,     0,     0,     0,    47,     0,    50,     0,     0,
       0,     0,     0,    18,    19,     0,     0,     0,    63,    56,
      68,     0,    42,    41,    53,    44,    45,    46,     0,    48,
      51,     0,     0,    31,    39,    60,    57,    66,     0,     0,
      67,    28,    49,    52,    24,     0,     0,    62,    61,    69,
       0,     0,    25,     0,    29,    23,    63
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -67,   -67,   -67,   164,   -67,   -67,     7,   -67,   -67,   150,
     -11,   -54,   -67,   -67,   -67,   -34,    97,   -26,   -10,   -66,
     -32,    53,    79,    54,    80,    32,    67
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,     5,     9,    13,    14,    25,    15,
      51,    41,    42,    93,   141,    61,    89,    52,    53,    54,
      55,    95,    56,    97,    57,    58,   111
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      16,    80,    59,    66,    63,    43,    99,    16,     1,    16,
      16,    62,    62,    75,   103,   112,   113,    79,    76,    12,
      40,     6,    77,    81,    82,    22,    40,    40,    27,    65,
      71,    72,    10,    48,    43,    74,     7,    40,    11,    78,
     124,   105,    43,    17,   121,    81,    82,    73,    12,    40,
      23,    24,    50,    12,   101,    18,   102,    40,    19,   104,
     108,    48,   112,    78,   131,   107,   123,    45,    46,    47,
     110,    48,    43,    20,    62,    64,    90,    91,    92,   114,
      50,    12,    81,    82,    21,    49,   144,    40,    28,    40,
      50,    12,    43,    81,    82,    30,   126,   127,    29,    48,
     110,    33,   138,   142,    31,    34,    35,    40,   146,    36,
      37,    38,    32,   136,    43,    81,    82,    39,   137,    12,
     128,    82,   115,   116,   117,    44,   143,    60,    66,    40,
      67,    69,    70,    68,    64,    94,    81,    82,    12,    50,
      12,    83,    84,    85,    86,    87,    88,    81,    82,    96,
      98,   108,    83,    84,    85,    86,    87,    88,   100,   109,
     118,   122,   134,   125,   130,   135,   139,   140,   145,     8,
      26,   106,   132,   119,   133,     0,   120,   129
};

static const yytype_int16 yycheck[] =
{
      11,    44,    34,    46,    38,    31,    60,    18,     3,    20,
      21,    37,    38,    44,    68,    81,    82,    49,    49,    50,
      31,    50,    48,    30,    31,    18,    37,    38,    21,    39,
      27,    28,    41,    30,    60,    45,     0,    48,     4,    49,
      47,    73,    68,     5,    98,    30,    31,    44,    50,    60,
      10,    11,    49,    50,    64,    41,    66,    68,    42,    69,
      45,    30,   128,    73,   118,    75,   100,    26,    27,    28,
      80,    30,    98,    43,   100,    44,    32,    33,    34,    89,
      49,    50,    30,    31,     6,    44,   140,    98,    46,   100,
      49,    50,   118,    30,    31,    49,   106,    45,     7,    30,
     110,    13,   128,   135,     8,    17,    18,   118,    45,    21,
      22,    23,    47,    44,   140,    30,    31,    29,    49,    50,
      30,    31,    90,    91,    92,    12,   136,    19,    46,   140,
       9,    48,    10,    41,    44,    25,    30,    31,    50,    49,
      50,    35,    36,    37,    38,    39,    40,    30,    31,    24,
      19,    45,    35,    36,    37,    38,    39,    40,    43,    45,
      14,    20,    20,    45,    45,    17,    43,    16,    15,     5,
      20,    74,   119,    94,   120,    -1,    96,   110
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    53,    54,    55,    56,    50,     0,    55,    57,
      41,     4,    50,    58,    59,    61,    62,     5,    41,    42,
      43,     6,    58,    10,    11,    60,    61,    58,    46,     7,
      49,     8,    47,    13,    17,    18,    21,    22,    23,    29,
      62,    63,    64,    69,    12,    26,    27,    28,    30,    44,
      49,    62,    69,    70,    71,    72,    74,    76,    77,    72,
      19,    67,    69,    67,    44,    70,    46,     9,    41,    48,
      10,    27,    28,    44,    70,    44,    49,    69,    70,    72,
      44,    30,    31,    35,    36,    37,    38,    39,    40,    68,
      32,    33,    34,    65,    25,    73,    24,    75,    19,    63,
      43,    70,    70,    63,    70,    72,    68,    70,    45,    45,
      70,    78,    71,    71,    70,    77,    77,    77,    14,    74,
      76,    63,    20,    67,    47,    45,    70,    45,    30,    78,
      45,    63,    73,    75,    20,    17,    44,    49,    69,    43,
      16,    66,    72,    70,    63,    15,    45
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    52,    53,    53,    54,    55,    55,    57,    56,    58,
      58,    59,    60,    60,    61,    61,    62,    63,    63,    64,
      64,    64,    65,    64,    64,    64,    64,    64,    66,    66,
      67,    67,    68,    68,    68,    68,    68,    68,    69,    69,
      70,    70,    70,    71,    71,    71,    71,    72,    73,    73,
      74,    75,    75,    76,    76,    76,    76,    76,    76,    76,
      76,    77,    77,    77,    77,    77,    77,    77,    78,    78
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     1,     1,     2,     0,    13,     0,
       3,     3,     1,     6,     1,     3,     1,     2,     3,     3,
       2,     1,     0,     7,     5,     6,     2,     2,     0,     2,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     4,
       1,     3,     3,     1,     3,     3,     3,     2,     0,     3,
       2,     0,     3,     3,     1,     1,     3,     4,     2,     2,
       4,     1,     1,     3,     2,     2,     4,     4,     1,     3
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
#line 88 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1432 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 89 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1438 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 92 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1444 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 95 "mini_l.y" /* yacc.c:1646  */
    { }
#line 1450 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 96 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1456 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 99 "mini_l.y" /* yacc.c:1646  */
    { sprintf(codestr, "func %s", (yyvsp[0].string_list)); emitCode(codestr); insert((yyvsp[0].string_list), m_void); }
#line 1462 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 99 "mini_l.y" /* yacc.c:1646  */
    { sprintf(codestr, "endfunc\n"); emitCode(codestr); }
#line 1468 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 102 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1474 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 103 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1480 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 106 "mini_l.y" /* yacc.c:1646  */
    { split_insert((yyvsp[-2].string_list), (yyvsp[0].typeNode).t); split_emit((yyvsp[-2].string_list), (yyvsp[0].typeNode).t, (yyvsp[0].typeNode).size); }
#line 1486 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 108 "mini_l.y" /* yacc.c:1646  */
    { (yyval.typeNode).t = m_int; }
#line 1492 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 109 "mini_l.y" /* yacc.c:1646  */
    { (yyval.typeNode).t = m_array; (yyval.typeNode).size = (int) (yyvsp[-3].dval); }
#line 1498 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 111 "mini_l.y" /* yacc.c:1646  */
    { (yyval.string_list) = (yyvsp[0].string_list); }
#line 1504 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 112 "mini_l.y" /* yacc.c:1646  */
    { (yyval.string_list) = concat((yyval.string_list), concat(",", (yyvsp[0].string_list))); }
#line 1510 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 115 "mini_l.y" /* yacc.c:1646  */
    { (yyval.string_list) = (yyvsp[0].string_list); }
#line 1516 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 117 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1522 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 118 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1528 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 121 "mini_l.y" /* yacc.c:1646  */
    { if (fetch((yyvsp[-2].typeNode).name)) if (!checkType((yyvsp[-2].typeNode).t, (yyvsp[0].typeNode).t)) reg_type_error("Mismatched assignment"); 
		 						 	sprintf(codestr, "= %s, %s", (yyvsp[-2].typeNode).name, (yyvsp[0].typeNode).name); emitCode(codestr);
								 }
#line 1536 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 124 "mini_l.y" /* yacc.c:1646  */
    { if (!checkType((yyvsp[0].typeNode).t, m_int)) reg_type_error("Trying to return a non int type");
			sprintf(codestr, "ret %s", (yyvsp[0].typeNode).name); emitCode(codestr);
		 }
#line 1544 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 127 "mini_l.y" /* yacc.c:1646  */
    { }
#line 1550 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 128 "mini_l.y" /* yacc.c:1646  */
    {
			char*temp = newlabel();
			sprintf(codestr, "?:= %s, %s", temp, (yyvsp[0].typeNode).name); emitCode(codestr);
		 }
#line 1559 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 131 "mini_l.y" /* yacc.c:1646  */
    { if ((yyvsp[-5].typeNode).t != m_bool) reg_type_error("If statement does not contain a boolean expression"); }
#line 1565 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 132 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1571 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 133 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1577 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 134 "mini_l.y" /* yacc.c:1646  */
    { sprintf(codestr, ".< %s", (yyvsp[0].typeNode).name); emitCode(codestr); }
#line 1583 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 135 "mini_l.y" /* yacc.c:1646  */
    { sprintf(codestr, ".> %s", (yyvsp[0].typeNode).name); emitCode(codestr); }
#line 1589 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 138 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1595 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 139 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1601 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 142 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1607 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 143 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1613 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 146 "mini_l.y" /* yacc.c:1646  */
    {(yyval.string_list) = "==";}
#line 1619 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 147 "mini_l.y" /* yacc.c:1646  */
    {(yyval.string_list) = "!=";}
#line 1625 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 148 "mini_l.y" /* yacc.c:1646  */
    {(yyval.string_list) = "<";}
#line 1631 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 149 "mini_l.y" /* yacc.c:1646  */
    {(yyval.string_list) = ">";}
#line 1637 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 150 "mini_l.y" /* yacc.c:1646  */
    {(yyval.string_list) = "<=";}
#line 1643 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 151 "mini_l.y" /* yacc.c:1646  */
    {(yyval.string_list) = ">=";}
#line 1649 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 154 "mini_l.y" /* yacc.c:1646  */
    { 
   (yyval.typeNode).name = (yyvsp[0].string_list); (yyval.typeNode).t = m_int; 
}
#line 1657 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 157 "mini_l.y" /* yacc.c:1646  */
    { 
	if (!checkType((yyvsp[-1].typeNode).t, m_int)) reg_type_error("Array access expression is not of type int"); 
	else { (yyval.typeNode).name = (yyvsp[-3].string_list); (yyval.typeNode).t = m_int; }
}
#line 1666 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 162 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1672 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 163 "mini_l.y" /* yacc.c:1646  */
    {
			if (!(checkType((yyvsp[-2].typeNode).t, (yyvsp[0].typeNode).t) && checkType((yyvsp[-2].typeNode).t, m_int)))
				reg_type_error("Expression uses non int types");
			(yyval.typeNode).name = newtemp();
			sprintf(codestr, ". %s", (yyval.typeNode).name); emitCode(codestr);
			sprintf(codestr, "+ %s, %s, %s", (yyval.typeNode).name, (yyvsp[-2].typeNode).name, (yyvsp[0].typeNode).name); emitCode(codestr);
		  }
#line 1684 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 170 "mini_l.y" /* yacc.c:1646  */
    {
		  	if (!(checkType((yyvsp[-2].typeNode).t, (yyvsp[0].typeNode).t) && checkType((yyvsp[-2].typeNode).t, m_int)))
				reg_type_error("Expression uses non int types");
			(yyval.typeNode).name = newtemp();
			sprintf(codestr, ". %s", (yyval.typeNode).name); emitCode(codestr);
			sprintf(codestr, "- %s, %s, %s", (yyval.typeNode).name, (yyvsp[-2].typeNode).name, (yyvsp[0].typeNode).name); emitCode(codestr);
		  }
#line 1696 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 179 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1702 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 180 "mini_l.y" /* yacc.c:1646  */
    {
				   		if (!(checkType((yyvsp[-2].typeNode).t, (yyvsp[0].typeNode).t) && checkType((yyvsp[-2].typeNode).t, m_int)))
							reg_type_error("Expression uses non int types");
						(yyval.typeNode).name = newtemp();
						sprintf(codestr, ". %s", (yyval.typeNode).name); emitCode(codestr);
						sprintf(codestr, "* %s, %s, %s", (yyval.typeNode).name, (yyvsp[-2].typeNode).name, (yyvsp[0].typeNode).name); emitCode(codestr);
				   }
#line 1714 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 187 "mini_l.y" /* yacc.c:1646  */
    {
						if (!(checkType((yyvsp[-2].typeNode).t, (yyvsp[0].typeNode).t) && checkType((yyvsp[-2].typeNode).t, m_int)))
							reg_type_error("Expression uses non int types");
						(yyval.typeNode).name = newtemp();
						sprintf(codestr, ". %s", (yyval.typeNode).name); emitCode(codestr);
						sprintf(codestr, "/ %s, %s, %s", (yyval.typeNode).name, (yyvsp[-2].typeNode).name, (yyvsp[0].typeNode).name); emitCode(codestr);
				   }
#line 1726 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 194 "mini_l.y" /* yacc.c:1646  */
    {
						if (!(checkType((yyvsp[-2].typeNode).t, (yyvsp[0].typeNode).t) && checkType((yyvsp[-2].typeNode).t, m_int)))
							reg_type_error("Expression uses non int types");
						(yyval.typeNode).name = newtemp();
						sprintf(codestr, ". %s", (yyval.typeNode).name); emitCode(codestr);
						sprintf(codestr, "% %s, %s, %s", (yyval.typeNode).name, (yyvsp[-2].typeNode).name, (yyvsp[0].typeNode).name); emitCode(codestr);
				   }
#line 1738 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 203 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1744 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 206 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1750 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 207 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1756 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 210 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1762 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 213 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1768 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 214 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1774 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 217 "mini_l.y" /* yacc.c:1646  */
    { 
	if (!(checkType((yyvsp[-2].typeNode).t, (yyvsp[0].typeNode).t) && checkType((yyvsp[-2].typeNode).t, m_int))) 
		reg_type_error("Comparison does not compare two int expressions"); 
	else (yyval.typeNode).t = m_bool; 
	char* temp_c = newtemp();
	sprintf(codestr, ". %s", temp_c); emitCode(codestr);
	sprintf(codestr, "%s %s, %s, %s", (yyvsp[-1].string_list), temp_c, (yyvsp[-2].typeNode).name, (yyvsp[0].typeNode).name); emitCode(codestr);
	
	(yyval.typeNode).name = temp_c;
	}
#line 1789 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 227 "mini_l.y" /* yacc.c:1646  */
    { (yyval.typeNode).t = m_bool; }
#line 1795 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 228 "mini_l.y" /* yacc.c:1646  */
    { (yyval.typeNode).t = m_bool; }
#line 1801 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 229 "mini_l.y" /* yacc.c:1646  */
    { (yyval.typeNode).t = m_bool; }
#line 1807 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 230 "mini_l.y" /* yacc.c:1646  */
    { 
	if (!(checkType((yyvsp[-2].typeNode).t, (yyvsp[0].typeNode).t) && checkType((yyvsp[-2].typeNode).t, m_int))) reg_type_error("Comparison does not compare two int expressions"); else (yyval.typeNode).t = m_bool;}
#line 1814 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 232 "mini_l.y" /* yacc.c:1646  */
    { (yyval.typeNode).t = m_bool; }
#line 1820 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 233 "mini_l.y" /* yacc.c:1646  */
    { (yyval.typeNode).t = m_bool; }
#line 1826 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 234 "mini_l.y" /* yacc.c:1646  */
    { (yyval.typeNode).t = m_bool; }
#line 1832 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 237 "mini_l.y" /* yacc.c:1646  */
    { 
	if (fetch((yyvsp[0].typeNode).name)) (yyval.typeNode) = (yyvsp[0].typeNode); 
	(yyval.typeNode).name = newtemp(); 
	sprintf(codestr, ". %s", (yyval.typeNode).name); emitCode(codestr); 
	sprintf(codestr, "= %s, %s", (yyval.typeNode).name, (yyvsp[0].typeNode).name); emitCode(codestr);
	}
#line 1843 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 243 "mini_l.y" /* yacc.c:1646  */
    { 
	(yyval.typeNode).t = m_int; 
	(yyval.typeNode).name = newtemp();	
	sprintf(codestr, ". %s", (yyval.typeNode).name); emitCode(codestr); 
	sprintf(codestr, "= %s, %d", (yyval.typeNode).name, (int)(yyvsp[0].dval)); emitCode(codestr);
	}
#line 1854 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 249 "mini_l.y" /* yacc.c:1646  */
    { 
	if (!checkType((yyvsp[-1].typeNode).t, m_int)) 
		reg_type_error("Expression is not an int type"); 
	else 
		(yyval.typeNode) = (yyvsp[-1].typeNode); 
	}
#line 1865 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 255 "mini_l.y" /* yacc.c:1646  */
    { 
	(yyval.typeNode) = (yyvsp[0].typeNode); (yyval.typeNode).name = "subtest2";
	}
#line 1873 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 258 "mini_l.y" /* yacc.c:1646  */
    { 
	(yyval.typeNode).t = m_int; (yyval.typeNode).name = "a"; 
	}
#line 1881 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 261 "mini_l.y" /* yacc.c:1646  */
    { 
	if (!checkType((yyvsp[-1].typeNode).t, m_int)) 
		reg_type_error("Expression is not an int type"); 
	else 
		(yyval.typeNode).t = m_int; 
	(yyval.typeNode).name = "subtest";
	}
#line 1893 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 268 "mini_l.y" /* yacc.c:1646  */
    { 
		(yyval.typeNode).t = m_int;
		(yyval.typeNode).name = newtemp();	
		sprintf(codestr, "param %s", (yyvsp[-1].typeNode).name); emitCode(codestr);
		/*NOTE WILL PROBABLY NEED TO IMPLEMENT SPLIT EMIT FOR PARAMS*/
		sprintf(codestr, ". %s", (yyval.typeNode).name); emitCode(codestr);
		sprintf(codestr, "call %s, %s", (yyvsp[-3].string_list), (yyval.typeNode).name); emitCode(codestr);
	}
#line 1906 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 278 "mini_l.y" /* yacc.c:1646  */
    { 
		   /*$$.name = newtemp(); 
		   sprintf(codestr, ". %s", $$.name); emitCode(codestr);
		   sprintf(codestr, "= %s, %s", $$.name, $1.name); emitCode(codestr);*/
		   }
#line 1916 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 283 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1922 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1926 "y.tab.c" /* yacc.c:1646  */
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
#line 286 "mini_l.y" /* yacc.c:1906  */


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

