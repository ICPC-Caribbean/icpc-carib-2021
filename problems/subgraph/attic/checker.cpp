#include "../../.box/testlib.h"
#include <vector>

using namespace std;

const int MAXV = 100;

int V, E;
int p[MAXV];
int cost[MAXV][MAXV];

int node_sum(const vector<int> &S)
{
    int sum = 0;
    for (int u : S)
    {
        sum += p[u];
    }
    return sum;
}

int edge_sum(const vector<int> &S)
{
    int sum = 0;
    for (int i = 0; i < S.size(); ++i)
    {
        int u = S[i];
        for (int j = 0; j < i; ++j)
        {
            int v = S[j];
            sum += cost[u][v];
        }
    }
    return sum;
}

double score(int den, int num)
{
    return num > 0 ? (den / (double)num) : 0.0;
}

vector<int> read_answer(InStream &stream)
{
    vector<int> S;
    int n = stream.readInt(0, V, "|S|");
    for (int i = 0; i < n; ++i)
    {
        int u = stream.readInt(1, V, format("S_%d", i));
        --u;
        if (count(begin(S), end(S), u) != 0)
        {
            stream.quitf(_wa, "duplicated vertex %d", u + 1);
        }
        S.push_back(u);
    }
    return S;
}

int main(int argc, char *argv[])
{
    setName("checks that the graph has the maximum score");
    registerTestlibCmd(argc, argv);

    V = inf.readInt();
    E = inf.readInt();
    for (int i = 0; i < V; ++i)
    {
        p[i] = inf.readInt();
    }

    for (int i = 1; i <= E; ++i)
    {
        int u = inf.readInt();
        int v = inf.readInt();
        int w = inf.readInt();
        u--;
        v--;
        cost[u][v] = cost[v][u] = w;
    }

    vector<int> jS = read_answer(ans);
    vector<int> pS = read_answer(ouf);

    int jDen = node_sum(jS) + edge_sum(jS);
    int pDen = node_sum(pS) + edge_sum(pS);

    if (jDen * (long long)pS.size() > pDen * (long long)jS.size())
    {
        quitf(_wa, "jury has the better answer: jans = %.10f, pans = %.10f\n", score(jDen, jS.size()), score(pDen, pS.size()));
    }
    else if (jDen * (long long)pS.size() < pDen * (long long)jS.size())
    {
        quitf(_fail, ":( participant has the better answer: jans = %.10f, pans = %.10f\n", score(jDen, jS.size()), score(pDen, pS.size()));
    }
    else
    {
        quitf(_ok, "maximum score is %.10f", score(jDen, jS.size()));
    }

    return 0;
}
