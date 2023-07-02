%{
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
%}

%token 
  MAIN 
  IF 
  WHILE
  ELSE
  PUTW
  PUTS
  INT

  MENOR
  MAYOR
  MENOR_IGUAL
  MAYOR_IGUAL
  IGUALDAD
  DESIGUALDAD

  AND
  OR

  SUMA
  RESTA
  DIVISION
  MULTIPLICACION
  DIVISION_ENTERA

  IDENTIFICADOR
  CONST_CADENA
  NUMERO

  ASIGNACION

  PARENTESIS_A
  PARENTESIS_C
  LLAVE_A
  LLAVE_C
  COMA
  FINAL_LINEA
%right ASIGNACION
%left MENOR MAYOR MENOR_IGUAL MAYOR_IGUAL IGUALDAD DESIGUALDAD
%left SUMA RESTA 
%left MULTIPLICACION DIVISION DIVISION_ENTERA

%%
S : M {}
  | D M {}
;

D: INT identifier_list FINAL_LINEA
;

identifier_list : IDENTIFICADOR {insert_hash();}
  | identifier_list COMA IDENTIFICADOR {insert_hash();}
;

M : MAIN PARENTESIS_A PARENTESIS_C LLAVE_A C LLAVE_C {}
;

I : IF PARENTESIS_A B PARENTESIS_C { Lcond(); } if_block
  ;

if_block : LLAVE_A C LLAVE_C { print_label(); }
          | LLAVE_A C LLAVE_C { Iincond(); print_label(); } ELSE LLAVE_A C LLAVE_C { print_label_if(); }
          ;

W : WHILE {print_label_while();} PARENTESIS_A B PARENTESIS_C {Lcond();} LLAVE_A C {Wincond();} LLAVE_C {print_label();} 

C : A FINAL_LINEA C {}
  | PUTS PARENTESIS_A CONST_CADENA {printf("Imprimir cadena: %s\n", yytext);} PARENTESIS_C FINAL_LINEA C {}
  | PUTW PARENTESIS_A E PARENTESIS_C FINAL_LINEA C{}
  | I C {}
  | W C {}
  | {}
;

B : E MENOR {push_pila();} E {codegen();}
  | E MAYOR {push_pila();} E {codegen();}
  | E MENOR_IGUAL {push_pila();} E {codegen();}
  | E MAYOR_IGUAL {push_pila();} E {codegen();}
  | E IGUALDAD {push_pila();} E {codegen();}
  | E DESIGUALDAD {push_pila();} E {codegen();}
;

A :  V {search_hash();} ASIGNACION {push_pila();}  E {codegen_assign();}
;

E : E SUMA   {push_pila();}  E {codegen();}
  | E RESTA   {push_pila();}  E {codegen();}
  | E MULTIPLICACION   {push_pila();}  E {codegen();}
  | E DIVISION   {push_pila();}  E {codegen();}
  | E DIVISION_ENTERA   {push_pila();}  E {codegen();}
  | PARENTESIS_A E PARENTESIS_C
  | V
  | NUMERO {push_pila();}
;

V : IDENTIFICADOR {push_pila();}
;

%%
void parse(FILE *file) {
  yyin = file;
  hash_table_init(&hash_table);
  yyparse();
  fclose(yyin);
}

void yyerror(char *s) {
  printf("\n%s\n", s);
}