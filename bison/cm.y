%code top{
#include <stdio.h> 
#include <stdlib.h>
#define YYDEBUG 1
}

%code requires {
#include "tables.h"
}

%union {
	int num;
	char *id;
	tac_address addr;
}

%code {
int yylex(void);
int yyerror(char* s);
extern int yylineno;
extern FILE *yyin;
void print_tac_address(FILE *stream, tac_address addr);
st_cell symbol_table[4096];
tac_cell tac_table[4096];
int tac_counter = 0;
int label_counter = 0;
}

%token <num> NUM
%token <id> ID
%nterm <enum TYPE> tipo
%nterm <addr>
			fator
			termo
			expr_ad
			expr_simples
			expr
%nterm <id> var
%token
			EQUAL
			PLUS
			MINUS
			ASTERISK
			SLASH
			LPAREN
			RPAREN
			LCURLY
			RCURLY
			LBRACK
			RBRACK
			SEMICOLON
			GT
			LT
			GT_EQ
			LT_EQ
			EQ_EQ
			NEQ
			IF
			ELSE
			WHILE
			RETURN
			COMMA
			INT
			VOID


%printer { fprintf(yyo, "%d", $$); } <num>;
%printer { fprintf(yyo, "%s", $$); } <id>;
%printer { print_tac_address(yyo, $$); } <addr>;


%%
/* Regras definindo a GLC e acoes correspondentes */
/* neste nosso exemplo quase todas as acoes estao vazias */

programa:
    lista_declaracoes {printf("Programa sintaticamente correto\n");}
    ;

lista_declaracoes:
    declaracao 											{;}
    | lista_declaracoes declaracao 	{;}
    ;

declaracao:
    declaracao_var 		{;}
		| declaracao_fun 	{;}
		;

declaracao_var:
		tipo ID SEMICOLON {;}
		| tipo ID LBRACK NUM RBRACK SEMICOLON {;}
		;

declaracao_fun:
		tipo ID LPAREN parametros RPAREN bloco_cmd {;}
    ;

tipo:
    VOID 	{;}
    | INT {;}
    ;

parametros:
    lista_parametros {;}
    | VOID {;}
    ;

lista_parametros:
    param {;}
    | lista_parametros COMMA param {;}
    ;

param:
    tipo ID {;}
		| tipo ID LBRACK RBRACK {;}
    ;

declaracoes_locais:
		/* empty */
		| declaracoes_locais declaracao_var

lista_cmds:
    /* empty */
    | lista_cmds cmd {;}
    ;

cmd:
    expr_cmd {;}
    | bloco_cmd {;}
    | if_cmd {;}
    | while_cmd {;}
    | ret_cmd {;}
    ;

bloco_cmd:
    LCURLY declaracoes_locais lista_cmds RCURLY {;}
    ;

expr_cmd:
    expr SEMICOLON {;}
    | SEMICOLON {;}
    ;

expr:
		var EQUAL expr	{
			tac_address id = {.name = $1, .addr_type = NAME};
			tac_cell tmp = {.source1=id, .source2=$3, .inst=CPY};
			tac_table[tac_counter] = tmp;
			$$ = make_tmp(tac_counter++);}

    | expr_simples {;}
    ;

expr_simples:
		expr_ad GT expr_ad			{
			tac_cell tmp = {.source1=$1, .source2=$3, .inst=SGT};
			tac_table[tac_counter] = tmp;
			$$ = make_tmp(tac_counter++);}

		| expr_ad LT expr_ad		{
			tac_cell tmp = {.source1=$1, .source2=$3, .inst=SLT};
			tac_table[tac_counter] = tmp;
			$$ = make_tmp(tac_counter++);}

		| expr_ad GT_EQ expr_ad	{
			tac_cell tmp = {.source1=$1, .source2=$3, .inst=SGTE};
			tac_table[tac_counter] = tmp;
			$$ = make_tmp(tac_counter++);}

		| expr_ad LT_EQ expr_ad	{
			tac_cell tmp = {.source1=$1, .source2=$3, .inst=SLTE};
			tac_table[tac_counter] = tmp;
			$$ = make_tmp(tac_counter++);}

		| expr_ad EQ_EQ expr_ad	{
			tac_cell tmp = {.source1=$1, .source2=$3, .inst=SEQ};
			tac_table[tac_counter] = tmp;
			$$ = make_tmp(tac_counter++);}

		| expr_ad NEQ expr_ad		{
			tac_cell tmp = {.source1=$1, .source2=$3, .inst=SNEQ};
			tac_table[tac_counter] = tmp;
			$$ = make_tmp(tac_counter++);}

		| expr_ad	{;}
		;

