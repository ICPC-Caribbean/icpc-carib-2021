#include "../../.box/testlib.h"

using namespace std;

const int T = 100;
const int N = 100;

int main(int argc, char *argv[])
{
    registerValidation(argc, argv);

    int test = inf.readInt(1, T, "t");
    inf.readEoln();
    int sum = 0;
    while (test--)
    {
        int n = inf.readInt(1, N, "n");
        inf.readSpace();
        inf.readInt(1, n, "a");
        inf.readSpace();
        inf.readInt(1, n, "b");
        inf.readEoln();

        sum += n;
        ensuref(sum <= N, "the sum of n exceed %d", N);
    }
    inf.readEof();

    return 0;
}
