RTS1DBF::RTS1DBF(int maxSize)
{
	t = (Node *)malloc(sizeof(Node) * (maxSize + 0x7f));
	id = 0;
}

RTS1DBF::~RTS1DBF()
{
	free(t);
}

void RTS1DBF::addInterval(int l, int r, int num)
{
	t[++id].l = l;
	t[id].r = r;
	t[id].num = num;
}

void RTS1DBF::addPoint(int x, int weight)
{
	for (int i = 1; i <= id; ++i)
	if (t[i].l <= x && x <= t[i].r && t[i].num >= 0)
	{
		t[i].num -= weight;
		if (t[i].num < 0)
			//printf("Interval %d[%d, %d] is fulfilled.\n", i, t[i].l, t[i].r);
			printf("Report\n");
	}

}