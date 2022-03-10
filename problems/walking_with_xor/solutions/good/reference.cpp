#include <iostream>
#include <vector>

using namespace std;

const int mod = 1e9 + 7;

struct node
{
	int dp, lazy;
	node *ch[2];
	node() : dp(0), lazy(0) { ch[0] = ch[1] = NULL; }
};

inline void add(int &x, int y)
{
	x += y;
	if (x >= mod)
		x -= mod;
}

inline void push(node *u)
{
	if (u->lazy)
	{
		add(u->dp, u->lazy);
		if (u->ch[0])
			add(u->ch[0]->lazy, u->lazy);
		if (u->ch[1])
			add(u->ch[1]->lazy, u->lazy);
		u->lazy = 0;
	}
}

void insert(node *u, int m)
{
	for (int i = 20; i >= 0; --i)
	{
		bool d = m >> i & 1;
		if (!u->ch[d])
			u->ch[d] = new node();
		u = u->ch[d];
	}
}

void update(node *u, int x, int m, int k)
{
	for (int i = 20; i >= 0; --i)
	{
		push(u);
		bool d = m >> i & 1;
		bool e = k >> i & 1;
		if (e && u->ch[d])
			add(u->ch[d]->lazy, x);
		if (!u->ch[d ^ e])
			break;
		u = u->ch[d ^ e];
	}
}

int get(node *u, int m)
{
	for (int i = 20; i >= 0; --i)
	{
		push(u);
		bool d = m >> i & 1;
		u = u->ch[d];
	}
	push(u);
	return u->dp;
}

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n, k;
	cin >> n >> k;
	vector<int> a(n);
	node *root = new node();
	for (int i = 0; i < n; ++i)
	{
		cin >> a[i];
		insert(root, a[i]);
	}

	for (int i = 0; i < n - 1; ++i)
	{
		int x = get(root, a[i]) + (!i);
		update(root, x, a[i], k);
	}

	cout << get(root, a.back()) + (n == 1) << "\n";

	return 0;
}
