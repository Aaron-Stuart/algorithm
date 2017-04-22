//递归实现输出全排列

#include <stdio.h>
#define N 4
int a[N];
int count = 0;

void init()
{
	for(int i = 0; i < N; i++)
	{
		a[i] = i + 1;
	}
}

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void permutation(int *a, int begin, int end)
{
	if(begin == end)
	{
		count++;
		printf("第%d种：", count);
		for(int i = 0; i < end; i++)
		{
			printf("%d ",a[i]);
		}
		printf("\n");
	}
	for(int i = begin; i < end; i++)
	{
		swap(&a[i], &a[begin]);
		permutation(a, begin + 1, end);
		swap(&a[i], &a[begin]);
	}
}

int main()
{
	init();
	permutation(a, 0, N);
}
