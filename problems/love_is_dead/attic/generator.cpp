#include "../../.box/testlib.h"

using namespace std;

const int MperT = 100;

int main(int argc, char *argv[])
{
    registerGen(argc, argv, 1);

    /* Read number from command line. */
    int test = atoi(argv[2]);
    int N = atoi(argv[3]);

    int sz = MperT;
    println(test);
    while (test--)
    {
        int n = rnd.next(1, min(sz - test, N));
        sz -= n;
        vector<int> x = {n, rnd.next(1, n), rnd.next(1, n)};
        println(x);
    }
}
