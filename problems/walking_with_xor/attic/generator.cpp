#include "../../.box/testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
    registerGen(argc, argv, 1);

    /* Read number from command line. */
    int n = atoi(argv[2]);
    int k = atoi(argv[3]);
    int m = atoi(argv[4]);
    if (n == -1) n = rnd.next(1, 200000);
    if (k == -1) k = rnd.next(0, (1<<20));
    if (m == -1) m = rnd.next(0, (1<<20));
    vector<int> t = { n, k };
    println(t);
    /* String of random binary string */
    vector<int> a;
    for (int i = 0; i < n; ++i)
        a.push_back(rnd.next(0, m));

	println(a);
}
