#include "rts1dbf.h"

int n;

int main(int args, char **argv)
{
	freopen("in.txt", "r" ,stdin);
	//freopen(argv[1], "r", stdin);
	scanf("%d", &n);
	RTS1DBF rts1d(n);
	for (int i = 1; i <= n; ++i)
	{
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
	}
	return 0;
}
