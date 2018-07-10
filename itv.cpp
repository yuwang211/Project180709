
Itv::Itv(int maxSize)
{
	int s = ((maxSize + 0xF) | 0xF);
	t = (ItvNode *)malloc(sizeof(ItvNode) * s);
	t[0].l = t[0].r = t[0].size = t[0].cnt = 0;
	t[0].lt = t[0].rt = 0;
	unused = 1;
	for (int i = 1; i < s; ++i)
		t[i].key = i + 1;
	t[s - 1].key = 0;
	
	bst = new Bst(maxSize * 2);
}

Itv::~Itv()
{
	free(t);
	delete bst;
}

inline void Itv::up(int p)
{
	//t[p].size = t[t[p].l].size + t[t[p].r].size + t[p].cnt;
}

inline Itv::ItvNode& Itv::operator[](int k)
{
	return t[k];
}

int Itv::insert(int p, int l, int r, int id)
{
	p = insertKey(p, l);
	p = insertKey(p, r);
	insertItv(p, l, r, id);
	return p;
}

int Itv::remove(int p, int l, int r, int id)
{
	p = removeKey(p, l);
	p = removeKey(p, r);
	removeItv(p, l, r, id);
	return p;
}

void Itv::change(int p, int x, int delta)
{
	if (p == 0) return;
	if (x <= t[p].key)
	{
		bst->change(t[p].lt, -INF, x, delta);
		bst->scanNegative(t[p].lt);
		change(t[p].l, x, delta);
	}
	else
	{
		bst->change(t[p].rt, x, INF, delta);
		bst->scanNegative(t[p].rt);
		change(t[p].r, x, delta);
	}
}

void Itv::linkDT(DT *d)
{
	bst->linkDT(d);
}

void Itv::collect(int p, int l, int r, int id)
{
	if (r < t[p].key)
	{
		collect(t[p].l, l, r, id);
	}
	else if (t[p].key < l)
	{
		collect(t[p].r, l, r, id);
	}
	else
	{
		bst->collect(t[p].lt, l, id);
		bst->collect(t[p].rt, r, id);
	}
}

void Itv::assign(int p, int l, int r, int id)
{
	if (r < t[p].key)
	{
		assign(t[p].l, l, r, id);
	}
	else if (t[p].key < l)
	{
		assign(t[p].r, l, r, id);
	}
	else
	{
		bst->assign(t[p].lt, l, id);
		bst->assign(t[p].rt, r, id);
	}
}

void Itv::print(int p, int dep)
{
	if (p == 0) return;
	print(t[p].l, dep + 1);
	for (int i =1 ; i <= dep; ++i)
		printf("  ");
	printf("%d:", t[p].key);
	bst->print(t[p].lt);
	printf(",");
	bst->print(t[p].rt);
	printf("\n");
	print(t[p].r, dep + 1);
}




int Itv::insertKey(int p, int key)
{
	if (p == 0)
	{
		p = unused;
		unused = t[unused].key;
		t[p].l = t[p].r = 0;
		t[p].key = key;
		t[p].cnt = 1;
		t[p].size = 0;
		t[p].lt = t[p].rt = 0;
		return p;
	}
	if (key == t[p].key)
	{
		++t[p].cnt;
		return p;
	}
	if (key < t[p].key)
	{
		t[p].l = insertKey(t[p].l, key);
	}
	else 
	{
		t[p].r = insertKey(t[p].r, key);
	}
	return p;
}

void Itv::insertItv(int p, int l, int r, int id)
{
	if (r < t[p].key)
	{
		insertItv(t[p].l, l, r, id);
	}
	else if (t[p].key < l)
	{
		insertItv(t[p].r, l, r, id);
	}
	else
	{
		t[p].lt = bst->insert(t[p].lt, l, id);
		t[p].rt = bst->insert(t[p].rt, r, id);
	}
}

int Itv::removeKey(int p, int key)
{
	if (key == t[p].key)
	{
		--t[p].cnt;
		return p;
	}
	if (key < t[p].key)
	{
		t[p].l = removeKey(t[p].l, key);
	}
	else 
	{
		t[p].r = removeKey(t[p].r, key);
	}
	return p;
}

void Itv::removeItv(int p, int l, int r, int id)
{
	if (r < t[p].key)
	{
		removeItv(t[p].l, l, r, id);
	}
	else if (t[p].key < l)
	{
		removeItv(t[p].r, l, r, id);
	}
	else
	{
		t[p].lt = bst->remove(t[p].lt, l, id);
		t[p].rt = bst->remove(t[p].rt, r, id);
	}
}