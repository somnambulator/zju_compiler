/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "/home/yuanli/zju_compiler/src/parser.ypp"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "ast.hpp"

// using namespace std;

extern int yylex(void);
extern int yyparse(void);
extern void yyrestart(FILE*);
extern void yyerror(char*);
extern int yylineno;
extern int errorLexFlag;
extern int errorSyntaxFlag;

ProgramAST* Program;

// extern int yyparse(yyFlexLexer* yyflex);

#line 91 "parser.y.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PARSER_Y_HPP_INCLUDED
# define YY_YY_PARSER_Y_HPP_INCLUDED
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
    COLON = 258,
    COMMA = 259,
    LC = 260,
    RC = 261,
    FUNCSPEC = 262,
    SEMI = 263,
    STRUCT = 264,
    IF = 265,
    WHILE = 266,
    TYPE = 267,
    ELSE = 268,
    DEF = 269,
    RETURN = 270,
    MAIN = 271,
    ID = 272,
    INT = 273,
    FLOAT = 274,
    ASSIGNOP = 275,
    OR = 276,
    AND = 277,
    RELOP = 278,
    ADD = 279,
    SUB = 280,
    MUL = 281,
    DIV = 282,
    NOT = 283,
    DOT = 284,
    LB = 285,
    RB = 286,
    LP = 287,
    RP = 288,
    LOWER_THAN_ELSE = 289
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 23 "/home/yuanli/zju_compiler/src/parser.ypp"

    int int_val;
    float float_val;

    std::string* name;
    std::string* op; 
    std::string* Str;

    ast_list* AST_list;
    ExprAST* exprAST;
    FunctionAST* functionAST;
    TypeAST* typeAST;
    PrototypeAST* prototypeAST;
    BodyAST* bodyAST;
    VariableExprAST* variableexprAST;
    DecExprAST* decexprAST;
    DecListAST* declistAST;

#line 197 "parser.y.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_Y_HPP_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  24
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   279

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  71
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  143

#define YYUNDEFTOK  2
#define YYMAXUTOK   289


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    82,    82,    84,    85,    87,    89,    90,    91,    92,
      94,    95,    97,    98,   102,   103,   105,   106,   108,   109,
     111,   115,   116,   117,   119,   120,   123,   125,   128,   130,
     131,   133,   136,   137,   138,   140,   141,   143,   144,   145,
     146,   147,   148,   150,   151,   153,   154,   156,   158,   159,
     161,   162,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   182,   183,   184,   185,   186,
     188,   189
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "COLON", "COMMA", "LC", "RC", "FUNCSPEC",
  "SEMI", "STRUCT", "IF", "WHILE", "TYPE", "ELSE", "DEF", "RETURN", "MAIN",
  "ID", "INT", "FLOAT", "ASSIGNOP", "OR", "AND", "RELOP", "ADD", "SUB",
  "MUL", "DIV", "NOT", "DOT", "LB", "RB", "LP", "RP", "LOWER_THAN_ELSE",
  "$accept", "Program", "ExtDefList", "ExtDef", "MainDef", "ExtDecList",
  "Specifier", "StructSpecifier", "OptTag", "Tag", "VarDec", "FunDec",
  "MainFunDec", "VarList", "ParamDec", "CompSt", "StmtList", "Stmt",
  "ReturnStmt", "DefList", "Def", "DecList", "Dec", "Exp", "Args", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289
};
# endif

