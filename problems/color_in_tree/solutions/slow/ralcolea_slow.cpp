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

int casos, a, b, n, vertex, value, query;
vector<int> adj[MAX];

int timer, queries, root;
int tin[MAX], tout[MAX];
int color[MAX], vertex_at_timeStamp[MAX];

void dfs(int current, int previous)
{
    tin[current] = timer;
    vertex_at_timeStamp[timer++] = current;

    for (auto next : adj[current])
        if (next != previous)
            dfs(next, current);

    tout[current] = timer - 1;
}

void modify(int a, int b)
{
    for (int i = a; i <= b; i++)
        color[vertex_at_timeStamp[i]] = (color[vertex_at_timeStamp[i]] + 1) % MAX_COLORS;
}

int get_value(int a, int b, int value)
{
    int sol = 0;

    for (int i = a; i <= b; i++)
        if (color[vertex_at_timeStamp[i]] == value)
            sol++;

    return sol;
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
