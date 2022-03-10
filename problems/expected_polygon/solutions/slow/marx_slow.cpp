#include <iostream>
#include <vector>

using namespace std;

typedef long long i64;

struct point
{
    i64 x, y;

    point operator-(const point &r)
    {
        return {x - r.x, y - r.y};
    }

    bool operator<(const point &r) const
    {
        return x == r.x ? y < r.y : x < r.x;
    }
};

i64 cross(point a, point b)
{
    return a.x * b.y - a.y * b.x;
}

int sign(i64 a)
{
    return a < 0 ? -1 : int(a > 0);
}

const i64 mod = 1000000007;

i64 powmod(i64 a, i64 b, i64 m)
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

i64 inverse(i64 a, i64 m)
{
    return powmod(a, m - 2, m);
}

vector<point> convex_hull(vector<point> cloud)
{
    int n = cloud.size(), k;
    vector<point> ch(2 * n);

    sort(cloud.begin(), cloud.end());

    for (int i = k = 0; i < n; ch[k++] = cloud[i++])
        while (k > 1 && sign(cross(ch[k - 1] - ch[k - 2], cloud[i] - ch[k - 2])) >= 0)
            --k;

    for (int i = n - 2, t = k; i >= 0; ch[k++] = cloud[i--])
        while (k > t && sign(cross(ch[k - 1] - ch[k - 2], cloud[i] - ch[k - 2])) >= 0)
            --k;

    ch.resize(k - (k > 1));
    return ch;
}

i64 area2(vector<point> hull)
{
    i64 A = 0;
    for (int i = 0, n = hull.size(); i < n; ++i)
        A += cross(hull[i], hull[(i + 1) % n]);
    return A;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<point> points(n);

    for (int i = 0; i < n; ++i)
        cin >> points[i].x >> points[i].y;

    i64 res = 0;

    for (int mask = 0; mask < (1 << n); ++mask)
    {
        vector<point> cloud;
        for (int j = 0; j < n; ++j)
            if (mask >> j & 1)
                cloud.push_back(points[j]);

        res = (res + abs(area2(convex_hull(cloud)))) % mod;
    }

    i64 i2 = inverse(2, mod);
    i64 den = powmod(i2, n + 1, mod);

    res = res * den % mod;

    cout << res << endl;

    return 0;
}
