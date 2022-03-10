//==================================================================================
// Contest     : ICPC Qualifier 2021
// Problem     : Colors in trees
// Author      : Rubén Alcolea Núñez
// Description : DS4: Segment tree on a rooted tree
//==================================================================================

#include <iostream>
#include <vector>

using namespace std;

const int MAX = 2e5 + 5;
const int MAX_COLORS = 64;

struct node
{
    node()
    {
        for (int i = 0; i < MAX_COLORS; i++)
            colors[i] = 0;
        start = 0;
        lazy = 0;
    }
    int colors[MAX_COLORS];
    int start;
    int lazy;
};

int casos, a, b, n, vertex, value, query;
vector<int> adj[MAX];

int timer, queries, root;
int tin[MAX], tout[MAX];
int color[MAX], vertex_at_timeStamp[MAX];

node tree[MAX << 2];

void dfs(int current, int previous)
{
    tin[current] = timer;
    vertex_at_timeStamp[timer++] = current;

    for (auto next : adj[current])
        if (next != previous)
            dfs(next, current);

    tout[current] = timer - 1;
}

node merge(node a, node b)
{
    node res;
    for (int i = 0; i < MAX_COLORS; i++)
        res.colors[i] = a.colors[(i - a.start + MAX_COLORS) % MAX_COLORS] +
                        b.colors[(i - b.start + MAX_COLORS) % MAX_COLORS];
    res.lazy = 0;
    res.start = 0;
    return res;
}

void build(int node = 1, int start = 0, int end = n - 1)
{
    if (start == end)
    {
        tree[node].colors[color[vertex_at_timeStamp[start]]] = 1;
        return;
    }

    int middle = (start + end) / 2;
    build(2 * node + 0, start, middle);
    build(2 * node + 1, middle + 1, end);
    tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
}

void update(int node, int value)
{
    tree[node].lazy += value;
    tree[node].start = (tree[node].start + value) % MAX_COLORS;
}

void push(int node)
{
    if (tree[node].lazy)
    {
        update(2 * node + 0, tree[node].lazy);
        update(2 * node + 1, tree[node].lazy);
        tree[node].lazy = 0; // lazy is pushed
    }
}

void modify(int a, int b, int node = 1, int start = 0, int end = n - 1)
{
    // if [start,end] is outside of [a,b]
    if (start > b || end < a)
        return;

    // if [start,end] is inside of [a,b]
    if (start >= a && end <= b)
    {
        update(node, +1);
        return;
    }

    // pushing lazy propagation
    push(node);

    // otherwise, we split the interval
    int middle = (start + end) / 2;
    modify(a, b, 2 * node + 0, start, middle);
    modify(a, b, 2 * node + 1, middle + 1, end);
    tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
}

int get_value(int a, int b, int value, int node = 1, int start = 0, int end = n - 1)
{
    // if [start,end] is outside of [a,b]
    if (start > b || end < a)
        return 0;

    // if [start,end] is inside of [a,b]
    if (start >= a && end <= b)
        return tree[node].colors[(value - tree[node].start + MAX_COLORS) % MAX_COLORS];

    // pushing lazy propagation
    push(node);

    int middle = (start + end) / 2;
    return get_value(a, b, value, 2 * node + 0, start, middle) +
           get_value(a, b, value, 2 * node + 1, middle + 1, end);
}

void preprocess(int root)
{
    timer = 0;
    dfs(root, root);
}

int main()
{
    cin.sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> queries;
    for (int i = 0; i < n; i++)
    {
        adj[i].clear();
        cin >> color[i];
    }

    // reading edges info
    for (int i = 1; i < n; i++)
    {
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    preprocess(root = 0);
    build(1, 0, n - 1);
    while (queries--)
    {
        cin >> query >> vertex;
        vertex--;

        if (query == 1) // update
            modify(tin[vertex], tout[vertex]);
        else if (query == 2)
        { // query
            cin >> value;
            cout << get_value(tin[vertex], tout[vertex], value) << "\n";
        }
    }
    return 0;
}
