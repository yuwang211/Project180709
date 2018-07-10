DT::DT(int maxSize, int sites)
{
	n = sites;
	int s = ((maxSize + 0xF) | 0xF);
	t = (TrackingUnit *)malloc(sizeof(TrackingUnit) * s);
	unused = 1;
	for (int i = 1; i < s; ++i)
		t[i].num = i + 1;
	t[s - 1].num = 0;
	todo = 0;
}

inline int DT::add(int num, int l, int r)
{
	int id = unused;
	unused = t[unused].num;
	
	t[id].l = l;
	t[id].r = r;
	t[id].num = num;
	t[id].numps = -INF;
	
	return id;
}

inline DT::TrackingUnit& DT::operator[](int k)
{
	return t[k];
}

inline int DT::get()
{
	if (todo == 0) return 0;
	int p = todo;
	todo = -t[p].numps;
	return p;
}

inline void DT::init(int id)
{
	t[id].s = (n << 1);
	t[id].numps = t[id].num / (n << 1);
}

inline int DT::assign(int id)
{
	if (t[id].s == 0){
		if (t[id].numps > 0)
		{
			t[id].numps = -todo;
			todo = id;
		}
		return 0;
	}
	t[id].num -= t[id].numps;
	--t[id].s;
	return t[id].numps;
}

inline void DT::report(int id, int &val)
{
	if (t[id].numps == 0)
	{
		t[id].num += val;
		val = 0;
		if (t[id].numps >= 0)
		{
			t[id].numps = -todo;
			todo = id;
		}
		return;
	}
	int k = (-val - 1) / t[id].numps + 1;
	if (t[id].s < k)
	{
		t[id].num += val;
		val = 0;
		if (t[id].numps >= 0)
		{
			t[id].numps = -todo;
			todo = id;
		}
		return;
	}
	t[id].s -= k;
	k *= t[id].numps;
	val += k;
	t[id].num -= k;
}

inline void DT::collect(int id, int &val)
{
	t[id].num += val;
	val = 0;
}


