import java.io.*;
import java.util.*;

public class cjoa_maxmin // implements Runnable
{
   public static void main (String[] args) throws IOException {
      (new cjoa_maxmin()).run();
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
      int N = nextInt();
      int[] A = new int[N];
      for (int i = 0; i < N; ++i)
         A[i] = nextInt();
      int res = Arrays.stream(A).max().getAsInt()
              - Arrays.stream(A).min().getAsInt();
      out.println(res);
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

