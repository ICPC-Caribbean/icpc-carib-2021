#include <iostream>

typedef long long ll;
using namespace std;

inline ll eval(ll x, ll p, ll k) {
    return ((x & 1) ? -x : x) * p + k;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        ll p, k, m;
        cin >> p >> k >> m;

        if (eval(1, p, k) >= m) {
            cout << 1 << "\n";
            continue;
        }

        ll x = 2;

        while (eval(x, p, k) < m) {
            x += 2;
        }

        cout << x << "\n";

    }

}
