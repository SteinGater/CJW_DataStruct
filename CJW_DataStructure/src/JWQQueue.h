#pragma once
//队列对象，产生队列类模板

/************************************************************************
结构体：单向队列链表样式单位结构体
  data：队列数据
  next：指向队列后继点
  ***********************************************************************/
template<class Types> struct Qnode
{
	Types data;
	struct Qnode<Types> *next;
};

/************************************************************************
类模板：单向队列类模板
	数据：
	struct Qnode<Type> *front;   队列头指针
	struct Qnode<Type> *rear;    队列尾指针
	int Qnumber;                 队列个数
	函数：
	int QueueLength(void);	检查长度
							参数：无
							返回值：长度值（空为0）
	int EnQueue(Type e);	在队尾插入元素
							参数：e ：要插入的元素
							返回值：是否成功
	int DeQueue(Type &e);	队头删除元素
							参数:e:存放删除的元素
							返回值：是否成功
	int GetHead(Type &Qhead)得到队头元素
							参数：Qhead：存放队头元素
							返回值：是否成功
	int GetLast(Type &Qlast)得到队尾元素
							参数：Qlast：存放队尾元素
							返回值：是否成功
  ***********************************************************************/
template<class Type> class JWQQueue
{
public:
	JWQQueue(void);
	~JWQQueue(void);
	int QueueLength(void);		//检查长度
	int EnQueue(Type e);		//在队尾插入元素
	int DeQueue(Type &e);		//队头删除元素
	int GetHead(Type &Qhead);	//得到队头元素
	int GetLast(Type &Qlast);	//得到队尾元素

private:
	struct Qnode<Type> *front;   //队列头指针
	struct Qnode<Type> *rear;    //队列尾指针
	int Qnumber;                 //队列个数

};

/********************函数定义*********************************************/
template<class Type> JWQQueue<Type>::JWQQueue(void)
{
	front=NULL;
	rear=NULL;
	Qnumber=0;
}

template<class Type> JWQQueue<Type>::~JWQQueue(void)
{
		struct Qnode<Type> *t;
		while(front)
		{
			t=front;
			if(front==rear)
			{
				front=NULL;
				rear=NULL;
			}
			else
			{
				front=front->next;
			}
			free(t);
		}
		front=NULL;
		rear=NULL;
		Qnumber=0;

}

template<class Type> int JWQQueue<Type>::QueueLength(void)
{
	return Qnumber;
}

template<class Type> int JWQQueue<Type>::EnQueue(Type e)
{
	struct Qnode<Type> *t;
	t=(struct Qnode<Type> *)malloc(sizeof(struct Qnode<Type>));
	t->data=e;
	t->next=NULL;
	if(Qnumber==0)
	{
		front=t;
		rear=t;
	}
	else
	{
		rear->next=t;
		rear=t;
	}
	Qnumber++;
	return 1;
}

template<class Type> int JWQQueue<Type>::DeQueue(Type &e)
{
	struct Qnode<Type> *t;
	if(Qnumber==0)
	{
		e=NULL;
		return 0;
	}
	else
	{
		e=front->data;
		t=front;
		if(Qnumber==1)
		{
			rear=NULL;
			front=NULL;
		}
		else
		{
			front=front->next;
		}
		free(t);
		Qnumber--;
		return 1;
	}

}

template<class Type> int JWQQueue<Type>::GetHead(Type &Qhead)
{
	if(Qnumber==0)
	{
		return 0;
	}
	else
	{
		Qhead=front->data;
		return 1;
	}
}

template<class Type> int JWQQueue<Type>::GetLast(Type &Qlast)
{
	if(Qnumber==0)
	{
		return 0;
	}
	else
	{
		Qlast=rear->data;
		return 1;
	}
}