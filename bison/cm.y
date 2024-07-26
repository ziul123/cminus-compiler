/* Verificando a sintaxe de programas segundo nossa GLC-exemplo */
/* considerando notacao polonesa para expressoes */
%{
#include <stdio.h> 
#define YYDEBUG 1
int yylex(void);
int yyerror(char* s);
extern int yylineno;
%}
%token NUM
%token ID
%token EQ
%token PLUS
%token MINUS
%token ASTERISK
%token SLASH
%token PAREN_OPEN
%token PAREN_CLOSE
%token CURLY_OPEN
%token CURLY_CLOSE
%token END_CMD
%token GT
%token LT
%token GT_EQ
%token LT_EQ
%token EQ_EQ
%token NEQ
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
				 	CURLY_OPEN lista_cmds CURLY_CLOSE	{;}
					;

expr_cmd:
					expr END_CMD	{;}
					| END_CMD			{;}
					;

expr:
					var EQ expr		{;}
					| expr_simples	{;}
					;

expr_simples:
					expr_ad op_rel expr_ad	{;}
					| expr_ad	{;}
					;

op_rel: GT | LT | GT_EQ | LT_EQ | EQ_EQ | NEQ ;

expr_ad:
			 		expr_ad op_ad termo	{;}
					| termo	{;}
					;

op_ad: PLUS | MINUS ;

termo:
		 			termo op_mul fator	{;}
					| fator	{;}
					;

op_mul: ASTERISK | SLASH ;

fator:
		 			PAREN_OPEN expr PAREN_CLOSE	{;}
					| var	{;}
					| NUM	{;}
					;

var: ID ;

%%
int main () 
{
//	yydebug = 1;
	yyparse ();
}
int yyerror (char *s) /* Called by yyparse on error */
{
	printf ("Erro na linha %d\n", yylineno);
}


