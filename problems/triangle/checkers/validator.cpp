#include "../../.box/testlib.h"

#include <vector>
#include <cassert>

using namespace std;

const int MAXN = 100000;
const int MAXM = 100000;
const int MAX_COORDINATE = 1000000000;
const long long MAX_COORDINATE_L = 1000000000;

long long cross(pair<long long, long long> a, pair<long long, long long> b)
{
    return a.first * b.second - a.second * b.first;
}

int main(int argc, char *argv[])
{
    registerValidation(argc, argv);

    int N = inf.readInt(1, MAXN, "N");
    inf.readSpace();
    int M = inf.readInt(1, MAXN, "N");
    inf.readEoln();

    for (int i = 0; i < N; ++i)
    {
        int x = inf.readInt(-MAX_COORDINATE, MAX_COORDINATE, "x_i");
        inf.readSpace();
        int y = inf.readInt(-MAX_COORDINATE, MAX_COORDINATE, "y_i");
        inf.readEoln();
    }

    for (int i = 0; i < M; ++i)
    {
        vector<pair<long long, long long>> triangle;

        for (int j = 0; j < 3; ++j)
        {
            long long x = inf.readLong(-MAX_COORDINATE_L, MAX_COORDINATE_L, "x_i");
            inf.readSpace();
            long long y = inf.readLong(-MAX_COORDINATE_L, MAX_COORDINATE_L, "x_i");
            if (j + 1 == 3)
                inf.readEoln();
            else
                inf.readSpace();

            triangle.push_back({x, y});
        }

        pair<long long, long long> a, b, c;
        a = triangle[0];
        b = triangle[1];
        c = triangle[2];

        assert(min(abs(a.first - b.first), abs(a.second - b.second)) == 0);
        assert(min(abs(a.first - c.first), abs(a.second - c.second)) == 0);

        long long ab = max(abs(a.first - b.first), abs(a.second - b.second));
        long long ac = max(abs(a.first - c.first), abs(a.second - c.second));

        assert(ab == ac);
        assert(cross({b.first - a.first, b.second - a.second}, {c.first - a.first, c.second - a.second}) > 0);
    }

    inf.readEof();

    return 0;
}
