#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cmath>

int min(int x, int y){return x < y ? x : y;}
int max(int x, int y){return x > y ? x : y;}

int random(int n)
{
	return (int)(((((long long)rand()) << 0) ^
	       (((long long)rand()) << 10) ^
		   (((long long)rand()) << 20) ^
		   (((long long)rand()) << 30) ^
		   (((long long)rand()) << 40)) % n);
}

void per(int *a, int n)
{
	for (int i = 2; i <= n; ++i)
	{
		int j = random(i - 1);
		int tmp = a[i];
		a[i] = a[j];
		a[j] = tmp;
	}
}

const int MAXN = 20000010;

int n;
int a[MAXN * 2];
int b[MAXN * 2];


int main(int argv, char **args)
{
	srand(time(NULL));
	n = atoi(args[1]);
	freopen(args[2], "w", stdout);
	for (int i = 1; i <= 2 * n; ++i)
		a[i] = i;
	for (int i = 1; i <= n; ++i)
		b[i] = 0;
	for (int i = n + 1; i <= 2 * n; ++i)
		b[i] = 1;
	per(a, 2 * n);
	per(b, 2 * n);
	printf("%d\n", 2 * n);
	int cur = 0;
	for (int i = 1; i <= 2 * n; ++i)
	{
		printf("%d ", b[i]);
		if (b[i] == 0)
		{
			int x = min(a[cur + 1], a[cur + 2]);
			int y = max(a[cur + 1], a[cur + 2]);
			cur += 2;
			printf("%d %d %d\n", x, y, rand() % 1000);
		}
		else
		{
			printf("%d %d\n", rand() % (2 * n) + 1, rand() % 200);
		}
	}
	fflush(stdout);
}