#define YYPACT_NINF (-85)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-47)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     177,    14,   -11,   -85,    19,   -85,    44,   -85,   177,   -85,
      46,    63,   -85,     8,   -85,   -85,    58,    72,   -85,    56,
      61,    64,    98,   104,   -85,   -85,   -85,   -85,    67,    88,
      45,   -85,    78,     4,    83,    83,   109,    84,    97,    12,
     108,    55,   155,   139,   167,   172,    13,   147,   181,   175,
      55,   -85,   -85,    30,   -85,    67,   -85,   -85,   -85,    30,
      67,    67,    67,   180,    30,   -85,    80,   -85,   168,   -85,
     -85,   -85,   -85,    67,   -85,    86,   160,   163,   164,   -85,
     -85,   182,   182,   182,   -85,    -5,    80,   126,   182,   -85,
     -85,   182,   182,   165,   103,   -12,   195,   -85,    50,   205,
     -85,   -85,   182,   182,   182,   182,   182,   182,   182,   182,
     196,   182,   249,   209,   223,   -85,   115,   190,   -85,   -85,
     146,   -85,   249,   135,   179,    96,   103,   103,   -12,   -12,
     -85,   237,    99,    99,   182,   -85,   -85,   -85,   199,   -85,
     -85,    99,   -85
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    19,    14,     0,    21,     0,     2,     0,     4,
       0,     0,    15,     0,     9,    23,    20,     0,    17,     0,
       0,     0,     0,     0,     1,     3,     6,     7,     0,     0,
       0,    26,     0,     0,     0,     0,    12,     0,     0,     0,
       0,     0,     0,    48,     0,     0,     0,     0,    30,     0,
       0,     8,    10,     0,    22,     0,    16,    45,    47,     0,
       0,     0,     0,     0,     0,    34,     0,    13,    50,    49,
      27,    25,    31,     0,    29,     0,     0,     0,    67,    68,
      69,     0,     0,     0,    38,     0,     0,     0,     0,    24,
      42,     0,     0,     0,    61,    62,     0,    32,     0,     0,
      35,    37,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    51,     0,     0,    64,    71,     0,    60,    44,
       0,    33,    52,    54,    53,    55,    56,    57,    58,    59,
      66,     0,     0,     0,     0,    63,    43,    65,    39,    41,
      70,     0,    40
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -85,   -85,   218,   -85,   -85,   174,   -21,   -85,   -85,   -85,
       0,   -85,   -85,   173,   -85,    68,   154,   -84,   -85,     9,
     -85,   192,   -85,   -79,   107
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    10,    11,    12,    17,    18,
      39,    22,    23,    47,    48,    84,    85,    86,    99,    40,
      41,    42,    43,    87,   117
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      13,    97,    94,    95,    96,    38,    16,    36,    13,   112,
      98,    28,   113,   114,   116,    55,    62,   110,   111,   120,
      19,     5,    14,   122,   123,   124,   125,   126,   127,   128,
     129,    38,   131,    46,    68,    20,    21,    45,    29,    70,
      71,    72,    29,    29,    24,    15,    38,     5,   138,   139,
      57,   -46,    89,    13,    26,   116,    38,   142,   119,    66,
     -46,   -46,     5,   -18,    46,   -46,   -46,    78,    79,    80,
     -46,    27,     5,   -46,   -46,    81,     2,    30,    82,     3,
     -46,    75,    83,   -46,    49,    50,   -36,   -46,    50,    31,
      76,    77,    65,    32,    90,   -36,    33,    78,    79,    80,
      75,    34,    51,    52,    50,    81,    37,    35,    82,    76,
      77,    44,    83,    53,    56,    54,    78,    79,    80,   134,
     106,   107,   108,   109,    81,   110,   111,    82,    15,   108,
     109,    83,   110,   111,   101,   102,   103,   104,   105,   106,
     107,   108,   109,    59,   110,   111,   102,   103,   104,   105,
     106,   107,   108,   109,   136,   110,   111,   104,   105,   106,
     107,   108,   109,    58,   110,   111,   102,   103,   104,   105,
     106,   107,   108,   109,    60,   110,   111,    -5,     1,    61,
      63,    65,    78,    79,    80,    64,     2,    73,    88,     3,
      81,     4,    91,    82,     5,    92,    93,    83,   115,    78,
      79,    80,   105,   106,   107,   108,   109,    81,   110,   111,
      82,   121,   141,   130,    83,   102,   103,   104,   105,   106,
     107,   108,   109,   135,   110,   111,    25,    67,   118,   102,
     103,   104,   105,   106,   107,   108,   109,    74,   110,   111,
     100,   140,   132,   102,   103,   104,   105,   106,   107,   108,
     109,    69,   110,   111,     0,     0,   133,   102,   103,   104,
     105,   106,   107,   108,   109,     0,   110,   111,   137,   102,
     103,   104,   105,   106,   107,   108,   109,     0,   110,   111
};

