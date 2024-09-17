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
	type_t type_var;
	strpair pair;
}

%code {
int yylex(void);
int yyerror(char* s);
extern int yylineno;
extern FILE *yyin;

void print_tac_address(FILE *stream, tac_address addr);
void print_ft_cell(ft_cell fun);
void print_st_cell(st_cell symbol);

//st_cell **symbol_table;
#define MAX_NEST 10
st_cell **environment[MAX_NEST];
ft_cell fun_table[4096];
tac_cell tac_table[4096];

int st_counter = 0;
int fun_counter = 0;
int tac_counter = 0;
int label_counter = 0;
char *new_label();
}

%token <num> NUM
%token <id> ID
%nterm <type_var> tipo
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
%printer { fprintf(yyo, "%s", str_type[$$]); } <type_var>

%%

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
		tipo ID SEMICOLON {
			st_cell **symbol_table = environment[st_counter];
			insert_sym(symbol_table, $2, INT_T, 0);
		}
		| tipo ID LBRACK NUM RBRACK SEMICOLON {
			st_cell **symbol_table = environment[st_counter];
			insert_sym(symbol_table, $2, INT_ARR_T, $4);
		}
		;

declaracao_fun:
		tipo ID {
			ft_cell new_fun = (ft_cell){.name=$2, .ret_type=$1};
			fun_table[fun_counter] = new_fun;
			st_counter++;	//entra no escopo da funcao
			environment[st_counter] = malloc(sizeof(st_cell*));
			if (!environment[st_counter])
				printf("Erro alocando memoria para escopo\n");
		}
		LPAREN parametros RPAREN {
			fun_counter++;
		}
		bloco_cmd {
			destroy_st(environment[st_counter]); 
			st_counter--;}
    ;

tipo:
    VOID 	{$$ = VOID_T;}
    | INT {$$ = INT_T;}
    ;

parametros:
    lista_parametros {;}
    | VOID {fun_table[fun_counter].param_types[0] = VOID_T;}
    ;

lista_parametros:
    param {;}
    | lista_parametros COMMA param {;}
    ;

param:
		tipo ID LBRACK RBRACK {
			st_cell **symbol_table = environment[st_counter];
			insert_sym(symbol_table, $2, INT_ARR_T, 0);
			add_param_t(&fun_table[fun_counter], INT_ARR_T);
		}
    | tipo ID {
			st_cell **symbol_table = environment[st_counter];
			insert_sym(symbol_table, $2, INT_T, 0);
			add_param_t(&fun_table[fun_counter], INT_T);
		}
    ;

declaracoes_locais:
		/* empty */
		| declaracoes_locais declaracao_var {;}

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
    LCURLY {
			st_counter++;	//entra no escopo do bloco
			environment[st_counter] = malloc(sizeof(st_cell*));
			if (!environment[st_counter])
				printf("Erro alocando memoria para escopo\n");
		} 
		declaracoes_locais lista_cmds RCURLY {
			destroy_st(environment[st_counter]); 
			st_counter--;}
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

var: ID {/* checar se ID foi declarada */
	 		int found = 0;
	 		for (int i=st_counter; i>=0; i--) {
				st_cell **symbol_table = environment[i];
				st_cell *symbol = find_sym(symbol_table, $1);
				if (symbol) {
					found = 1;
					symbol->usado = 1;
					break;
				}
			}

			if(!found) {
				printf("%d: ERRO: Variavel %s nao foi declarada!\n", yylineno, $1);
				exit(1);
			}
			}

	 	| ID LBRACK expr RBRACK {
	 		int found = 0;
	 		for (int i=st_counter; i>=0; i--) {
				st_cell **symbol_table = environment[i];
				st_cell *symbol = find_sym(symbol_table, $1);
				if (symbol) {
					found = 1;
					symbol->usado = 1;
					break;
				}
			}

			if(!found) {
				printf("%d: ERRO: Variavel %s nao foi declarada!\n", yylineno, $1);
				exit(1);
			}
			}

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
    ID LPAREN argumentos RPAREN {
			int flag = 0;
			for (int i=0; i<fun_counter; i++) {
				if (fun_table[i].name == $1) {
					flag = 1;
					fun_table[i].usado = 1;
					break;
				}
			}
			if (!flag) {
				printf("%d: ERRO: Funcao %s nao foi declarada!\n", yylineno, $1);
			exit(1);
		}}
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
void print_st_cell(st_cell symbol) {
	printf("%s: %s", symbol.name, str_type[symbol.sym_type]);
	if (symbol.sym_type == INT_ARR_T)
		printf("[%d]", symbol.len);
}

void print_ft_cell(ft_cell fun) {
	printf("%s %s(", str_type[fun.ret_type], fun.name);
	printf("%s", str_type[fun.param_types[0]]);
	for (int i=1; i<=8; i++) {
		if (fun.param_types[i] == VOID_T)
			break;
		printf(", ");
		printf("%s", str_type[fun.param_types[i]]);
	}
	printf(")");
}

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
	environment[0] = malloc(sizeof(st_cell*));
	if (!environment[0])
		printf("Erro alocando memoria para escopo\n");

//	yydebug = 1;
	yyparse();


	st_cell **symbol_table = environment[st_counter];
	st_cell *current = *symbol_table;
	if (current) {
		while (current) {
			if (!current->usado)
				printf("WARNING: Variavel %s declarada mas nao utilizada!\n", current->name);
			current = current->next;
		}
	}

	for (int i=0; i<fun_counter; i++) {
		if (strcmp(fun_table[i].name, "main") == 0)
			fun_table[i].usado = 1;
		if (!fun_table[i].usado)
			printf("WARNING: Funcao %s declarada mas nao utilizada!\n", fun_table[i].name);
	}

	for (int i = 0; i < tac_counter; i++) {
		print_tac_cell(tac_table[i], i);
	}

}
int yyerror (char *s) /* Called by yyparse on error */
{
	printf ("Erro na linha %d\n", yylineno);
	exit(1);
}
