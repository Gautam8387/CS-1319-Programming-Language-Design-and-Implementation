/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_3_A5_TAB_H_INCLUDED
# define YY_YY_3_A5_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    CHARACTER = 258,               /* CHARACTER  */
    ELSE = 259,                    /* ELSE  */
    FOR = 260,                     /* FOR  */
    IF = 261,                      /* IF  */
    INTEGER = 262,                 /* INTEGER  */
    RETURN = 263,                  /* RETURN  */
    VOID = 264,                    /* VOID  */
    L_BOX_BRACKET = 265,           /* L_BOX_BRACKET  */
    R_BOX_BRACKET = 266,           /* R_BOX_BRACKET  */
    L_PARENTHESIS = 267,           /* L_PARENTHESIS  */
    R_PARENTHESIS = 268,           /* R_PARENTHESIS  */
    L_CURLY_BRACE = 269,           /* L_CURLY_BRACE  */
    R_CURLY_BRACE = 270,           /* R_CURLY_BRACE  */
    ARROW = 271,                   /* ARROW  */
    AMPERSAND = 272,               /* AMPERSAND  */
    ASTERISK = 273,                /* ASTERISK  */
    PLUS = 274,                    /* PLUS  */
    MINUS = 275,                   /* MINUS  */
    EXCLAMATION = 276,             /* EXCLAMATION  */
    DIV = 277,                     /* DIV  */
    MOD = 278,                     /* MOD  */
    LESS_THAN = 279,               /* LESS_THAN  */
    GREATER_THAN = 280,            /* GREATER_THAN  */
    LESS_THAN_EQUAL = 281,         /* LESS_THAN_EQUAL  */
    GREATER_THAN_EQUAL = 282,      /* GREATER_THAN_EQUAL  */
    IS_EQUAL = 283,                /* IS_EQUAL  */
    NOT_EQUAL = 284,               /* NOT_EQUAL  */
    LOGICAL_AND = 285,             /* LOGICAL_AND  */
    LOGICAL_OR = 286,              /* LOGICAL_OR  */
    QUESTION = 287,                /* QUESTION  */
    COLON = 288,                   /* COLON  */
    ASSIGN = 289,                  /* ASSIGN  */
    SEMICOLON = 290,               /* SEMICOLON  */
    COMMA = 291,                   /* COMMA  */
    PUNCTUATOR = 292,              /* PUNCTUATOR  */
    WS = 293,                      /* WS  */
    IDENTIFIER = 294,              /* IDENTIFIER  */
    INTEGER_CONSTANT = 295,        /* INTEGER_CONSTANT  */
    CHARACTER_CONSTANT = 296,      /* CHARACTER_CONSTANT  */
    STRING_LITERAL = 297           /* STRING_LITERAL  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 23 "3_A5.y"

    char* intval;
    char* strval;
    char* charval;
    char* u_op;
    int count;
    int instr_no;
    char UNIARY_OPERATOR;
    struct symboltableentry* sym_entry;
    struct symboltype* sym_type;
    struct expression* expr;
    struct statement* stmt;

#line 120 "3_A5.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_3_A5_TAB_H_INCLUDED  */
