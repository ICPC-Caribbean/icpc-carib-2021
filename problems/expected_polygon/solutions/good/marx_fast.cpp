#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <list>
#include <numeric>
#include <random>

using namespace std;

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

const i64 mod = 1000000007;

i64 powmod(i64 a, i64 b, i64 m = mod)
{
    i64 c = 1;
    while (b)
    {
        if (b & 1)
            c = a * c % m;
        a = a * a % m;
        b >>= 1;
    }
    return c;
}

i64 inverse(i64 a, i64 m = mod)
{
    return powmod(a, m - 2, m);
}

i64 upd(i64 a)
{
    return (a % mod + mod) % mod;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    /// p2i[j] = 2**(-j) % mod
    vector<i64> p2i(n + 2);
    p2i[0] = 1;
    i64 i2 = inverse(2);
    for (int i = 1; i <= n + 1; ++i)
        p2i[i] = p2i[i - 1] * i2 % mod;

    vector<point> points(n);

    for (int i = 0; i < n; ++i)
        cin >> points[i].x >> points[i].y;

    i64 res = 0;

    for (int i = 0; i < n; ++i)
    {
        auto &pivot = points[i];

        vector<int> index(points.size());
        iota(index.begin(), index.end(), 0);

        sort(index.begin(), index.end(), [&](int i_a, int i_b)
             {
                 auto ap = (points[i_a] - pivot).positive();
                 auto bp = (points[i_b] - pivot).positive();

                 if (ap == point())
                     return true;
                 if (bp == point())
                     return false;

                 return cross(ap, bp) > 0; });

        int inside = 0, outside = 0;

        for (int j = 1; j < n; ++j)
        {
            if (points[index[j]].y >= pivot.y)
                inside++;
            else
                outside++;
        }

        for (int j = 1; j < n; ++j)
        {
            i64 cur;
            if (points[index[j]].y >= pivot.y)
            {
                inside--;
                cur = upd(cross(pivot, points[index[j]])) * p2i[outside + 2 + 1] % mod;
                outside++;
            }
            else
            {
                outside--;
                cur = upd(cross(pivot, points[index[j]])) * p2i[inside + 2 + 1] % mod;
                inside++;
            }
            res = (res + cur) % mod;
        }
    }

    cout << res << endl;

    return 0;
}
