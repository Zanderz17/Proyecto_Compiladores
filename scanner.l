%{
#include<stdio.h>
#include "y.tab.h"
void yyerror(char *);
%}

%option noyywrap

/* Comentarios - Varias lineas */
COMENTARIO \/\*(.|\n)*?\*\/

/* Palabrtas Reservadas */
MAIN "main"
IF "if"
WHILE "while"
ELSE "else"
PUTW "putw"
PUTS "puts"
INT "int"

/* Operadores de relación */
MENOR "<"
MAYOR ">"
MENOR_IGUAL "<="
MAYOR_IGUAL ">="
IGUALDAD "=="
DESIGUALDAD "!="

/* Operadores lógicos */
AND "&&"
OR "||"

/* Operadores Aritméticos */
SUMA "+"
RESTA "-"
DIVISION "/"
MULTIPLICACION "*"
DIVISION_ENTERA "%"

/* Identificadores y cadenas */
IDENTIFICADOR {LETRA}({LETRA}|{DIGITO}|[_])*
CONST_CADENA \"[^\"]*\"|\'[^\']*\'
NUMERO {DIGITO}({DIGITO})*

/* Asignación */
ASIGNACION "="

/* Delimitadores */
PARENTESIS_A "("
PARENTESIS_C ")"
LLAVE_A  "{"
LLAVE_C "}"
COMA ","
FINAL_LINEA ";"

/* Expresiones Regulares */
LETRA [a-zA-Z]
DIGITO [0-9]

%%
{COMENTARIO}			{}
{MAIN} 						{return(MAIN);}
{IF} 							{return(IF);}
{WHILE} 					{return(WHILE);}
{ELSE} 						{return(ELSE);}
{PUTW} 						{return(PUTW);}
{PUTS} 						{return(PUTS);}
{INT} 						{return(INT);}

{MENOR} 					{return(MENOR);}
{MAYOR} 					{return(MAYOR);}
{MENOR_IGUAL} 		{return(MENOR_IGUAL);}
{MAYOR_IGUAL} 		{return(MAYOR_IGUAL);}
{IGUALDAD} 				{return(IGUALDAD);}
{DESIGUALDAD} 		{return(DESIGUALDAD);}

{AND} 						{return(AND);}
{OR} 							{return(OR);}

{SUMA} 						{return(SUMA);}
{RESTA} 					{return(RESTA);}
{DIVISION} 				{return(DIVISION);}
{MULTIPLICACION} 	{return(MULTIPLICACION);}
{DIVISION_ENTERA} {return(DIVISION_ENTERA);}

{IDENTIFICADOR} 	{return(IDENTIFICADOR);}
{CONST_CADENA}	 	{return(CONST_CADENA);}
{NUMERO} 					{return(NUMERO);}

{ASIGNACION} 			{return(ASIGNACION);}

{PARENTESIS_A} 		{return(PARENTESIS_A);}
{PARENTESIS_C} 		{return(PARENTESIS_C);}
{LLAVE_A} 				{return(LLAVE_A);}
{LLAVE_C} 				{return(LLAVE_C);}
{COMA} 						{return(COMA);}
{FINAL_LINEA} 		{return(FINAL_LINEA);}

"\n"              {}
"\t" 							{}
" " 							{}
<<EOF>>           {yyterminate();}
. 								{return yytext[0];}
%%