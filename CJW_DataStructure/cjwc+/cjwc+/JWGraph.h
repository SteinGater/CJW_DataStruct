#pragma once
//ͼ�����ģ�壨�ڽӱ������ʽͼ��

/******************�������*********************/
#define DG  0     //����ͼ
#define DN  1     //������
#define UDG  2     //����ͼ
#define UDN  3     //������
#define MAXnode 30 //���Ľڵ����
#define INF     1000  //��������ֵ

/************************************************************************
�ṹ�壺ͼ��λ��ϵ��ṹ��
	int advjex;							������ϵʽĩ��ָ���λ��
	struct Arcnode<Types>  *nextarc;	ָ����һ����ϵʽͬ��ʼ�˵Ĺ�ϵʽ��λ�ã�
	double info;						�ù�ϵʽ����Ϣ
  ***********************************************************************/
template<class Types> struct Arcnode
{
	int advjex;   //������ϵʽĩ��ָ���λ��
	struct Arcnode<Types>  *nextarc;//ָ����һ����ϵʽͬ��ʼ�˵Ĺ�ϵʽ��λ�ã�
	double info; //�ù�ϵʽ����Ϣ
};

/************************************************************************
�ṹ�壺������Ϣ�ṹ��
	Types data;								��������
	struct Arcnode<Types>  *firstarc;		��һ����ϵʽ
  ***********************************************************************/
template<class Types> struct Vnode
{
	Types data;
	struct Arcnode<Types>  *firstarc;//��һ����ϵʽ
};

/************************************************************************
��ģ�壺��ջ��ģ��
	���ݣ�
	struct Vnode<Type>  vertices[MAXnode];			����ʹ������洢
	int    vexnum,arcnum;							ͼ��ǰ��a��������a��ϵ��
	int    kind;									ͼ������
	bool   visit_state[MAXnode];					���ʱ�־λ
	������
	int CreateDG(int(* creat)(Type &mem));								��������ͼ
																		������creat �����뵥��Ԫ�غ���
																		����ֵ���Ƿ�ɹ���1��
	int DFStraverse(int(* visit)(Type e));								��ȱ���ʹ�ú���
																		������visit����������
																		����ֵ���Ƿ�ɹ���1��
	int BFStraverse(int(* visit)(Type e));								��ȱ���ʹ�ú���
																		������visit����������
																		����ֵ���Ƿ�ɹ���1��
  ***********************************************************************/
template<class Type>  class JWGraph
{
public:
	JWGraph(void);
	~JWGraph(void);
	int CreateDG(int(* creat)(Type &mem));     //��������ͼ(�������뷨)
	int ALCreateDG(int(* creat)(Type &mem));     //��������ͼ(�ڽӾ������뷨��

	int DispalyGraph(int(* dispaly)(Type mem));	//��ʾ����

	int DFStraverse(int(* visit)(Type e));     //��ȱ���ʹ�ú���
	int BFStraverse(int(* visit)(Type e));     //��ȱ���ʹ�ú���

	//int MiniSpanTree_PRIM(struct Binode<Type> * &GT);//������ķ�㷨������С������
	//int MiniSpanTree_KLS(struct Binode<Type> * &GT);//�ÿ�³˹�����㷨������С������

	int ShortestPath_DIJ(void);					//����Vnode��������������·��
	int ShortestPath_FLOYD(void);				//���������������̾���
	int GetShortPath(int start,int end);		//�õ��������·��

	int TopologicalSort(void);					//��������
protected:
	int DFS (int gnumber,int(* visit)(Type e));//���ƺ���
	int Inits(void);								//���ԭ������

private:
	struct Vnode<Type>  vertices[MAXnode];	//����ʹ������洢	
	int    vexnum,arcnum;					//ͼ��ǰ��a��������a��ϵ��
	int    kind;							//ͼ������
	double ALGraph[MAXnode][MAXnode];		//�ڽ�����洢
	bool   visit_state[MAXnode];			//���ʱ�־λ
	double distance[MAXnode][MAXnode];		//��a��b�����·��ֵ
	int    lpath[MAXnode][MAXnode][MAXnode];//��a��b�����·��
	int	   fcount[MAXnode];					//ǰ�õ����
};

