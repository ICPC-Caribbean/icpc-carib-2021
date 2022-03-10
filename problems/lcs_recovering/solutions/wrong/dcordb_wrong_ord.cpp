#include <cassert>
#include <iostream>
#include <vector>
#include <functional>
using namespace std;

using int64 = long long;

void DBG() { cerr << "]" << '\n'; }
template<class H, class... T> void DBG(H h, T... t) {
    cerr << h;
    if (sizeof...(t)) cerr << ", ";
    DBG(t...);
}

#ifdef LOCAL // compile with -DLOCAL
    #define dbg(...) cerr << "LINE(" << __LINE__ << ") -> [" << #__VA_ARGS__ << "]: [", DBG(__VA_ARGS__)
#else
    #define dbg(...) 0
#endif

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m; cin >> n >> m;

    vector <vector <int>> lcs(n + 1, vector <int> (m + 1));
    vector <vector <int>> g(n + m + 1);
    vector <pair <int, int>> dif;

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> lcs[i][j];

            if(lcs[i - 1][j - 1] != lcs[i][j - 1] || lcs[i - 1][j - 1] != lcs[i - 1][j])
                continue;

            if(lcs[i - 1][j - 1] + 1 == lcs[i][j])
            {
                g[i].push_back(j + n);
                g[j + n].push_back(i);
            }

            else {
                assert(lcs[i - 1][j - 1] == lcs[i][j]);
                dif.push_back({i, j + n});
            }
        }
    }

    vector <int> cc(n + m + 1, -1);
    vector <vector <int>> who(n + m + 1);
    int k = 0;

    function <void(int)> dfs = [&] (int u) {
        cc[u] = k;
        who[k].push_back(u);

        for(int v : g[u])
            if(cc[v] == -1)
                dfs(v);
    };

    for(int i = 1; i <= n + m; i++) {
        if(cc[i] == -1) {
            k++;
            dfs(i);
        }
    }

    vector <vector <int>> gn(k + 1);

    for(auto o : dif) {
        int x = o.first;
        int y = o.second;

        if(cc[x] != cc[y]) {
            gn[cc[x]].push_back(cc[y]);
            gn[cc[y]].push_back(cc[x]);
        }
    }

    vector <int> c(k + 1, -1);

    function <void(int, int)> bip = [&] (int u, int col) {
        c[u] = col;

        for(int v : gn[u]) {
            if(c[v] == -1)
                bip(v, col ^ 1);

            else assert(c[u] != c[v]);
        }
    };

    for(int i = 1; i <= k; i++)
        if(c[i] == -1)
            bip(i, 1);

    vector <int> ans(n + m + 1);
    for(int i = 1; i <= k; i++)
        for(int u : who[i])
            ans[u] = c[i];

    for(int i = 1; i <= n; i++)
        cout << ans[i];
    cout << "\n";

    for(int i = n + 1; i <= n + m; i++)
        cout << ans[i];
    cout << "\n";

    return 0;
}

