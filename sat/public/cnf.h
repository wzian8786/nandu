#pragma once
#include <stdio.h>
#include <vector>
#include <cstdint>
namespace nandu {
class Literal {
 public:
    Literal() : _data{.v{0}} {}
    Literal(unsigned long var, bool s) :
        _data{{var, s}} {}

    Literal& operator=(const Literal& l) {
        _data.v = l._data.v;
        return *this;
    }

    bool isInv() const { return _data.s; }
    uint64_t getVariable() const { return _data.var; }
    uint64_t hash() const { return _data.v; }
    Literal flip() const { return Literal(_data.var, !_data.s); }

    static Literal& literal() { return gLiteral; }

    void print(FILE* s) const;
        
 private:
    union {
        struct {
            uint64_t        var:63;
            uint64_t        s:1;
        };
        uint64_t            v;
    }                       _data;
    static Literal          gLiteral;
};

class Clause {
 public:
    Clause() {}
    Clause(Clause&& c) : _literals(std::move(c._literals)) {}

    Clause& operator=(Clause&& c) {
        _literals = std::move(c._literals);
        return *this;
    }
    
    typedef std::vector<Literal>::iterator lit;
    typedef std::vector<Literal>::const_iterator clit;

    void addLiteral(const Literal& l) { _literals.push_back(l); }

    lit begin() { return _literals.begin(); }
    lit end() { return _literals.end(); }

    clit begin() const { return _literals.begin(); }
    clit end() const { return _literals.end(); }

    static Clause& clause() { return gClause; }

    void print(FILE* s) const;

 private:
    std::vector<Literal>    _literals;
    static Clause           gClause;
};

class CNF {
 public:
    CNF() {}

    typedef std::vector<Clause>::iterator cit;
    typedef std::vector<Clause>::const_iterator ccit;

    void addClause(Clause&& clause) {
        _clauses.push_back(std::move(clause));
    }

    cit begin() { return _clauses.begin(); }
    cit end() { return _clauses.end(); }
    ccit begin() const { return _clauses.begin(); }
    ccit end() const { return _clauses.end(); }

    void read(const char* cnf);

    static CNF* cnf() { return gCNF; }

    void print(FILE* s) const;

 private:
    std::vector<Clause>     _clauses;
    static CNF*             gCNF;
};
}
