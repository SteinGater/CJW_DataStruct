#pragma once
//图与表类模板（邻接表存贮方式图）

/******************定义变量*********************/
#define DG  0     //有向图
#define DN  1     //有向网
#define UDG  2     //无向图
#define UDN  3     //无向网
#define MAXnode 30 //最大的节点个数
#define INF     1000  //无穷大代替值

/************************************************************************
结构体：图单位关系表结构体
	int advjex;							该条关系式末端指向的位置
	struct Arcnode<Types>  *nextarc;	指向下一条关系式同起始端的关系式的位置；
	double info;						该关系式的信息
  ***********************************************************************/
template<class Types> struct Arcnode
{
	int advjex;   //该条关系式末端指向的位置
	struct Arcnode<Types>  *nextarc;//指向下一条关系式同起始端的关系式的位置；
	double info; //该关系式的信息
};

/************************************************************************
结构体：定点信息结构体
	Types data;								顶点数据
	struct Arcnode<Types>  *firstarc;		第一条关系式
  ***********************************************************************/
template<class Types> struct Vnode
{
	Types data;
	struct Arcnode<Types>  *firstarc;//第一条关系式
};

/************************************************************************
类模板：堆栈类模板
	数据：
	struct Vnode<Type>  vertices[MAXnode];			顶点使用数组存储
	int    vexnum,arcnum;							图当前的a定点数和a关系数
	int    kind;									图的种类
	bool   visit_state[MAXnode];					访问标志位
	函数：
	int CreateDG(int(* creat)(Type &mem));								构造有相图
																		参数：creat ：输入单个元素函数
																		返回值：是否成功（1）
	int DFStraverse(int(* visit)(Type e));								深度遍历使用函数
																		参数：visit：遍历函数
																		返回值：是否成功（1）
	int BFStraverse(int(* visit)(Type e));								广度遍历使用函数
																		参数：visit：遍历函数
																		返回值：是否成功（1）
  ***********************************************************************/
template<class Type>  class JWGraph
{
public:
	JWGraph(void);
	~JWGraph(void);
	int CreateDG(int(* creat)(Type &mem));     //构造有相图(链表输入法)
	int ALCreateDG(int(* creat)(Type &mem));     //构造有相图(邻接矩阵输入法）

	int DispalyGraph(int(* dispaly)(Type mem));	//显示数组

	int DFStraverse(int(* visit)(Type e));     //深度遍历使用函数
	int BFStraverse(int(* visit)(Type e));     //广度遍历使用函数

	//int MiniSpanTree_PRIM(struct Binode<Type> * &GT);//用普利姆算法构造最小生成树
	//int MiniSpanTree_KLS(struct Binode<Type> * &GT);//用克鲁斯卡尔算法构造最小生成树

	int ShortestPath_DIJ(void);					//顶点Vnode到各个顶点的最短路径
	int ShortestPath_FLOYD(void);				//任意两个顶点的最短距离
	int GetShortPath(int start,int end);		//得到两点最短路径

	int TopologicalSort(void);					//拓扑排序
protected:
	int DFS (int gnumber,int(* visit)(Type e));//递推函数
	int Inits(void);								//清楚原先数据

private:
	struct Vnode<Type>  vertices[MAXnode];	//顶点使用数组存储	
	int    vexnum,arcnum;					//图当前的a定点数和a关系数
	int    kind;							//图的种类
	double ALGraph[MAXnode][MAXnode];		//邻接数组存储
	bool   visit_state[MAXnode];			//访问标志位
	double distance[MAXnode][MAXnode];		//從a到b的最短路径值
	int    lpath[MAXnode][MAXnode][MAXnode];//從a到b的最短路徑
	int	   fcount[MAXnode];					//前置点个数
};