static const yytype_int16 yycheck[] =
{
       0,     6,    81,    82,    83,     1,    17,    28,     8,    88,
      15,     3,    91,    92,    93,     3,     3,    29,    30,    98,
       1,    17,     8,   102,   103,   104,   105,   106,   107,   108,
     109,     1,   111,    33,    55,    16,    17,    33,    30,    60,
      61,    62,    30,    30,     0,    31,     1,    17,   132,   133,
      41,     6,    73,    53,     8,   134,     1,   141,     8,    50,
       5,     6,    17,     5,    64,    10,    11,    17,    18,    19,
      15,     8,    17,    18,    19,    25,     9,     5,    28,    12,
      25,     1,    32,    28,     1,     5,     6,    32,     5,    33,
      10,    11,     6,    32,     8,    15,    32,    17,    18,    19,
       1,     3,    34,    35,     5,    25,    18,     3,    28,    10,
      11,    33,    32,     4,     6,    31,    17,    18,    19,     4,
      24,    25,    26,    27,    25,    29,    30,    28,    31,    26,
      27,    32,    29,    30,     8,    20,    21,    22,    23,    24,
      25,    26,    27,     4,    29,    30,    20,    21,    22,    23,
      24,    25,    26,    27,     8,    29,    30,    22,    23,    24,
      25,    26,    27,     8,    29,    30,    20,    21,    22,    23,
      24,    25,    26,    27,     7,    29,    30,     0,     1,     7,
      33,     6,    17,    18,    19,     4,     9,     7,    20,    12,
      25,    14,    32,    28,    17,    32,    32,    32,    33,    17,
      18,    19,    23,    24,    25,    26,    27,    25,    29,    30,
      28,     6,    13,    17,    32,    20,    21,    22,    23,    24,
      25,    26,    27,    33,    29,    30,     8,    53,    33,    20,
      21,    22,    23,    24,    25,    26,    27,    64,    29,    30,
      86,   134,    33,    20,    21,    22,    23,    24,    25,    26,
      27,    59,    29,    30,    -1,    -1,    33,    20,    21,    22,
      23,    24,    25,    26,    27,    -1,    29,    30,    31,    20,
      21,    22,    23,    24,    25,    26,    27,    -1,    29,    30
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     9,    12,    14,    17,    36,    37,    38,    39,
      40,    41,    42,    45,     8,    31,    17,    43,    44,     1,
      16,    17,    46,    47,     0,    37,     8,     8,     3,    30,
       5,    33,    32,    32,     3,     3,    41,    18,     1,    45,
      54,    55,    56,    57,    33,    33,    45,    48,    49,     1,
       5,    50,    50,     4,    31,     3,     6,    54,     8,     4,
       7,     7,     3,    33,     4,     6,    54,    40,    41,    56,
      41,    41,    41,     7,    48,     1,    10,    11,    17,    18,
      19,    25,    28,    32,    50,    51,    52,    58,    20,    41,
       8,    32,    32,    32,    58,    58,    58,     6,    15,    53,
      51,     8,    20,    21,    22,    23,    24,    25,    26,    27,
      29,    30,    58,    58,    58,    33,    58,    59,    33,     8,
      58,     6,    58,    58,    58,    58,    58,    58,    58,    58,
      17,    58,    33,    33,     4,    33,     8,    31,    52,    52,
      59,    13,    52
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    35,    36,    37,    37,    37,    38,    38,    38,    38,
      39,    39,    40,    40,    41,    41,    42,    42,    43,    43,
      44,    45,    45,    45,    46,    46,    46,    47,    47,    48,
      48,    49,    50,    50,    50,    51,    51,    52,    52,    52,
      52,    52,    52,    53,    53,    54,    54,    55,    56,    56,
      57,    57,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      59,    59
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     0,     2,     2,     4,     2,
       4,     2,     3,     5,     1,     1,     5,     2,     1,     0,
       1,     1,     4,     2,     6,     5,     2,     5,     2,     3,
       1,     3,     4,     5,     2,     2,     0,     2,     1,     5,
       7,     5,     2,     3,     2,     2,     0,     2,     1,     3,
       3,     5,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     4,     3,     4,     3,     1,     1,     1,
       3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
#line 82 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { printf("in parser-Program\n"); Program = new ProgramAST(std::move(*(yyvsp[0].AST_list))); }
#line 1492 "parser.y.cpp"
    break;

  case 3:
#line 84 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.AST_list) = (yyvsp[0].AST_list); (yyval.AST_list)->push_back(std::unique_ptr<ExprAST>((yyvsp[-1].exprAST))); }
#line 1498 "parser.y.cpp"
    break;

  case 4:
#line 85 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.AST_list) = new ast_list();
                                                              (yyval.AST_list)->push_back(std::unique_ptr<ExprAST>((yyvsp[0].functionAST))); }
