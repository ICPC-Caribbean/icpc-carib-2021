import java.io.*;
import java.util.*;

public class cjoa_gr
{
   public static void main (String[] args) throws IOException {
      (new cjoa_gr()).run();
   }
   
   BufferedReader in;
   PrintWriter out;
   StringTokenizer st = new StringTokenizer("");

   void run() throws IOException {
      try {
         in = new BufferedReader(new FileReader("input.txt"));
         out = new PrintWriter("output.txt");
      } catch (Exception e) {
         in = new BufferedReader(new InputStreamReader(System.in));
         out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
      }

      solve();

      out.close();
   }

   int N, M;
   int[][] DP;
   boolean checkRow(int i, char c, char[] B) {
      for (int j = 1; j < B.length; ++j) {
         boolean canBeEq  = DP[i][j] == DP[i-1][j-1] + 1;
         boolean canBeDif = DP[i][j] == DP[i-1][j] || DP[i][j] == DP[i][j-1];
         if (B[j] == '\0') {
            if (!canBeDif && !canBeEq)
               return false;  // A[i] is inconsistent
            if (canBeDif && canBeEq)
               continue;     // leave B[j] as '?'
            if (canBeEq)
               B[j] = c;
            else
               B[j] = c == '0' ? '1' : '0';
         }
         else if (c == B[j]) {
            if (!canBeEq)
               return false;
         }
         else {
            if (!canBeDif)
               return false;
         }
      }
      return true;
   }

   void solve() throws IOException {
      N = nextInt();
      M = nextInt();
      DP = new int[N+1][M+1];
      for (int i = 1; i <= N; ++i)
         for (int j = 1; j <= M; ++j)
            DP[i][j] = nextInt();

      char[] A = new char[N + 1];
      char[] B = new char[M + 1];

      for (int i = 1; i <= N; ++i) {
         // try to set A[i] to '0'
         A[i] = '0';
         char[] newB = B.clone();
         if (checkRow(i, A[i], newB)) {
            B = newB;
            continue;
         }

         // else set to '1'
         A[i] = '1';
         newB = B.clone();
         if (checkRow(i, A[i], newB)) {
            B = newB;
            continue;
         }

         assert(false);
      }

      out.println( String.valueOf(A, 1, N) );
      for (int j = 1; j <= M; ++j)
         if (B[j] == '\0')
            B[j] = '0';
      out.println( String.valueOf(B, 1, M) );
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