/********************��������*********************************************/
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

	//���þ���
	struct Arcnode<Type> *V,*VN;
	vexnum=20;

	for(int s=0;s<vexnum;s++)
	{
		vertices[s].data=(char)(65+s);
		vertices[s].firstarc=NULL;
	}

	for(int s=0;s<vexnum;s++)
	{
		int time=0;//��һ����ʱ����
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
	for(int s=0;s<vexnum;s++)				//���ݳ�ʼ��
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
	for(int s=0;s<vexnum;s++)						//	�ڽӾ����ʼ��
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

template<class Type> int JWGraph<Type>::DispalyGraph(int(* display)(Type mem))	//��ʾ����
{
	printf("�Ѿ�����ͼ���£�\n");
	printf("ͼ�Ķ������£�\n");
	for(int s=0;s<vexnum;s++)						//	������ʾ
	{
		display(vertices[s].data);
	}
	printf("\n�ڽӾ������£�\n");
	for(int s=0;s<vexnum;s++)						//	�ڽӾ�����ʾ
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
	//�����ڽӱ��ʾ
	int Vnumber=0,linknum=1,link=0;;
	struct Arcnode<Type> *V,*VN;
	kind=DG;

	Inits();//����ɵ�����

	printf("�������뷨\n");

	printf("�������%d������Ԫ�� ",Vnumber+1);
	while(!creat(vertices[Vnumber].data)) 
	{
		++Vnumber;
		printf("�������%d������Ԫ�� ",Vnumber+1);
	}

	vexnum=Vnumber;

	for(Vnumber=0;Vnumber<vexnum;Vnumber++)
	{
		V=vertices[Vnumber].firstarc;
		vertices[Vnumber].firstarc=NULL;
		link=0;

		printf("��������%d�Ķ���Ϊ������Ĺ�ϵʽ���ո��������\n",Vnumber+1);
		while(1)
		{
			printf("��������һ��Ŀ��Ԫ�����ڴ洢λ�� ��ͬ��λ�ý�����");
			cin>>linknum;

			if(linknum==Vnumber+1) break;

			arcnum++;				//��¼��ϵ��
			VN=(struct Arcnode<Type> *)malloc(sizeof(struct Arcnode<Type>*));
			printf("������ù�ϵȨ��");
			cin>>(VN->info);

			ALGraph[Vnumber][linknum-1]=VN->info;			//�ڽ������ȡ

			if(link==1)										
			{
				V->nextarc=VN;
			}
			else											//��һ�λ�����
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

	Inits();//����ɵ�����

	printf("�������뷨\n");

	printf("�������%d������Ԫ�� �����Ž�����",vexnum+1);
	while(!creat(vertices[vexnum].data)) 
	{
		vertices[vexnum].firstarc=NULL;
		++vexnum;
		printf("�������%d������Ԫ�� �����Ž�����",vexnum+1);
	}

	for(int s=0;s<vexnum;s++)
	{
		printf("�������%d���ڽӾ��󣬶���Ԫ�� ���ո������س�������",s+1);
		int time=0;//��һ����ʱ����
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

template<class Type> int JWGraph<Type>::BFStraverse(int(* visit)(Type e))		 //��ȱ���ʹ�ú���
{
	struct Arcnode<Type>  *nowline;
	int nownode;
	JWQQueue<int> QGraph;

	for(int i=0;i<vexnum;i++)											//��ʼ��״̬����
	{
		visit_state[i]=0;
	}
	for(int i=0;i<vexnum;i++)											//��ȱ���
	{
		if(visit_state[i]==0)
		{
			visit(vertices[i].data);
			visit_state[i]=1;

			QGraph.EnQueue(i);			//ѹ��ջ

			while(QGraph.QueueLength()!=0)
			{
				QGraph.DeQueue(nownode);
				nowline=vertices[nownode].firstarc;			//��¼��ʼ��

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

template<class Type> int JWGraph<Type>::DFStraverse(int(* visit)(Type e))		 //��ȱ���ʹ�ú���
{
	for(int i=0;i<vexnum;i++)											//��ʼ��״̬����
	{
		visit_state[i]=0;
	}
	for(int i=0;i<vexnum;i++)											//�������
	{
		if(visit_state[i]==0)
		{
			DFS(i,visit);
		}
	}
	return 1;
}

template<class Type> int JWGraph<Type>::DFS(int gnumber,int(* visit)(Type e))		 //��ȱ���ʹ�ú���
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

template<class Type> int JWGraph<Type>::ShortestPath_DIJ(void)			//����Vnode��������������·��
{
	//һ�εڽ�˹�����㷨
	for(int s=0;s<vexnum;s++)				
	{
		//��ʼ������
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
		//��һ�������ݼ���
		distance[s][s]=INF;
		visit_state[s]=1;
		lpath[s][s][1]=0;
		//��ʼ����̾��룬��ͣ�����̾���
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
			visit_state[nowminnode]=1;//��������㣻
			int line=0;
			for(int w=0;w<vexnum;w++)//ˢ������
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

template<class Type> int JWGraph<Type>::ShortestPath_FLOYD(void)				//���������������̾���
{
	//�Խڵ��ʼ��
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

template<class Type> int JWGraph<Type>::GetShortPath(int start,int end)		//�õ��������·��
{
	if(lpath[start-1][end-1][1]==0)
	{
		printf("��%d�㵽%d�㵽�ﲻ��\n",start,end);	
		return 0;
	}
	printf("��%d�㵽%d������·���ľ���Ϊ��%f\n",start,end,distance[start-1][end-1]);
	int t=0;
	printf("��%d�㵽%d������·��Ϊ:",start,end);
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
	int e=0,e_f=0;//0������ı�ͷ�ͱ�β��
	//���㶥��Ķ�
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
	//�γɵ�0������
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
	printf("��չ��������:");
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