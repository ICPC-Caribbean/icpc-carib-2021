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

public final class Greedy2 {

    static final int MAXV = 100;
    static final int MAXE = 1000;

    int N, E;
    int V;
    int[] w;
    int[] edgeSum;
    int[][] cost;
    int[] answer;

    int computeCost(int[] choosen, int size) {
        int totalCost = 0;
        for (int j = 0; j < size; ++j) {
            int u = choosen[j];
            totalCost += w[u];
            for (int k = 0; k < j; ++k) {
                int v = choosen[k];
                totalCost += cost[u][v];
            }
        }
        return totalCost;
    }

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

            int candidateSize = i + 1;
            int candidateCost = computeCost(order, candidateSize);

            if (bestNum * (long) candidateSize < candidateCost * (long) bestDen) {
                bestNum = candidateCost;
                bestDen = candidateSize;
                answer = Arrays.copyOf(order, candidateSize);
            }

            int[] choosen = Arrays.copyOf(order, candidateSize);
            

            boolean removed;
            do {                
                removed = false;
                for (int j = 0; j < choosen.length && choosen.length > 0; ++j) {
                    int totalCost = candidateCost;

                    // try to remove choosen[j]
                    int u = choosen[j];
                    totalCost -= w[u];

                    for (int k = 0; k < choosen.length; ++k) {
                        if (k != j) {
                            int v = order[k];
                            totalCost -= cost[u][v];
                        }
                    }
                    if (totalCost * (long) candidateSize > candidateCost * (long) (choosen.length - 1)) {

                        candidateCost = totalCost;
                        candidateSize = choosen.length - 1;

                        int[] tmp = new int[choosen.length - 1];
                        System.arraycopy(choosen, 0, tmp, 0, j);
                        System.arraycopy(choosen, j + 1, tmp, j, choosen.length - 1 - j);
                        choosen = tmp;

                        removed = true;

                        if (bestNum * (long) candidateSize < candidateCost * (long) bestDen) {
                            bestNum = candidateCost;
                            bestDen = candidateSize;
                            answer = Arrays.copyOf(choosen, choosen.length);
                        }
                    }
                }
            } while (removed);

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
        Greedy2 solver = new Greedy2();
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