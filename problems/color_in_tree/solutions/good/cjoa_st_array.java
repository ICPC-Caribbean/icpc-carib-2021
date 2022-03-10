import java.io.*;
import java.util.*;

class SegmentTree {
   static final int NUM_COLORS = 64;

   private int N;
   int[][] freq;
   int[] delay;

   int[] tmp_freq = new int[NUM_COLORS];

   void update(int x, int d) {
      delay[x] = (delay[x] + d) % NUM_COLORS;
      System.arraycopy(freq[x], 0, tmp_freq, 0, NUM_COLORS);
      for (int c = 0; c < NUM_COLORS; ++c)
         freq[x][(c + d) % NUM_COLORS] = tmp_freq[c];
   }

   void propagate(int x) {
      if (delay[x] != 0) {
         update(2*x    , delay[x]);
         update(2*x + 1, delay[x]);
         delay[x]  = 0;
      }
   }

   void join(int x, int pL, int pR) {
      for (int c = 0; c < NUM_COLORS; ++c)
         freq[x][c] = freq[pL][c] + freq[pR][c];
   }

   private void build(int[] A, int node, int L, int R) {
      if (L == R) {
         freq[node][A[L]]++;
         return;
      }
      build(A, 2*node, L, (L+R)/2);
      build(A, 2*node+1, (L+R)/2+1, R);
      join(node, 2*node, 2*node+1);
   }

   void increment(int p, int q, int node, int L, int R) {
      if (q < L || p > R) return;
      if (p <= L && R <= q) {
         update(node, 1);
         return;
      }
      propagate(node);
      increment(p, q, 2*node, L, (L+R)/2);
      increment(p, q, 2*node+1, (L+R)/2+1, R);
      join(node, 2*node, 2*node+1);
   }
   
   private int query(int p, int q, int c, int node, int L, int R) {
      if (q < L || p > R) return 0;
      if (p <= L && R <= q) return freq[node][c];
      propagate(node);
      int resL = query(p, q, c, 2*node, L, (L+R)/2);
      int resR = query(p, q, c, 2*node+1, (L+R)/2+1, R);
      return resL + resR;
   }
   
   SegmentTree(int[] A) {
      N = A.length;
      freq = new int[4 * N][NUM_COLORS];
      delay = new int[4 * N];
      build(A, 1, 0, N-1);
   }

   void increment(int p, int q) {
      increment(p, q, 1, 0, N-1);
   }

   int query(int p, int q, int c) {
      return query(p, q, c, 1, 0, N-1);
   }
}

public class cjoa_st_array implements Runnable
{
   public static void main (String[] args) throws IOException {
   // (new cjoa_st_array()).run();
      new Thread(null, new cjoa_st_array(), "", 1l * 50 * 1024 * 1024).start();
   }
   
   BufferedReader in;
   PrintWriter out;
   StringTokenizer st = new StringTokenizer("");

   public void run() {
      try {
         try {
            in = new BufferedReader(new FileReader("input.txt"));
            out = new PrintWriter("output.txt");
         } catch (Exception e) {
            in = new BufferedReader(new InputStreamReader(System.in));
            out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
         }

         solve();
         out.close();
      } catch (IOException ex) {
      }
   }

   List<Integer>[] tree;

   int dfs_time;
   int[] dfs_start, dfs_end;
   void dfs(int u, int p) {
      ++dfs_time;
      dfs_start[u] = dfs_time;
      for (int v : tree[u]) {
         if (v != p)
            dfs(v, u);
      }
      dfs_end[u] = dfs_time;
   }

   void solve() throws IOException {
      int N = nextInt();
      int Q = nextInt();
      int[] C = new int[N];
      for (int i = 0; i < N; ++i)
         C[i] = nextInt();
      tree = new ArrayList[N];
      for (int u = 0; u < N; ++u)
         tree[u] = new ArrayList<Integer>();
      for (int j = 1; j < N; ++j) {
         int u = nextInt() - 1;
         int v = nextInt() - 1;
         tree[u].add(v);
         tree[v].add(u);
      }

      dfs_time  = -1;
      dfs_start = new int[N];
      dfs_end   = new int[N];
      dfs(0, -1);
      
      int[] A = new int[N];
      for (int u = 0; u < N; ++u) {
         int t = dfs_start[u];
         A[t] = C[u];
      }

      SegmentTree st = new SegmentTree(A);

      for (int q = 0; q < Q; ++q) {
         int op = nextInt();
         int v = nextInt() - 1;
         if (op == 1) {
            st.increment(dfs_start[v], dfs_end[v]);
         }
         else {
            int c = nextInt();
            out.println(st.query(dfs_start[v], dfs_end[v], c));
         }
      }
   }

   // get next token
   String next() throws IOException {
      while (!st.hasMoreTokens())
         st = new StringTokenizer(in.readLine());
      return st.nextToken();
   }

   // get next int
   int nextInt() throws IOException {
      return Integer.parseInt(next());
   }
}

