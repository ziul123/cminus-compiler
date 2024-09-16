%code top{
#include <stdio.h> 
#include <stdlib.h>
#define YYDEBUG 1
}

%code requires {
#include "tables.h"
typedef struct strpair {char* str1; char* str2;} strpair;
}

%union {
	int num;
	char *id;
	tac_address addr;
	strpair pair;
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
char *new_label();
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
    IF LPAREN expr RPAREN{

      char* exit_label = new_label();

      tac_cell jmp_exit = {.jmp_addr=exit_label, .source1=$3, .inst=JF};
      tac_table[tac_counter++] = jmp_exit;

      $<id>$ = exit_label;
     } bloco_cmd {

      tac_cell opr_exit = { .line_addr = $<idr>5, .inst=NOP};
      tac_table[tac_counter++] = opr_exit;

    }

    | IF LPAREN expr RPAREN{

      char* exit_label = new_label();
      char* else_label = new_label();


      tac_cell jmp_else = {.jmp_addr=else_label, .source1=$3, .inst=JF};
      tac_table[tac_counter++] = jmp_else;

      $<pair>$ = (strpair){.str1 = exit_label, .str2 = else_label};

     }bloco_cmd {

         tac_cell jump_exit = { .jump_addr = $<pair>5.str1, .inst=JMP};
         tac_table[tac_counter++] = jump_exit;

         tac_cell label_else = { .line_addr = $<pair>5.str2, .inst=NOP};
         tac_table[tac_counter++] = label_else;

     }
     ELSE bloco_cmd {

        tac_cell opr_exit = { .line_addr = $<pair>5.str1, .inst=NOP};
        tac_table[tac_counter++] = opr_exit;
     }



while_cmd:
    WHILE LPAREN expr RPAREN{

        char* top_label = new_label();
        char* botton_label = new_label();

        tac_cell tmp1 = {.jmp_addr=botton_label, .line_addr = top_label, .source1=$3, .inst=JF};
        tac_table[tac_counter++] = tmp1;

        $<pair>$ = (strpair){.str1 = top_label, .str2 = botton_label};
    } cmd {

        tac_cell tmp2 = {.jmp_addr=$<pair>5.str1, .inst=JMP};
        tac_table[tac_counter++] = tmp2;

        tac_cell tmp3 = { .line_addr = $<pair>5.str2, .inst=NOP};
        tac_table[tac_counter++] = tmp3;
    }



ret_cmd:
    RETURN SEMICOLON {

        tac_cell opr_ret = { .inst=RET};
        tac_table[tac_counter++] = opt_ret;
    }
    | RETURN expr SEMICOLON {

        tac_cell opr_ret_src = {.source1=$2, .inst=RET};
        tac_table[tac_counter++] = opt_ret_src;
    }

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
		printf("%s: ", cell.line_addr);
	printf(" %s ", str_inst[cell.inst]);
	print_tac_address(stdout, cell.source1);
	printf(" ");
	print_tac_address(stdout, cell.source2);
	if (cell.inst >= JMP && cell.inst <= BLE)
		printf(" %s", cell.jmp_addr);
	printf("\n");
}

char *new_label(){
    char *l = malloc(10);
    if(!l)
        printf("Erro alocando label \n");
    sprintf(l, "L%d", label_counter++);
    return l;
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
