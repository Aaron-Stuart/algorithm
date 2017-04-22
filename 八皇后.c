//递归解决八皇后
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#define N 8		//皇后个数

int record[N];	//用来记录已放置棋子的列坐标
int counter = 0; //统计情况数

void print()
{
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			if(j == record[i])
				printf("1 ");
			else
				printf("0 ");
		}
		printf("\n");
	}
	printf("\n");
}

void place(int row)
{
	if(row == N)
	{
		counter++;
		print();
		return;
	}
	
	for(int col = 0; col < N; col++)
	{
		
		record[row] = col;	//记下位置
		
		bool can_place = true;
		for(int i = 0; i < row; i++)
		{
			if(col == record[i] || (fabs(row - i) == fabs(col - record[i])))
			{
				can_place = false;
				break;
			}
		}
		
		if(can_place)
		{
			place(row + 1);
		}
	}
}

int main()
{
	
	place(0);
	
	printf("%d\n",counter);
	
	return 0;
}
