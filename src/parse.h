/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_SRC_PARSE_H_INCLUDED
# define YY_YY_SRC_PARSE_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 7 "bison/cm.y" /* yacc.c:1909  */

#include "tables.h"

#line 48 "src/parse.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NUM = 258,
    ID = 259,
    EQUAL = 260,
    PLUS = 261,
    MINUS = 262,
    ASTERISK = 263,
    SLASH = 264,
    LPAREN = 265,
    RPAREN = 266,
    LCURLY = 267,
    RCURLY = 268,
    LBRACK = 269,
    RBRACK = 270,
    SEMICOLON = 271,
    GT = 272,
    LT = 273,
    GT_EQ = 274,
    LT_EQ = 275,
    EQ_EQ = 276,
    NEQ = 277,
    IF = 278,
    ELSE = 279,
    WHILE = 280,
    RETURN = 281,
    COMMA = 282,
    INT = 283,
    VOID = 284
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 11 "bison/cm.y" /* yacc.c:1909  */

	int num;
	char *id;
	tac_address addr;
	type_t type_var;

#line 97 "src/parse.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_PARSE_H_INCLUDED  */
