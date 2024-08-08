/* Verificando a sintaxe de programas segundo nossa GLC-exemplo */
/* considerando notacao polonesa para expressoes */
%{
#include <stdio.h> 
#define YYDEBUG 1
int yylex(void);
int yyerror(char* s);
extern int yylineno;
%}
%define api.value.type union
%token <int> NUM
%token <char *> ID
%nterm <int>
			fator
			termo
			expr_ad
			expr_simples
			expr
%nterm <char *>
			var
%token
			EQ	
			PLUS
			MINUS
			ASTERISK
			SLASH
			PAREN_OPEN
			PAREN_CLOSE
			CURLY_OPEN
			CURLY_CLOSE
			END_CMD
			GT
			LT
			GT_EQ
			LT_EQ
			EQ_EQ
			NEQ

%printer { fprintf(yyo, "%s", $$); } ID;
%printer { fprintf(yyo, "%s", $$); } var;
%printer { fprintf(yyo, "%d", $$); } <int>;

%destructor {free($$);} <char *>

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
						var EQ expr		{printf("%s: %d\n", $1, $3); $$ = $3;}
					| expr_simples	{;}
					;

expr_simples:
					expr_ad op_rel expr_ad	{;}
					| expr_ad	{;}
					;

op_rel: GT | LT | GT_EQ | LT_EQ | EQ_EQ | NEQ ;

expr_ad:
			 		expr_ad op_ad termo	{$$ = $1 + $3;}
					| termo	{;}
					;

op_ad: PLUS | MINUS ;

termo:
		 			termo op_mul fator	{$$ = $1 * $3;}
					| fator	{;}
					;

op_mul: ASTERISK | SLASH ;

fator:
		 			PAREN_OPEN expr PAREN_CLOSE	{;}
					| var	{;}
					| NUM	{;}
					;

var: ID {;};

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


