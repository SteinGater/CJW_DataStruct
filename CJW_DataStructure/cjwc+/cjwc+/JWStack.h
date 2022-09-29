#pragma once
//��ջ���󣬲�����ջ��ģ��

#include <assert.h>
#include <map>

/************************************************************************
�ṹ�壺��ջ������ʽ��λ�ṹ��
  data����ջ����
  next��ָ���ջ��̵�
  ***********************************************************************/
template<class Types> struct Stacknode
{
	Types data;
	struct Stacknode<Types> *next;
};

/************************************************************************
��ģ�壺��ջ��ģ��
	���ݣ�
	*head����ջ�ṹ��ͷָ��
	������
	int push(Type x);		������ѹ��Ѷ�
							������x ��Ҫѹ���ջ��Ԫ��
							����ֵ���Ƿ�ɹ���1��
	Type pop(void);			�Ƴ�ջ��Ԫ��
							��������
							����ֵ��ջ��Ԫ��
	int empty(void);		����Ƿ�Ϊ��
							����:��
							����ֵ���գ�1��
	Type gettop(void);      �õ�ջ��Ԫ�ص�ֵ
							��������
							����ֵ��ջ��Ԫ��ֵ��
  ***********************************************************************/
template<class Type> class JWStack
{
public:
	JWStack(void);
	~JWStack(void);
public:
	int push(Type x);	//ѹ���ջ
	Type pop(void);		//������ջ
	int empty(void);	//����Ƿ�Ϊ��
	Type gettop(void);	//�õ�ջ��Ԫ��
private:
	struct Stacknode<Type> *head;//��ջԪ��
};

/********************��������*********************************************/
template<class Type> JWStack<Type>::JWStack(void)
{
	//top=-1;
	head=NULL;
}

template<class Type> JWStack<Type>::~JWStack(void)
{
	struct Stacknode<Type> *t;
	while(head)
	{
		t=head;
		head=head->next;
		free(t);
	}
	head=NULL;
}

template<class Type> int JWStack<Type>::push(Type x)
{
	//top++;
	//s[top]=x;
	struct Stacknode<Type> *t;
	t=(struct Stacknode<Type> *)malloc(sizeof(struct Stacknode<Type>));
	t->data=x;
    t->next=head;
	head=t;
	return 1;
}

template<class Type> Type JWStack<Type>::pop(void)
{
	Type x;
    struct Stacknode<Type> *t;
	//x=s[top];
	//top--;
	//return x;
	if(head==NULL)
	{
		return NULL;
	}
	x=head->data;
	t=head;
	head=head->next;
	free(t);
	return x;
}

template<class Type> int JWStack<Type>::empty(void)
{
	//return (-1==top);
	return (NULL==head);
}

template<class Type> Type JWStack<Type>::gettop(void)
{
	if(head==NULL)
	{
		return NULL;
	}
	else
	{
		return(head->data);
	}
}