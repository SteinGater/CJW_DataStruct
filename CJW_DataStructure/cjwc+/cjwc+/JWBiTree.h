#pragma once
//��������ģ��

/************************************************************************
�ṹ�壺������������ʽ�洢��λ�ṹ��
  data����ջ����
  *lchild:��ָ��
  *rchild����ָ��
  Binumber����֦���
*************************************************************************/
template<class Types> struct Binode
{ 
	Types data;                                 //����
	struct Binode<Types> *lchild,*rchild;		//��������
	int Binumber;								//��������֦ʱ��ı��
};

/************************************************************************
��ģ�壺����������ģ��
	���ݣ�
	struct Binode<Type> *top; ����Ԫ��ָ��
	int    Binumbers;         Ԫ������
	int    BiLeafnumber;      Ҷ�Ӹ���
	������
	int BiTreeCreate(int(* creat)(Type &mem));			�������������
														������int(* creat)(Type &mem)�����뵥��Ԫ�صĺ���
														����ֵ���Ƿ�ɹ���1��
	int BiTreeCreateCopy(struct Binode<Type> *T);		ֱ�ӹ���������
														������T:�����Ķ�����
														����ֵ���Ƿ�ɹ���1��
	int GetBiTop(struct Binode<Type> *T);				�õ����ڵ�ָ��
														����:T:���ڵ�ָ��
														����ֵ���Ƿ�ɹ���1��
	int PreOrderTrans(int(* visit)(Type e));			��ʽ��ȱ�������visit����
														������visit ����������
														����ֵ���Ƿ�ɹ���1��
	int InOrderTra(int(* visit)(Type e));				��ʽ��������������visit����
														������visit ����������
														����ֵ���Ƿ�ɹ���1��
	int PreOrderTravers(int(* visit)(Type e),struct Binode<Type> *T);   �����������
																		������visit ����������
																			  T:����
																		����ֵ���Ƿ�ɹ���1��
  ***********************************************************************/
template<class Type> class JWBiTree
{
public:
	JWBiTree(void);
	~JWBiTree(void);

	int Init(void);										//��ʼ����

	int BiTreeCreate(int(* creat)(Type &mem));			//�������������

	int Display(int(* visit)(Type e));					//��ʾ

	int GetBiTop(struct Binode<Type> * &T);				//�õ����ڵ�ָ��

	int PreOrderTrans(int(* visit)(Type e));			//��ȱ���
	int PreOrderTravers(int(* visit)(Type e),struct Binode<Type> *T);    //��ȵ����������
	int PreOrderTra(int(* visit)(Type e));				//��ȷǵ����������
	int PostOrderTra(int(* visit)(Type e));				//��ȷǵ��ƺ������
	

protected:
	int TreeCreate(int(* creat)(Type &mem),struct Binode<Type> * &T);//���ƽ���

private:
	struct Binode<Type> *top;//����Ԫ��
	int    Binumbers;         //Ԫ������
	int    BiLeafnumber;     //Ҷ�Ӹ���
};

/********************��������*********************************************/
template<class Type> JWBiTree<Type>::JWBiTree(void)
{
	top=NULL;
	Init();

	//������
	struct Binode<Type> *A,*B,*C,*D,*E,*F,*G;
		G=(struct Binode<Type> *)malloc(sizeof(struct Binode<Type>));
	G->data='G';G->Binumber=8;G->lchild=NULL;G->rchild=NULL;
		F=(struct Binode<Type> *)malloc(sizeof(struct Binode<Type>));
	F->data='F';F->Binumber=7;F->lchild=NULL;F->rchild=NULL;
		E=(struct Binode<Type> *)malloc(sizeof(struct Binode<Type>));
	E->data='E';E->Binumber=5;E->lchild=NULL;E->rchild=NULL;
		D=(struct Binode<Type> *)malloc(sizeof(struct Binode<Type>));
	D->data='D';D->Binumber=4;D->lchild=G;D->rchild=NULL;
		C=(struct Binode<Type> *)malloc(sizeof(struct Binode<Type>));
	C->data='C';C->Binumber=3;C->lchild=NULL;C->rchild=F;
		B=(struct Binode<Type> *)malloc(sizeof(struct Binode<Type>));
	B->data='B';B->Binumber=2;B->lchild=D;B->rchild=E;
		A=(struct Binode<Type> *)malloc(sizeof(struct Binode<Type>));
	A->data='A';A->Binumber=1;A->lchild=B;A->rchild=C;

	top=A;
	A=NULL;B=NULL;C=NULL;D=NULL;E=NULL;F=NULL;G=NULL;
	Binumbers=7;
	BiLeafnumber=3;

}

template<class Type> JWBiTree<Type>::~JWBiTree(void)
{
   Init();
}

