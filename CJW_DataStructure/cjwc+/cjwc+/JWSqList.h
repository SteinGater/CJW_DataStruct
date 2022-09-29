#pragma once
//���ɿ��������б�
#include <assert.h>
#include <map>

#define MAXList 30

//����������
template<class Type> class JWSqList
{
public:
	JWSqList(void);
	~JWSqList(void);
	int SqListCreate(int(* creat)(Type &mem));				//����һ��������

	int SqDisplay(int(* visit)(Type e));                    //��ʾ����˳��

	int MSort(int low,int high);							//ð������
	int SelectSort(int low,int high);						//ѡ������
	int InsetSort(int low,int high);						//��������
	int QSort(int low,int high);							//�����������

	int GetLength(void);									//�õ��L��

protected:
	int SqInit(void);
	int SqPartition(int low,int high);									//һ�ο�������

private:
	Type  info[MAXList+1];		//[0]��Ϊ�ڱ�Ԫ��
	int   infoKey[MAXList+1];   //[0]��Ϊ�ڱ��ؼ���Ԫ��
	int   length;				//����
};

/********************��������*********************************************/
template<class Type>  JWSqList<Type>::JWSqList(void)
{
	SqInit();

	//������ֵ
	for(int s=1;s<MAXList+1;s++)
	{
		info[s]=rand()%43+43;
		infoKey[s]=rand()%100;
	}
	length=MAXList;
}

template<class Type> JWSqList<Type>::~JWSqList(void)
{
}

template<class Type> int JWSqList<Type>::SqInit(void)
{
	length=0;
	for(int s=0;s<MAXList+1;s++)
	{
		info[s]=NULL;
		infoKey[s]=0;
	}
	return 1;
}

template<class Type> int JWSqList<Type>::SqDisplay(int(* visit)(Type e))
{
	printf("�������������£�\n����ֵ\t�ؼ���\n");
	for(int s=0;s<length;s++)
	{
		visit(info[s+1]);
		printf("%d\n",infoKey[s+1]);
	}
	return 1;
}

template<class Type> int JWSqList<Type>::SqListCreate(int(* creat)(Type &mem))//����һ��������
{
	SqInit();
	printf("�������%d��Ԫ�� ",length+1);
	while(!creat(info[length+1])) 
	{
		++length;
		printf("�������%d��Ԫ�� ",length+1);
	}
	for(int s=0;s<length;s++)
	{
		printf("�������%d��Ԫ�صĹؼ��� ",s+1);
		cin>>infoKey[s+1];
	}
	return 1;
}

template<class Type> int JWSqList<Type>::SqPartition(int low,int high)								//��������
{
	int part=infoKey[low];
	//��¼�ָ�ֵ
	info[0]=info[low];
	infoKey[0]=infoKey[low];
	while(low<high)
	{
		while((low<high)&&(infoKey[high]>=infoKey[0])) --high;
		info[low]=info[high];
		infoKey[low]=infoKey[high];
		while((low<high)&&(infoKey[low]<=infoKey[0])) ++low;
		info[high]=info[low];
		infoKey[high]=infoKey[low];
	}
	info[low]=info[0];
	infoKey[low]=infoKey[0];

	return low;
}

template<class Type> int JWSqList<Type>::MSort(int low,int high)
{
	if((low>high)||(low<1)||(high>length))
	{
		return 0;
	}

	int flag=1;
	for(int i=low;(i<high)&&(flag);i++)
	{
		flag=0;
		for(int j=low;j<high-i+low;j++)
		{
			if(infoKey[j]>infoKey[j+1])
			{
				flag=1;
				info[0]=info[j+1];
				infoKey[0]=infoKey[j+1];
				info[j+1]=info[j];
				infoKey[j+1]=infoKey[j];
				info[j]=info[0];
				infoKey[j]=infoKey[0];
			}
		}
	}
	return 1;
}

template<class Type> int JWSqList<Type>::SelectSort(int low,int high)
{
	if((low>high)||(low<1)||(high>length))
	{
		return 0;
	}
	 
	for(int i=low;i<high;i++)
	{
		int k=i;
		for(int j=i+1;j<=high;j++)
		{
			if(infoKey[j]<infoKey[k])
			{
				k=j;
			}
		}
		info[0]=info[i];
		infoKey[0]=infoKey[i];
		info[i]=info[k];
		infoKey[i]=infoKey[k];
		info[k]=info[0];
		infoKey[k]=infoKey[0];
	}

	return 1;
}

template<class Type> int JWSqList<Type>::InsetSort(int low,int high)
{
	if((low>high)||(low<1)||(high>length))
	{
		return 0;
	}
	for(int i=low+1;i<=high;i++)
	{
		if(infoKey[i]<infoKey[i-1])
		{	//����Ϊ�ڱ�
			info[0]=info[i];
			infoKey[0]=infoKey[i];
			//����
			int j;
			for(j=i-1;(infoKey[0]<infoKey[j])&&(j>=low);j--)
			{
				info[j+1]=info[j];
				infoKey[j+1]=infoKey[j];
			}
			info[j+1]=info[0];
			infoKey[j+1]=infoKey[0];
		}
	}
	return 1;
}

template<class Type> int JWSqList<Type>::QSort(int low,int high)								//���ƿ�������
{
	if((low>high)||(low<1)||(high>length))
	{
		return 0;
	}
	if(low<high)
	{
		int QS=SqPartition(low,high);
		QSort(low,QS-1);
		QSort(QS+1,high);
	}
	return 1;
}

template<class Type> int JWSqList<Type>::GetLength(void)
{
	return length;
}