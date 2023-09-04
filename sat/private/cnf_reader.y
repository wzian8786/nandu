%{
#include <stdio.h>
#include "cnf.h"
extern int yylex(void);
void yyerror(const char* s);
using nandu::CNF;
using nandu::Clause;
using nandu::Literal;
%}

%token T_LPT;
%token T_RPT;
%token T_NUMBER;
%token T_NOT;

%union yyu {
    unsigned long var;
}

%start cnf;
%%
cnf
    : clauses
    |
    ;

clauses
    : clause {
        CNF::cnf()->addClause(std::move(Clause::clause()));
    }
    | clauses clause {
        CNF::cnf()->addClause(std::move(Clause::clause()));
    }
    ;

clause
    : T_LPT literals T_RPT 
    ;

literals
    : literal {
        Clause::clause().addLiteral(Literal::literal());
    }
    | literals literal {
        Clause::clause().addLiteral(Literal::literal());
    }
    ;

literal
    : T_NUMBER {
        Literal::literal() = Literal(yylval.var, false);
    }
    | T_NOT T_NUMBER {
        Literal::literal() = Literal(yylval.var, true);
    }
    ;
%%

void yyerror(const char* s) {
    fprintf(stderr, "--- Oops, %s\n", s);
}
