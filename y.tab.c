/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lex.yy.c"
void yyerror(char *s);
FILE *yyin;

#define HASH_TABLE_SIZE 100
/* --- INICIO: ESTRUCTURAS -------*/

/* Estructura para guardar los temporales y los label */
struct TempLabel {
    char letra;
    int numero;
};

void aumentarTempLabel(struct TempLabel* objeto) {
    objeto->numero++;
}

void imprimirObjeto(struct TempLabel objeto) {
    printf("%c%d\n", objeto.letra, objeto.numero);
}

/* Pila dinámica */
struct Nodo {
    struct TempLabel objeto;
    struct Nodo* siguiente;
};

struct Pila {
    struct Nodo* tope;
};

void inicializarPila(struct Pila* pila) {
    pila->tope = NULL;
}

int estaVacia(struct Pila* pila) {
    return pila->tope == NULL;
}

void push(struct Pila* pila, struct TempLabel objeto) {
    struct Nodo* nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    if (nuevoNodo == NULL) {
        yyerror("Error: Could not allocate memory for the new node.\n");
        exit(1);
    }

    nuevoNodo->objeto = objeto;
    nuevoNodo->siguiente = pila->tope;
    pila->tope = nuevoNodo;
}

struct TempLabel pop(struct Pila* pila) {
    struct TempLabel objetoVacio = {'\0', 0};

    if (estaVacia(pila)) {
        yyerror("Error: stack is empty.\n");
        exit(1);
    }

    struct Nodo* nodoDesapilado = pila->tope;
    struct TempLabel objeto = nodoDesapilado->objeto;
    pila->tope = nodoDesapilado->siguiente;

    free(nodoDesapilado);

    return objeto;
}

void imprimirPila(struct Pila* pila) {
    if (estaVacia(pila)) {
        printf("Error: stack is empty.\n");
        return;
    }

    printf("Contenido de la pila:\n");
    struct Nodo* nodoActual = pila->tope;
    while (nodoActual != NULL) {
        printf("Letra: %c, Número: %d\n", nodoActual->objeto.letra, nodoActual->objeto.numero);
        nodoActual = nodoActual->siguiente;
    }
}

struct TempLabel peek(struct Pila* pila) {
    struct TempLabel objetoVacio = {'\0', 0};

    if (estaVacia(pila)) {
        yyerror("Error: stack is empty.\n");
        exit(1);
    }

    return pila->tope->objeto;
}

/* Hash */
typedef struct Node {
    char *key;
    struct Node *next;
} Node;

typedef struct HashTable {
    Node *buckets[HASH_TABLE_SIZE];
} HashTable;

unsigned long hash_djb2(const unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

void hash_table_init(HashTable *hash_table) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        hash_table->buckets[i] = NULL;
    }
}

