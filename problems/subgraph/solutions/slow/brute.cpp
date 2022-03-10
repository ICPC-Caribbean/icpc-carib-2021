#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

const int MAXV = 100;

int V, E;
int w[MAXV];
int G[MAXV][MAXV];

int main(int argc, char const *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> V >> E;
    for (int i = 0; i < V; ++i) {
        cin >> w[i];
    }
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        --u;
        --v;
        G[u][v] = G[v][u] = w;
    }    

    int best_n = 0;
    int best_d = 1;
    int best_mask = 0;

    for (int s = 1; s < (1 << V); ++s) {
        int cnt = 0;
        int sum_w = 0;
        int sum_e = 0;
        for (int u = 0; u < V; ++u) {
            if (s & (1 << u)) {
                cnt++;
                sum_w += w[u];
                for (int v = 0; v < u; ++v) {
                    if (s & (1 << v)) {
                        sum_e += G[u][v];
                    }
                }
            }
        }
        if ((sum_w + sum_e) * best_d > best_n * cnt) {
            best_n = (sum_w + sum_e);
            best_d = cnt;            
            best_mask = s;
        }
    }

    cout << best_d << endl;
    for (int i = 0; i < V; i++) {
        if (best_mask & (1 << i)) {
            cout << (i + 1) << " ";
        }
    }
    cout << endl;

    return 0;
}