template<class Type> int JWBiTree<Type>::Init(void)
{
	struct Binode<Type> *T;
	JWQQueue<struct Binode<Type>*> QTree;

	T=top;

	while(T!=NULL)
	{
		if(T->lchild!=NULL)
		{
			QTree.EnQueue(T->lchild);
		}
		if(T->rchild!=NULL)
		{
			QTree.EnQueue(T->rchild);
		}
		free(T);
		QTree.DeQueue(T);
	}

	top=NULL;
	Binumbers=0;
	BiLeafnumber=0;

	return 1;
}

template<class Type> int JWBiTree<Type>::BiTreeCreate(int(* creat)(Type &mem))
{
	Init();

	printf("��������ڵ�����ݰ�");

	TreeCreate(creat,top);

	return 1;
}

template<class Type> int JWBiTree<Type>::TreeCreate(int(* creat)(Type &mem),struct Binode<Type> * &T)
{
	T=(struct Binode<Type> *)malloc(sizeof(struct Binode<Type>));
	
	if(creat(T->data))
	{
		T=NULL;
		return 0;
	}
	else
	{
		Binumbers++;
		T->Binumber=Binumbers;
		printf("������%d�������������������ݰ�",T->Binumber);
		TreeCreate(creat,T->lchild);
		printf("������%d��������ұ����������ݰ�",T->Binumber);
		TreeCreate(creat,T->rchild);
	}

    return 1;
}

template<class Type> int JWBiTree<Type>::Display(int(* visit)(Type e))
{
	if(top==NULL)
	{
		return 0;
	}

	return 1;
}

//��ȱ���
template<class Type> int JWBiTree<Type>::PreOrderTrans(int(* visit)(Type e))
{
	struct Binode<Type> *T;
	JWQQueue<struct Binode<Type>*> QTree;

	T=top;

	while(T!=NULL)
	{
		visit(T->data);
		if(T->lchild!=NULL)
		{
			QTree.EnQueue(T->lchild);
		}
		if(T->rchild!=NULL)
		{
			QTree.EnQueue(T->rchild);
		}
		QTree.DeQueue(T);
	}
	return 1;
}

//��ȵ����������
template<class Type> int JWBiTree<Type>::PreOrderTravers(int(* visit)(Type e),struct Binode<Type> *T)
{
	if(T!=NULL)
	{
        visit(T->data);//����
		PreOrderTravers(visit,T->lchild);
		//visit(T->data);//����
		PreOrderTravers(visit,T->rchild);
		//visit(T->data);//����
		return 1;
	}
	return 0;
}

//��ȷǵ����������
template<class Type> int JWBiTree<Type>::PreOrderTra(int(* visit)(Type e))
{
	struct Binode<Type> *T;
    JWStack<struct Binode<Type>*> STree;

	T=top;
	
	//����1��
	//STree.push(T);
	//while(!STree.empty())
	//{
	//	while(T!=NULL)
	//	{
	//		visit(T->data);//����
	//		T=T->lchild;
	//		STree.push(T);
	//	}
	//	T=STree.pop();
	//	if((!STree.empty()))
	//	{
	//		T=STree.pop();
	//		//visit(T->data);//����
	//		T=T->rchild;
	//		STree.push(T);
	//	}
	//}

	//����2��
	while((!STree.empty())||(T))
	{
		if(T)
		{
			visit(T->data);//����
			STree.push(T);
			T=T->lchild;
		}
		else
		{
			T=STree.pop();
			//visit(T->data);//����
			T=T->rchild;
		}
	}

	return 1;
}

//��ȷǵ��ƺ������
template<class Type> int JWBiTree<Type>::PostOrderTra(int(* visit)(Type e))
{
	struct Binode<Type> *T,*G;
    JWStack<struct Binode<Type>*> STree;

	T=top;
	
	//����1��
	//STree.push(T);
	//while(!STree.empty())
	//{
	//	T=STree.gettop();//��ֹ�Ѿ�visit��ʹ��
	//	while(T!=NULL)
	//	{
	//		T=T->lchild;
	//		STree.push(T);
	//	}
	//	T=STree.pop();
	//	while((G=STree.gettop())&&(G->rchild==T))
	//	{
	//		T=STree.pop();
	//		visit(T->data);//����
	//	}
	//	if(G!=NULL)
	//	{
	//		STree.push(G->rchild);
	//	}
	//}

	//����2��
	int flag=0;
	while((!STree.empty())||(T))
	{
		if(T&&(flag!=1))
		{
			flag=-1;
			STree.push(T);
			T=T->lchild;
		}
		else if((G=STree.gettop())&&(G->rchild==T))
		{
			flag=1;
			T=STree.pop();
			visit(T->data);//����	
		}
		else if(G)
		{
			flag=0;
			T=G->rchild;
		}
		else
		{
			flag=0;
			T=NULL;
		}
		
	}

	return 1;
}

template<class Type> int JWBiTree<Type>::GetBiTop(struct Binode<Type> * &T)
{
	T=top;
	return 1;
}