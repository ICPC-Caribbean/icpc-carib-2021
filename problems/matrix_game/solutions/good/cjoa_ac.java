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
      int R = nextInt(), C = nextInt(), K = nextInt(), Q = nextInt();
      int[] freq = new int[C + 1];
      for (int k = 0; k < K; ++k) {
         int i = nextInt(), j = nextInt();
         ++freq[j];
      }
      int[] xor = new int[C+1];
      for (int j = 1; j <= C; ++j) {
         xor[j] = xor[j-1];
         if ((freq[j] & 1) != 0)
            xor[j] ^= j - 1;
      }
      for (int q = 0; q < Q; ++q) {
         int j = nextInt();
      // System.err.println(xor[j]);
         out.println(xor[j] != 0 ? "Alice" : "Bob");
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

