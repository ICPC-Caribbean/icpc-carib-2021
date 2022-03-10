#include <iostream>
#include <vector>

using namespace std;

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	int test;
	cin >> test;
	while (test--)
	{
		int n, a, b;
		cin >> n >> a >> b;

		if (a + b > n)
		{
			cout << "No\n";
			continue;
		}

		vector<vector<int>> men(n), women(n);
		vector<vector<bool>> mark(n, vector<bool>(n));
		int w = 0;
		for (int i = 0; i < n; ++i)
			for (int it = a; it--;)
			{
				men[i].push_back(w % n);
				mark[i][w % n] = true;
				++w;
			}
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n && (int)women[i].size() < b; ++j)
				if (!mark[j][i])
					women[i].push_back(j);

		cout << "Yes\n";
		for (auto &i : men)
			for (auto &j : i)
				cout << j + 1 << " \n"[&j == &i.back()];
		for (auto &i : women)
			for (auto &j : i)
				cout << j + 1 << " \n"[&j == &i.back()];
	}

	return 0;
}
