//分治法实现归并排序
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//注意边界问题
void merge(int *a, int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;
	
	//多出来的一个放无穷大，简化实现
	int *L = (int *)malloc((n1 + 1) * sizeof(int));
	int *R = (int *)malloc((n2 + 1) * sizeof(int));
	
	for(int i = 0; i < n1; i++)
	{
		L[i] = a[p + i];
	}
	for(int j = 0; j < n2; j++)
	{
		R[j] = a[q + 1 + j];
	}
	L[n1] = INT_MAX;
	R[n2] = INT_MAX;
	
	int i = 0;
	int j = 0;
	for(int k = p; k <= r; k++)
	{
		if(L[i] < R[j])
		{
			a[k] = L[i++];
		}
		else
		{
			a[k] = R[j++];
		}
	}
}

//q、r为数组下标
void merge_sort(int *a, int p, int r)
{
	if(p != r)
	{
		int q = (p + r) / 2;
		
		merge_sort(a, p ,q);
		merge_sort(a, q + 1, r);
		merge(a, p, q, r);
	}
}

int main()
{
	printf("输入排序个数：");
	int n;
	scanf("%d",&n);
	
	int *a = (int *)malloc(n * sizeof(int));
	printf("输入要排序的数字：");
	for(int i = 0; i < n; i++)
	{
		scanf("%d",&a[i]);
	}
	
	merge_sort(a, 0, n - 1);
	
	for(int i = 0; i < n; i++)
	{
		printf("%d ",a[i]);
	}
	return 0;
}

