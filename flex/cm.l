%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parse.h"
%}
%option yylineno
id	[a-zA-Z][a-zA-Z0-9]*
number [-\+]?([0-9]+\.?[0-9]*|\.[0-9]+)
comment (\/\/.*\n)
c_start \/\*
c_end \*\/
branco [ \t\n]+
equal \=
plus \+
minus \-
asterisk \*
slash \/
lparen \(
rparen \)
lcurly \{
rcurly \}
semicolon ;
gt \>
lt \<
gt_eq \>\=
lt_eq \<\=
eq_eq \=\=
neq	\!\=

outro .

%x ML_COMMENT
%%

int			{return INT;}
void		{return VOID;}
if			{return IF;}
else		{return ELSE;}
while		{return WHILE;}
return	{return RETURN;}
,				{return COMMA;}

{id}		{
					yylval.id = strdup(yytext);
					if (!yylval.id)
						perror("Error allocating memory for var identifier.\n");
					return ID;
				}
{number}		{yylval.num = atoi(yytext); return NUM;}
{comment}		{;}
{c_start}		{BEGIN(ML_COMMENT);}
<ML_COMMENT>{
	.|\n				{yymore();}
	{c_end}			{BEGIN(INITIAL);}
}
{branco}		{;}
{equal}			{return EQUAL;}
{plus}			{return PLUS;}
{minus}			{return MINUS;}
{asterisk}	{return ASTERISK;}
{slash}			{return SLASH;}
{lparen}		{return LPAREN;}
{rparen}		{return RPAREN;}
{lcurly}		{return LCURLY;}
{rcurly}		{return RCURLY;}
{semicolon}	{return SEMICOLON;}
%%

int yywrap() {
 return 1;
}
