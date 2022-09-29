#pragma once
//���ж��󣬲���������ģ��

/************************************************************************
�ṹ�壺�������������ʽ��λ�ṹ��
  data����������
  next��ָ����к�̵�
  ***********************************************************************/
template<class Types> struct Qnode
{
	Types data;
	struct Qnode<Types> *next;
};

/************************************************************************
��ģ�壺���������ģ��
	���ݣ�
	struct Qnode<Type> *front;   ����ͷָ��
	struct Qnode<Type> *rear;    ����βָ��
	int Qnumber;                 ���и���
	������
	int QueueLength(void);	��鳤��
							��������
							����ֵ������ֵ����Ϊ0��
	int EnQueue(Type e);	�ڶ�β����Ԫ��
							������e ��Ҫ�����Ԫ��
							����ֵ���Ƿ�ɹ�
	int DeQueue(Type &e);	��ͷɾ��Ԫ��
							����:e:���ɾ����Ԫ��
							����ֵ���Ƿ�ɹ�
	int GetHead(Type &Qhead)�õ���ͷԪ��
							������Qhead����Ŷ�ͷԪ��
							����ֵ���Ƿ�ɹ�
	int GetLast(Type &Qlast)�õ���βԪ��
							������Qlast����Ŷ�βԪ��
							����ֵ���Ƿ�ɹ�
  ***********************************************************************/
template<class Type> class JWQQueue
{
public:
	JWQQueue(void);
	~JWQQueue(void);
	int QueueLength(void);		//��鳤��
	int EnQueue(Type e);		//�ڶ�β����Ԫ��
	int DeQueue(Type &e);		//��ͷɾ��Ԫ��
	int GetHead(Type &Qhead);	//�õ���ͷԪ��
	int GetLast(Type &Qlast);	//�õ���βԪ��

private:
	struct Qnode<Type> *front;   //����ͷָ��
	struct Qnode<Type> *rear;    //����βָ��
	int Qnumber;                 //���и���

};

/********************��������*********************************************/
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