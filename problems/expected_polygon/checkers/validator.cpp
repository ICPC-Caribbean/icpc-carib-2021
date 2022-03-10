#include "../../.box/testlib.h"
#include <vector>

using namespace std;

const int MAX_C = 1000000000;
const int MAX_N = 2000;

typedef long long i64;
struct point
{
    i64 x, y;

    point(i64 x = 0, i64 y = 0) : x(x), y(y) {}

    bool operator==(const point &r)
    {
        return x == r.x && y == r.y;
    }

    bool operator!=(const point &r)
    {
        return !(*this == r);
    }

    point operator-(const point &r)
    {
        return {x - r.x, y - r.y};
    }

    point positive()
    {
        if (y < 0)
            return {-x, -y};
        else
            return {x, y};
    }
};

i64 cross(point a, point b)
{
    return a.x * b.y - a.y * b.x;
}

int main(int argc, char *argv[])
{
    registerValidation(argc, argv);

    int n = inf.readInt(2, MAX_N, "n");
    inf.readEoln();

    vector<point> points(n);

    for (int i = 1; i <= n; ++i)
    {
        points[i - 1].x = inf.readInt(-MAX_C, MAX_C, format("x_%d", i));
        inf.readSpace();
        points[i - 1].y = inf.readInt(-MAX_C, MAX_C, format("y_%d", i));
        inf.readEoln();
    }

    inf.readEof();

    for (int i = 0; i < n; ++i)
    {
        auto pivot = points[i];

        auto points_c = points;

        sort(points_c.begin(), points_c.end(), [&](point &a, point &b)
             {
                 auto ap = (a - pivot).positive();
                 auto bp = (b - pivot).positive();

                 if (ap == point())
                     return true;
                 if (bp == point())
                     return false;

                 return cross(ap, bp) > 0; });

        ensuref(points_c[0] == pivot, "Failed sorting");
        ensuref(points_c[0] != points_c[1], "Repeated points are not allowed");
        for (int j = 2; j < n; ++j)
            ensuref(cross((points_c[j - 1] - pivot).positive(), (points_c[j] - pivot).positive()) > 0, "Collinear points are not allowed");
    }

    return 0;
}