/********************函数定义*********************************************/
template<class Type> JWGraph<Type>::JWGraph(void)
{
	vexnum=0;
	arcnum=0;
	kind=0;
	for(int s=0;s<MAXnode;s++)
	{
		vertices[s].data=NULL;
		vertices[s].firstarc=NULL;
		visit_state[s]=0;
		for(int t=0;t<MAXnode;t++)
		{
			ALGraph[s][t]=0;
			distance[s][t]=0;
			for(int m=0;m<MAXnode;m++)
			{
				lpath[s][t][m]=0;
			}
		}
	}

	//内置矩阵
	struct Arcnode<Type> *V,*VN;
	vexnum=20;

	for(int s=0;s<vexnum;s++)
	{
		vertices[s].data=(char)(65+s);
		vertices[s].firstarc=NULL;
	}

	for(int s=0;s<vexnum;s++)
	{
		int time=0;//第一次临时变量
		for(int t=0;t<vexnum;t++)
		{
			if(s!=t)
			{
				ALGraph[s][t]=rand()%10;
			}
			else
			{
				ALGraph[s][t]=0;
			}
			if(ALGraph[s][t]!=0)
			{
				VN=(struct Arcnode<Type> *)malloc(sizeof(struct Arcnode<Type>*));
				VN->advjex=t;
				VN->info=ALGraph[s][t];
				VN->nextarc=NULL;
				if(time>0)
				{
					V->nextarc=VN;
				}
				else
				{
					vertices[s].firstarc=VN;
					time=1;
				}
				V=VN;
				arcnum++;
			}
		}
	}
}

template<class Type> JWGraph<Type>::~JWGraph(void)
{
	Inits();
}

template<class Type> int JWGraph<Type>::Inits(void)
{
	struct Arcnode<Type> *initenceA,*initenceB;
	for(int s=0;s<vexnum;s++)				//数据初始化
	{
		vertices[s].data=NULL;
		vertices[s].firstarc=NULL;
		visit_state[s]=0;
		fcount[s]=0;
		for(int t=0;t<MAXnode;t++)
		{
			ALGraph[s][t]=0;
			distance[s][t]=0;
			for(int m=0;m<MAXnode;m++)
			{
				lpath[s][t][m]=0;
			}
		}
	}
	for(int s=0;s<vexnum;s++)						//	邻接矩阵初始化
	{
		vertices[s].data=NULL;
		initenceA=vertices[s].firstarc;
		vertices[s].firstarc=NULL;
		initenceB=vertices[s].firstarc;
		while(initenceB!=NULL)
		{				
			free(initenceA);
			initenceA=initenceB;
			initenceB=initenceA->nextarc;
		}
	}

	vexnum=0;
	arcnum=0;
	kind=0;

	return 1;
}

template<class Type> int JWGraph<Type>::DispalyGraph(int(* display)(Type mem))	//显示数组
{
	printf("已经输入图如下：\n");
	printf("图的顶点如下：\n");
	for(int s=0;s<vexnum;s++)						//	顶点显示
	{
		display(vertices[s].data);
	}
	printf("\n邻接矩阵如下：\n");
	for(int s=0;s<vexnum;s++)						//	邻接矩阵显示
	{
		for(int t=0;t<vexnum;t++)
		{
			printf("%g\t",ALGraph[s][t]);
		}
		printf("\n");
	}
	return 1;
}

template<class Type> int JWGraph<Type>::CreateDG(int(* creat)(Type &mem))
{
	//采用邻接表表示
	int Vnumber=0,linknum=1,link=0;;
	struct Arcnode<Type> *V,*VN;
	kind=DG;

	Inits();//清楚旧的数据

	printf("链表输入法\n");

	printf("请输入第%d个顶点元素 ",Vnumber+1);
	while(!creat(vertices[Vnumber].data)) 
	{
		++Vnumber;
		printf("请输入第%d个顶点元素 ",Vnumber+1);
	}

	vexnum=Vnumber;

	for(Vnumber=0;Vnumber<vexnum;Vnumber++)
	{
		V=vertices[Vnumber].firstarc;
		vertices[Vnumber].firstarc=NULL;
		link=0;

		printf("请输入以%d的顶点为出发点的关系式（空格结束）：\n",Vnumber+1);
		while(1)
		{
			printf("请输入下一个目标元素所在存储位置 （同个位置结束）");
			cin>>linknum;

			if(linknum==Vnumber+1) break;

			arcnum++;				//记录关系是
			VN=(struct Arcnode<Type> *)malloc(sizeof(struct Arcnode<Type>*));
			printf("请输入该关系权重");
			cin>>(VN->info);

			ALGraph[Vnumber][linknum-1]=VN->info;			//邻接数组存取

			if(link==1)										
			{
				V->nextarc=VN;
			}
			else											//第一次化处理
			{
				vertices[Vnumber].firstarc=VN;
			}

			VN->advjex=linknum-1;
			V=VN;
			VN->nextarc=NULL;
			link=1;
			arcnum++;
		}

	}

	return 1;
}

