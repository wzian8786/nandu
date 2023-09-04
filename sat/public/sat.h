#pragma once
namespace nandu {
class CNF;
class SAT {
 public:
    SAT() : _cnf(nullptr) {}
    bool solve(CNF* cnf);

 private:
    const CNF*              _cnf;
};
}
