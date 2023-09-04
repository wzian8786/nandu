#include "cnf.h"
#include <string.h>
#include <cassert>
extern int yyparse(void);
extern FILE* yyin;
extern "C" int yywrap(void) {
    return 1;
}
extern int yydebug;

namespace nandu {
Literal Literal::gLiteral;
Clause Clause::gClause;
CNF* CNF::gCNF = nullptr;
void CNF::read(const char* cnf) {
    size_t len = strlen(cnf);
    FILE* fp = fmemopen((void*)cnf, len, "r");
    assert(!gCNF);
    gCNF = this;
    yyin = fp;
    yyparse();
    gCNF = nullptr;
    fclose(fp);
}

void CNF::print(FILE* fp) const {
    for (size_t i = 0; i < _clauses.size(); ++i) {
        if (i) fputc('\n', fp);
        _clauses[i].print(fp);
    }
}

void Clause::print(FILE* fp) const {
    fputc('(', fp);
    for (size_t i = 0; i < _literals.size(); ++i) {
        if (i) fputc(' ', fp);
        _literals[i].print(fp);
    }
    fputc(')', fp);
}

void Literal::print(FILE* fp) const {
    if (isInv()) fputc('~', fp);
    fprintf(fp, "%lu", getVariable());
}

}
