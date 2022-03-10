#include "../../.box/testlib.h"

using namespace std;

const int MAX_N = 100000;
const int MAX_A = (1 << 30) - 1;

int main(int argc, char *argv[])
{
    registerValidation(argc, argv);

    int n = inf.readInt(1, MAX_N, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i)
    {
        inf.readInt(0, MAX_A, format("a_%d", i));
        if (i + 1 < n)
            inf.readSpace();
        else
            inf.readEoln();
    }

    inf.readEof();

    return 0;
}
