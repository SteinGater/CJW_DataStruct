// cjwc+.cpp : 定义控制台应用程序的入口点。
#include "stdafx.h"

//数据结构常用底层
#include "JWStack.h"
#include "JWQQueue.h"
#include "JWBiTree.h"
#include "JWGraph.h"
#include "JWSqList.h"

using namespace std;

int tifa(char s)
{
	printf("%c\t",s);
	return 1;
}

int mycreate(char &mychar)
{
	cin>>mychar;
	printf("\n");
	if((mychar==',')||(mychar=='.'))
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

int mydisplay(char &mydis)
{
	printf("%c\t",mydis);
	return 1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	char task;//任务选择标志
	while(1)
	{	
		printf("请输入测试需要（L：排序；T：二叉树；G：图；其他结束程序）：");
		cin>>task;
	/*****************************************排序的测试程序************************************/
		if(task=='L')
		{
			JWSqList<char> ceshi;
			printf("是否自己输入排序值?(Y or N)：");
			cin>>task;
			if(task=='Y')
			{
				ceshi.SqListCreate(mycreate);
			}
			ceshi.SqDisplay(tifa);
			printf("选择排序方式（M冒泡，S选择，I插入，Q快速：");
			cin>>task;
			if(task=='M')
			{
				printf("冒泡排序排序之后\n");
				ceshi.MSort(1,ceshi.GetLength());
			}
			else if(task=='S')
			{
				printf("选择排序排序之后\n");
				ceshi.SelectSort(1,ceshi.GetLength());
			}
			else if(task=='I')
			{
				printf("插入排序排序之后\n");
				ceshi.InsetSort(1,ceshi.GetLength());
			}
			else if(task=='M')
			{
				printf("快速排序排序之后\n");
				ceshi.QSort(1,ceshi.GetLength());
			}
			ceshi.SqDisplay(tifa);
		}
	/******************************************树的测试程序************************************/
		else if(task=='T')
		{
			JWBiTree<char> ceshi;
			struct Binode<char> *ceshiBi;
			printf("是否自己输入图?(Y or N)：");
			cin>>task;
			if(task=='Y')
			{
				ceshi.BiTreeCreate(mycreate);
			}
			printf("广度遍历：");
			ceshi.PreOrderTrans(tifa);
			printf("\n");

			printf("深度递推先序遍历：");
			ceshi.GetBiTop(ceshiBi);
			ceshi.PreOrderTravers(tifa,ceshiBi);
			printf("\n");

			printf("深度非递推先序遍历：");
			ceshi.PreOrderTra(tifa);
			printf("\n");

			printf("深度非递推后序遍历：");
			ceshi.PostOrderTra(tifa);
			printf("\n");
		}
	/******************************************图的测试程序************************************/
		else if(task=='G')
		{
			JWGraph<char> ceshi;
			printf("是否自己输入图?(Y or N)：");
			cin>>task;
			if(task=='Y')
			{
				printf("是否使用链表输入?(Y or N)否为链接矩阵：");
				cin>>task;
				if(task=='Y')
				{
					ceshi.CreateDG(mycreate);
				}
				else
				{
					ceshi.ALCreateDG(mycreate);
				}
			}
			ceshi.DispalyGraph(tifa);
			ceshi.TopologicalSort();

			int start_time,end_time;
			int duration;
			start_time=GetTickCount();
			for(int sg=0;sg<1000;sg++)
			{
			ceshi.ShortestPath_DIJ();
			}
			end_time=GetTickCount();
			duration=(end_time-start_time);
			printf("迪杰斯特计算时间：%d\n",duration);

			start_time=GetTickCount();
			for(int sg=0;sg<1000;sg++)
			{
			ceshi.ShortestPath_FLOYD();
			}
			end_time=GetTickCount();
			duration=(end_time-start_time);
			printf("佛罗伊德计算时间：%d\n",duration);

			int a,b;
			printf("得到xy顶点的距离：");
			cin>>a>>b;
			ceshi.GetShortPath(a,b);
		}
	/********************************************  错误代码************************************/
		else
		{
			break;
		}
	}
	return 0;
}

