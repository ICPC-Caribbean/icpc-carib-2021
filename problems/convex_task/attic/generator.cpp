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

int main(int argc, char *argv[])
{
    // use ./generator <seed> <n> <in_CH> <q> <C>
    parseArgs(argc, argv);
    use_seed(argv[1]);

    string seed;
    int n;       // Number of input points
    int in_CH;   // Number of points in convex hull boundary
    int q;       // Number of queries
    long long C; // Maximum Coordinates of vertices

    getPositional(seed, n, in_CH, q, C);
    
    assert(n >= 3 && in_CH <= n);

    const int MAX = 3 * 300000000;
    auto polygon = jngen::GeometryRandom::convexPolygon(in_CH, C);
    
    for (auto &p : polygon) {
        p.x *= 3;
        p.y *= 3;
    }

    // Create the rest of the points inside the convex polygon by getting
    // three random points in the polygon and taking average
    int out_CH = n - in_CH;
    vector<jngen::Point> no_CH_points;
    set<pair<int,int>> s;

    int a, b, c;
    auto get_indices = [&] {
        a = jngen::rnd.next(in_CH);
        b = jngen::rnd.next(in_CH);
        c = jngen::rnd.next(in_CH);
    };

    for (int i = 0; i < out_CH; i++) {
        jngen::Point p;
        while(true) {
            get_indices();
            if (a == b || b == c || a == c)
                continue;
            p = (polygon[a] + polygon[b] + polygon[c]);
            p.x /= 3;
            p.y /= 3;
            if (!s.count({p.x, p.y}))
                break;
        }

        s.insert({p.x, p.y});
        no_CH_points.push_back(p);
    }        

    vector<jngen::Point> all;
    for (auto i : polygon)
        all.push_back(i);
    for (auto i : no_CH_points)
        all.push_back(i);
    jngen::shuffle(all.begin(), all.end());

    cout << n << '\n';
    for (auto i : all)
        cout << i.x << ' ' << i.y << '\n';
    cout << q << '\n';

    // 3 types of queries here
    // - 25%: points created by picking 3 random point from the CH and take average
    // - 65%: take the bounding box of the polygon and generate random points inside it
    // - 10%: fully random points whiting the allowed coordinates range

    int t1 = q / 4;
    int t2 = q * 65 / 100;
    int t3 = q - t1 - t2;

    vector<pair<int,int>> queries;

    // t1
    for (int i = 0; i < t1; i++) {
        jngen::Point p;
        while(true) {
            get_indices();
            if (a == b || b == c || a == c)
                continue;
            p = (polygon[a] + polygon[b] + polygon[c]);
            p.x /= 3;
            p.y /= 3;
            queries.push_back({p.x, p.y});
            break;
        }
    }

    // t2
    int minx = MAX, miny = MAX, mayx = 0, mayy = 0;
    for (auto i : all){
        minx = min(minx, (int)i.x);
        miny = min(miny, (int)i.y);
        mayx = max(mayx, (int)i.x);
        mayy = max(mayy, (int)i.y);
    }

    int dx = mayx - minx;
    int dy = mayy - miny;
    for (int i = 0; i < t2; i++) {
        int x = minx + jngen::rnd.next(dx);
        int y = miny + jngen::rnd.next(dy);
        queries.push_back({x, y});
    }

    // t3
    for (int i = 0; i < t3; i++) {
        int x = jngen::rnd.next(C);
        int y = jngen::rnd.next(C);
        queries.push_back({x, y});
    }

    jngen::shuffle(queries.begin(), queries.end());
    for (auto i : queries)
        cout << i.first << ' ' << i.second << endl;

    return 0;
}   