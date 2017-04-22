//A*算法（启发式搜索）解决八数码问题
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory.h>

int Target[3][3] = {
	{1,2,3},
	{8,0,4},
	{7,6,5}
};

typedef struct Node{
	int panel[3][3];	//八数码状态
	int row,col;		//空白所在行列
	int g,f;			//代价
	struct Node *parent;
	struct Node *next;
}Node;

Node *OPEN = NULL;
Node *CLOSED = NULL;

//判断是不是目标状态
int isGoal(Node *n)
{
	int flag = 1;
	
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(n->panel[i][j] != Target[i][j])
			{
				flag = 0;
			}
		}
	}
	return flag;
}

//移动空白到row col位置,返回移动后的节点(注意未完全初始化，只修改了panel row col)
Node *move(Node *n, int row, int col)
{
	//不可破坏父节点状态，返回新建的节点
	Node *tempNode = (Node *)malloc(sizeof(Node));
	memcpy(tempNode->panel, n->panel, sizeof(int) * 9);
	//移动空白
	tempNode->panel[row][col] = n->panel[n->row][n->col];
	tempNode->panel[n->row][n->col] = 0;
	tempNode->row = row;
	tempNode->col = col;
	
	return tempNode;
}

//判断是两节点panel状态是否相同
int equal(Node *n1, Node *n2)
{
	int flag = 1;
	
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(n1->panel[i][j] != n2->panel[i][j])
			{
				flag = 0;
			}
		}
	}
	return flag;
}

//判断当前节点n是不是其父节点father的父节点
int isGrandParent(Node *n, Node *parent)
{
	int flag = 0;
	while(parent)
	{
		if(!equal(n, parent))
		{
			//不断上溯判断
			parent = parent->parent;
			continue;
		}
		else
		{
			flag = 1;
			break;
		}
	}
	return flag;
}

//计算当前节点到目的节点的代价
int H(Node *n)
{
	//此处的代价定义为两状态中不同的数码个数
	int count = 0;
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(n->panel[i][j] != Target[i][j])
			{
				count++;
			}
		}
	}
	return count;
}

//扩展节点，返回后继节点的链表
Node *extent(Node * n)
{
	Node *subNodeList;	//要返回的后继节点链表，每次在表头插入
	for(int row = -1; row <= 1; row++)
	{
		for(int col = -1; col <= 1; col++)
		{
			//保证空白只能上下左右移动
			if(row == 0 && col ==0)
			{
				continue;
			}
			if(row != 0 && col != 0)
			{
				continue;
			}
			
			//移动后行列数
			int row1 = n->row + row;
			int col1 = n->col + col;
			if(row1 < 0 || row1 > 2 || col1 < 0 || col1 > 2)
			{
				//保证移动后位置合法
				continue;
			}
			
			Node *next = move(n, row1, col1);	//移动空白到row1 col1
			if(isGrandParent(next, n))
			{
				//如果是回到上一步，则放弃此移动
				free(next);
				continue;
			}
			next->parent = n;
			next->g = n->g + 1;				//g代价增加1
			next->f = next->g + H(next);	//计算f代价
			next->next = subNodeList;
			subNodeList = next;				//在表头插入
		}
	}
	return subNodeList;
}

//判断节点n是否在list中，如果在就返回它的指针
Node *in(Node *n, Node *list)
{
	int flag = 1;
	while(list)
	{
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				if(n->panel[i][j] != list->panel[i][j])
				{
					flag = 0;
				}
			}
		}
		if(flag == 1)//如果在表内
		{
			break;
		}
		else
		{
			list = list->next;
		}
	}
	return list;
}

//把节点n加入OPEN表（按f值从小到大）,返回OPEN表
Node *addToOpen(Node *n, Node *open)
{
	if(!open)
	{
		open = n;
		n->next = NULL;
	}
	else
	{
		if(n->f < open->f)
		{
			//插入到表头
			n->next = open->next;
			open = n;
		}
		else
		{
			//注意不可直接移动OPEN
			//temp1指向temp2前一个元素
			Node *temp1 = open;
			Node *temp2 = temp1->next;
			while(temp2)
			{
				if(n->f < temp2->f)
				{
					break;
				}
				else
				{
					temp1 = temp2;
					temp2 = temp2->next;
				}
			}
			if(!temp2)
			{
				//插在表尾
				temp1 = n;
				n->next = NULL;
			}
			else
			{
				temp1 = n;
				n->next = temp2;
			}
		}
	}
	return open;
}

//把节点n放入CLOSED表
Node *addToClosed(Node *n, Node *closed)
{
	//插入到表头
	n->next = closed;
	closed = n;
	return closed;
}

//从表中删除节点
Node *del(Node *n, Node *list)
{
	if(equal(n, list))
	{
		//如果在表头
		Node *temp = list;
		list = list->next;
		free(temp);
	}
	else
	{
		Node *temp1 = list;
		Node *temp2 = temp1->next;
		while(temp2)
		{
			if(equal(n, temp2))
			{
				temp2 = temp2->next;
				free(temp1);
			}
			else
			{
				temp1 = temp2;
				temp2 = temp2->next;
			}
		}
	}
	return list;
}


Node *createNode(int a[][3])
{
	Node *root = (Node *)malloc(sizeof(Node));
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(a[i][j] == 0)
			{
				root->row = i;
				root->col = j;
			}
			root->panel[i][j] = a[i][j];
		}
	}
	
	root->g = 0;
	root->f = 0;
	root->parent = NULL;
	root->next = NULL;
	
	return root;
}
//输出结点
void printNode(Node *n)
{
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			printf("%d ", n->panel[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

//输出路径
void printPath(Node *n)
{
	if(!n)
	{
		return;
	}
	else
	{
		//从底向上递归
		printPath(n->parent);
		printNode(n);
	}
}

Node *A_Star(Node *root)
{
	OPEN = root;	//开始节点放入OPEN表
	
	while(OPEN)		//OPEN不空
	{
		
		Node *n = OPEN;	//从OPEN选取第一个节点
		if(isGoal(n))
		{
			return n;
		}
		
		CLOSED = addToClosed(n, CLOSED);
		//扩展best节点
		Node *subNodeList = extent(n);
		
		while(subNodeList)
		{
			Node *m = subNodeList;	//取第一个后继节点
			subNodeList = subNodeList->next;
			
			Node *pNode = NULL;
			if(pNode = in(m, OPEN))	//这里有问题，segment fault
			{
				
				//如果该后继节点n已存在于OPEN表
				if(m->f < pNode->f)
				{
					//如果新的后继节点m的f代价较小，就删除OPEN中旧的
					OPEN = addToOpen(m, del(pNode, OPEN));
					free(pNode);
				}
			}
			else if(pNode = in(m, CLOSED))
			{
				//如果该后继节点n已存在于CLOSED表
				if(m->f < pNode->f)
				{
					//如果新的后继节点m的f代价较小，就删除CLOSED中旧的,把m放入OPEN表
					CLOSED = del(pNode, CLOSED);
					OPEN = addToOpen(m, OPEN);
					free(pNode);
				}
			}
			else
			{
				//如果该后继节点n不存在于两个表中
				OPEN = addToOpen(m, OPEN);
			}
		}
	}
	return root;	//OPEN为空返回空值
}
int main()
{
	
	int a[3][3] = {2,8,3,1,0,4,7,6,5};
	Node *root = createNode(a);
	
	Node *s = A_Star(root);
	if(s)
	{
		printPath(s);
		printf("\n");
	}
	else
	{
		printf("无解\n");
	}
	return 0;
}
