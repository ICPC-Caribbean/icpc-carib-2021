#include "../../.box/testlib.h"
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

int main(int argc, char *argv[])
{
	registerGen(argc, argv, 1);

	/* Read number from command line. */
	int n = atoi(argv[2]);
	int m = atoi(argv[3]);
	if (n == -1)
		n = rnd.next(1, 2000);
	if (m == -1)
		m = rnd.next(1, 2000);
	vector<int> t = {n, m};
	println(t);
	/* String of random binary string */
	string a = rnd.next(format("[0-1]{%d,%d}", n, n));
	string b = rnd.next(format("[0-1]{%d,%d}", m, m));

	auto x = LCS(a, b);
	for (auto i : x)
		println(i);
}
