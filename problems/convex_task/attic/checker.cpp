#include "../../.box/testlib.h"
#include <cassert>

using namespace std;

typedef long double ld;

const ld eps = 1e-5;

struct point {
    ld x, y;
    int id;
    point (ld xx = 0, ld yy = 0, int iidd = 0): x(xx), y(yy), id(iidd) {}
    point operator + (const point &p) const {
        return {x + p.x, y + p.y};
    }
    point operator - (const point &p) const {
        return {x - p.x, y - p.y};
    }
    point operator * (const ld &t) const {
        return {x * t, y * t};
    }
};

inline ld dot(const point &p, const point &q) {
    return p.x * q.x + p.y * q.y;
}
inline ld norm(const point &p) {
    return dot(p, p);
}

int main(int argc, char * argv[])
{
    setName("convex task");
    registerTestlibCmd(argc, argv);

    const int maxn = 100000;
    const int maxc = 1000000000;

    int n = inf.readInt(1, maxn);
    inf.readEoln();

    vector<point> p(n);
    for (int i = 0; i < n; i++) {
        int x = inf.readInt(0, maxc);
        inf.readSpace();
        int y = inf.readInt(0, maxc);
        p[i] = point(x, y);
        inf.readEoln();
    }
 
    int q = inf.readInt(1, maxn);
    inf.readEoln();

    for (int i = 0; i < q; i++) {
        int x = inf.readInt(0, maxc);
        inf.readSpace();
        int y = inf.readInt(0, maxc);
        point pi(x, y);
        inf.readEoln();

        string out;
        ouf.readWordTo(out);
        ouf.readEoln();

        string _out;
        ans.readWordTo(_out);
        ans.readEoln();

        if (out == "impossible") {
            if (_out != "impossible") {
                quitf(_wa, "Contestant didn't find a solution but Judge did");
            }
        } else {
            if (_out == "impossible") {
                quitf(_wa, "There is no solution for this point");
            }

            // read stuff from Judge's solution (garbage)
            int _c = atoi(_out.c_str());
            for (int j = 0; j < _c; j++) {
                int _id = ans.readInt(1, n);
                ans.readSpace();
                ld _coeff = ans.readDouble(0, 1);
                ans.readEoln();
            }

            // read stuff from Contestant's solution
            int c = atoi(out.c_str());
            if (c <= 0) {
                quitf(_wa, "Number of used points must be positive");
            }

            if (c > 5) {
                quitf(_wa, "Contestant's solution used more than 5 elements");
            }
            
            point p_prime(0, 0);
            ld sum = 0;
            for (int j = 0; j < c; j++) {
                int id = ouf.readInt(1, n);
                ouf.readSpace();
                ld coeff = ouf.readDouble(0, 1);
                ouf.readEoln();
                // if (coeff < 1e-9) {
                //     quitf(_wa, "Coefficients must be greater than 0");
                // }
                p_prime = p_prime + p[id-1] * coeff;
                sum += coeff;
            }

            if (abs(sum - 1) > 1e-9) {
                quitf(_wa, "Coefficients does not sum 1");
            }
            
            if (norm(pi - p_prime) > eps) {
                quitf(_wa, "Linear combination gives a different point");
            }
        }
    }

    inf.readEof();
    ouf.readEof();
    ans.readEof();
    
    quitf(_ok, "ok");

    return 0;
}