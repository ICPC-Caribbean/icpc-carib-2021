//==================================================================================
// Contest     : ICPC Qualifier 2021
// Problem     : Problem Encoding Matrix
// Author      : Rubén Alcolea Núñez
// Description : Ad Hoc 1
//==================================================================================

#include <iostream>
using namespace std;

const int MAX = 1e2 + 5;

int n;
char star_ones[MAX * MAX];
char star_zeros[MAX * MAX];
char s[MAX];

int main()
{
    cin.sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    int zeros = 0, ones = 0;
    char firstBit = 'a';
    for (int i = 0; i < n; i++)
    {
        cin >> s;
        if (firstBit == 'a')
            firstBit = s[0];
        for (int j = 0; j < n; j++)
            if (s[j] == '0')
            {
                zeros++;
                star_zeros[n * i + j] = '*';
                star_ones[n * i + j] = 'o';
            }
            else if (s[j] == '1')
            {
                ones++;
                star_ones[n * i + j] = '*';
                star_zeros[n * i + j] = 'o';
            }
    }
    char *x = star_ones;
    if (zeros > ones || (zeros == ones && firstBit == '0'))
        x = star_zeros;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << x[n * i + j];
        }
        cout << "\n";
    }
    return 0;
}