template<class Type> int JWGraph<Type>::ALCreateDG(int(* creat)(Type &mem))
{
	struct Arcnode<Type> *V,*VN;

	Inits();//清楚旧的数据

	printf("矩阵输入法\n");

	printf("请输入第%d个顶点元素 （逗号结束）",vexnum+1);
	while(!creat(vertices[vexnum].data)) 
	{
		vertices[vexnum].firstarc=NULL;
		++vexnum;
		printf("请输入第%d个顶点元素 （逗号结束）",vexnum+1);
	}

	for(int s=0;s<vexnum;s++)
	{
		printf("请输入第%d行邻接矩阵，顶点元素 （空格间隔，回撤结束）",s+1);
		int time=0;//第一次临时变量
		for(int t=0;t<vexnum;t++)
		{
			cin>>ALGraph[s][t];
			if(ALGraph[s][t]!=0)
			{
				VN=(struct Arcnode<Type> *)malloc(sizeof(struct Arcnode<Type>*));
				VN->advjex=t;
				VN->info=ALGraph[s][t];
				VN->nextarc=NULL;
				if(time>0)
				{
					V->nextarc=VN;
				}
				else
				{
					vertices[s].firstarc=VN;
					time=1;
				}
				V=VN;
				arcnum++;
			}
		}
		cout<<"\n";
	}
	return 1;
}

template<class Type> int JWGraph<Type>::BFStraverse(int(* visit)(Type e))		 //广度遍历使用函数
{
	struct Arcnode<Type>  *nowline;
	int nownode;
	JWQQueue<int> QGraph;

	for(int i=0;i<vexnum;i++)											//初始化状态数组
	{
		visit_state[i]=0;
	}
	for(int i=0;i<vexnum;i++)											//广度遍历
	{
		if(visit_state[i]==0)
		{
			visit(vertices[i].data);
			visit_state[i]=1;

			QGraph.EnQueue(i);			//压入栈

			while(QGraph.QueueLength()!=0)
			{
				QGraph.DeQueue(nownode);
				nowline=vertices[nownode].firstarc;			//记录开始点

				while(nowline!=NULL)
				{
					if(visit_state[nowline->advjex]==0)
					{
						visit(vertices[nowline->advjex].data);
						visit_state[nowline->advjex]=1;
						QGraph.EnQueue(nowline->advjex);
					}
					nowline=nowline->nextarc;
				}
			}
		}
	}
	return 1;
}

template<class Type> int JWGraph<Type>::DFStraverse(int(* visit)(Type e))		 //深度遍历使用函数
{
	for(int i=0;i<vexnum;i++)											//初始化状态数组
	{
		visit_state[i]=0;
	}
	for(int i=0;i<vexnum;i++)											//进入遍历
	{
		if(visit_state[i]==0)
		{
			DFS(i,visit);
		}
	}
	return 1;
}

template<class Type> int JWGraph<Type>::DFS(int gnumber,int(* visit)(Type e))		 //深度遍历使用函数
{
	struct Arcnode<Type>  *nowline;

	visit(vertices[gnumber].data);
	visit_state[gnumber]=1;

	nowline=vertices[gnumber].firstarc;

	while(nowline!=NULL)
	{
		if(visit_state[nowline->advjex]==0)
		{
			DFS(nowline->advjex,visit);
		}
		nowline=nowline->nextarc;
	}
	return 1;
}

template<class Type> int JWGraph<Type>::ShortestPath_DIJ(void)			//顶点Vnode到各个顶点的最短路径
{
	//一次第杰斯拉特算法
	for(int s=0;s<vexnum;s++)				
	{
		//初始化距离
		for(int t=0;t<vexnum;t++)
		{
			visit_state[t]=0;
			distance[s][t]=ALGraph[s][t];
			for(int m=0;m<vexnum;m++)
			{
				lpath[s][t][m]=0;
			}
			if(distance[s][t]==0)
			{
				distance[s][t]=INF;
			}
			lpath[s][t][0]=s+1;
		}
		//第一个点数据集合
		distance[s][s]=INF;
		visit_state[s]=1;
		lpath[s][s][1]=0;
		//开始求最短距离，不停求解最短距离
		int nowminnode=s;
		for(int tG=1;tG<vexnum;tG++)
		{	
			double min = INF;
			for(int w=0;w<vexnum;w++)
			{
				if(!visit_state[w])
				{
					if(distance[s][w]<min)
					{
						nowminnode=w;
						min=distance[s][w];
					}
				}
			}
			visit_state[nowminnode]=1;//加入最近点；
			int line=0;
			for(int w=0;w<vexnum;w++)//刷新坐标
			{
				if((!visit_state[w])&&(min+ALGraph[nowminnode][w]<distance[s][w])&&(ALGraph[nowminnode][w]!=0))
				{
					distance[s][w]=min+ALGraph[nowminnode][w];
					line=0;
					while(lpath[s][nowminnode][line]!=0) 
					{
						lpath[s][w][line]=lpath[s][nowminnode][line];
						line++;
					}
					lpath[s][w][line]=nowminnode+1;
				}
			}
		}
		for(int tG=0;tG<vexnum;tG++)
		{
			int line=0;
			while(distance[s][tG]<INF)
			{
				if(lpath[s][tG][line]==0)
				{
					lpath[s][tG][line]=tG+1;
					break;
				}
				line++;
			}
		}
	}
	return 1;
}

