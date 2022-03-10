//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")
//#pragma GCC target("avx2")
#pragma GCC target("sse,sse2,sse3,sse4,sse4.1,sse4.2")

#include <iostream>

using namespace std;

#define MOD 1000000007
#define MAXN 200000

int N, K;
int A[MAXN];
int DP[MAXN];

int main() {
   ios_base::sync_with_stdio(false); 
   cin.tie(nullptr);

   cin >> N >> K;
   for (int i = 0; i < N; ++i)
      cin >> A[i];

   DP[0] = 1;
   for (int i = 0; i < N; ++i) {
      int dpi = DP[i];
      if (dpi == 0) continue;
      for (int j = i+1; j < N; ++j) {
         if ((A[i] ^ A[j]) < K) {
            DP[j] += dpi;
            if (DP[j] >= MOD)
               DP[j] -= MOD;
         }
      }
   }

   cout << DP[N-1] << '\n';
}