void hash_table_insert(HashTable *hash_table, const char *key) {
    unsigned long hash_value = hash_djb2((const unsigned char *)key);
    int index = hash_value % HASH_TABLE_SIZE;

    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->key = strdup(key);
    new_node->next = NULL;

    if (hash_table->buckets[index] == NULL) {
        hash_table->buckets[index] = new_node;
    } else {
        Node *current = hash_table->buckets[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

bool hash_table_contains(const HashTable *hash_table, const char *key) {
    unsigned long hash_value = hash_djb2((const unsigned char *)key);
    int index = hash_value % HASH_TABLE_SIZE;

    Node *current = hash_table->buckets[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return true;
        }
        current = current->next;
    }

    return false;
}

/* --- FIN: Estructuras */

/* --- INICIO: FUNCIONES E Declaraciones de estructuras --- */
struct TempLabel temporal= {'t', 0};
char pila[100][10];
int top=0;

struct Pila pila_label;
struct TempLabel label= {'L', 0};

struct Pila pila_while;
struct TempLabel label_while= {'W', 0};

struct Pila pila_if;
struct TempLabel label_if= {'I', 0};

HashTable hash_table;

void push_pila()
{
  strcpy(pila[++top],yytext);
}

void push_label()
{
  push(&pila_label, label);
  aumentarTempLabel(&label);
}

void push_label_while()
{
  push(&pila_while, label_while);
  aumentarTempLabel(&label_while);
}

void push_label_if()
{
  push(&pila_if, label_if);
  aumentarTempLabel(&label_if);
}

void codegen()
{
  printf("%c%d = %s %s %s \n", temporal.letra, temporal.numero, pila[top-2],pila[top-1],pila[top]);
  top-=2;
  sprintf(pila[top], "%c%d", temporal.letra, temporal.numero);
  aumentarTempLabel(&temporal);
}

void codegen_comparisons()
{
  printf("%s %s %s \n", pila[top-2],pila[top-1],pila[top]);
  top-=2;
}

void codegen_assign()
{
  printf("%s = %s\n",pila[top-2],pila[top]);
  top-=2;
}


void print_label()
{
  struct TempLabel objetoDesapilado = pop(&pila_label);
  imprimirObjeto(objetoDesapilado);
}

void print_label_while()
{
  imprimirObjeto(label_while);
  push_label_while();
}

void print_label_if()
{
  struct TempLabel objetoDesapilado = pop(&pila_if);
  imprimirObjeto(objetoDesapilado);
}

void Wincond()
{
  printf("goto ");
  struct TempLabel objetoDesapilado = pop(&pila_while);
  imprimirObjeto(objetoDesapilado);
}

void Iincond()
{
  push_label_if();
  printf("goto ");
  struct TempLabel objetoDesapilado = peek(&pila_if);
  imprimirObjeto(objetoDesapilado);
}

void Lcond()
{
  printf("%c%d = not %s \n",temporal.letra, temporal.numero,pila[top]);
  printf("if %c%d goto",temporal.letra, temporal.numero);
  printf(" ");
  imprimirObjeto(label);
  aumentarTempLabel(&temporal);
  push_label();
}

void search_hash() {
    if (hash_table_contains(&hash_table, yytext) == false) {
      yyerror("Parsing aborted: Variable not defined");
      exit(1);
    } 
}

void insert_hash()
{
  hash_table_insert(&hash_table, yytext);
}
/* --- FIN: FUNCIONES E INICIALIZACIONES --- */

#line 349 "y.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    MAIN = 258,                    /* MAIN  */
    IF = 259,                      /* IF  */
    WHILE = 260,                   /* WHILE  */
    ELSE = 261,                    /* ELSE  */
    PUTW = 262,                    /* PUTW  */
    PUTS = 263,                    /* PUTS  */
    INT = 264,                     /* INT  */
    MENOR = 265,                   /* MENOR  */
    MAYOR = 266,                   /* MAYOR  */
    MENOR_IGUAL = 267,             /* MENOR_IGUAL  */
    MAYOR_IGUAL = 268,             /* MAYOR_IGUAL  */
    IGUALDAD = 269,                /* IGUALDAD  */
    DESIGUALDAD = 270,             /* DESIGUALDAD  */
    AND = 271,                     /* AND  */
    OR = 272,                      /* OR  */
    SUMA = 273,                    /* SUMA  */
    RESTA = 274,                   /* RESTA  */
    DIVISION = 275,                /* DIVISION  */
    MULTIPLICACION = 276,          /* MULTIPLICACION  */
    DIVISION_ENTERA = 277,         /* DIVISION_ENTERA  */
    IDENTIFICADOR = 278,           /* IDENTIFICADOR  */
    CONST_CADENA = 279,            /* CONST_CADENA  */
    NUMERO = 280,                  /* NUMERO  */
    ASIGNACION = 281,              /* ASIGNACION  */
    PARENTESIS_A = 282,            /* PARENTESIS_A  */
    PARENTESIS_C = 283,            /* PARENTESIS_C  */
    LLAVE_A = 284,                 /* LLAVE_A  */
    LLAVE_C = 285,                 /* LLAVE_C  */
    COMA = 286,                    /* COMA  */
    FINAL_LINEA = 287              /* FINAL_LINEA  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define MAIN 258
#define IF 259
#define WHILE 260
#define ELSE 261
#define PUTW 262
#define PUTS 263
#define INT 264
#define MENOR 265
#define MAYOR 266
#define MENOR_IGUAL 267
#define MAYOR_IGUAL 268
#define IGUALDAD 269
#define DESIGUALDAD 270
#define AND 271
#define OR 272
#define SUMA 273
#define RESTA 274
#define DIVISION 275
#define MULTIPLICACION 276
#define DIVISION_ENTERA 277
#define IDENTIFICADOR 278
#define CONST_CADENA 279
#define NUMERO 280
#define ASIGNACION 281
#define PARENTESIS_A 282
#define PARENTESIS_C 283
#define LLAVE_A 284
#define LLAVE_C 285
#define COMA 286
#define FINAL_LINEA 287

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_MAIN = 3,                       /* MAIN  */
  YYSYMBOL_IF = 4,                         /* IF  */
  YYSYMBOL_WHILE = 5,                      /* WHILE  */
  YYSYMBOL_ELSE = 6,                       /* ELSE  */
  YYSYMBOL_PUTW = 7,                       /* PUTW  */
  YYSYMBOL_PUTS = 8,                       /* PUTS  */
  YYSYMBOL_INT = 9,                        /* INT  */
  YYSYMBOL_MENOR = 10,                     /* MENOR  */
  YYSYMBOL_MAYOR = 11,                     /* MAYOR  */
  YYSYMBOL_MENOR_IGUAL = 12,               /* MENOR_IGUAL  */
  YYSYMBOL_MAYOR_IGUAL = 13,               /* MAYOR_IGUAL  */
  YYSYMBOL_IGUALDAD = 14,                  /* IGUALDAD  */
  YYSYMBOL_DESIGUALDAD = 15,               /* DESIGUALDAD  */
  YYSYMBOL_AND = 16,                       /* AND  */
  YYSYMBOL_OR = 17,                        /* OR  */
  YYSYMBOL_SUMA = 18,                      /* SUMA  */
  YYSYMBOL_RESTA = 19,                     /* RESTA  */
  YYSYMBOL_DIVISION = 20,                  /* DIVISION  */
  YYSYMBOL_MULTIPLICACION = 21,            /* MULTIPLICACION  */
  YYSYMBOL_DIVISION_ENTERA = 22,           /* DIVISION_ENTERA  */
  YYSYMBOL_IDENTIFICADOR = 23,             /* IDENTIFICADOR  */
  YYSYMBOL_CONST_CADENA = 24,              /* CONST_CADENA  */
  YYSYMBOL_NUMERO = 25,                    /* NUMERO  */
  YYSYMBOL_ASIGNACION = 26,                /* ASIGNACION  */
  YYSYMBOL_PARENTESIS_A = 27,              /* PARENTESIS_A  */
  YYSYMBOL_PARENTESIS_C = 28,              /* PARENTESIS_C  */
  YYSYMBOL_LLAVE_A = 29,                   /* LLAVE_A  */
  YYSYMBOL_LLAVE_C = 30,                   /* LLAVE_C  */
  YYSYMBOL_COMA = 31,                      /* COMA  */
  YYSYMBOL_FINAL_LINEA = 32,               /* FINAL_LINEA  */
  YYSYMBOL_YYACCEPT = 33,                  /* $accept  */
  YYSYMBOL_S = 34,                         /* S  */
  YYSYMBOL_D = 35,                         /* D  */
  YYSYMBOL_identifier_list = 36,           /* identifier_list  */
  YYSYMBOL_M = 37,                         /* M  */
  YYSYMBOL_I = 38,                         /* I  */
  YYSYMBOL_39_1 = 39,                      /* $@1  */
  YYSYMBOL_if_block = 40,                  /* if_block  */
  YYSYMBOL_41_2 = 41,                      /* $@2  */
  YYSYMBOL_W = 42,                         /* W  */
  YYSYMBOL_43_3 = 43,                      /* $@3  */
  YYSYMBOL_44_4 = 44,                      /* $@4  */
  YYSYMBOL_45_5 = 45,                      /* $@5  */
  YYSYMBOL_C = 46,                         /* C  */
  YYSYMBOL_47_6 = 47,                      /* $@6  */
  YYSYMBOL_B = 48,                         /* B  */
  YYSYMBOL_49_7 = 49,                      /* $@7  */
  YYSYMBOL_50_8 = 50,                      /* $@8  */
  YYSYMBOL_51_9 = 51,                      /* $@9  */
  YYSYMBOL_52_10 = 52,                     /* $@10  */
  YYSYMBOL_53_11 = 53,                     /* $@11  */
  YYSYMBOL_54_12 = 54,                     /* $@12  */
  YYSYMBOL_A = 55,                         /* A  */
  YYSYMBOL_56_13 = 56,                     /* $@13  */
  YYSYMBOL_57_14 = 57,                     /* $@14  */
  YYSYMBOL_E = 58,                         /* E  */
  YYSYMBOL_59_15 = 59,                     /* $@15  */
  YYSYMBOL_60_16 = 60,                     /* $@16  */
  YYSYMBOL_61_17 = 61,                     /* $@17  */
  YYSYMBOL_62_18 = 62,                     /* $@18  */
  YYSYMBOL_63_19 = 63,                     /* $@19  */
  YYSYMBOL_V = 64                          /* V  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
typedef yytype_int8 yy_state_t;

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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   103

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  52
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  107

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   287


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

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
      25,    26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   322,   322,   323,   326,   329,   330,   333,   336,   336,
     339,   340,   340,   343,   343,   343,   343,   345,   346,   346,
     347,   348,   349,   350,   353,   353,   354,   354,   355,   355,
     356,   356,   357,   357,   358,   358,   361,   361,   361,   364,
     364,   365,   365,   366,   366,   367,   367,   368,   368,   369,
     370,   371,   374
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "MAIN", "IF", "WHILE",
  "ELSE", "PUTW", "PUTS", "INT", "MENOR", "MAYOR", "MENOR_IGUAL",
  "MAYOR_IGUAL", "IGUALDAD", "DESIGUALDAD", "AND", "OR", "SUMA", "RESTA",
  "DIVISION", "MULTIPLICACION", "DIVISION_ENTERA", "IDENTIFICADOR",
  "CONST_CADENA", "NUMERO", "ASIGNACION", "PARENTESIS_A", "PARENTESIS_C",
  "LLAVE_A", "LLAVE_C", "COMA", "FINAL_LINEA", "$accept", "S", "D",
  "identifier_list", "M", "I", "$@1", "if_block", "$@2", "W", "$@3", "$@4",
  "$@5", "C", "$@6", "B", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12", "A",
  "$@13", "$@14", "E", "$@15", "$@16", "$@17", "$@18", "$@19", "V", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-27)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-12)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       1,   -18,   -11,    16,    28,   -27,     4,   -27,   -26,   -27,
     -27,     5,    14,   -27,    10,   -27,    11,   -27,    30,    31,
     -27,    10,    10,    25,    29,   -27,    41,    33,    41,    39,
     -27,   -27,   -27,    10,    46,   -27,    41,    45,    81,   -27,
      41,     2,   -27,   -27,   -27,     7,   -27,   -27,   -27,   -27,
     -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27,    47,    35,
      50,    41,   -27,    48,    41,    41,    41,    41,    41,    41,
      41,    41,    41,    41,    41,   -27,    10,    51,    32,    10,
     -27,    32,    32,    32,    32,    32,    32,    49,    49,   -27,
     -27,   -27,    52,   -27,    10,    55,    10,   -27,    73,   -27,
      80,    57,    59,   -27,    10,    67,   -27
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     2,     0,     5,     0,     1,
       3,     0,     0,     4,    23,     6,     0,    13,     0,     0,
      52,    23,    23,     0,     0,    36,     0,     0,     0,     0,
      21,    22,     7,    23,     0,    51,     0,     0,     0,    50,
       0,     0,    18,    17,    37,     0,     8,    24,    26,    28,
      30,    32,    34,    39,    41,    45,    43,    47,     0,     0,
       0,     0,    49,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    14,    23,     0,    38,    23,
       9,    25,    27,    29,    31,    33,    35,    40,    42,    46,
      44,    48,     0,    20,    23,     0,    23,    19,    10,    15,
       0,     0,     0,    16,    23,     0,    12
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -27,   -27,   -27,   -27,    85,   -27,   -27,   -27,   -27,   -27,
     -27,   -27,   -27,   -20,   -27,    58,   -27,   -27,   -27,   -27,
     -27,   -27,   -27,   -27,   -27,   -25,   -27,   -27,   -27,   -27,
     -27,   -14
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,     8,     5,    21,    63,    80,   100,    22,
      27,    92,   101,    23,    60,    37,    64,    65,    66,    67,
      68,    69,    24,    34,    61,    38,    70,    71,    73,    72,
      74,    39
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      25,    30,    31,    41,     1,    12,    13,    25,    25,     6,
       2,    45,     7,    43,    16,    17,     9,    18,    19,    25,
      53,    54,    55,    56,    57,    53,    54,    55,    56,    57,
      59,     1,    11,    20,    14,    62,    78,    15,    26,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      53,    54,    55,    56,    57,    32,    93,    28,    29,    95,
      40,    33,    25,    42,    20,    25,    35,    76,    36,    55,
      56,    57,    44,    46,    97,    75,    99,    79,    77,   -11,
      25,    96,    25,    94,   105,    98,   102,   103,   104,    10,
      25,    47,    48,    49,    50,    51,    52,   106,    58,    53,
      54,    55,    56,    57
};

static const yytype_int8 yycheck[] =
{
      14,    21,    22,    28,     3,    31,    32,    21,    22,    27,
       9,    36,    23,    33,     4,     5,     0,     7,     8,    33,
      18,    19,    20,    21,    22,    18,    19,    20,    21,    22,
      28,     3,    28,    23,    29,    28,    61,    23,    27,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      18,    19,    20,    21,    22,    30,    76,    27,    27,    79,
      27,    32,    76,    24,    23,    79,    25,    32,    27,    20,
      21,    22,    26,    28,    94,    28,    96,    29,    28,     6,
      94,    29,    96,    32,   104,    30,     6,    30,    29,     4,
     104,    10,    11,    12,    13,    14,    15,    30,    40,    18,
      19,    20,    21,    22
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     9,    34,    35,    37,    27,    23,    36,     0,
      37,    28,    31,    32,    29,    23,     4,     5,     7,     8,
      23,    38,    42,    46,    55,    64,    27,    43,    27,    27,
      46,    46,    30,    32,    56,    25,    27,    48,    58,    64,
      27,    58,    24,    46,    26,    58,    28,    10,    11,    12,
      13,    14,    15,    18,    19,    20,    21,    22,    48,    28,
      47,    57,    28,    39,    49,    50,    51,    52,    53,    54,
      59,    60,    62,    61,    63,    28,    32,    28,    58,    29,
      40,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    44,    46,    32,    46,    29,    46,    30,    46,
      41,    45,     6,    30,    29,    46,    30
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    33,    34,    34,    35,    36,    36,    37,    39,    38,
      40,    41,    40,    43,    44,    45,    42,    46,    47,    46,
      46,    46,    46,    46,    49,    48,    50,    48,    51,    48,
      52,    48,    53,    48,    54,    48,    56,    57,    55,    59,
      58,    60,    58,    61,    58,    62,    58,    63,    58,    58,
      58,    58,    64
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     3,     1,     3,     6,     0,     6,
       3,     0,     8,     0,     0,     0,    10,     3,     0,     7,
       6,     2,     2,     0,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     0,     5,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     3,
       1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  case 2: /* S: M  */
#line 322 "parser.y"
      {}
#line 1571 "y.tab.c"
    break;

  case 3: /* S: D M  */
#line 323 "parser.y"
        {}
#line 1577 "y.tab.c"
    break;

  case 5: /* identifier_list: IDENTIFICADOR  */
#line 329 "parser.y"
                                {insert_hash();}
#line 1583 "y.tab.c"
    break;

  case 6: /* identifier_list: identifier_list COMA IDENTIFICADOR  */
#line 330 "parser.y"
                                       {insert_hash();}
#line 1589 "y.tab.c"
    break;

  case 7: /* M: MAIN PARENTESIS_A PARENTESIS_C LLAVE_A C LLAVE_C  */
#line 333 "parser.y"
                                                     {}
#line 1595 "y.tab.c"
    break;

  case 8: /* $@1: %empty  */
#line 336 "parser.y"
                                   { Lcond(); }
#line 1601 "y.tab.c"
    break;

  case 10: /* if_block: LLAVE_A C LLAVE_C  */
#line 339 "parser.y"
                             { print_label(); }
#line 1607 "y.tab.c"
    break;

  case 11: /* $@2: %empty  */
#line 340 "parser.y"
                              { Iincond(); print_label(); }
#line 1613 "y.tab.c"
    break;

  case 12: /* if_block: LLAVE_A C LLAVE_C $@2 ELSE LLAVE_A C LLAVE_C  */
#line 340 "parser.y"
                                                                                   { print_label_if(); }
#line 1619 "y.tab.c"
    break;

  case 13: /* $@3: %empty  */
#line 343 "parser.y"
          {print_label_while();}
#line 1625 "y.tab.c"
    break;

  case 14: /* $@4: %empty  */
#line 343 "parser.y"
                                                             {Lcond();}
#line 1631 "y.tab.c"
    break;

  case 15: /* $@5: %empty  */
#line 343 "parser.y"
                                                                                  {Wincond();}
#line 1637 "y.tab.c"
    break;

  case 16: /* W: WHILE $@3 PARENTESIS_A B PARENTESIS_C $@4 LLAVE_A C $@5 LLAVE_C  */
#line 343 "parser.y"
                                                                                                       {print_label();}
#line 1643 "y.tab.c"
    break;

  case 17: /* C: A FINAL_LINEA C  */
#line 345 "parser.y"
                    {}
#line 1649 "y.tab.c"
    break;

  case 18: /* $@6: %empty  */
#line 346 "parser.y"
                                   {printf("Imprimir cadena: %s\n", yytext);}
#line 1655 "y.tab.c"
    break;

  case 19: /* C: PUTS PARENTESIS_A CONST_CADENA $@6 PARENTESIS_C FINAL_LINEA C  */
#line 346 "parser.y"
                                                                                                         {}
#line 1661 "y.tab.c"
    break;

  case 20: /* C: PUTW PARENTESIS_A E PARENTESIS_C FINAL_LINEA C  */
#line 347 "parser.y"
                                                  {}
#line 1667 "y.tab.c"
    break;

  case 21: /* C: I C  */
#line 348 "parser.y"
        {}
#line 1673 "y.tab.c"
    break;

  case 22: /* C: W C  */
#line 349 "parser.y"
        {}
#line 1679 "y.tab.c"
    break;

  case 23: /* C: %empty  */
#line 350 "parser.y"
    {}
#line 1685 "y.tab.c"
    break;

  case 24: /* $@7: %empty  */
#line 353 "parser.y"
            {push_pila();}
#line 1691 "y.tab.c"
    break;

  case 25: /* B: E MENOR $@7 E  */
#line 353 "parser.y"
                             {codegen();}
#line 1697 "y.tab.c"
    break;

  case 26: /* $@8: %empty  */
#line 354 "parser.y"
            {push_pila();}
#line 1703 "y.tab.c"
    break;

  case 27: /* B: E MAYOR $@8 E  */
#line 354 "parser.y"
                             {codegen();}
#line 1709 "y.tab.c"
    break;

  case 28: /* $@9: %empty  */
#line 355 "parser.y"
                  {push_pila();}
#line 1715 "y.tab.c"
    break;

  case 29: /* B: E MENOR_IGUAL $@9 E  */
#line 355 "parser.y"
                                   {codegen();}
#line 1721 "y.tab.c"
    break;

  case 30: /* $@10: %empty  */
#line 356 "parser.y"
                  {push_pila();}
#line 1727 "y.tab.c"
    break;

  case 31: /* B: E MAYOR_IGUAL $@10 E  */
#line 356 "parser.y"
                                   {codegen();}
#line 1733 "y.tab.c"
    break;

  case 32: /* $@11: %empty  */
#line 357 "parser.y"
               {push_pila();}
#line 1739 "y.tab.c"
    break;

  case 33: /* B: E IGUALDAD $@11 E  */
#line 357 "parser.y"
                                {codegen();}
#line 1745 "y.tab.c"
    break;

  case 34: /* $@12: %empty  */
#line 358 "parser.y"
                  {push_pila();}
#line 1751 "y.tab.c"
    break;

  case 35: /* B: E DESIGUALDAD $@12 E  */
#line 358 "parser.y"
                                   {codegen();}
#line 1757 "y.tab.c"
    break;

  case 36: /* $@13: %empty  */
#line 361 "parser.y"
       {search_hash();}
#line 1763 "y.tab.c"
    break;

  case 37: /* $@14: %empty  */
#line 361 "parser.y"
                                   {push_pila();}
#line 1769 "y.tab.c"
    break;

  case 38: /* A: V $@13 ASIGNACION $@14 E  */
#line 361 "parser.y"
                                                     {codegen_assign();}
#line 1775 "y.tab.c"
    break;

  case 39: /* $@15: %empty  */
#line 364 "parser.y"
             {push_pila();}
#line 1781 "y.tab.c"
    break;

  case 40: /* E: E SUMA $@15 E  */
#line 364 "parser.y"
                               {codegen();}
#line 1787 "y.tab.c"
    break;

  case 41: /* $@16: %empty  */
#line 365 "parser.y"
              {push_pila();}
#line 1793 "y.tab.c"
    break;

  case 42: /* E: E RESTA $@16 E  */
#line 365 "parser.y"
                                {codegen();}
#line 1799 "y.tab.c"
    break;

  case 43: /* $@17: %empty  */
#line 366 "parser.y"
                       {push_pila();}
#line 1805 "y.tab.c"
    break;

  case 44: /* E: E MULTIPLICACION $@17 E  */
#line 366 "parser.y"
                                         {codegen();}
#line 1811 "y.tab.c"
    break;

  case 45: /* $@18: %empty  */
#line 367 "parser.y"
                 {push_pila();}
#line 1817 "y.tab.c"
    break;

  case 46: /* E: E DIVISION $@18 E  */
#line 367 "parser.y"
                                   {codegen();}
#line 1823 "y.tab.c"
    break;

  case 47: /* $@19: %empty  */
#line 368 "parser.y"
                        {push_pila();}
#line 1829 "y.tab.c"
    break;

  case 48: /* E: E DIVISION_ENTERA $@19 E  */
#line 368 "parser.y"
                                          {codegen();}
#line 1835 "y.tab.c"
    break;

  case 51: /* E: NUMERO  */
#line 371 "parser.y"
           {push_pila();}
#line 1841 "y.tab.c"
    break;

  case 52: /* V: IDENTIFICADOR  */
#line 374 "parser.y"
                  {push_pila();}
#line 1847 "y.tab.c"
    break;


#line 1851 "y.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 377 "parser.y"

void parse(FILE *file) {
  yyin = file;
  hash_table_init(&hash_table);
  yyparse();
  fclose(yyin);
}

void yyerror(char *s) {
  printf("\n%s\n", s);
}
