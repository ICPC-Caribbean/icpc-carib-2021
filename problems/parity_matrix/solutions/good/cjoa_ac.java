import java.io.*;
import java.util.*;

public class cjoa_ac // implements Runnable
{
   public static void main (String[] args) throws IOException {
      (new cjoa_ac()).run();
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

   void solve() throws IOException {
      int R = nextInt();
      int C = nextInt();
      int [][] A = new int[R][C];
      for (int i = 0; i < R; ++i) {
         for (int j = 0; j < C; ++j)
            A[i][j] = nextInt();
      }
      int[] rowParity = new int[R];
      for (int i = 0; i < R; ++i) {
         for (int j = 0; j < C; ++j)
            rowParity[i] ^= A[i][j] & 1;
      }
      int[] colParity = new int[C];
      for (int i = 0; i < R; ++i) {
         for (int j = 0; j < C; ++j)
            colParity[j] ^= A[i][j] & 1;
      }

      ArrayList<Integer> oddRows = new ArrayList<Integer>();
      for (int i = 0; i < R; ++i)
         if (rowParity[i] != 0)
            oddRows.add(i);
      ArrayList<Integer> oddCols = new ArrayList<Integer>();
      for (int j = 0; j < C; ++j)
         if (colParity[j] != 0)
            oddCols.add(j);
      int k = 0;
      for (; k < oddRows.size() || k < oddCols.size(); ++k) {
         int i = k < oddRows.size() ? oddRows.get(k) : 0;
         int j = k < oddCols.size() ? oddCols.get(k) : 0;
         A[i][j]++;
      }
      for (int i = 0; i < R; ++i) {
         for (int j = 0; j < C; ++j)
            out.print(A[i][j] + " ");
         out.println();
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

