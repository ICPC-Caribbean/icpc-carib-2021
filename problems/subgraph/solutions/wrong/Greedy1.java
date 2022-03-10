// Alfonso² Peterssen
// Greedy (incorrect) solution
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Comparator;
import java.util.StringTokenizer;
import java.util.stream.Stream;

public final class Greedy1 {

    static final int MAXV = 100;
    static final int MAXE = 1000;

    int N, E;
    int V;
    int[] w;
    int[] edgeSum;
    int[][] cost;
    int[] answer;

    public void solve(int testNumber, InputReader in, PrintWriter out) {

        N = in.nextInt();
        E = in.nextInt();

        w = new int[N];
        for (int i = 0; i < N; ++i) {
            w[i] = in.nextInt();
        }

        edgeSum = new int[N];
        cost = new int[N][N];

        for (int i = 0; i < E; ++i) {
            int u, v, w;
            u = in.nextInt();
            v = in.nextInt();
            w = in.nextInt();
            --u;
            --v;
            cost[u][v] = cost[v][u] = w;
            edgeSum[u] += w;
            edgeSum[v] += w;
        }

        int[] order = Stream.iterate(0, i -> i + 1).limit(N) //
                        .sorted(Comparator.<Integer>comparingInt(e -> w[e] + edgeSum[e]).reversed()) //
                        .mapToInt(i -> i) //
                        .toArray();
        
        int bestNum = 0;
        int bestDen = 1;
        int[] answer = new int[0];
        for (int i = 0; i < N; ++i) {
            int eCost = 0;
            int wCost = 0;

            for (int j = 0; j <= i; ++j) {
                int u = order[j];
                wCost += w[u];
                for (int k = 0; k < j; ++k) {
                    int v = order[k];
                    eCost += cost[u][v];
                }
            }
            if (bestNum * (long) (i + 1) < (wCost + eCost) * (long) bestDen) {
                bestNum = (wCost + eCost);
                bestDen = (i + 1);
                answer = Arrays.copyOf(order, (i + 1));
            }
        }

        out.println(answer.length);
        for (int i = 0; i < answer.length; i++) {
            if (i > 0) {
                out.print(" ");
            }
            out.print(answer[i] + 1);
        }
        out.println();
    }

    public static void main(String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        Greedy1 solver = new Greedy1();
        solver.solve(1, in, out);
        out.close();
    }

    static class InputReader {
        public BufferedReader reader;
        public StringTokenizer tokenizer;

        public InputReader(InputStream stream) {
            reader = new BufferedReader(new InputStreamReader(stream), 32768);
            tokenizer = null;
        }

        public String next() {
            while (tokenizer == null || !tokenizer.hasMoreTokens()) {
                try {
                    tokenizer = new StringTokenizer(reader.readLine());
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            return tokenizer.nextToken();
        }

        public int nextInt() {
            return Integer.parseInt(next());
        }
    }
}