template<class Type> int JWGraph<Type>::ShortestPath_FLOYD(void)				//任意两个顶点的最短距离
{
	//对节点初始化
	for(int s=0;s<vexnum;s++)				
	{
		for(int t=0;t<vexnum;t++)				
		{
			distance[s][t]=ALGraph[s][t];
			for(int m=0;m<vexnum;m++)
			{
				lpath[s][t][m]=0;
			}
			if(distance[s][t]==0)
			{
				distance[s][t]=INF;
			}
			lpath[s][t][0]=s+1;
		}
	}
	for(int m=0;m<vexnum;m++)				
	{
		for(int s=0;s<vexnum;s++)				
		{
			for(int t=0;t<vexnum;t++)				
			{
				if(distance[s][m]+distance[m][t]<distance[s][t])
				{
					distance[s][t]=distance[s][m]+distance[m][t];
					int line1=0,line2;
				    for(line1=0;lpath[s][m][line1];line1++)				
					{
						lpath[s][t][line1]=lpath[s][m][line1];
					}
					for(line2=0;lpath[m][t][line2];line1++,line2++)				
					{
						lpath[s][t][line1]=lpath[m][t][line2];
					}
				}
			}
		}
	}
	for(int s=0;s<vexnum;s++)
	{
		for(int t=0;t<vexnum;t++)
		{
			int line=0;
			while(distance[s][t]<INF)
			{
				if(lpath[s][t][line]==0)
				{
					lpath[s][t][line]=t+1;
					break;
				}
				line++;
			}
		}
	}
	return 1;
}

template<class Type> int JWGraph<Type>::GetShortPath(int start,int end)		//得到两点最短路径
{
	if(lpath[start-1][end-1][1]==0)
	{
		printf("从%d点到%d点到达不了\n",start,end);	
		return 0;
	}
	printf("从%d点到%d点的最短路径的距离为：%f\n",start,end,distance[start-1][end-1]);
	int t=0;
	printf("从%d点到%d点的最短路径为:",start,end);
	while(1)
	{
		printf("%d\t",lpath[start-1][end-1][t]);
		t++;
		if(lpath[start-1][end-1][t]==0)
		{
			printf("\n");	
			break;
		}
	}
	return 1;
}

template<class Type> int JWGraph<Type>::TopologicalSort(void)
{
	int e=0,e_f=0;//0度链表的标头和表尾巴
	//计算顶点的度
	for(int n=0;n<vexnum;n++)				
	{
		visit_state[n]=0;
		fcount[n]=0;
		for(int m=0;m<vexnum;m++)				
		{
			if(ALGraph[m][n]!=0)
			{
				fcount[n]++;
			}
		}
	}
	//形成的0度链表
	for(int n=0,ecount=0;n<vexnum;n++)				
	{
		if(fcount[n]==0)	
		{
			if(ecount>0)
			{
				fcount[n]=e_f;
			}
			else
			{
				e=n;
				ecount=1;
			}
			e_f=n;
		}
	}
	printf("拓展排序如下:");
	for(int ecount=0;(fcount[e])||(!visit_state[e]);)				
	{
		printf("%d\t",e+1);
		visit_state[e]=1;
		for(int t=0;t<vexnum;t++)
		{
			if(ALGraph[e][t]!=0)
			{
				fcount[t]--;
				if(fcount[t]==0)
				{
					fcount[e_f]=t;
					e_f=t;
				}
			}
		}
		ecount=e;
		e=fcount[e];
		fcount[ecount]=0;
	}
	return 1;
}