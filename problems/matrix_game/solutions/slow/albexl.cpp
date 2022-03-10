#include <iostream>
#include <vector>

using namespace std;

#define endl '\n'

typedef pair<int, int> pii;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m, c, q;
    cin >> n >> m >> c >> q;

    vector<pii> coins(c);

    for (int i = 0; i < c; i++)
    {
        int x, y;
        cin >> x >> y;
        coins[i] = {x, y};
    }

    for (int i = 0; i < q; i++)
    {
        int r;
        cin >> r;

        int xor_sum = 0;

        for (auto coin : coins)
            if (coin.second <= r)
                xor_sum ^= coin.second - 1;

        cout << (xor_sum ? "Alice" : "Bob") << endl;
    }

    return 0;
}
