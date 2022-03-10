#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<double> point;
#define F first
#define S second

struct union_find
{
   vector<int> p;

   union_find(int n) : p(n, -1) {}

   bool join(int u, int v)
   {
      if ((u = root(u)) == (v = root(v)))
         return false;
      if (p[u] > p[v])
         swap(u, v);
      p[u] += p[v];
      p[v] = u;
      return true;
   }

   int root(int u)
   {
      return p[u] < 0 ? u : p[u] = root(p[u]);
   }
};

struct edge
{
   ll u, v, w;
};

int main()
{
#ifdef DGC
   // freopen("a.txt", "r", stdin);
   // freopen("b.txt", "w", stdout);
#endif

   ios_base::sync_with_stdio(0), cin.tie(0);

   int n;
   cin >> n;
   vector<ll> a(n);
   for (auto &i : a)
      cin >> i;

   vector<edge> e;
   for (int i = 0; i < n; ++i)
      for (int j = i + 1; j < n; ++j)
         e.push_back({i, j, abs(a[i] - a[j])});

   sort(e.begin(), e.end(), [](const edge &a, const edge &b)
       { return a.w < b.w; });

   ll ans = 0;
   union_find uf(n);

   for (auto i : e)
      if (uf.join(i.u, i.v))
         ans += i.w;

   cout << ans << "\n";

   return 0;
}