expr_ad:
		expr_ad PLUS termo		{
			tac_cell tmp = {.source1=$1, .source2=$3, .inst=ADD};
			tac_table[tac_counter] = tmp;
			$$ = make_tmp(tac_counter++);}

		| expr_ad MINUS termo	{
			tac_cell tmp = {.source1=$1, .source2=$3, .inst=SUB};
			tac_table[tac_counter] = tmp;
			$$ = make_tmp(tac_counter++);}

		| termo	{;}
		;

termo:
		termo ASTERISK fator	{
			tac_cell tmp = {.source1=$1, .source2=$3, .inst=MUL};
			tac_table[tac_counter] = tmp;
			$$ = make_tmp(tac_counter++);}

		| termo SLASH fator		{
			tac_cell tmp = {.source1=$1, .source2=$3, .inst=DIV};
			tac_table[tac_counter] = tmp;
			$$ = make_tmp(tac_counter++);}

		| fator	{;}
		;

fator:
		LPAREN expr RPAREN	{$$ = $2;}
		| var	{$$ = (tac_address){.name = $1, .addr_type = NAME};}
		| NUM	{$$ = (tac_address){.constant = $1, .addr_type = CONST};}
		| chamada_funcao {;}
		;

var: ID {;}
	 	| ID LBRACK expr RBRACK {;}

/* Comandos de controle de fluxo */

if_cmd:
    IF LPAREN expr RPAREN bloco_cmd {;}
    | IF LPAREN expr RPAREN bloco_cmd ELSE bloco_cmd {;}
    ;

while_cmd:
    WHILE LPAREN expr RPAREN cmd {;}
    ;

ret_cmd:
    RETURN SEMICOLON {;}
    | RETURN expr SEMICOLON {;}
    ;

/* Chamadas de função e argumentos */

chamada_funcao:
    ID LPAREN argumentos RPAREN {;}
    ;

argumentos:
		/* empty */
		| lista_argumentos {;}
		;

lista_argumentos:
		expr {;}
		| lista_argumentos COMMA expr {;}
		;

%%

void print_tac_address(FILE *stream, tac_address addr) {
	switch (addr.addr_type) {
		case TEMP:
			fprintf(stream, "(%d)", addr.temporary);
			break;

		case CONST:
			fprintf(stream, "%d", addr.constant);
			break;

		case NAME:
			fprintf(stream, "%s", addr.name);
			break;
	}
}

void print_tac_cell(tac_cell cell, int lineno) {
	printf("%d\t", lineno);
	if (cell.line_addr)
		printf("%s", cell.line_addr);
	printf(" %s", str_inst[cell.inst]);
	print_tac_address(stdout, cell.source1);
	printf(" ");
	print_tac_address(stdout, cell.source2);
	if (cell.jmp_addr)
		printf("%s", cell.jmp_addr);
	printf("\n");
}

int main(int argc, char **argv) {
	if (argc == 2) {
		if (!(yyin = fopen(argv[1], "r"))) {
			perror("Error reading file.\n");
			return 1;
		}
	}
	yydebug = 1;
	yyparse();

	// botamos para ficar padronizado com o tamanho do tac_counter
	for (int i = 0; i < tac_counter; i++) {
		print_tac_cell(tac_table[i], i);
	}
}
int yyerror (char *s) /* Called by yyparse on error */
{
	printf ("Erro na linha %d\n", yylineno);
	exit(1);
}
