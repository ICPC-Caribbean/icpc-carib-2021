#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

using llong = long long;
using VI = vector<int>;
using VVI = vector<VI>;

#define BITCOUNT(mask) ( __builtin_popcount((mask)) )

int R, C;
VVI A;
int min_changes;
VVI resA;
void go(int r = 0, int c = 0,
        bool row_parity = false, llong col_parity = 0,
        int nchanges = 0) {
   if (r == R-1) {
      // last row is fixed
      row_parity = 0;
      VI last_row = A.back();
      for (int c = 0; c < C; ++c) {
         int p = A[r][c] & 1;
         if (((col_parity >> c) & 1) ^ p) {
            ++nchanges;
            A[r][c]++;
            row_parity ^= (p ^ 1);
         }
         else {
            row_parity ^= p;
         }
      }
      if (row_parity == 0) {
         if (min_changes > nchanges) {
            min_changes = nchanges;
            resA = A;
         }
      }
      // restore last row
      copy(last_row.begin(), last_row.end(), A.back().begin());
      return;
   }
   if (c >= C) {
      if (row_parity == 0)
         go(r+1, 0, 0, col_parity, nchanges);
      return;
   }

   llong p = A[r][c] & 1;

   // do not change
   go(r, c+1, row_parity ^ p, col_parity ^ (p << c), nchanges);

   // change
   A[r][c]++;
   p ^= 1;
   go(r, c+1, row_parity ^ p, col_parity ^ (p << c), nchanges + 1);
   A[r][c]--;

}


int main(int argc, char* argv[]) {
   ios_base::sync_with_stdio(false); 
   cin.tie(nullptr);

   cin >> R >> C;

   A = VVI(R, VI(C));
   for (int r = 0; r < R; ++r) {
      for (int c = 0; c < C; ++c)
         cin >> A[r][c];
   }

   min_changes = 1000000000;
   go();

   cerr << min_changes << endl;
   assert( !resA.empty() );
   for (int r = 0; r < R; ++r) {
      for (int c = 0; c < C; ++c)
         cout << resA[r][c] << ' ';
      cout << '\n';
   }

   return 0;
}
