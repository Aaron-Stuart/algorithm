#include <stdio.h>

#define N 3	//盘子数目

void change(int n, char source, char destination, char helper)
{
	if(n == 1)
	{
		printf("%c -> %c\n", source, destination);
	}
	else
	{
		change(n-1, source, helper, destination);
		printf("%c -> %c\n", source, destination);
		change(n-1, helper, destination, source);
	}
}

int main()
{
	char A = 'A',B = 'B',C = 'C';	//ABC三个柱子
	
	change(N,A,C,B);
	
	return 0;
}
