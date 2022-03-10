#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
//#include <queue>
//#include <numeric>
#include <cassert>

using namespace std;

#ifdef LOCAL_DEBUG
#include <local_debug.h>
#define DEBUG(...) DBG2::cprint(#__VA_ARGS__, __LINE__, __VA_ARGS__)
#else
#define DEBUG(...)
#endif

#define SZ(a) int((a).size())
#define REP(i,n) for(int i=0,_n=(n);i<_n;++i)
#define FOR(i,a,b) for(int i=(a),_b=(b);i<=_b;++i)

using llong = long long;
using VI = vector<int>;
using VVI = vector<VI>;
using II = pair<int,int>;


int N, M;
VVI DP;
string A, B;


bool go_col(int i, string& B) {
   FOR(j, 1, M) {
      bool can_be_eq  = DP[i][j] == DP[i-1][j-1] + 1;
      bool can_be_dif = DP[i][j] == DP[i-1][j] or DP[i][j] == DP[i][j-1];
      if (B[j] == '?') {
         if (!can_be_dif and !can_be_eq)
            return false;
         if (can_be_dif and can_be_eq)
            continue;
         if (can_be_eq)
            B[j] = A[i];
         else
            B[j] = A[i] == '0' ? '1' : '0';
      }
      else if (A[i] == B[j]) {
         if (!can_be_eq)
            return false;
      }
      else {
         if (!can_be_dif)
            return false;
      }
   }
   return true;
}


void go_row(int i, string B) {
   if (i > N) {
      cout << A.substr(1) << '\n';
      transform(B.begin()+1, B.end(), B.begin()+1,
                [](unsigned char c) -> unsigned char { return c == '?' ? '0' : c; });
      cout << B.substr(1) << '\n';
      exit(0);
   }

   // try to set A[i] to 0
   A[i] = '0';
   string newB = B;
   if (go_col(i, newB)) {
      go_row(i + 1, newB);
   }
   
   // otherwise try to set to 1
   A[i] = '1';
   newB = B;
   if (go_col(i, newB)) {
      go_row(i + 1, newB);
   }

   // if both failed, recursively backtrack
}

int main(int argc, char* argv[]) {
   ios_base::sync_with_stdio(false); 
   cin.tie(nullptr);

   cin >> N >> M;

   DP = VVI(N + 1, VI(M + 1));
   FOR(i, 1, N)
      FOR(j, 1, M)
         cin >> DP[i][j];

   A = string(N + 1, '?');
   B = string(M + 1, '?');

   go_row(1, B);

   assert(false);

   return 0;
}
