#include <stdio.h>

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int partion(int *a, int begin, int end)
{
	int median = a[end];	//选最后一个元素为中值
	int i = begin - 1;		//i为小于中值的区域的最大下标
	for(int j = begin; j < end; j++)
	{
		if(a[j] < median)	//j找到了一个小于中值的元素
		{
			i++;	//向右侵蚀一个元素
			swap(&a[i], &a[j]);	//把j找到的元素交换到侵蚀位置
		}
	}
	swap(&a[i + 1], &a[end]);	//把中值交换到两个区域中间
	return i + 1;				//返回中值索引
}

void quick_sort(int *a, int begin, int end)
{
	if(begin < end)
	{
		int index = partion(a, begin, end);	//选一个元素作为中值
		quick_sort(a, begin, index - 1);
		quick_sort(a, index + 1, end);
	}
}

int main()
{
	int a[5] = {5,6,7,9,2};
	quick_sort(a, 0, 4);
	for(int i = 0; i < 5; i++)
	{
		printf("%d ",a[i]);
	}
	putchar('\n');
	return 0;
}
