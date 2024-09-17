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

st_cell **symbol_table;
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
			PROC
			RETURN
			COMMA
			INT
			VOID
			READ
			WRITE


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
			insert_sym(symbol_table, $2, INT_T, 0);
		}
		| tipo ID LBRACK NUM RBRACK SEMICOLON {
			insert_sym(symbol_table, $2, INT_ARR_T, $4);
		}
		;

declaracao_fun:
		PROC ID {
			ft_cell new_fun = (ft_cell){.name=$2};
			fun_table[fun_counter++] = new_fun;
			size_t label_len = strlen($2) + 2; //espaco para : e \0
			char *func_label = malloc(label_len); 
			strcpy(func_label, $2);
			func_label[label_len-1] = ':';
      tac_cell func_enter = { .line_addr = func_label, .inst=NOP};
      tac_table[tac_counter++] = func_enter;
		}
		bloco_cmd {;}
    ;

tipo:
    VOID 	{$$ = VOID_T;}
    | INT {$$ = INT_T;}
    ;

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
		| chamada_funcao
		| read_cmd {;}
		| write_cmd {;}
    ;

bloco_cmd:
    LCURLY lista_cmds RCURLY {;}
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
		;

var: ID {/* checar se ID foi declarada */
	 		int found = 0;
			st_cell *symbol = find_sym(symbol_table, $1);
			if (symbol) {
				found = 1;
				symbol->usado = 1;
			}

			if(!found) {
				printf("%d: ERRO: Variavel %s nao foi declarada!\n", yylineno, $1);
				exit(1);
			}
			}

	 	| ID LBRACK expr RBRACK {
	 		int found = 0;
	 		for (int i=st_counter; i>=0; i--) {
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
			;

/* Comandos de controle de fluxo */

/* como if e if-else tem prefixo em comum, essa regra e necessaria */
if_prefix:
		IF LPAREN expr RPAREN {
      char* exit_label = new_label();
      char* else_label = new_label(); // tem que ser desfeito caso if

      tac_cell jmp_else = {.jmp_addr=exit_label, .source1=$3, .inst=JF};
      tac_table[tac_counter++] = jmp_else;
      $<pair>$ = (strpair){.str1 = exit_label, .str2 = else_label};
	}
	;

if_cmd:
    if_prefix bloco_cmd {

      tac_cell opr_exit = { .line_addr = ($<pair>1.str1), .inst=NOP};
      tac_table[tac_counter++] = opr_exit;
			free($<pair>1.str2);	// nao foi usado
			label_counter--;
    }

    | if_prefix bloco_cmd {

         tac_cell jump_exit = { .jmp_addr = ($<pair>1.str2), .inst=JMP};
         tac_table[tac_counter++] = jump_exit;

         tac_cell label_else = { .line_addr = ($<pair>1.str1), .inst=NOP};
         tac_table[tac_counter++] = label_else;

     }
     ELSE bloco_cmd {

        tac_cell opr_exit = { .line_addr = ($<pair>1.str2), .inst=NOP};
        tac_table[tac_counter++] = opr_exit;
     }
		 ;



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
		;


ret_cmd:
    RETURN SEMICOLON {

        tac_cell op_ret = { .inst=RET};
        tac_table[tac_counter++] = op_ret;
    }
		;

/* Chamadas de função e argumentos */

chamada_funcao:
    ID LPAREN RPAREN {
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


/* Comandos de entrada e saída */

read_cmd:
	READ var {;}

write_cmd:
	WRITE expr_simples {;}

%%
void print_st_cell(st_cell symbol) {
	printf("%s: %s", symbol.name, str_type[symbol.sym_type]);
	if (symbol.sym_type == INT_ARR_T)
		printf("[%d]", symbol.len);
	printf(" (usado: %s)\n", symbol.usado?"sim":"nao");
}

void print_ft_cell(ft_cell fun) {
	printf("%s (usado: %s)\n", fun.name, fun.usado?"sim":"nao");
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
	symbol_table = malloc(sizeof(st_cell*));

//	yydebug = 1;
	yyparse();

	st_cell *current = *symbol_table;
	if (current) {
		while (current) {
			//print_st_cell(*current);
			if (!current->usado)
				printf("WARNING: Variavel %s declarada mas nao utilizada!\n", current->name);
			current = current->next;
		}
	}

	for (int i=0; i<fun_counter; i++) {
		if (strcmp(fun_table[i].name, "main") == 0)
			fun_table[i].usado = 1;
		//print_ft_cell(fun_table[i]);
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
