%{
#include <stdlib.h>
#include <string.h>
#include <cassert>
#include "cnf.h"
#include "cnf_reader_def.h"
#define YY_NO_UNPUT
#define YY_NO_INPUT
static unsigned long parseULong(const char* text) {
    size_t len = strlen(text);
    (void) len;
    assert(len);
    char* end = nullptr;
    unsigned long ret = strtoul(text, &end, 10);
    assert(end == text + len);
    return ret;
}
%}
SPACE       [ \t\r\n]
LPT         \(
RPT         \)
COMMA       ,
NUMBER      (0|([1-9][0-9]*))
NOT         ~
%%

#[^\n]*     { ; }
{SPACE}     { ; }
{LPT}       { return T_LPT; }
{RPT}       { return T_RPT; }
{NUMBER}    { yylval.var = parseULong(yytext); return T_NUMBER; }
{NOT}       { return T_NOT; }
