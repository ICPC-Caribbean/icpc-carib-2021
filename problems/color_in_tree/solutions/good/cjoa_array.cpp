#include <iostream>
#include <vector>
#include <valarray>
#include <array>

using namespace std;

#ifdef LOCAL_DEBUG
#include <local_debug.h>
#define DEBUG(...) DBG2::cprint(#__VA_ARGS__, __LINE__, __VA_ARGS__)
#else
#define DEBUG(...)
#endif

using VI = vector<int>;
using VVI = vector<VI>;

const int NUM_COLORS = 64;

struct SegmentTreeNode {
   array<int, NUM_COLORS> freq;
   int delay_shift;   // delta for cumulative sum
   SegmentTreeNode() : freq({0}), delay_shift(0) { }
   SegmentTreeNode(int _color) : freq({0}), delay_shift(0) { freq[_color]++; }

   SegmentTreeNode operator+(const SegmentTreeNode& R) const {
      SegmentTreeNode res;
      for (int c = 0; c < NUM_COLORS; ++c)
         res.freq[c] = this->freq[c] + R.freq[c];
      return res;
   }
   void update(int L, int R, int d) {
      delay_shift = (delay_shift + d) % NUM_COLORS;
      array<int, NUM_COLORS> new_freq;
      for (int c = 0; c < NUM_COLORS; ++c)
         new_freq[(c + d) % NUM_COLORS] = freq[c];
      freq = new_freq;
   }
   void propagate(SegmentTreeNode& pL, SegmentTreeNode& pR, int L, int R) {
      if (delay_shift) {
         pL.update(L, (L+R)/2, delay_shift);
         pR.update((L+R)/2+1, R, delay_shift);
         delay_shift  = 0;
      }
   }
};

struct SegmentTree {
   int N;
   vector<SegmentTreeNode> tree;

   void _build(const vector<int>& A, int node, int L, int R) {
      if (L == R) {
         tree[node] = SegmentTreeNode(A[L]);
         return;
      }
      _build(A, 2*node, L, (L+R)/2);
      _build(A, 2*node+1, (L+R)/2+1, R);
      tree[node] = tree[2*node] + tree[2*node+1];
   }
   void _increment(int p, int q, int node, int L, int R) {
      if (q < L || p > R) return;
      if (p <= L && R <= q) {
         tree[node].update(L, R, 1);
         return;
      }
      tree[node].propagate(tree[2*node], tree[2*node+1], L, R);
      _increment(p, q, 2*node, L, (L+R)/2);
      _increment(p, q, 2*node+1, (L+R)/2+1, R);
      tree[node] = tree[2*node] + tree[2*node+1];
   }
   int _query(int p, int q, int c, int node, int L, int R) {
      if (q < L || p > R) return 0;
      if (p <= L && R <= q) return tree[node].freq[c];
      tree[node].propagate(tree[2*node], tree[2*node+1], L, R);
      int resL = _query(p, q, c, 2*node, L, (L+R)/2);
      int resR = _query(p, q, c, 2*node+1, (L+R)/2+1, R);
      return resL + resR;
   }
public:
   SegmentTree(const vector<int>& A) {
      N = A.size();
      int NUM_NODES = 4*N+1;
      tree = vector<SegmentTreeNode>(NUM_NODES);
      _build(A, 1, 0, N-1);
   }
   void increment(int p, int q) {
      _increment(p, q, 1, 0, N-1);
   }
   int query(int p, int q, int c) {
      return _query(p, q, c, 1, 0, N-1);
   }
};

VI dfs_order, dfs_start, dfs_end;
void dfs(const VVI& tree, int u, int p = -1) {
   dfs_start[u] = dfs_order.size();
   dfs_order.push_back(u);
   for (int v : tree[u]) {
      if (v == p) continue;
      dfs(tree, v, u);
   }
   dfs_end[u] = dfs_order.size();
}

int main() {
   ios_base::sync_with_stdio(false); 
   cin.tie(nullptr);

   int N, Q;
   cin >> N >> Q;
   vector<int> C(N);
   for (int i = 0; i < N; ++i)
      cin >> C[i];
   VVI tree(N);
   for (int j = 1; j < N; ++j) {
      int u, v;
      cin >> u >> v;
      --u, --v;
      tree[u].push_back(v);
      tree[v].push_back(u);
   }

   dfs_order.clear();
   dfs_start.assign(N, 0);
   dfs_end.assign(N, 0);
   dfs(tree, 0);

// DEBUG(dfs_order);

// for (int u = 0; u < N; ++u)
//    cerr << u << ": " << dfs_start[u] << ' ' << dfs_end[u] << endl;

   VI A(N);
   for (int t = 0; t < N; ++t) {
      int u = dfs_order[t];
      A[t] = C[u];
   }
   
// DEBUG(A);

   SegmentTree st(A);

   for (int q = 0; q < Q; ++q) {
      int op, v;
      cin >> op >> v;
      --v;
      if (op == 1) {
         st.increment(dfs_start[v], dfs_end[v]-1);
      }
      else {
         int c;
         cin >> c;
         int res = st.query(dfs_start[v], dfs_end[v]-1, c);
         cout << res << '\n';
      }
   }

   return 0;
}