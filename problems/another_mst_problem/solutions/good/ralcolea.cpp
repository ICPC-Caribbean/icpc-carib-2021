//==================================================================================
// Contest     : ICPC Qualifier 2021
// Problem     : Joining cities
// Author      : Rubén Alcolea Núñez
// Description : AH1: Easy
//==================================================================================
#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MAX = 1e5 + 5;
ll a[MAX], n;

int main()
{
    cin.sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    sort(a, a + n);
    ll total = 0LL;
    for (int i = n-1; i > 0; i--)
        total += (a[i] - a[i-1]);
    cout << total << "\n";
    return 0;
}

