#include "../../.box/testlib.h"

using namespace std;

const int MAX_T = 100000;
const long long MAX_P = 100000000000000000L;
const long long MAX_K = 100000000000000000L;
const long long MAX_M = 100000000000000000L;

int main(int argc, char *argv[])
{
    registerValidation(argc, argv);

    int t = inf.readInt(1, MAX_T, "t");
    inf.readEoln();

    for (int i = 1; i <= t; ++i)
    {
        inf.readLong(1, MAX_P, format("p[%d]", i));
        inf.readSpace();
        inf.readLong(1, MAX_K, format("k[%d]", i));
        inf.readSpace();
        inf.readLong(1, MAX_M, format("m[%d]", i));
        inf.readEoln();
    }

    inf.readEof();

    return 0;
}
