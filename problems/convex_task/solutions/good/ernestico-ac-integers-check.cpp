#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <algorithm>
#include <cassert>

#define endl '\n'

using namespace std;

typedef long double ld;
typedef long long ll;

const ld eps = 1e-9;

struct point
{
    ld x, y;
    int id;
    point(ld xx = 0, ld yy = 0, int iidd = 0) : x(xx), y(yy), id(iidd) {}
    point operator+(const point &p) const
    {
        return {x + p.x, y + p.y};
    }
    point operator-(const point &p) const
    {
        return {x - p.x, y - p.y};
    }
    point operator*(const ld &t) const
    {
        return {x * t, y * t};
    }
    point operator/(const ld &t) const
    {
        return {x / t, y / t};
    }
    point operator/(const point &a) const
    {
        return point{x * a.x + y * a.y, y * a.x - x * a.y} /
               /*divide 2 complejos*/ (a.x * a.x + a.y * a.y);
    }
    bool operator<(const point &p) const
    {
        if (abs(p.x - x) > eps)
            return x < p.x;
        return y < p.y;
    }
};
struct line
{
    point p[2];
    line(const point p1, const point p2)
    {
        p[0] = p1, p[1] = p2;
    }
    point &operator[](int id)
    {
        return id ? p[1] : p[0];
    }
    const point &operator[](int id) const
    {
        return id ? p[1] : p[0];
    }
};

inline ld cross(const point &p, const point &q)
{
    return p.x * q.y - p.y * q.x;
}
inline ld dot(const point &p, const point &q)
{
    return p.x * q.x + p.y * q.y;
}
inline ld norm(const point &p)
{
    return dot(p, p);
}
inline ld abs(const point &p)
{
    return sqrt(norm(p));
}

int ccw(point a, point b, point c)
{
    b = b - a;
    c = c - a;
    if (cross(b, c) > 0)
        return +1; // counter clockwise
    if (cross(b, c) < 0)
        return -1; // clockwise
    if (dot(b, c) < 0)
        return +2; // c--a--b on line
    if (norm(b) < norm(c))
        return -2; // a--b--c on line
    return 0;
}

ll gcd(ll a, ll b) {
    while (b) {
        ll t = b;
        b = a % b;
        a = t;
    }
    return a;
}

bool intersectSP(const line &s, const point &p)
{
    ll x1 = s[0].x + 0.5, y1 = s[0].y + 0.5;
    ll x2 = s[1].x + 0.5, y2 = s[1].y + 0.5; 
    ll x = p.x + 0.5, y = p.y + 0.5;
    ll dx = x2 - x1;
    ll dy = y2 - y1;
    ll g = abs(gcd(dx, dy));
    dx /= g;
    dy /= g;

    ll dx1 = x - x1;
    ll dy1 = y - y1;


    if (dx != 0 && dy != 0) {
        if ( dx1 % dx != 0 || dy1 % dy != 0 || dx1 / dx != dy1 / dy)
            return false;
        return (dx1 / dx <= g && dx1 / dx >= 0);
    } else if (dy != 0) {
        if (dx1 != 0 || dy1 % dy != 0)
            return false;
        return (dy1 / dy <= g && dy1 / dy >= 0);
    } else if (dx != 0) {
        if (dy1 != 0 || dx1 % dx != 0)
            return false;
        return (dx1 / dx <= g && dx1 / dx >= 0);

    } else assert(false);
}

point crosspoint(const line &l, const line &m)
{
    ld A = cross(l[1] - l[0], m[1] - m[0]);
    ld B = cross(l[1] - l[0], l[1] - m[0]);
    if (abs(A) < eps && abs(B) < eps)
        return m[0]; // same line
    if (abs(A) < eps)
        assert(false); // PRECONDITION NOT SATISFIED
    return m[0] + (m[1] - m[0]) * B / A;
}

