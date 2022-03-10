#include <iostream>

using namespace std;

int floorDiv(int x, int y) {
    int d = x / y;
    int r = x % y;
    return r ? (d - ((x < 0) ^ (y < 0))) : d;
}

int ceilDiv(int x, int y) {
    return -floorDiv(-x, y);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int p, k, m;
        cin >> p >> k >> m;

        int firstImage = -p + k;

        if (firstImage >= m) {
            cout << 1 << "\n";
            continue;
        }

        int requiredS = ceilDiv(m-k,2*p);

        cout << max(2, 2*requiredS) << "\n";
    }

}
