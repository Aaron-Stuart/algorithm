//最大堆
#include <stdio.h>

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

//用于维护最大堆的性质,len是数组长度
void max_heapify(int *a, int len, int i)
{
	int left = 2 * i;	//左儿子
	int right = 2 * i + 1;	//右儿子
	int largest;	//三者取最大
	
	if(left < len && a[left] > a[i])
	{
		largest = left;
	}
	else
	{
		largest = i;
	}
	if(right < len && a[right] > a[largest])
	{
		largest = right;
	}
	
	//把根节点和最大的调换，再递归维护子堆
	if(largest != i)
	{
		swap(&a[largest], &a[i]);
		max_heapify(a, len, largest);
	}
}

void build_max_heap(int *a, int len)
{
	//父节点下标为（len / 2）- 1，子数组（len / 2）+ 1..n中的元素是叶节点，对每个非叶节点维护最大堆性质就建成了最大堆
	//注意只能递减，不能递增
	for(int i = len / 2 - 1; i >= 0; i--)
	{
		max_heapify(a, len, i);
	}
}

void heap_sort(int *a, int len)
{
	//建堆
	build_max_heap(a, len);
	
	//不断将根节点和最后一个交换，再维护最大堆性质（堆长度-1）
	for(int i = len - 1; i > 0; i--)
	{
		swap(&a[0],&a[i]);
		max_heapify(a, i, 0);
	}
}

int main()
{
	int a[10] = {1,4,2,3,9,7,8,10,14,16};
	heap_sort(a, 10);
	
	for(int i = 0; i < 10; i++)
	{
		printf("%d ",a[i]);
	}
	printf("\n");
	return 0;
}