#line 1505 "parser.y.cpp"
    break;

  case 5:
#line 87 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.AST_list) = new ast_list(); }
#line 1511 "parser.y.cpp"
    break;

  case 6:
#line 89 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.exprAST) = new GlobalDecListAST(std::move(*(yyvsp[-1].AST_list))); }
#line 1517 "parser.y.cpp"
    break;

  case 7:
#line 90 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            {  }
#line 1523 "parser.y.cpp"
    break;

  case 8:
#line 91 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.exprAST) = new FunctionAST((yyvsp[-2].prototypeAST), (yyvsp[0].bodyAST)); }
#line 1529 "parser.y.cpp"
    break;

  case 9:
#line 92 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            {  }
#line 1535 "parser.y.cpp"
    break;

  case 10:
#line 94 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.functionAST) = new FunctionAST((yyvsp[-2].prototypeAST), (yyvsp[0].bodyAST)); }
#line 1541 "parser.y.cpp"
    break;

  case 11:
#line 95 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            {  }
#line 1547 "parser.y.cpp"
    break;

  case 12:
#line 97 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.AST_list) = new ast_list(); (yyval.AST_list)->push_back(std::unique_ptr<ExprAST>(new DecExprAST((yyvsp[-2].variableexprAST), (yyvsp[0].typeAST)))); }
#line 1553 "parser.y.cpp"
    break;

  case 13:
#line 98 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.AST_list) = (yyvsp[0].AST_list); (yyval.AST_list)->push_back(std::unique_ptr<ExprAST>(new DecExprAST((yyvsp[-4].variableexprAST), (yyvsp[-2].typeAST)))); }
#line 1559 "parser.y.cpp"
    break;

  case 14:
#line 102 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.typeAST) = new TypeAST(*(yyvsp[0].Str)); }
#line 1565 "parser.y.cpp"
    break;

  case 15:
#line 103 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            {  }
#line 1571 "parser.y.cpp"
    break;

  case 16:
#line 105 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            {  }
#line 1577 "parser.y.cpp"
    break;

  case 17:
#line 106 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            {  }
#line 1583 "parser.y.cpp"
    break;

  case 18:
#line 108 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            {  }
#line 1589 "parser.y.cpp"
    break;

  case 19:
#line 109 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            {  }
#line 1595 "parser.y.cpp"
    break;

  case 20:
#line 111 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            {  }
#line 1601 "parser.y.cpp"
    break;

  case 21:
#line 115 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.variableexprAST) = new VariableExprAST(*(yyvsp[0].name)); }
#line 1607 "parser.y.cpp"
    break;

  case 22:
#line 116 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            {  }
#line 1613 "parser.y.cpp"
    break;

  case 23:
#line 117 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            {  }
#line 1619 "parser.y.cpp"
    break;

  case 24:
#line 119 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.prototypeAST) = new PrototypeAST((yyvsp[0].typeAST), *(yyvsp[-5].name), std::move(*(yyvsp[-3].AST_list))); }
#line 1625 "parser.y.cpp"
    break;

  case 25:
#line 120 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { ast_list* void_args; 
                                                              void_args = new ast_list(); 
                                                              (yyval.prototypeAST) = new PrototypeAST((yyvsp[0].typeAST), *(yyvsp[-4].name), std::move(*void_args)); }
#line 1633 "parser.y.cpp"
    break;

  case 26:
#line 123 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            {  }
#line 1639 "parser.y.cpp"
    break;

  case 27:
#line 125 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { ast_list* void_args; 
                                                              void_args = new ast_list(); 
                                                              (yyval.prototypeAST) = new PrototypeAST((yyvsp[0].typeAST), std::string("main"), std::move(*void_args)); }
#line 1647 "parser.y.cpp"
    break;

  case 28:
#line 128 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            {  }
#line 1653 "parser.y.cpp"
    break;

  case 29:
#line 130 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.AST_list) = (yyvsp[0].AST_list); (yyval.AST_list)->push_back(std::unique_ptr<ExprAST>((yyvsp[-2].decexprAST))); }
#line 1659 "parser.y.cpp"
    break;

  case 30:
