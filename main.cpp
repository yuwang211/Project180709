#include "rts1d.h"

int n;

int main(int args, char **argv)
{
	freopen("in.txt", "r" ,stdin);
	//freopen(argv[1], "r", stdin);
	scanf("%d", &n);
	RTS1D rts1d(n);
	for (int i = 1; i <= n; ++i)
	{
		//if (i == 59) 
		printf("Time %d:\n", i);
		int flag;
		
		scanf("%d", &flag);
		if (flag == 0)
		{
			int l, r, num;
			scanf("%d %d %d", &l, &r, &num);
			rts1d.addInterval(l, r, num);
		}
		else
		{
			int x, weight;
			scanf("%d %d", &x, &weight);
			rts1d.addPoint(x, weight);
		}
			/*rts1d.itv->collect(rts1d.root, (*rts1d.dt)[22].l, (*rts1d.dt)[22].r, 22);
			rts1d.dt->init(22);
			printf("counter[%d] = %d\n", 22, (*rts1d.dt)[22].num);
			rts1d.itv->assign(rts1d.root, (*rts1d.dt)[22].l, (*rts1d.dt)[22].r, 22);*/
		
	}
	return 0;
}
