#include "../../.box/jngen.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <cstdlib>

using namespace std;

void use_seed(char *value)
{
    vector<uint32_t> seed;
    for (int i = 0; value[i]; ++i)
        seed.push_back(value[i]);
    rnd.seed(seed);
}

int gcd(int a, int b)
{
    while (b)
    {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main(int argc, char *argv[])
{
    // use ./generator-line <seed> <q> <C>
    parseArgs(argc, argv);
    use_seed(argv[1]);

    string seed;
    int q;       // Number of queries
    long long C; // C*100 is Maximum Coordinates of vertices

    getPositional(seed, q, C);

    int x1, y1;
    tie(x1, y1) = jngen::rnd.nextp(C, jngen::dpair);

    int d = jngen::rnd.next(1, (int)C - max(x1, y1) + 1);

    int dx = d * jngen::rnd.next(1, 100);
    int dy = d * jngen::rnd.next(100);
    int g = gcd(dx, dy);

    int x2 = x1 + dx;
    int y2 = y1 + dy;

    cout << 2 << '\n';
    cout << x1 << ' ' << y1 << '\n';
    cout << x2 << ' ' << y2 << '\n';
    cout << q << '\n';

    // two types of queries
    // 70%: generated random point over the segment
    // 30%: fully random point
    vector<pair<int, int>> queries;
    for (int i = 0; i < q; i++)
    {
        if (i < q * 7 / 10)
        {
            int v = jngen::rnd.next(g + 1);
            int x = x1 + dx / g * v;
            int y = y1 + dy / g * v;
            queries.push_back({x, y});
        }
        else
        {
            int x, y;
            tie(x, y) = jngen::rnd.nextp(C * 100, jngen::dpair);
            queries.push_back({x, y});
        }
    }

    jngen::shuffle(queries.begin(), queries.end());
    for (auto i : queries)
        cout << i.first << ' ' << i.second << endl;

    return 0;
}