#line 131 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.AST_list) = new ast_list(); (yyval.AST_list)->push_back(std::unique_ptr<ExprAST>((yyvsp[0].decexprAST))); }
#line 1665 "parser.y.cpp"
    break;

  case 31:
#line 133 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.decexprAST) = new DecExprAST((yyvsp[-2].variableexprAST), (yyvsp[0].typeAST)); }
#line 1671 "parser.y.cpp"
    break;

  case 32:
#line 136 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.bodyAST) = new BodyAST(std::move(*(yyvsp[-2].AST_list)), std::move(*(yyvsp[-1].AST_list)), new VoidExprAST()); }
#line 1677 "parser.y.cpp"
    break;

  case 33:
#line 137 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.bodyAST) = new BodyAST(std::move(*(yyvsp[-3].AST_list)), std::move(*(yyvsp[-2].AST_list)), (yyvsp[-1].exprAST)); }
#line 1683 "parser.y.cpp"
    break;

  case 34:
#line 138 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            {  }
#line 1689 "parser.y.cpp"
    break;

  case 35:
#line 140 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.AST_list) = (yyvsp[0].AST_list); (yyval.AST_list)->push_back(std::unique_ptr<ExprAST>((yyvsp[-1].exprAST))); }
#line 1695 "parser.y.cpp"
    break;

  case 36:
#line 141 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.AST_list) = new ast_list(); }
#line 1701 "parser.y.cpp"
    break;

  case 37:
#line 143 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.exprAST) = (yyvsp[-1].exprAST); }
#line 1707 "parser.y.cpp"
    break;

  case 38:
#line 144 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.exprAST) = (yyvsp[0].bodyAST); }
#line 1713 "parser.y.cpp"
    break;

  case 39:
#line 145 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            {  }
#line 1719 "parser.y.cpp"
    break;

  case 40:
#line 146 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            {  }
#line 1725 "parser.y.cpp"
    break;

  case 41:
#line 147 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            {  }
#line 1731 "parser.y.cpp"
    break;

  case 42:
#line 148 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            {  }
#line 1737 "parser.y.cpp"
    break;

  case 43:
#line 150 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.exprAST) = (yyvsp[-1].exprAST); }
#line 1743 "parser.y.cpp"
    break;

  case 44:
#line 151 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.exprAST) = new VoidExprAST(); }
#line 1749 "parser.y.cpp"
    break;

  case 45:
#line 153 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.AST_list) = (yyvsp[0].AST_list); (yyval.AST_list)->push_back(std::unique_ptr<ExprAST>((yyvsp[-1].declistAST))); }
#line 1755 "parser.y.cpp"
    break;

  case 46:
#line 154 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.AST_list) = new ast_list(); }
#line 1761 "parser.y.cpp"
    break;

  case 47:
#line 156 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.declistAST) = new DecListAST(std::move(*(yyvsp[-1].AST_list))); }
#line 1767 "parser.y.cpp"
    break;

  case 48:
#line 158 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.AST_list) = new ast_list(); (yyval.AST_list)->push_back(std::unique_ptr<ExprAST>((yyvsp[0].exprAST))); }
#line 1773 "parser.y.cpp"
    break;

  case 49:
#line 159 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.AST_list) = (yyvsp[0].AST_list); (yyval.AST_list)->push_back(std::unique_ptr<ExprAST>((yyvsp[-2].exprAST))); }
#line 1779 "parser.y.cpp"
    break;

  case 50:
#line 161 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.exprAST) = new DecExprAST((yyvsp[-2].variableexprAST), (yyvsp[0].typeAST)); }
#line 1785 "parser.y.cpp"
    break;

  case 51:
#line 162 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { DecExprAST* var;
                                                              var = new DecExprAST((yyvsp[-4].variableexprAST), (yyvsp[-2].typeAST)); 
                                                              (yyval.exprAST) = new AssignExprAST(var, (yyvsp[0].exprAST)); }
#line 1793 "parser.y.cpp"
    break;

  case 52:
#line 167 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.exprAST) = new AssignExprAST((yyvsp[-2].exprAST), (yyvsp[0].exprAST)); }
#line 1799 "parser.y.cpp"
    break;

  case 53:
