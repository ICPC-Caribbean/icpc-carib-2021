#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl '\n'

typedef pair<int, int> pii;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m, c, q;
    cin >> n >> m >> c >> q;

    vector<pii> coins(c), games(q);
    vector<string> ans(q);

    for (int i = 0; i < c; i++)
    {
        int x, y;
        cin >> x >> y;
        coins[i] = {y, x};
    }

    for (int i = 0; i < q; i++)
    {
        int r;
        cin >> r;
        games[i] = {r, i};
    }

    sort(coins.begin(), coins.end());
    sort(games.begin(), games.end());
    int xor_sum = 0, coin_idx = 0;
    for (auto game : games)
    {
        int col = game.first;
        int idx = game.second;
        while (coin_idx < c && coins[coin_idx].first <= col)
        {
            xor_sum ^= coins[coin_idx].first - 1;
            coin_idx++;
        }
        ans[idx] = (xor_sum ? "Alice" : "Bob");
    }

    for (int i = 0; i < q; i++)
        cout << ans[i] << endl;

    return 0;
}
