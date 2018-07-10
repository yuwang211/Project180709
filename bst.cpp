
Bst::Bst(int maxSize)
{
	int s = ((maxSize + 0xF) | 0xF);
	t = (BstNode *)malloc(sizeof(BstNode) * s);
	t[0].l = t[0].r = t[0].size = t[0].delta = 0;
	t[0].val = t[0].min = INF;
	unused = 1;
	for (int i = 1; i < s; ++i)
		t[i].key = i + 1;
	t[s - 1].key = 0;
}

Bst::~Bst()
{
	free(t);
}

inline void Bst::add(int p, int delta)
{
	if (p != 0)
	{
		t[p].val += delta;
		t[p].delta += delta;
		t[p].min += delta;
	}
}

inline void Bst::down(int p)
{
	if (t[p].delta != 0)
	{
		add(t[p].l, t[p].delta);
		add(t[p].r, t[p].delta);
		t[p].delta = 0;
	}
}

inline void Bst::up(int p)
{
	t[p].size = t[t[p].l].size + t[t[p].r].size + 1;
	t[p].min = min(min(t[t[p].l].min, t[t[p].r].min), t[p].val);
}

int Bst::toList(int p, int tail)
{
	if (p == 0) return tail;
	down(p);
	t[p].r = toList(t[p].r, tail);
	return toList(t[p].l, p);
}

int Bst::toTree(int p)
{
	int size = 0;
	for (int q = p; q != 0; q = t[q].r) ++size;
	return buildTree(p, size);
}

int Bst::buildTree(int &p, int size)
{
	if (size == 0) return 0;
	int mid = ((1 + size) >> 1);
	int q = buildTree(p, mid - 1);
	t[p].l = q;
	q = p;
	p = t[p].r;
	t[q].r = buildTree(p, size - mid);
	up(q);
	return q;
}

inline Bst::BstNode& Bst::operator[](int k)
{
	return t[k];
}

int Bst::insert(int p, int key, int id, bool flag)
{
	if (p == 0)
	{
		p = unused;
		unused = t[unused].key;
		t[p].l = t[p].r = 0;
		t[p].key = key;
		t[p].size = 1;
		t[p].id = id;
		t[p].val = dt->assign(id);
		t[p].min = t[p].val;
		t[p].delta = 0;
		return p;
	}
	down(p);
	if (key < t[p].key || ((key == t[p].key) && (id < t[p].id)))
	{
		bool flag2 = ((t[t[p].l].size - 3 > (t[t[p].r].size << 1)));
		t[p].l = insert(t[p].l, key, id, flag && flag2);
		up(p);
		if (flag2)
			t[p].l = toTree(toList(t[p].l));
	}
	else
	{
		bool flag2 = ((t[t[p].r].size - 3 > (t[t[p].l].size << 1)));
		t[p].r = insert(t[p].r, key, id, flag && flag2);
		up(p);
		if (flag2)
			t[p].r = toTree(toList(t[p].r));
	}
	return p;
}



int Bst::insert(int p, int n, bool flag)
{
	if (p == 0)
	{
		p = n;
		t[p].l = t[p].r = 0;
		t[p].size = 1;
		t[p].min = t[p].val;
		t[p].delta = 0;
		return p;
	}
	down(p);
	if (t[n].key < t[p].key || ((t[n].key == t[p].key) && (t[n].id < t[p].id)))
	{
		bool flag2 = ((t[t[p].l].size - 3 > (t[t[p].r].size << 1)));
		t[p].l = insert(t[p].l, n, flag && flag2);
		up(p);
		if (flag2)
			t[p].l = toTree(toList(t[p].l));
	}
	else
	{
		bool flag2 = ((t[t[p].r].size - 3 > (t[t[p].l].size << 1)));
		t[p].r = insert(t[p].r, n, flag && flag2);
		up(p);
		if (flag2)
			t[p].r = toTree(toList(t[p].r));
	}
	return p;
}

