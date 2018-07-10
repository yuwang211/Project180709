RTS1D::RTS1D(int maxSize)
{
	dt = new DT(maxSize);
	itv = new Itv(maxSize);
	itv->linkDT(dt);
	root = 0;
}

RTS1D::~RTS1D()
{
	delete dt;
	delete itv;
}

void RTS1D::addInterval(int l, int r, int num)
{
	int id = dt->add(num, l, r);
	dt->init(id);
	root = itv->insert(root, l, r, id);
	//itv->print(root);
}

void RTS1D::addPoint(int x, int weight)
{
	itv->change(root, x, -weight);
	//itv->print(root);
	for (int id = dt->get(); id != 0; id = dt->get())
	{
		itv->collect(root, (*dt)[id].l, (*dt)[id].r, id);
		if ((*dt)[id].num < 0)
		{
			//Report
			//printf("Interval %d[%d, %d] is fulfilled.\n", id, (*dt)[id].l, (*dt)[id].r);
			printf("Report\n");
			
 			root = itv->remove(root, (*dt)[id].l, (*dt)[id].r, id);
			//itv->print(root);
		}
		else
		{
			dt->init(id);
			itv->assign(root, (*dt)[id].l, (*dt)[id].r, id);
		}
		//itv->print(root);
	}
	
}