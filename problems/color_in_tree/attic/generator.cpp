//#include "../../.box/testlib.h"
#include "../../.box/jngen.h"
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;
typedef pair<int, int> ii;

const int MAX = 2e5;
const int MAX_COLOR = 64;

/*
Generates a random tree.
First argument: n, the number of nodes
Second argument: type of tree, as follows:
    1: rope
    2: almost rope
    3: balanced binary tree
    4: almost balanced binary tree
    5: random MST
Third argument: q, the number of queries
 */

struct DisjointSet
{
    vector<int> s;
    DisjointSet(int n): s(vector<int>(n, -1)) {}

    int find(int i) {
        return s[i] < 0 ? i : (s[i] = find(s[i]));
    }

    void join(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (s[a] == s[b])
            s[a]--;
        if (s[a] <= s[b])
            s[b] = a;
        else
            s[a] = b;
    }
};


vector<int> getPerm(int n)
{
    vector<int> res(n);
    for (int i = 0; i < n; i++)
        res[i] = i + 1;
    shuffle(res.begin(), res.end());
    return res;
}

vector<ii> getRope(int n)
{
    vector<ii> res;
    for (int i = 1; i < n; i++)
        res.emplace_back(i - 1, i);
    return res;
}

//makes the first 50% be a rope
vector<ii> getAlmostRope(int n)
{
    assert(n > 1);
    vector<ii> res = getRope( n / 2);
    for (int i = n / 2; i < n; i++)
        res.emplace_back(i, rnd.next(i));
    return res;
}

vector<ii> getBalancedTree(int n)
{
    vector<ii> res;
    for (int i = 1; i < n; i++)
        res.emplace_back(i, i / 2);
    return res;
}

vector<ii> getAlmostBalancedTree(int n)
{
    assert(n > 1);
    vector<ii> res = getBalancedTree(n / 2);
    for (int i = n / 2; i < n; i++)
        res.emplace_back(i, rnd.next(i));
    return res;
}

vector<ii> getRandomMST(int n)
{
    DisjointSet dj(n);
    vector<ii> res;
    while ((int)res.size() + 1 < n) {
        int a = rnd.next(n), b = rnd.next(n);
        if (dj.find(a) != dj.find(b)) {
            res.emplace_back(a, b);
            dj.join(a, b);
        }
    }
    return res;
}

int main(int argc, char* argv[])
{
    // use ./generator <n> <type_of_tree> <queries> <seed>
    // <type_of_tree> -> 1: rope,
    //                -> 2: almost rope,
    //                -> 3: balanced binary tree,
    //                -> 4: almost balanced binary tree,
    //                -> 5: random MST
    //registerGen(argc, argv, 1);
    parseArgs(argc, argv);

    string seed;
    int n, type, q;
    getPositional(seed, n, type, q);
    
    //int n = atoi(argv[1]);     // number of nodes in the tree
    //int type = atoi(argv[2]);  // type of tree
    //int q = atoi(argv[3]);     // number of queries
    
    assert(n > 0 && n <= MAX);
    assert(q > 0 && q <= MAX);

    vector<int> perm = getPerm(n);
    vector<ii> edges;
    if (type == 1) {
        edges = getRope(n);
    }
    else if (type == 2) {
        edges = getAlmostRope(n);
    }
    else if (type == 3) {
        edges = getBalancedTree(n);
    }
    else if (type == 4) {
        edges = getAlmostBalancedTree(n);
    }
    else if (type == 5) {
        edges = getRandomMST(n);
    }
    else {
        assert(0);
    }

    // nodes and queries
    cout << n << " " << q << "\n";

    // colors of nodes
    int max_color = 10;
    for (int i = 0; i < n; i++) {
        int color = rnd.next(0, 63);
        max_color = max(color, max_color);
        assert(color >= 0 && color < MAX_COLOR);
        cout << color;
        if (i == n - 1)
            cout << "\n";
        else
            cout << " ";
    }

    // edges of tree
    for (ii i : edges)
        cout << perm[i.first] << " " << perm[i.second] << '\n';

    // queries
    for (int i = 0; i < q; i++) {
        type = rnd.next(1, 2);
        assert(type >= 1 && type <= 2);

        int node = rnd.next(1, n);
        assert(node >= 1 && node <= n);

        if (type == 1) {    // update
            cout << type << " " << node << "\n";
        }
        else if (type == 2) {   // query
            int color = rnd.next(0, max_color);
            assert(color >= 0 && color < MAX_COLOR);
            cout << type << " " << node << " " << color << "\n";
        }
    }
    return 0;
}

