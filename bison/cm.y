%code top{
#include <stdio.h> 
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

st_cell symbol_table[4096];
tac_cell tac_table[4096];
int tac_counter = 0;
int label_counter = 0;
}

%token <num> NUM
%token <id> ID
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
			END_CMD
			GT
			LT
			GT_EQ
			LT_EQ
			EQ_EQ
			NEQ

%printer { print_tac_address(yyo, $$); } <tac_address>;


%%
/* Regras definindo a GLC e acoes correspondentes */
/* neste nosso exemplo quase todas as acoes estao vazias */

programa:
					lista_cmds	{printf("Programa sintaticamente correto\n");}
					;

lista_cmds:
					/* empty */
					| lista_cmds cmd	{;}
					;

cmd:
					expr_cmd	{;}
					| bloco_cmd	{;}
					;

bloco_cmd:
				 	LCURLY lista_cmds RCURLY	{;}
					;

expr_cmd:
					expr END_CMD	{;}
					| END_CMD			{;}
					;

expr:
					var EQUAL expr		{/*
						tac_cell *tmp = make_tac_cell($1, $3, (SGT));
						tac_table[tac_counter++] = tmp;
						$$ = make_tmp(tmp)*/;}
					| expr_simples	{;}
					;

expr_simples:
					expr_ad GT expr_ad			{
						tac_cell tmp = {.source1=$1, .source2=$3, .inst=SGT};
						tac_table[tac_counter] = tmp;
						$$ = tac_counter++;}
					| expr_ad LT expr_ad		{
						tac_cell tmp = {.source1=$1, .source2=$3, .inst=SLT};
						tac_table[tac_counter] = tmp;
						$$ = tac_counter++;}
					| expr_ad GT_EQ expr_ad	{
						tac_cell tmp = {.source1=$1, .source2=$3, .inst=SGTE};
						tac_table[tac_counter] = tmp;
						$$ = tac_counter++;}
					| expr_ad LT_EQ expr_ad	{
						tac_cell tmp = {.source1=$1, .source2=$3, .inst=SLTE};
						tac_table[tac_counter] = tmp;
						$$ = tac_counter++;}
					| expr_ad EQ_EQ expr_ad	{
						tac_cell tmp = {.source1=$1, .source2=$3, .inst=SEQ};
						tac_table[tac_counter] = tmp;
						$$ = tac_counter++;}
					| expr_ad NEQ expr_ad		{
						tac_cell tmp = {.source1=$1, .source2=$3, .inst=SNEQ};
						tac_table[tac_counter] = tmp;
						$$ = tac_counter++;}
					| expr_ad	{;}
					;

expr_ad:
			 		expr_ad PLUS termo		{
						tac_cell tmp = {.source1=$1, .source2=$3, .inst=ADD};
						tac_table[tac_counter] = tmp;
						$$ = tac_counter++;}
			 		| expr_ad MINUS termo	{
						tac_cell tmp = {.source1=$1, .source2=$3, .inst=SUB};
						tac_table[tac_counter] = tmp;
						$$ = tac_counter++;}
					| termo	{;}
					;

termo:
		 			termo ASTERISK fator	{
						tac_cell tmp = {.source1=$1, .source2=$3, .inst=MUL};
						tac_table[tac_counter] = tmp;
						$$ = tac_counter++;}
		 			| termo SLASH fator		{
						tac_cell tmp = {.source1=$1, .source2=$3, .inst=DIV};
						tac_table[tac_counter] = tmp;
						$$ = tac_counter++;}
					| fator	{;}
					;

fator:
		 			LPAREN expr RPAREN	{;}
					| var	{$$ = (tac_address){.name = $1, .addr_type = NAME};}
					| NUM	{$$ = (tac_address){.constant = $1, .addr_type = CONST};}
					;

var: ID {;};

%%

void print_tac_address(FILE *stream, tac_address addr) {
	switch (addr.addr_type) {
		case TEMP:
			fprintf(stream, "(%d)", (int) addr.temporary);
			break;

		case CONST:
			fprintf(stream, "%d", addr.constant);
			break;

		case NAME:
			fprintf(stream, "%s", addr.name);
			break;
	}
}

void print_tac_cell(tac_cell *cell, int lineno) {
	printf("%d: %s ", lineno, str_inst[cell->inst]);
	print_tac_address(stdout, cell->source1);
	printf(" ");
	print_tac_address(stdout, cell->source2);
	printf("\n");
}

int main(int argc, char **argv) {
	if (argc == 2) {
		if (!(yyin = fopen(argv[1], "r"))) {
			perror("Error reading file.\n");
			return 1;
		}
	}
//	yydebug = 1;
	yyparse();

	for (int i = 0; i < tac_counter; i++) {
		print_tac_cell(tac_table[i], i);
	}
}
int yyerror (char *s) /* Called by yyparse on error */
{
	printf ("Erro na linha %d\n", yylineno);
}


