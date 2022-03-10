#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>

using namespace std;

typedef long long i64;

struct point
{
    i64 x, y;
};

i64 l1(point a)
{
    return a.x + a.y;
}

struct Triangle
{
    point vertex;
    i64 side;
    int index;

    i64 diagonal()
    {
        return l1(vertex) + side;
    }
};

i64 median(i64 a, i64 b, i64 c)
{
    return a + b + c - max({a, b, c}) - min({a, b, c});
}

struct LSM
{
    vector<vector<i64>> segments;

    void insert(i64 x)
    {
        segments.push_back({x});

        while (segments.size() >= 2 && segments[segments.size() - 1].size() == segments[segments.size() - 2].size())
        {
            auto a = segments.back();
            segments.pop_back();
            auto b = segments.back();
            segments.pop_back();
            vector<i64> c(a.size() + b.size());
            merge(a.begin(), a.end(), b.begin(), b.end(), c.begin());
            segments.push_back(c);
        }
    }

    /// How many inserted elements are bigger than or equal to x
    int query(i64 x)
    {
        int res = 0;
        for (auto &s : segments)
            res += s.size() - (lower_bound(s.begin(), s.end(), x) - s.begin());
        return res;
    }
};

struct BIT
{
    vector<i64> coordinates;
    vector<LSM> data;

    BIT(set<i64> coords) : coordinates(coords.begin(), coords.end()), data(coords.size() + 1)
    {
    }

    void insert(i64 x, i64 y)
    {
        int pos = lower_bound(coordinates.begin(), coordinates.end(), x) - coordinates.begin() + 1;
        assert(coordinates[pos - 1] == x);
        while (pos < data.size())
        {
            data[pos].insert(y);
            pos += pos & -pos;
        }
    }

    int _query(int pos, i64 y)
    {
        int res = 0;
        while (pos > 0)
        {
            res += data[pos].query(y);
            pos -= pos & -pos;
        }
        return res;
    }

    int query(i64 x, i64 y)
    {
        int lo = lower_bound(coordinates.begin(), coordinates.end(), x) - coordinates.begin() + 1;
        assert(coordinates[lo - 1] == x);

        int hi = data.size() - 1;
        return _query(hi, y) - _query(lo - 1, y);
    }
};

int pos_from_orientation(i64 dx, i64 dy)
{
    assert(dx != 0 && dy != 0);

    if (dx > 0 && dy > 0)
        return 0;
    else if (dx > 0 && dy < 0)
        return 1;
    else if (dx < 0 && dy < 0)
        return 2;
    else
        return 3;
}

void rotate(point &p)
{
    i64 x = p.x, y = p.y;
    p.x = -y, p.y = x;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    vector<point> P(n);

    for (int i = 0; i < n; ++i)
    {
        int x, y;
        cin >> x >> y;
        P[i] = {x, y};
    }

    vector<vector<Triangle>> triangles_groups(4);

    for (int i = 0; i < q; ++i)
    {
        i64 x1, y1, x2, y2, x3, y3;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

        i64 x = median(x1, x2, x3);
        i64 y = median(y1, y2, y3);

        i64 dx = x1 + x2 + x3 - 3 * x;
        i64 dy = y1 + y2 + y3 - 3 * y;

        int pos = pos_from_orientation(dx, dy);
        triangles_groups[pos].push_back({{x, y}, abs(dx), i});
    }

    vector<int> answer(q);

    for (auto &triangles : triangles_groups)
    {
        sort(triangles.begin(), triangles.end(), [&](Triangle &a, Triangle &b)
             { return a.diagonal() < b.diagonal(); });

        sort(P.begin(), P.end(), [&](point &a, point &b)
             { return l1(a) < l1(b); });

        set<i64> x_coordinates;

        for (auto &p : P)
            x_coordinates.insert(p.x);

        for (auto &t : triangles)
            x_coordinates.insert(t.vertex.x);

        BIT bit(x_coordinates);

        for (int i = 0, j = 0; i < triangles.size(); ++i)
        {
            auto &t = triangles[i];
            i64 diag = t.diagonal();

            while (j < P.size() && l1(P[j]) <= diag)
            {
                bit.insert(P[j].x, P[j].y);
                j++;
            }

            answer[t.index] = bit.query(t.vertex.x, t.vertex.y);
        }

        for (auto &p : P)
            rotate(p);

        for (auto &g : triangles_groups)
            for (auto &t : g)
                rotate(t.vertex);
    }

    for (auto x : answer)
        cout << x << endl;

    return 0;
}
