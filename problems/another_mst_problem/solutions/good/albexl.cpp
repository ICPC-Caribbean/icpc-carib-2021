#include <iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{

    int n;
    cin >> n;

    vector<long long> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    sort(a.begin(), a.end());
    cout << a[n - 1] - a[0] << '\n';
}
