#pragma once
//生成快速排序列表
#include <assert.h>
#include <map>

#define MAXList 30

//快速排序类
template<class Type> class JWSqList
{
public:
	JWSqList(void);
	~JWSqList(void);
	int SqListCreate(int(* creat)(Type &mem));				//构件一个排序类

	int SqDisplay(int(* visit)(Type e));                    //显示排序顺序

	int MSort(int low,int high);							//冒泡排序
	int SelectSort(int low,int high);						//选择排序
	int InsetSort(int low,int high);						//插入排序
	int QSort(int low,int high);							//快速排序递推

	int GetLength(void);									//得到長度

protected:
	int SqInit(void);
	int SqPartition(int low,int high);									//一次快速排序

private:
	Type  info[MAXList+1];		//[0]作为哨兵元素
	int   infoKey[MAXList+1];   //[0]作为哨兵关键字元素
	int   length;				//长度
};

/********************函数定义*********************************************/
template<class Type>  JWSqList<Type>::JWSqList(void)
{
	SqInit();

	//内置数值
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
	printf("排序列数据如下：\n内容值\t关键字\n");
	for(int s=0;s<length;s++)
	{
		visit(info[s+1]);
		printf("%d\n",infoKey[s+1]);
	}
	return 1;
}

template<class Type> int JWSqList<Type>::SqListCreate(int(* creat)(Type &mem))//构件一个排序类
{
	SqInit();
	printf("请输入第%d个元素 ",length+1);
	while(!creat(info[length+1])) 
	{
		++length;
		printf("请输入第%d个元素 ",length+1);
	}
	for(int s=0;s<length;s++)
	{
		printf("请输入第%d个元素的关键词 ",s+1);
		cin>>infoKey[s+1];
	}
	return 1;
}

template<class Type> int JWSqList<Type>::SqPartition(int low,int high)								//快速排序
{
	int part=infoKey[low];
	//记录分割值
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
		{	//复制为哨兵
			info[0]=info[i];
			infoKey[0]=infoKey[i];
			//后退
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

template<class Type> int JWSqList<Type>::QSort(int low,int high)								//递推快速排序
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