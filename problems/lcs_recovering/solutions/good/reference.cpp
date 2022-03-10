#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <cassert>

using namespace std;

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n, m;
	cin >> n >> m;
	vector<vector<int>> M(n, vector<int>(m));
	for (auto &i : M)
		for (auto &j : i)
			cin >> j;

	M.insert(M.begin(), vector<int>(m));
	for (auto &i : M)
		i.insert(i.begin(), 0);

	vector<vector<int>> eq(n + m), dif(n + m);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
		{
			int e = M[i - 1][j - 1] + 1;
			int r = max(M[i - 1][j], M[i][j - 1]);
			if (e == M[i][j] && e > r)
				eq[i - 1].push_back(n + j - 1), eq[n + j - 1].push_back(i - 1);
			if (e > M[i][j])
				dif[i - 1].push_back(n + j - 1), dif[n + j - 1].push_back(i - 1);
		}

	int id = -1;
	vector<int> comp(n + m, -1);
	for (int i = 0; i < n + m; ++i)
		if (comp[i] == -1)
		{
			queue<int> q;
			q.push(i);
			comp[i] = ++id;
			while (!q.empty())
			{
				int u = q.front();
				q.pop();
				for (auto v : eq[u])
					if (comp[v] == -1)
					{
						comp[v] = id;
						q.push(v);
					}
			}
		}

	vector<vector<int>> adj(id + 1);
	for (int u = 0; u < n + m; ++u)
		for (auto v : dif[u])
			if (comp[u] != comp[v])
			{
				adj[comp[u]].push_back(comp[v]);
				adj[comp[v]].push_back(comp[u]);
			}

	vector<int> color(id + 1, -1);
	function<bool(int, int)> dfs = [&](int u, int c)
	{
		color[u] = c;
		for (auto v : adj[u])
			if ((color[v] == -1 && !dfs(v, !c)) || color[v] == c)
				return false;
		return true;
	};

	for (int u = 0; u < n + m; ++u)
		if (color[comp[u]] == -1 && !dfs(comp[u], 0))
		{
			assert(false);
			cout << "-1\n";
			return 0;
		}

	for (int u = 0; u < n + m; ++u)
	{
		cout << color[comp[u]];
		if (u == n - 1 || u == n + m - 1)
			cout << "\n";
	}

	return 0;
}
