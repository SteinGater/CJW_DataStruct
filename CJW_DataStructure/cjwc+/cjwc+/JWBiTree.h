#pragma once
//二叉树类模板

/************************************************************************
结构体：二叉树数的链式存储单位结构体
  data：堆栈数据
  *lchild:左指针
  *rchild：右指针
  Binumber：满枝编号
*************************************************************************/
template<class Types> struct Binode
{ 
	Types data;                                 //数据
	struct Binode<Types> *lchild,*rchild;		//左右子树
	int Binumber;								//二叉树满枝时候的编号
};

/************************************************************************
类模板：二叉树类类模板
	数据：
	struct Binode<Type> *top; 树根元素指针
	int    Binumbers;         元素数量
	int    BiLeafnumber;      叶子个数
	函数：
	int BiTreeCreate(int(* creat)(Type &mem));			创立存入二叉树
														参数：int(* creat)(Type &mem)：输入单个元素的函数
														返回值：是否成功（1）
	int BiTreeCreateCopy(struct Binode<Type> *T);		直接构建二叉树
														参数：T:拷贝的二叉树
														返回值：是否成功（1）
	int GetBiTop(struct Binode<Type> *T);				得到根节点指针
														参数:T:根节点指针
														返回值：是否成功（1）
	int PreOrderTrans(int(* visit)(Type e));			链式广度遍历调用visit函数
														参数：visit ：遍历函数
														返回值：是否成功（1）
	int InOrderTra(int(* visit)(Type e));				链式深度中序遍历调用visit函数
														参数：visit ：遍历函数
														返回值：是否成功（1）
	int PreOrderTravers(int(* visit)(Type e),struct Binode<Type> *T);   递推先序遍历
																		参数：visit ：遍历函数
																			  T:树根
																		返回值：是否成功（1）
  ***********************************************************************/
template<class Type> class JWBiTree
{
public:
	JWBiTree(void);
	~JWBiTree(void);

	int Init(void);										//初始化树

	int BiTreeCreate(int(* creat)(Type &mem));			//创立存入二叉树

	int Display(int(* visit)(Type e));					//显示

	int GetBiTop(struct Binode<Type> * &T);				//得到根节点指针

	int PreOrderTrans(int(* visit)(Type e));			//广度遍历
	int PreOrderTravers(int(* visit)(Type e),struct Binode<Type> *T);    //深度递推先序遍历
	int PreOrderTra(int(* visit)(Type e));				//深度非递推先序遍历
	int PostOrderTra(int(* visit)(Type e));				//深度非递推后序遍历
	

protected:
	int TreeCreate(int(* creat)(Type &mem),struct Binode<Type> * &T);//递推建立

private:
	struct Binode<Type> *top;//树根元素
	int    Binumbers;         //元素数量
	int    BiLeafnumber;     //叶子个数
};

/********************函数定义*********************************************/
template<class Type> JWBiTree<Type>::JWBiTree(void)
{
	top=NULL;
	Init();

	//內置树
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

	printf("请输入根节点的数据包");

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
		printf("请输入%d个输入的左边子树的数据包",T->Binumber);
		TreeCreate(creat,T->lchild);
		printf("请输入%d个输入的右边子树的数据包",T->Binumber);
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

//广度遍历
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

//深度递推先序遍历
template<class Type> int JWBiTree<Type>::PreOrderTravers(int(* visit)(Type e),struct Binode<Type> *T)
{
	if(T!=NULL)
	{
        visit(T->data);//先序
		PreOrderTravers(visit,T->lchild);
		//visit(T->data);//中序
		PreOrderTravers(visit,T->rchild);
		//visit(T->data);//后序
		return 1;
	}
	return 0;
}

//深度非递推先序遍历
template<class Type> int JWBiTree<Type>::PreOrderTra(int(* visit)(Type e))
{
	struct Binode<Type> *T;
    JWStack<struct Binode<Type>*> STree;

	T=top;
	
	//方法1：
	//STree.push(T);
	//while(!STree.empty())
	//{
	//	while(T!=NULL)
	//	{
	//		visit(T->data);//先序
	//		T=T->lchild;
	//		STree.push(T);
	//	}
	//	T=STree.pop();
	//	if((!STree.empty()))
	//	{
	//		T=STree.pop();
	//		//visit(T->data);//中序
	//		T=T->rchild;
	//		STree.push(T);
	//	}
	//}

	//方法2：
	while((!STree.empty())||(T))
	{
		if(T)
		{
			visit(T->data);//先序
			STree.push(T);
			T=T->lchild;
		}
		else
		{
			T=STree.pop();
			//visit(T->data);//中序
			T=T->rchild;
		}
	}

	return 1;
}

//深度非递推后序遍历
template<class Type> int JWBiTree<Type>::PostOrderTra(int(* visit)(Type e))
{
	struct Binode<Type> *T,*G;
    JWStack<struct Binode<Type>*> STree;

	T=top;
	
	//方法1：
	//STree.push(T);
	//while(!STree.empty())
	//{
	//	T=STree.gettop();//防止已经visit的使用
	//	while(T!=NULL)
	//	{
	//		T=T->lchild;
	//		STree.push(T);
	//	}
	//	T=STree.pop();
	//	while((G=STree.gettop())&&(G->rchild==T))
	//	{
	//		T=STree.pop();
	//		visit(T->data);//中序
	//	}
	//	if(G!=NULL)
	//	{
	//		STree.push(G->rchild);
	//	}
	//}

	//方法2：
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
			visit(T->data);//中序	
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