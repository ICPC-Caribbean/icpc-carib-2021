/*O(n^2) brute force*/
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
    ans = max(suff[2], pref[n-3]) + 2ll * v; // both elements are the extreme ones
    for (int i = 1; i < n-2; i++)
        ans = max(ans, pref[i-1] + suff[i+2] + get_best_with_2(a[i-1], a[i+2]));


    for (int i = 0; i < n; i++) {
        // change only element i
        ll tmp = pref[n-1];
        if (i > 0)
            tmp -= (a[i] ^ a[i-1]);
        if (i < n-1)
            tmp -= (a[i] ^ a[i+1]);
        
        if (i > 0 && i < n-1)
            tmp += get_best_with_1(a[i-1], a[i+1]);
        else
            tmp += v;
        
        ans = max(ans, tmp);
        
        for (int j = i + 2; j < n; j++) {
            ll tmp1 = tmp;
            tmp1 -= (a[j] ^ a[j-1]);
            if (j < n-1) {
                tmp1 -= (a[j] ^ a[j+1]);
                tmp1 += get_best_with_1(a[j-1], a[j+1]);
            } else 
                tmp1 += v;
            ans = max(ans, tmp1);
        }
    }

    cout << ans << endl;

    return 0;
}
