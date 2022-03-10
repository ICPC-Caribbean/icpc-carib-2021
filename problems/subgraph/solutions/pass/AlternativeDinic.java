
// Alfonso² Peterssen
// Original solution
// Uses graph construction derived from the Baseball Elimination problem.
// Implemented using Dinic maximum flow algorithm.
// Complexity: O((E + V)^3 * log X)
// log X -> binary search till certain precision is attained.
import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.StringTokenizer;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.InputStream;

public final class AlternativeDinic {

    static final int MAXV = 100;
    static final int MAXE = 1000;
    static final double EPS = 1e-6;
    static final int INF = 1 << 28;

    static class Edge {
        final int u, v;
        double flow, cap;
        final int next;
        Edge(int u, int v, double flow, double cap, int next) {
            this.u = u;
            this.v = v;
            this.flow = flow;
            this.cap = cap;            
            this.next = next;
        }
    };

    int N, E;
    int V;
    int[] w;
    int edgeSum;

    int edgeCount;
    Edge[] edges = new Edge[2 * (MAXE + 2 * MAXE + MAXV)];

    int[] first;

    int source, sink;
    int[] Q =  new int[MAXE + MAXV + 2];
    int[] level;
    int[] cut;

    int[] answer;

    void addEdge(int u, int v, double cap) {
        edges[edgeCount++] = new Edge(u, v, 0.0, cap, first[u]);
        first[u] = edgeCount - 1;
        edges[edgeCount++] = new Edge(v, u, cap, cap, first[v]);
        first[v] = edgeCount - 1;
    }

    boolean bfs() {
        Arrays.fill(level, -1);
        level[source] = 0;

        int front = 0, back = 0;
        for (Q[front++] = source; back < front;) {
            int u = Q[back++];
            for (int e = first[u]; e >= 0; e = edges[e].next) {
                int v = edges[e].v;
                if (level[v] < 0 && edges[e].cap - edges[e].flow > EPS) {
                    Q[front++] = v;
                    level[v] = level[u] + 1;
                }
            }
        }
        return level[sink] >= 0;
    }

    double dfs(int u, double flow) {
        if (u == sink) {
            return flow;
        }
        for (int e = first[u]; e >= 0; e = edges[e].next) {
            int v = edges[e].v;
            if (level[u] < level[v]) {
                double r = edges[e].cap - edges[e].flow;
                if (r > EPS) {
                    double f = dfs(v, Math.min(flow, r));
                    if (f > EPS) {
                        edges[e].flow += f;
                        edges[e ^ 1].flow -= f;
                        return f;
                    }
                }
            }
        }
        return 0.0;
    }

    int minCut(double W) {
        // cerr << "can_win W=" << W << endl;

        // Set node -> sink capacities.
        for (int i = 0; i < N; ++i) {
            int e = first[E + i];
            edges[e].cap = W - w[i];
        }

        // Reset flow.
        for (int e = 0; e < edgeCount; e++) {
            if ((e & 1) == 1) {
                // back edges are saturated
                edges[e].flow = edges[e].cap;
            } else {
                // forward edges are fully available
                edges[e].flow = 0;
            }
        }

        while (bfs()) {
            while (dfs(source, INF) > EPS) {
                // empty
            }
        }

        int cutSize = 0;
        for (int i = 0; i < N; ++i) {
            if (level[E + i] >= 0) {
                cut[cutSize++] = i;
            }
        }

        return cutSize;
    }

    public void solve(int testNumber, InputReader in, PrintWriter out) {

        N = in.nextInt();
        E = in.nextInt();

        V = E + N;
        source = V++;
        sink = V++;

        first = new int[V];
        Arrays.fill(first, -1);

        w = new int[N];
        for (int i = 0; i < N; ++i) {
            w[i] = in.nextInt();
        }

        for (int i = 0; i < E; ++i) {
            int u, v, w;
            u = in.nextInt();
            v = in.nextInt();
            w = in.nextInt();
            --u;
            --v;
            addEdge(source, i, w);
            addEdge(i, E + u, INF);
            addEdge(i, E + v, INF);
            edgeSum += w;
        }

        for (int i = 0; i < N; ++i) {
            addEdge(E + i, sink, 0);
        }

        level = new int[V];
        cut = new int[V];

        double lo = Arrays.stream(w).max().getAsInt();
        double hi = edgeSum + Arrays.stream(w).sum() + 1;
        while (hi - lo > EPS) {
            double mid = (lo + hi) / 2.0;
            int cutSize = minCut(mid);
            if (cutSize == 0) {
                hi = mid;
            } else {
                answer = Arrays.copyOf(cut, cutSize);
                lo = mid;
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
        AlternativeDinic solver = new AlternativeDinic();
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