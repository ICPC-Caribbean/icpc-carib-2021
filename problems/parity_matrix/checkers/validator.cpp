#include "../../.box/testlib.h"

using namespace std;

const int MIN_D = 1;
const int MAX_D = 50;
const int MIN_V = 0;
const int MAX_V = 100;

int main(int argc, char *argv[])
{
    registerValidation(argc, argv);

    int n = inf.readInt(MIN_D, MAX_D, "n");
    inf.readSpace();
    int m = inf.readInt(MIN_D, MAX_D, "m");
    inf.readEoln();

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            inf.readInt(MIN_V, MAX_V, format("a_%d_%d", i, j));
            if (j + 1 < m)
                inf.readSpace();
            else
                inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
