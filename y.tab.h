/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

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
