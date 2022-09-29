// cjwc+.cpp : �������̨Ӧ�ó������ڵ㡣
#include "stdafx.h"

//���ݽṹ���õײ�
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
	char task;//����ѡ���־
	while(1)
	{	
		printf("�����������Ҫ��L������T����������G��ͼ�������������򣩣�");
		cin>>task;
	/*****************************************����Ĳ��Գ���************************************/
		if(task=='L')
		{
			JWSqList<char> ceshi;
			printf("�Ƿ��Լ���������ֵ?(Y or N)��");
			cin>>task;
			if(task=='Y')
			{
				ceshi.SqListCreate(mycreate);
			}
			ceshi.SqDisplay(tifa);
			printf("ѡ������ʽ��Mð�ݣ�Sѡ��I���룬Q���٣�");
			cin>>task;
			if(task=='M')
			{
				printf("ð����������֮��\n");
				ceshi.MSort(1,ceshi.GetLength());
			}
			else if(task=='S')
			{
				printf("ѡ����������֮��\n");
				ceshi.SelectSort(1,ceshi.GetLength());
			}
			else if(task=='I')
			{
				printf("������������֮��\n");
				ceshi.InsetSort(1,ceshi.GetLength());
			}
			else if(task=='M')
			{
				printf("������������֮��\n");
				ceshi.QSort(1,ceshi.GetLength());
			}
			ceshi.SqDisplay(tifa);
		}
	/******************************************���Ĳ��Գ���************************************/
		else if(task=='T')
		{
			JWBiTree<char> ceshi;
			struct Binode<char> *ceshiBi;
			printf("�Ƿ��Լ�����ͼ?(Y or N)��");
			cin>>task;
			if(task=='Y')
			{
				ceshi.BiTreeCreate(mycreate);
			}
			printf("��ȱ�����");
			ceshi.PreOrderTrans(tifa);
			printf("\n");

			printf("��ȵ������������");
			ceshi.GetBiTop(ceshiBi);
			ceshi.PreOrderTravers(tifa,ceshiBi);
			printf("\n");

			printf("��ȷǵ������������");
			ceshi.PreOrderTra(tifa);
			printf("\n");

			printf("��ȷǵ��ƺ��������");
			ceshi.PostOrderTra(tifa);
			printf("\n");
		}
	/******************************************ͼ�Ĳ��Գ���************************************/
		else if(task=='G')
		{
			JWGraph<char> ceshi;
			printf("�Ƿ��Լ�����ͼ?(Y or N)��");
			cin>>task;
			if(task=='Y')
			{
				printf("�Ƿ�ʹ����������?(Y or N)��Ϊ���Ӿ���");
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
			printf("�Ͻ�˹�ؼ���ʱ�䣺%d\n",duration);

			start_time=GetTickCount();
			for(int sg=0;sg<1000;sg++)
			{
			ceshi.ShortestPath_FLOYD();
			}
			end_time=GetTickCount();
			duration=(end_time-start_time);
			printf("�������¼���ʱ�䣺%d\n",duration);

			int a,b;
			printf("�õ�xy����ľ��룺");
			cin>>a>>b;
			ceshi.GetShortPath(a,b);
		}
	/********************************************  �������************************************/
		else
		{
			break;
		}
	}
	return 0;
}