vector<point> convex_hull(vector<point> ps)
{
    int n = ps.size(), k = 0;
    sort(ps.begin(), ps.end());
    vector<point> ch(2 * n);
    for (int i = 0; i < n; ch[k++] = ps[i++]) // lower-hull
        while (k >= 2 && ccw(ch[k - 2], ch[k - 1], ps[i]) <= 0)
            --k;
    for (int i = n - 2, t = k + 1; i >= 0; ch[k++] = ps[i--]) // upper-hull
        while (k >= t && ccw(ch[k - 2], ch[k - 1], ps[i]) <= 0)
            --k;
    ch.resize(k - 1);
    return ch;
}

int main()
{
#ifdef ernestico
    freopen("a.in", "r", stdin);
#endif // ernestico
    ios_base::sync_with_stdio(0); cin.tie(0);

    cout << fixed << setprecision(20);

    int n;
    cin >> n;
    vector<point> p(n);
    for (int i = 0; i < n; i++)
    {
        cin >> p[i].x >> p[i].y;
        p[i].id = i + 1;
    }

    p = convex_hull(p);
    n = p.size();

    auto check_on_point = [](const point &a, const point &pi)
    {
        if (norm(a - pi) < eps)
        {
            cout << 1 << endl;
            cout << a.id << ' ' << 1 << endl;
            return true;
        }
        return false;
    };

    auto check_on_segment = [] (const point &a, const point &b, const point &pi) {
        if (intersectSP(line(a, b), pi)) {
            ld t = abs(pi - a) / abs(b -  a);

            cout << 2 << endl;
            cout << a.id << ' ' << (1 - t) << endl;
            cout << b.id << ' ' << t << endl;

            point p_prime = a * (1 - t) + b * t;
            assert(norm(p_prime - pi) < eps);
            return true;
        }
        return false;
    };

    int q;
    cin >> q;
    while (q--)
    {
        point pi;
        cin >> pi.x >> pi.y;
        if (n == 1)
        { // only one point
            if (!check_on_point(p[0], pi))
                cout << "impossible" << endl;
        }
        else if (n == 2)
        { // two points -> line
            point a = p[0], b = p[1];
            if (check_on_point(a, pi) || check_on_point(b, pi)) // on one of the points
                continue;

            if (!check_on_segment(a, b, pi)) // not on the segment
                cout << "impossible" << endl;
        }
        else
        { // more than 3 point -> polygon
            if (cross(p[1] - p[0], pi - p[0]) < -eps)
            {
                cout << "impossible" << endl;
                continue;
            }
            if (cross(p[n - 1] - p[0], pi - p[0]) > eps)
            {
                cout << "impossible" << endl;
                continue;
            }

            // find triangle containing the point
            int lo = 1, hi = n - 2;
            while (lo < hi)
            {
                int m = (lo + hi + 1) >> 1;
                if (cross(p[m] - p[0], pi - p[0]) >= 0)
                    lo = m;
                else
                    hi = m - 1;
            }

            point a = p[0], b = p[lo], c = p[lo + 1];

            // check if it's outside the triangle
            if (cross(c - b, pi - b) < -eps)
            {
                cout << "impossible" << endl;
                continue;
            }

            // check if it's one of the three points
            if (check_on_point(a, pi) || check_on_point(b, pi) || check_on_point(c, pi))
                continue;

            // check if it's on one of the three segments
            if (check_on_segment(a, b, pi) || check_on_segment(b, c, pi) || check_on_segment(a, c, pi))
                continue;

            // it's inside abc triangle
            point d = crosspoint(line(b, pi), line(a, c));
            ld t = abs(pi - b) / abs(d - b);
            ld k = abs(d - a) / abs(c - a);

            cout << 3 << endl;
            cout << a.id << ' ' << t * (1 - k) << endl;
            cout << b.id << ' ' << (1 - t) << endl;
            cout << c.id << ' ' << t * k << endl;

            assert(abs(1 - t * (1 - k) - (1 - t) - t * k) < eps);
            point p_prime = a * t * (1 - k) + b * (1 - t) + c * t * k;
            assert(norm(p_prime - pi) < 1e-5);
        }
    }

    return 0;
}
