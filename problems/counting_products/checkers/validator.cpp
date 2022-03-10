#include "../../.box/testlib.h"

using namespace std;

const int MAX_N = 1000;
const int MAX_K = 1000;

int main(int argc, char *argv[])
{
    registerValidation(argc, argv);

    int n = inf.readInt(1, MAX_N, "n");
    inf.readSpace();
    int k = inf.readInt(1, MAX_K, "k");
    inf.readEoln();
    inf.readEof();

    return 0;
}
