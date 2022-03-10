#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <algorithm>
#include <cassert>

#define endl '\n'

using namespace std;

typedef long long ll;

ll get_best_with_2(int a, int b) {
    ll ret = 0;
    for (int i = 0; i < 30; i++) {
        if ( (a&(1<<i)) == (b&(1<<i)) )
            ret += 2ll * (1<<i);
        else 
            ret += 3ll * (1<<i);
    }
    return ret;
}

ll get_best_with_1(int a, int b) {
    ll ret = 0;
    for (int i = 0; i < 30; i++) {
        if ( (a&(1<<i)) == (b&(1<<i)) )
            ret += 2ll * (1<<i);
        else 
            ret += 1ll * (1<<i);
    }
    return ret;
}

int main() {
#ifdef ernestico
    freopen("a.in", "r", stdin);
#endif // ernestico
    // ios_base::sync_with_stdio(0); cin.tie(0);

    const int v = (1<<30) - 1;

    int n; cin >> n;
    vector<int> a(n);
    for (auto &i : a) cin >> i;

    if (n == 2) {
        cout << v << endl;
        return 0;
    }
    if (n == 3) {
        cout << 2ll * v << endl;
        return 0;
    }

    vector<ll> pref(n), suff(n);
    for (int i = 1; i < n; i++)
        pref[i] = pref[i-1] + 1ll * (a[i-1] ^ a[i]);
    for (int i = n-2; i >= 0; i--)
        suff[i] = suff[i+1] + 1ll * (a[i] ^ a[i+1]);

    assert(pref[n-1] == suff[0]);
    ll ans = pref[n-1]; // no change at all

    // change two adjacent elements
    // ans = max(suff[2], pref[n-3]) + 2ll * v; // both elements are the extreme ones
    // for (int i = 1; i < n-2; i++)
    //     ans = max(ans, pref[i-1] + suff[i+2] + get_best_with_2(a[i-1], a[i+2]));

    // change two non-adjacent elements
    vector<ll> dp(n); // dp[i] stores best prefix changing only one element up to i position but considering the next element when calculating prefix xor sums
    dp[0] = v;
    ans = max(ans, suff[1] + v); // change only first element
    for (int i = 1; i < n; i++) {
        dp[i] = pref[i-1];
        if (i < n-1)
            dp[i] += get_best_with_1(a[i-1], a[i+1]);
        else
            dp[i] += v;

        // change only element i
        ans = max(ans, dp[i] + ((i == n-1)? 0 : suff[i+1]));
        
        // change element i along with a previously changed j < i-1 element
        if (i > 1) 
            ans = max(ans, dp[i-2] + ((i == n-1)? v : get_best_with_1(a[i-1], a[i+1]) + suff[i+1]) );

        dp[i] = max(dp[i], dp[i-1] + ((i == n-1)? 0 : a[i] ^ a[i+1]));
    }

    cout << ans << endl;

    return 0;
}