#line 168 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.exprAST) = new BinaryExprAST(*(yyvsp[-1].op), (yyvsp[-2].exprAST), (yyvsp[0].exprAST)); }
#line 1805 "parser.y.cpp"
    break;

  case 54:
#line 169 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.exprAST) = new BinaryExprAST(*(yyvsp[-1].op), (yyvsp[-2].exprAST), (yyvsp[0].exprAST)); }
#line 1811 "parser.y.cpp"
    break;

  case 55:
#line 170 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.exprAST) = new BinaryExprAST(*(yyvsp[-1].op), (yyvsp[-2].exprAST), (yyvsp[0].exprAST)); }
#line 1817 "parser.y.cpp"
    break;

  case 56:
#line 171 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                           { (yyval.exprAST) = new BinaryExprAST(*(yyvsp[-1].op), (yyvsp[-2].exprAST), (yyvsp[0].exprAST)); }
#line 1823 "parser.y.cpp"
    break;

  case 57:
#line 172 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                          { (yyval.exprAST) = new BinaryExprAST(*(yyvsp[-1].op), (yyvsp[-2].exprAST), (yyvsp[0].exprAST)); }
#line 1829 "parser.y.cpp"
    break;

  case 58:
#line 173 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                           { (yyval.exprAST) = new BinaryExprAST(*(yyvsp[-1].op), (yyvsp[-2].exprAST), (yyvsp[0].exprAST)); }
#line 1835 "parser.y.cpp"
    break;

  case 59:
#line 174 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.exprAST) = new BinaryExprAST(*(yyvsp[-1].op), (yyvsp[-2].exprAST), (yyvsp[0].exprAST)); }
#line 1841 "parser.y.cpp"
    break;

  case 60:
#line 175 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.exprAST) = (yyvsp[-1].exprAST); }
#line 1847 "parser.y.cpp"
    break;

  case 61:
#line 176 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                          { (yyval.exprAST) = new BinaryExprAST(*(yyvsp[-1].op), new IntExprAST(0), (yyvsp[0].exprAST)); }
#line 1853 "parser.y.cpp"
    break;

  case 62:
#line 177 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.exprAST) = new BinaryExprAST(*(yyvsp[-1].op), new VoidExprAST(), (yyvsp[0].exprAST)); }
#line 1859 "parser.y.cpp"
    break;

  case 63:
#line 178 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.exprAST) = new CallExprAST(*(yyvsp[-3].name), std::move(*(yyvsp[-1].AST_list))); }
#line 1865 "parser.y.cpp"
    break;

  case 64:
#line 179 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { ast_list* void_args; 
                                                              void_args = new ast_list();  
                                                              (yyval.exprAST) = new CallExprAST(*(yyvsp[-2].name), std::move(*void_args)); }
#line 1873 "parser.y.cpp"
    break;

  case 65:
#line 182 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            {  }
#line 1879 "parser.y.cpp"
    break;

  case 66:
#line 183 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            {  }
#line 1885 "parser.y.cpp"
    break;

  case 67:
#line 184 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.exprAST) = new VariableExprAST(*(yyvsp[0].name)); }
#line 1891 "parser.y.cpp"
    break;

  case 68:
#line 185 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.exprAST) = new IntExprAST((yyvsp[0].int_val)); }
#line 1897 "parser.y.cpp"
    break;

  case 69:
#line 186 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.exprAST) = new FloatExprAST((yyvsp[0].float_val)); }
#line 1903 "parser.y.cpp"
    break;

  case 70:
#line 188 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.AST_list) = (yyvsp[0].AST_list); (yyval.AST_list)->push_back(std::unique_ptr<ExprAST>((yyvsp[-2].exprAST))); }
#line 1909 "parser.y.cpp"
    break;

  case 71:
#line 189 "/home/yuanli/zju_compiler/src/parser.ypp"
                                                            { (yyval.AST_list) = new ast_list(); (yyval.AST_list)->push_back(std::unique_ptr<ExprAST>((yyvsp[0].exprAST))); }
#line 1915 "parser.y.cpp"
    break;


#line 1919 "parser.y.cpp"

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
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
                  yystos[+*yyssp], yyvsp);
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
#line 191 "/home/yuanli/zju_compiler/src/parser.ypp"


void yyerror(char* msg){
    fprintf(stderr, "Error type B at line %d: %s.\n", yylineno, msg);
}
