#include "../../.box/testlib.h"
#include <vector>
#include <queue>
#include <functional>

using namespace std;

char const msg[] = "Not exists two binary strings for the given matrix.";

void LCS(string a, string b, vector<vector<int>> M)
{
   int n = a.length();
   int m = b.length();
   vector<vector<int>> dp(n + 1, vector<int>(m + 1));
   for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j)
      {
         if (a[i - 1] == b[j - 1])
            dp[i][j] = dp[i - 1][j - 1] + 1;
         else
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
      }
   // dp.erase(dp.begin());
   // for (auto &i : dp) i.erase(i.begin());
   ensuref(dp == M, msg);
}

void check(int n, int m, vector<vector<int>> M)
{
   M.insert(M.begin(), vector<int>(m));
   for (auto &i : M)
      i.insert(i.begin(), 0);

   vector<vector<int>> eq(n + m), dif(n + m);
   for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j)
      {
         int e = M[i - 1][j - 1] + 1;
         int r = max(M[i - 1][j], M[i][j - 1]);

         ensuref(r == M[i][j] || e == M[i][j], msg);

         if (e == M[i][j] && e > r)
            eq[i - 1].push_back(n + j - 1), eq[n + j - 1].push_back(i - 1);
         if (e > M[i][j])
            dif[i - 1].push_back(n + j - 1), dif[n + j - 1].push_back(i - 1);
      }

   int id = -1;
   vector<int> comp(n + m, -1);
   for (int i = 0; i < n + m; ++i)
      if (comp[i] == -1)
      {
         queue<int> q;
         q.push(i);
         comp[i] = ++id;
         while (!q.empty())
         {
            int u = q.front();
            q.pop();
            for (auto v : eq[u])
               if (comp[v] == -1)
               {
                  comp[v] = id;
                  q.push(v);
               }
         }
      }

   vector<vector<int>> adj(id + 1);
   for (int u = 0; u < n + m; ++u)
      for (auto v : dif[u])
         if (comp[u] != comp[v])
         {
            adj[comp[u]].push_back(comp[v]);
            adj[comp[v]].push_back(comp[u]);
         }

   vector<int> color(id + 1, -1);
   function<bool(int, int)> dfs = [&](int u, int c)
   {
      color[u] = c;
      for (auto v : adj[u])
         if ((color[v] == -1 && !dfs(v, !c)) || color[v] == c)
            return false;
      return true;
   };

   for (int u = 0; u < n + m; ++u)
      if (color[comp[u]] == -1)
         ensuref(dfs(comp[u], 0), msg);

   vector<string> ans(2, "");
   for (int u = 0; u < n + m; ++u)
      ans[u >= n] += '0' + color[comp[u]];

   LCS(ans[0], ans[1], M);
}

const int N = 2000;

int main(int argc, char *argv[])
{
   registerValidation(argc, argv);

   int n = inf.readInt(1, N, "n");
   inf.readSpace();
   int m = inf.readInt(1, N, "m");
   inf.readEoln();

   vector<vector<int>> a(n, vector<int>(m));
   for (int i = 1; i <= n; ++i)
   {
      for (int j = 1; j <= m; ++j)
      {
         a[i - 1][j - 1] = inf.readInt(0, N, format("M[%d, %d]", i, j));
         if (j < m)
            inf.readSpace();
      }
      if (i < n)
         inf.readEoln();
   }

   check(n, m, a);

   inf.readEoln();
   inf.readEof();

   return 0;
}
