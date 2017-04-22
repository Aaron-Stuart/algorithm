#include <stdio.h>

typedef struct result
{
	int low;
	int high;
	int sum;
}result;

result max;	//全局变量，存a[0]到a[i-1]的最大子数组

void find_max_subarray(int *a, int len)
{
	//从左到右遍历数组，最大子数组有两种可能：以a[i]结尾或a[0]到a[i-1]的最大子数组（类似递归）
	for(int i = 0; i < len; i++)
	{
		if(i == 0)
		{
			max.low = i;
			max.high = i;
			max.sum = a[i];
		}
		else
		{
			int sum = 0;
			for(int j = i; j != 0; j--)
			{
				sum += a[j];
				if(sum > max.sum)
				{
					max.sum = sum;
					max.low = j;
					max.high = i;
				}
			}
		}
	}
}
int main()
{
	int a[16] = {13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7};
	find_max_subarray(a, 16);
	printf("low = %d, high = %d, max = %d\n",max.low, max.high, max.sum);
	return 0;
}
