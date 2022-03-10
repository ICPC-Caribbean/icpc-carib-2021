#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <cassert>

using namespace std;

using VI = vector<int>;
using VVI = vector<VI>;

int main() {
   int R, C;
   cin >> R >> C;

   VVI A(R, VI(C));
   for (int r = 0; r < R; ++r) {
      for (int c = 0; c < C; ++c)
         cin >> A[r][c];
   }

   VI row_parity(R);
   VI col_parity(C);
   for (int r = 0; r < R; ++r) {
      for (int c = 0; c < C; ++c) {
         int b = A[r][c] & 1;
         row_parity[r] ^= b;
         col_parity[c] ^= b;
      }
   }

// int nchanges = max(count(row_parity.begin(), row_parity.end(), 1),
//                    count(col_parity.begin(), col_parity.end(), 1));
   int nchanges = 0;

   queue<int> Q;
   for (int r = 0; r < R; ++r)
      if (row_parity[r])
         Q.push(r);

   stack<int> S;
   for (int c = 0; c < C; ++c)
      if (col_parity[c])
         S.push(c);

   while (not Q.empty() and not S.empty()) {
      int r = Q.front(); Q.pop();
      int c = S.top(); S.pop();
      ++A[r][c];
      ++nchanges;
   }

   assert(Q.size() % 2 == 0);
   assert(S.size() % 2 == 0);

   while (not S.empty()) {
      int c = S.top(); S.pop();
      ++A[R-1][c];
      ++nchanges;
   }

   while (not Q.empty()) {
      int r = Q.front(); Q.pop();
      ++A[r][C-1];
      ++nchanges;
   }

// cerr << nchanges << endl;

   for (const VI& row : A) {
      for (int c = 0; c < C; ++c) {
         if (c > 0)
            cout << ' ';
         cout << row[c];
      }
      cout << '\n';
   }

   return 0;
}