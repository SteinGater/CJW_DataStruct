#pragma once
//堆栈对象，产生堆栈类模板

#include <assert.h>
#include <map>

/************************************************************************
结构体：堆栈链表样式单位结构体
  data：堆栈数据
  next：指向堆栈后继点
  ***********************************************************************/
template<class Types> struct Stacknode
{
	Types data;
	struct Stacknode<Types> *next;
};

/************************************************************************
类模板：堆栈类模板
	数据：
	*head：堆栈结构体头指针
	函数：
	int push(Type x);		将数据压入堆顶
							参数：x ：要压入堆栈的元素
							返回值：是否成功（1）
	Type pop(void);			推出栈顶元素
							参数：无
							返回值：栈顶元素
	int empty(void);		检查是否为空
							参数:无
							返回值：空（1）
	Type gettop(void);      得到栈顶元素的值
							参数：无
							返回值：栈顶元素值。
  ***********************************************************************/
template<class Type> class JWStack
{
public:
	JWStack(void);
	~JWStack(void);
public:
	int push(Type x);	//压入堆栈
	Type pop(void);		//弹出堆栈
	int empty(void);	//检查是否为空
	Type gettop(void);	//得到栈顶元素
private:
	struct Stacknode<Type> *head;//堆栈元素
};

/********************函数定义*********************************************/
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