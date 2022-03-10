import java.io.*;
import java.util.*;

/**
 *
 * @author Rubén Alcolea Núñez 
 * Problem Colors in trees
 * DS4: Segment tree on a rooted tree
 */
public class ralcolea_scanner {
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

    public static class SegmentTree {

        int leftmost, rightmost;
        SegmentTree left, right;

        int[] colors = new int[MAX_COLORS];
        int initialPos;
        int lazy;

        public SegmentTree(int l, int r, int[] A) {
            leftmost = l;
            rightmost = r;

            if (leftmost == rightmost) {
                // leaf node
                for (int i = 0; i < MAX_COLORS; i++) {
                    colors[i] = 0;
                }

                initialPos = 0;
                lazy = 0;

                // setting color
                colors[initial_colors[dfs_vertices[leftmost]]] = 1;
            } else {
                int middle = (leftmost + rightmost) / 2;
                left = new SegmentTree(leftmost, middle, A);
                right = new SegmentTree(middle + 1, rightmost, A);
                merge();
            }
        }

        public void merge() {
            if (leftmost != rightmost) {
                for (int i = 0; i < MAX_COLORS; i++) {
                    colors[i] = left.colors[(i - left.initialPos + MAX_COLORS) % MAX_COLORS]
                            + right.colors[(i - right.initialPos + MAX_COLORS) % MAX_COLORS];
                }
                lazy = 0;
                initialPos = 0;
            }
        }

        public void update(int value) {
            lazy += value;
            initialPos = (initialPos + value) % MAX_COLORS;
        }

        public void push() {
            if (lazy > 0) {
                left.update(lazy);
                right.update(lazy);
                lazy = 0;
            }
        }

        public void modify(int a, int b) {
            // if [start,end] is outside of [a,b]
            if (leftmost > b || rightmost < a) return;

            // if [start,end] is inside of [a,b]
            if (leftmost >= a && rightmost <= b) {
                update(+1);
                return;
            }

            // pushing lazy propagation
            push();

            //otherwise, we split the interval
            left.modify(a, b);
            right.modify(a, b);
            merge();
        }

        public int get_value(int a, int b, int value) {
            // if [start,end] is outside of [a,b]
            if (leftmost > b || rightmost < a) return 0;

            // if [start,end] is inside of [a,b]
            if (leftmost >= a && rightmost <= b)
                return colors[(value - initialPos + MAX_COLORS) % MAX_COLORS];

            // pushing lazy propagation
            push();

            return left.get_value(a, b, value) + right.get_value(a, b, value);
        }
    }

    public static void dfs(int current, int parent) {
        tin[current] = timer;
        dfs_vertices[timer++] = current;

        for (Integer next : ady[current]) {
            if (next != parent)
                dfs(next, current);
        }
        tout[current] = timer - 1;
    }

    /**
     * @param args the command line arguments
     * @throws java.io.IOException
     */
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(System.in);
        // n and q
        n = in.nextInt();
        q = in.nextInt();
        initial_colors = new int[n];

        // initializing dfs properties
        dfs_vertices = new int[n + 5];
        tin = new int[n + 5];
        tout = new int[n + 5];

        ady = new ArrayList[n];
        Arrays.setAll(ady, e -> new ArrayList<>());
        for (int i = 0; i < n; i++)
            initial_colors[i] = in.nextInt();

        for (int i = 0; i < n - 1; i++) {
            int a = in.nextInt();
            int b = in.nextInt();
            a--;
            b--;
            ady[a].add(b);
            ady[b].add(a);
        }

        dfs(root, root);
        SegmentTree tree = new SegmentTree(0, n - 1, initial_colors);
        while (q > 0) {
            q--;
            int type = in.nextInt();
            int vertex = in.nextInt();
            vertex--;
            if (type == 1) {  // update
                tree.modify(tin[vertex], tout[vertex]);
            } else if (type == 2) { // query
                int value = in.nextInt();
                System.out.println(tree.get_value(tin[vertex], tout[vertex], value));
            }
        }
    }
}
