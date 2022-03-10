// Alfonso² Peterssen
// Uses graph construction derived from the Baseball Elimination problem.
// Implemented using Ford-Fulkerson maximum flow algorithm.
// Complexity: O(E * f * log X)? With real capacities the complexity may be off.
// log X -> binary search till certain precision is attained.
#include <iostream>
#include <vector>
#include <numeric>
#include <queue>
#include <algorithm>

using namespace std;

const int MAXN = 100;
const int MAXE = 1000;
const int MAXV = MAXE + MAXN + 2;
const int INF = 1 << 29;
const double EPS = 1e-6;

int N, E;
int V;
int w[MAXN];
int total_edge_sum;
int M;
int edge_sum[MAXV];

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
double flow[MAXV];
int from[MAXV];

vector<int> answer;

void add_edge(int u, int v, double cap)
{
    edges[edge_count++] = {u, v, 0.0, cap, first[u]};
    first[u] = edge_count - 1;
    edges[edge_count++] = {v, u, cap, cap, first[v]};
    first[v] = edge_count - 1;
}

vector<int> min_cut(double W)
{

    cerr << "min_cut W=" << W << endl;

    // Set node -> sink capacities.
    for (int i = 0; i < N; ++i)
    {
        int e = first[E + i];
        edges[e].cap = max(0.0, W - w[i]);
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

    while (true)
    {
        fill(from, from + V, -1);
        fill(flow, flow + V, 0);
        flow[source] = INF;
        from[source] = source;

        queue<int> Q;
        for (Q.push(source); !Q.empty(); Q.pop())
        {
            int u = Q.front();
            for (int e = first[u]; e >= 0; e = edges[e].next)
            {
                int v = edges[e].v;
                if (from[v] >= 0)
                {
                    continue;
                }
                double residual = edges[e].cap - edges[e].flow;
                if (residual > EPS)
                {
                    Q.push(v);
                    from[v] = e;
                    flow[v] = min(flow[u], residual);
                }
            }
        }

        if (from[sink] < 0)
        {
            break;
        }

        total_flow += flow[sink];
        for (int u = sink; u != source;)
        {
            int e = from[u];
            edges[e].flow += flow[sink];
            edges[e ^ 1].flow -= flow[sink];
            u = edges[e].u;
        }
    }

    vector<int> cut;
    for (int i = 0; i < N; ++i)
    {
        if (from[E + i] >= 0)
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

    V = E + N;
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
        total_edge_sum += w;
        add_edge(source, i, w);
        add_edge(i, E + u, INF);
        add_edge(i, E + v, INF);
    }

    for (int i = 0; i < N; ++i)
    {
        add_edge(E + i, sink, 0.0);
    }

    int max_answer = total_edge_sum + accumulate(w, w + N, 0) + 1;

    double lo = *max_element(w, w + N);
    double hi = max_answer;
    while (hi - lo > EPS)
    {
        double mid = (lo + hi) / 2.0;
        vector<int> cut = min_cut(mid);
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
