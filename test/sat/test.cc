#define BOOST_TEST_MODULE CNF_READER_TEST
#include <boost/test/unit_test.hpp>
#include "cnf.h"
using nandu::CNF;
BOOST_AUTO_TEST_CASE ( test_cnf_reader ) {
    constexpr const char* txt = \
        "(1 ~2 3)\n(1 4 ~6)\n(2 ~7 ~8)";
    constexpr size_t len = strlen(txt) + 1;
    char buff[len];
    CNF cnf;
    cnf.read(txt);
    FILE* fp = fmemopen(buff, len, "w");
    cnf.print(fp);
    fclose(fp);
    BOOST_CHECK(!strcmp(txt, buff));
}
