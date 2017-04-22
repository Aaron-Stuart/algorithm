//分治法解最大子数组问题
#include <stdio.h>
#include <limits.h>

typedef struct result
{
	int low;
	int high;
	int sum;
}result;

result max(result r1, result r2, result r3)
{
	result max = r1;
	if(r2.sum > max.sum)
		max = r2;
	if(r3.sum > max.sum)
		max = r3;
	return max;
}

//寻找跨越中点的最大子数组
result find_max_cross_subarray(int *a, int low, int mid, int high)
{
	//找到中点左边的最大子数组
	int max_left;
	int left_sum = INT_MIN;
	int sum1 = 0;
	for(int i = mid; i != low; i--)
	{
		sum1 += a[i];
		if(sum1 > left_sum)
		{
			left_sum = sum1;
			max_left = i;
		}
	}
	
	//找到中点右边的最大子数组
	int max_right;
	int right_sum = INT_MIN;
	int sum2 = 0; 
	for(int i = mid + 1; i != high; i++)
	{
		sum2 += a[i];
		if(sum2 > right_sum)
		{
			right_sum = sum2;
			max_right = i;
		}
	}
	
	//左右合并为跨越中点的最大子数组
	result max;
	max.low = max_left;
	max.high = max_right;
	max.sum = left_sum + right_sum;
	
	return max;
}

//寻找最大子数组，分三种情况：中点左边，中点右边，跨越中点
result find_max_subarray(int *a, int low, int high)
{
	if(low == high)
	{
		result r1;
		r1.low = low;
		r1.high = high;
		r1.sum = a[low];
		return r1;
	}
	else
	{
		int mid = (low + high) / 2;
		
		result r2;
		r2 = find_max_subarray(a, low, mid);
		
		result r3;
		r3 = find_max_subarray(a, mid + 1, high);
		
		result r4;
		r4 = find_max_cross_subarray(a, low, mid, high);
		
		return max(r2, r3, r4);
	}
}
int main()
{
	int a[16] = {13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7};
	result max = find_max_subarray(a, 0, 15);
	printf("low = %d, high = %d, max = %d\n",max.low, max.high, max.sum);
	return 0;
}
