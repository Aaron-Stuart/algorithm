#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRLEN 10
char Source[MAX_STRLEN];	//目标串
char Pattern[MAX_STRLEN];	//模式串
int Next[MAX_STRLEN];		//模式串对应的next数组

void init()
{
	printf("输入目标字符串:");
	gets(Source);
	printf("输入模式字符串:");
	gets(Pattern);
}

void buildNext(char *Pattern, int *next)
{
	int p_len = strlen(Pattern);
	int k = 1;
	int j = 0;
	next[1] = 0;
	
	while(k < p_len)
	{
		if(j == 0 || Pattern[k] == Pattern[j])
		{
			k++;
			j++;
			if(Pattern[k] != Pattern[j])
			{
				next[k] = j;
			}
			else
			{
				next[k] = next[j];
			}
		}
		else
		{
			next[j] = j;
		}
	}
}

//返回第pos个字符后，第一个模式串的位置
int KMP(char *Source, char *Pattern, int pos)
{
	int s_len = strlen(Source);
	int p_len = strlen(Pattern);
	
	int k = pos;
	int j = 0;
	while(k < s_len && j < p_len)
	{
		if(j == -1 || Source[k] == Pattern[j])
		{
			k++;
			j++;
		}
		else
		{
			j = Next[j];
		}
	}
	if(j >= p_len)
	{
		return k - p_len;
	}
	else
	{
		return -1;
	}
}

int main()
{
	init();
	buildNext("abaabcac", Next);
	for(int i = 0; i < MAX_STRLEN; i++)
	{
		printf("%d ",Next[i]);
	}
	return 0;
}
