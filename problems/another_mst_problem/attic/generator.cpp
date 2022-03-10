#include "../../.box/testlib.h"
#include <vector>

using namespace std;

const int K = 1e9;

int main(int argc, char *argv[])
{
    registerGen(argc, argv, 1);

    /* Read number from command line. */
    int n = atoi(argv[2]);
    int k = atoi(argv[3]);
    if (n == -1)
        n = rnd.next(2, 500);
    if (k == -1)
        k = rnd.next(1, K);
    println(n);
    /* String of random binary string */
    vector<int> a;
    for (int i = 0; i < n; ++i)
        a.push_back(rnd.next(1, k));

    println(a);
}
