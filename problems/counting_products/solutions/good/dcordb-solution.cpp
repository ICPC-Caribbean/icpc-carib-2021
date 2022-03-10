#include <iostream>

using namespace std;

using int64 = long long;

void DBG() { cerr << "]" << '\n'; }
template <class H, class... T>
void DBG(H h, T... t)
{
    cerr << h;
    if (sizeof...(t))
        cerr << ", ";
    DBG(t...);
}

#ifdef LOCAL // compile with -DLOCAL
#define dbg(...) cerr << "LINE(" << __LINE__ << ") -> [" << #__VA_ARGS__ << "]: [", DBG(__VA_ARGS__)
#else
#define dbg(...) 0
#endif

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);

    int n, k;
    cin >> n >> k;

    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        int x = i;
        int s = 0;
        for (int j = 2; j * j <= x; j++)
        {
            if (x % j == 0)
            {
                while (x % j == 0)
                {
                    x /= j;
                    s += j;
                }
            }
        }

        if (x > 1)
            s += x;

        if (s <= k)
            ans++;
    }

    cout << ans << "\n";
    return 0;
}
