#include "StdAfx.h"
#include "JWStack.h"



// template<class Type> JWStack<Type>::JWStack(void)
//{
//	//top=-1;
//	head=NULL;
//}
//
//
//template<class Type> JWStack<Type>::~JWStack(void)
//{
//}
//
//template<class Type> void JWStack<Type>::push(Type x)
//{
//	//top++;
//	//s[top]=x;
//	struct node<Type> *t;
//	t=(struct node<Type> *)malloc(sizeof(struct node<Type>));
//	t->data=x;
//    t->next=head;
//	head=t;
//}
//
//template<class Type> Type JWStack<Type>::pop(void)
//{
//	Type x;
//    struct node<Type> *t;
//	//x=s[top];
//	//top--;
//	//return x;
//	x=head->data;
//	t=head;
//	head=head->next;
//	free(t);
//	return x;
//}
//
//template<class Type> int JWStack<Type>::empty(void)
//{
//	//return (-1==top);
//	return (NULL==head);
//}