#include <iostream>
#include <vector>

using namespace std;

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n, k;
	cin >> n >> k;
	vector<int> a(n);
	for (auto &i : a)
		cin >> i;

	vector<long long> dp(n);
	dp[0] = 1;

	const long long mod = 1e9 + 7;
	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j)
			if ((a[i] ^ a[j]) < k)
			{
				dp[j] += dp[i];
				dp[j] %= mod;
			}

	cout << dp[n - 1] << "\n";

	return 0;
}
