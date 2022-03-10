import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class sol_rchaves {
  public static long ceilDiv(long a, long b) {
    return -Math.floorDiv(-a, b);
  }
  
  public static void main(String[] paramArrayOfString) throws IOException {
    BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
    int t = Integer.parseInt(bufferedReader.readLine());
    while (t-- != 0) {
      String[] tokens = bufferedReader.readLine().split(" ");
      long p = Long.parseLong(tokens[0]);
      long k = Long.parseLong(tokens[1]);
      long m = Long.parseLong(tokens[2]);
      long firstImage = -p + k;
      if (firstImage >= m) {
        System.out.println(1);
        continue;
      } 
      long requiredS = ceilDiv(m - k, 2L * p);
      System.out.println(Math.max(2L, 2L * requiredS));
    } 
  }
}

