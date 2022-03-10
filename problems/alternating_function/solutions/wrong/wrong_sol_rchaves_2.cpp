#include <iostream>

typedef long long ll;
using namespace std;

ll floorDiv(ll x, ll y) {
    ll d = x / y;
    ll r = x % y;
    return r ? (d - ((x < 0) ^ (y < 0))) : d;
}

ll ceilDiv(ll x, ll y) {
    return -floorDiv(-x, y);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        ll p, k, m;
        cin >> p >> k >> m;

        ll firstImage = -p + k;

        if (firstImage >= m) {
            cout << 1 << "\n";
            continue;
        }

        ll requiredS = ceilDiv(m-k,2*p);

        cout << (2*requiredS) << "\n";
    }

}
