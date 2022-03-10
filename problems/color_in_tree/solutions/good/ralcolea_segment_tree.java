import java.io.*;
import java.util.*;

/**
 *
 * @author Rubén Alcolea Núñez 
 * Problem Colors in trees 
 * DS4: Segment tree on a rooted tree
 */
public class ralcolea_segment_tree implements Runnable {
    static BufferedReader in;
    static PrintWriter out;
    static StringTokenizer st = new StringTokenizer("");

    public static final int MAX = 200005;
    public static final int MAX_COLORS = 64;

    // depth-first search properties
    public static int[] dfs_vertices;
    public static int[] tin;
    public static int[] tout;
    public static int root;
    public static int timer = 0;

    public static int n, q;
    public static int[] initial_colors;
    public static List<Integer> ady[];

    public static class SegmentTree
    {    
        public static class node {
            public int[] colors = new int[MAX_COLORS];
            public int initialPos;
            public int lazy;

            public node() {
                for (int i = 0; i < MAX_COLORS; i++) colors[i] = 0;
                initialPos = 0;
                lazy = 0;
            }
        }
        
        node[] tree;

        public SegmentTree(int l, int r, int[] A) {
            tree = new node[4 * n + 5];
            build(1, 0, n-1);
        }
        
        public final void build(int current, int start, int end) {
            if (start == end) {
                tree[current] = new node();
                tree[current].colors[initial_colors[dfs_vertices[start]]] = 1;
                return;
            }

            int middle = (start + end) / 2;
            build(2 * current + 0, start, middle);
            build(2 * current + 1, middle + 1, end);
            tree[current] = merge(tree[2 * current], tree[2 * current + 1]);
        }

        public node merge(node a, node b) {
            node res = new node();
            for (int i = 0; i < MAX_COLORS; i++)
                res.colors[i] = a.colors[(i - a.initialPos + MAX_COLORS) % MAX_COLORS]
                        + b.colors[(i - b.initialPos + MAX_COLORS) % MAX_COLORS];
           
            res.lazy = 0;
            res.initialPos = 0;
            return res;
        }

        public void update(int node, int value) {
            tree[node].lazy += value;
            tree[node].initialPos = (tree[node].initialPos + value) % MAX_COLORS;
        }

        public void push(int current_node) {
            if (tree[current_node].lazy > 0) {
                update(2 * current_node + 0, tree[current_node].lazy);
                update(2 * current_node + 1, tree[current_node].lazy);
                tree[current_node].lazy = 0;  // lazy is pushed
            }
        }

        public void modify(int a, int b, int current, int start, int end) {
            // if [start,end] is outside of [a,b]
            if (start > b || end < a) return;

            // if [start,end] is inside of [a,b]
            if (start >= a && end <= b) {
                update(current, +1);
                return;
            }

            // pushing lazy propagation
            push(current);

            //otherwise, we split the interval
            int middle = (start + end) / 2;
            modify(a, b, 2 * current + 0, start, middle);
            modify(a, b, 2 * current + 1, middle + 1, end);
            tree[current] = merge(tree[2 * current], tree[2 * current + 1]);
        }

        public int get_value(int a, int b, int value, int node, int start, int end) {
            // if [start,end] is outside of [a,b]
            if (start > b || end < a) return 0;

            // if [start,end] is inside of [a,b]
            if (start >= a && end <= b)
                return tree[node].colors[(value - tree[node].initialPos + MAX_COLORS) % MAX_COLORS];

            // pushing lazy propagation
            push(node);

            int middle = (start + end) / 2;
            return get_value(a, b, value, 2 * node + 0, start, middle) +
                   get_value(a, b, value, 2 * node + 1, middle + 1, end);
        }
    }

    public static void dfs(int current, int parent) {
        tin[current] = timer;
        dfs_vertices[timer++] = current;

        for (Integer next : ady[current]) {
            if (next != parent) {
                dfs(next, current);
            }
        }
        tout[current] = timer - 1;
    }

    /**
     * @param args the command line arguments
     * @throws java.io.IOException
     */
    public static void main(String[] args) throws IOException {
        new Thread(null, new ralcolea_segment_tree(), "", 1l * 50 * 1024 * 1024).start();
    }

   public void run() {
      try {
        /*try {
            in = new BufferedReader(new FileReader("input.txt"));
            out = new PrintWriter("output.txt");
        } catch (Exception e) {
            in = new BufferedReader(new InputStreamReader(System.in));
            out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
        }*/
        in = new BufferedReader(new InputStreamReader(System.in));
        out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
        //Scanner in = new Scanner(System.in);
        // n and q
        n = nextInt();
        q = nextInt();
        initial_colors = new int[n + 5];

        // initializing dfs properties
        dfs_vertices = new int[n + 5];
        tin = new int[n + 5];
        tout = new int[n + 5];

        ady = new ArrayList[n];
        Arrays.setAll(ady, e->new ArrayList<>());
        for (int i = 0; i < n; i++)
            initial_colors[i] = nextInt();

        for (int i = 0; i < n - 1; i++) {
            int a = nextInt();
            int b = nextInt();
            a--;
            b--;
            ady[a].add(b);
            ady[b].add(a);
        }

        dfs(root, root);
        SegmentTree tree = new SegmentTree(0, n - 1, initial_colors);
        while (q > 0) {
            q--;
            int type = nextInt();
            int vertex = nextInt();
            vertex--;
            if (type == 1) {  // update
                tree.modify(tin[vertex], tout[vertex], 1, 0, n-1);
            } else if (type == 2) { // query
                int value = nextInt();
                out.println(tree.get_value(tin[vertex], tout[vertex], value, 
                        1, 0, n-1));
            }
        }
        out.flush();
      } catch (Exception ex) {}
    }

    public static String next() throws IOException {
        while (!st.hasMoreTokens()) {
            st = new StringTokenizer(in.readLine());
        }
        return st.nextToken();
    }

    public static int nextInt() throws IOException {
        return Integer.parseInt(next());
    }
}
