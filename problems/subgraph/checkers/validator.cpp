#include "../../.box/testlib.h"

using namespace std;

const int MAXV = 100;
const int MAXE = 10000;
const int MAXW = 1000;
const int MAXP = 1000;

int main(int argc, char *argv[])
{
    registerValidation(argc, argv);

    int V = inf.readInt(1, MAXV, "V");
    inf.readSpace();
    int E = inf.readInt(1, MAXE, "E");
    inf.readEoln();

    for (int i = 1; i <= V; ++i)
    {
        inf.readInt(0, MAXP, format("p[%d]", i));
        if (i < V)
        {
            inf.readSpace();
        }
    }
    inf.readEoln();

    set<pair<int, int>> edges;

    for (int i = 1; i <= E; ++i)
    {
        int u = inf.readInt(1, V, format("u_%d", i));
        inf.readSpace();
        int v = inf.readInt(1, V, format("v_%d", i));
        inf.readSpace();
        int w = inf.readInt(0, MAXW, format("w_%d", i));
        inf.readEoln();

        ensuref(u != v, "forbidden self edge");
        ensuref(edges.count(make_pair(u, v)) == 0, "Graph can't contain multiple undirected edges between a pair of vertices");

        edges.insert(make_pair(u, v));
        edges.insert(make_pair(v, u));
    }
    inf.readEof();

    return 0;
}
