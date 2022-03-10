// Alfonso² Peterssen
// Uses the flow graph construction described in https://digitalassets.lib.berkeley.edu/techreports/ucb/text/CSD-84-171.pdf
// Implemented using Dinic maximum flow algorithm.
// Complexity: O(V^2 * E log X)
// log X -> binary search till certain precision is attained.
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

const int MAXN = 100;
const int MAXE = 10000;
const int MAXV = MAXN + 2;
const int INF = 1 << 29;
const double EPS = 1e-6;

int N, E;
int V;
int w[MAXN];
int edge_sum[MAXV];
int M;

struct edge
{
    int u, v;
    double flow, cap;
    int next;
};

edge edges[2 * (MAXE + 2 * MAXE + MAXV)];
int edge_count;
int first[MAXV];
int source, sink;
int level[MAXV];
int Q[MAXV];

vector<int> answer;

void add_edge(int u, int v, double cap)
{
    edges[edge_count++] = {u, v, 0.0, cap, first[u]};
    first[u] = edge_count - 1;
    edges[edge_count++] = {v, u, cap, cap, first[v]};
    first[v] = edge_count - 1;
}

bool bfs()
{
    // cerr << "bfs" << endl;
    fill(level, level + V, -1);
    level[source] = 0;

    int front = 0, back = 0;
    for (Q[front++] = source; back < front;)
    {
        int u = Q[back++];
        for (int e = first[u]; e >= 0; e = edges[e].next)
        {
            int v = edges[e].v;
            if (level[v] < 0 && edges[e].cap - edges[e].flow > EPS)
            {
                Q[front++] = v;
                level[v] = level[u] + 1;
            }
        }
    }
    return level[sink] >= 0;
}

double dfs(int u, double flow)
{
    if (u == sink)
    {
        return flow;
    }
    for (int e = first[u]; e >= 0; e = edges[e].next)
    {
        int v = edges[e].v;
        if (level[u] < level[v])
        {
            double r = edges[e].cap - edges[e].flow;
            if (r > EPS)
            {
                double f = dfs(v, min(flow, r));
                if (f > EPS)
                {
                    edges[e].flow += f;
                    edges[e ^ 1].flow -= f;
                    return f;
                }
            }
        }
    }
    return 0.0;
}

vector<int> max_cut(double W)
{

    cerr << "max_cut W=" << W << endl;

    // Set node -> sink capacities.
    for (int i = 0; i < N; ++i)
    {
        int e = first[i];
        edges[e].cap = M + 2 * W - edge_sum[i] - 2 * w[i];
    }

    // Reset flow.
    for (int e = 0; e < edge_count; e++)
    {
        if (e & 1)
        {
            // back edges are saturated
            edges[e].flow = edges[e].cap;
        }
        else
        {
            // forward edges are fully available
            edges[e].flow = 0;
        }
    }

    double total_flow = 0;
    while (bfs())
    {
        double f;
        // cerr << "dfs" << endl;
        while ((f = dfs(source, INF)) > EPS)
        {
            total_flow += f;
        }
    }

    vector<int> cut;
    for (int i = 0; i < N; ++i)
    {
        if (level[i] >= 0)
        {
            cut.push_back(i);
        }
    }

    return cut;
}

int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> E;

    V = N;
    source = V++;
    sink = V++;

    fill(first, first + V, -1);

    for (int i = 0; i < N; ++i)
    {
        cin >> w[i];
    }

    for (int i = 0; i < E; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        --u;
        --v;
        add_edge(u, v, w);
        add_edge(v, u, w);
        edge_sum[u] += w;
        edge_sum[v] += w;        
    }

    // Compute m' described in the paper
    for (int i = 0; i < N; ++i)
    {
        M = max(M, edge_sum[i] + 2 * w[i]);
    }

    for (int i = 0; i < N; ++i)
    {
        add_edge(source, i, M);
        add_edge(i, sink, M /* + 2 * guess - */ - edge_sum[i] - 2 * w[i]);
    }

    int max_answer = accumulate(edge_sum, edge_sum + N, 0) + accumulate(w, w + N, 0) + 1;

    double lo = *max_element(w, w + N);
    double hi = max_answer;
    while (hi - lo > EPS)
    {
        double mid = (lo + hi) / 2.0;
        vector<int> cut = max_cut(mid);
        if (cut.empty())
        {
            hi = mid;
        }
        else
        {
            answer = cut;
            lo = mid;
        }
    }

    cout << answer.size() << endl;
    for (int i = 0; i < answer.size(); ++i)
    {
        cout << (answer[i] + 1) << " \n"[i + 1 == answer.size()];
    }

    return 0;
}
