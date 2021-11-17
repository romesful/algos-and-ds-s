// ДО на прибавление на отрезке + запрос на сумму на отрезке
typedef long long ll;

struct segment_tree {
	ll* tAdd; // push
	ll* t;
	int n;
	
	ll func(ll left, ll right)
	{
		return left + right; // change if needed
	}

	void build(int n)
	{
		this->n = n;
		tAdd = new ll[4 * n];
		t = new ll[4 * n];

		for (int i = 0; i < 4 * n; i++)
		{
			tAdd[i] = 0;
			t[i] = 0;
		}
	}

	void build(int v, int tl, int tr, vector<int>& a)
	{
		if (tl == tr)
		{
			t[v] = a[tl];
			return;
		}

		int tm = (tl + tr) / 2;

		build(2 * v + 1, tl, tm, a);
		build(2 * v + 2, tm + 1, tr, a);
		t[v] = func(t[2 * v + 1], t[2 * v + 2]);
	}

	void build(int n, vector<int>& a)
	{
		build(n);
		build(0, 0, n - 1, a);
	}

	ll query(int v, int tl, int tr, int l, int r)
	{
		int tm = (tl + tr) / 2;
		if (r < tl || tr < l)
			return 0; // change if needed
		if (l <= tl && tr <= r)
			return t[v];

		return func(query(2 * v + 1, tl, tm, l, r), query(2 * v + 2, tm + 1, tr, l, r));
	}

	ll query(int l, int r)
	{
		return query(0, 0, n - 1, l, r);
	}

	void push_to_node_function(ll v) // change if needed
	{
		t[v] += tAdd[v];
	}

	void push(int v, int tl, int tr) // change if needed
	{
		if (tAdd[v])
		{
			if (tl != tr)
			{
				tAdd[2 * v + 1] += tAdd[v];
				tAdd[2 * v + 2] += tAdd[v];
			}

			push_to_node_function(v);
			tAdd[v] = 0;
		}
	}

	void modify(int v, int tl, int tr, int l, int r, ll val)
	{
		if (l <= tl && tr <= r)
		{
			tAdd[v] = val;
			push(v, tl, tr);

			return;
		}

		if (r < tl || l > tr)
			return;

		push(v, tl, tr);

		int tm = (tl + tr) / 2;

		modify(2 * v + 1, tl, tm, l, r, val);
		modify(2 * v + 2, tm + 1, tr, l, r, val);
		t[v] = func(t[2 * v + 1], t[2 * v + 2]);
	}

	void modify(int l, int r, ll val) // change if needed
	{
		modify(0, 0, n - 1, l, r, val);
	}
};
