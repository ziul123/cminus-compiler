%{
#include <stdio.h>
#include "parse.h"
extern FILE *yyin;
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
paren_open \(
paren_close \)
curly_open \{
curly_close \}
end_cmd ;
gt \>
lt \<
gt_eq \>\=
lt_eq \<\=
eq_eq \=\=
neq	\!\=
outro .

%x ML_COMMENT
%%
{id}		{return ID;}
{number}	{return NUM;}
{comment}	{;}
{c_start}	{BEGIN(ML_COMMENT);}
<ML_COMMENT>{
	.|\n	{yymore();}
	{c_end}	{BEGIN(INITIAL);}
}
{branco}	{;}
{equal}		{return EQ;}
{plus}		{return PLUS;}
{minus}		{return MINUS;}
{asterisk}		{return ASTERISK;}
{slash}		{return SLASH;}
{paren_open}		{return PAREN_OPEN;}
{paren_close}		{return PAREN_CLOSE;}
{curly_open}		{return CURLY_OPEN;}
{curly_close}		{return CURLY_CLOSE;}
{end_cmd}		{return END_CMD;}
{outro} 	{printf(":-(\n");}
%%
/* recomendavel declarar sempre
   funcao yywrap() */

int yywrap() {
 return 1;
}