int Bst::remove(int p, int key, int id, bool flag)
{
	if (p == 0) return 0;
	down(p);
	
	if (key == t[p].key && id == t[p].id)
	{
		if (t[p].l == 0)
		{
			int q = t[p].r;
			t[p].key = unused;
			unused = p;
			return q;
		}
		else if (t[p].r == 0)
		{
			int q = t[p].l;
			t[p].key = unused;
			unused = p;
			return q;
		}
		else
		{
			int q;
			for (q = t[p].l; t[q].r != 0; q = t[q].r)
				down(q);
			down(q);
			
			t[p].key = t[q].key;
			t[p].id = t[q].id;
			t[p].val = t[q].val;
			t[q].key = key;
			t[q].id = id;
			
			t[p].l = remove(t[p].l, key, id);
			up(p);
			if (t[t[p].r].size - 3 > (t[t[p].l].size << 1))
				t[p].l = toTree(toList(t[p].l));
		}
	}
	else if (key < t[p].key || ((key == t[p].key) && (id < t[p].id)))
	{
		bool flag2 = ((t[t[p].r].size - 3 > (t[t[p].l].size << 1)));
		t[p].l = remove(t[p].l, key, id, flag2 && flag);
		up(p);
		if (flag2)
			t[p].l = toTree(toList(t[p].l));
	}
	else
	{
		bool flag2 = ((t[t[p].l].size - 3 > (t[t[p].r].size << 1)));
		t[p].r = remove(t[p].r, key, id, flag2 && flag);
		up(p);
		if (flag2)
			t[p].r = toTree(toList(t[p].r));
	}
	return p;
}

int Bst::merge(int p, int q)
{
	int tmp;
	if (t[p].size < t[q].size)
	{
		tmp = p;
		p = q;
		q = tmp;
	}
	
	q = toList(q);
	while (q != 0)
	{
		tmp = t[q].r;
		insert(p, q);
		q = tmp;
	}
	return p;
}

void Bst::change(int p, int l, int r, int delta)
{
	if (p == 0) return;
	down(p);
	
	if (l == -INF && r == INF)
	{
		add(p, delta);
		return;
	}
	
	if (l <= t[p].key && t[p].key <= r)
		t[p].val += delta;
	if (l <= t[p].key)
	{
		if (r >= t[p].key)
			change(t[p].l, l, INF, delta);
		else
			change(t[p].l, l, r, delta);
	}
	if (r >= t[p].key)
	{
		if (l <= t[p].key)
			change(t[p].r, -INF, r, delta);
		else
			change(t[p].r, l, r, delta);
	}
	up(p);
}

inline void Bst::linkDT(DT *d)
{
	dt = d;
}

void Bst::scanNegative(int p)
{
	if (p == 0) return;
	down(p);
	if (t[p].min >= 0) return;
	
	if (t[p].val < 0)
		dt->report(t[p].id, t[p].val);
	up(p);
	
	scanNegative(t[p].l);
	scanNegative(t[p].r);
	up(p);
}


void Bst::collect(int p, int key, int id)
{
	if (p == 0) return;
	down(p);
	
	if (key == t[p].key && id == t[p].id)
	{
		dt->collect(id, t[p].val);
		up(p);
	}
	else if (key < t[p].key || ((key == t[p].key) && (id < t[p].id)))
	{
		collect(t[p].l, key, id);
		up(p);
	}
	else
	{
		collect(t[p].r, key, id);
		up(p);
	}
}


void Bst::assign(int p, int key, int id)
{
	if (p == 0) return;
	down(p);
	
	if (key == t[p].key && id == t[p].id)
	{
		t[p].val = dt->assign(id);
		up(p);
	}
	else if (key < t[p].key || ((key == t[p].key) && (id < t[p].id)))
	{
		assign(t[p].l, key, id);
		up(p);
	}
	else
	{
		assign(t[p].r, key, id);
		up(p);
	}
}

void Bst::print(int p)
{
	if (p == 0) return;
	printf("(");
	print(t[p].l);
	printf("%d:%d[%d,%d]", t[p].key, t[p].id, t[p].min, t[p].val);
	print(t[p].r);
	printf(")");
}
