#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> LCS(string a, string b)
{
	int n = a.length();
	int m = b.length();
	vector<vector<int>> dp(n + 1, vector<int>(m + 1));
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
		{
			if (a[i - 1] == b[j - 1])
				dp[i][j] = dp[i - 1][j - 1] + 1;
			else
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		}
	dp.erase(dp.begin());
	for (auto &i : dp)
		i.erase(i.begin());
	return dp;
}

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n, m;
	cin >> n >> m;
	vector<vector<int>> M(n, vector<int>(m));
	for (auto &i : M)
		for (auto &j : i)
			cin >> j;

	string ans = string(n + m, '1');
	if (n > 30)
		while (1)
			;
	for (int i = 0; i < 1 << n; ++i)
	{
		string a = "";
		for (int k = 0; k < n; ++k)
			a += '0' + (i >> k & 1);

		for (int j = 0; j < 1 << m; ++j)
		{
			string b = "";
			for (int k = 0; k < m; ++k)
				b += '0' + (j >> k & 1);

			if (LCS(a, b) == M)
				ans = min(ans, a + b);
		}
	}

	ans.insert(ans.begin() + n, '\n');
	cout << ans << "\n";

	return 0;
}
