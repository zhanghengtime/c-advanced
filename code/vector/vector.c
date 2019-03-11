//用c语言实现Vector 用成员指针的方法 方法二:链表形式还没有实现

//方法一:
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

typedef int DataType; //数据类型int

typedef struct array
{
	DataType *Data; 
	int size,max_size;  //max_szie为vector最大容量 szie为当前大小
    void (*Constructor)(struct array *); //构造函数
	void (*Input)(DataType,struct array*); //输入数据
	int (*get_array_size)(struct array *); //获取array的大小
	int (*return_index_value)(struct array*,int); //返回下标为index的值
	void (*print)(struct array*);  //打印结果
	void (*Destructor)(struct array *);  //析构函数
}Array;

void Init(Array *this);
void _print(struct array *this);
void _constructor(Array *this);
void _denstructor(Array *this);
void _input(DataType data,Array *this);
int _get_size(Array *this);
int _return_index_value(Array *this,int index);

void Init(Array *this) //构造函数
{
	this->Input = _input;
	this->print = _print;
	this->get_array_size = _get_size;
	this->return_index_value = _return_index_value;
	this->Constructor = _constructor;
	this->Destructor= _denstructor;
	this->Constructor(this);
}

void _constructor(Array *this)  //构造函数
{
	this->size=0;
	this->max_size=10;  //默认最大容量为10
	this->Data=(DataType *)malloc(this->max_size*sizeof(DataType));
	memset(this->Data,0,10*sizeof(DataType)); //初始化函数
}

void _input(DataType data,Array *this) //输入函数
{
	int i;
	DataType *ptr;
	if(this->size>=this->max_size)
	{
		ptr=(DataType *)malloc(this->max_size*sizeof(DataType));
		for(i=0;i<this->size;i++)
			ptr[i]=this->Data[i];
		free(this->Data); //释放之前空间
		this->Data=ptr;
	}
	this->Data[this->size]=data;
    this->size+=1;
}

void _print(struct array *this)  //输出函数
{
	int i=0;
	struct array *ptr=this;
	assert(this!=NULL);
	for(i=0;i<ptr->size;i++)
		printf("data is %d\n",ptr->Data[i]);
	return;
}

int  _get_size(Array *this) //获取array大小
{
	assert(this!=NULL);
	return this->size;
}

int _return_index_value(Array *this,int index) //返回下标为index的值
{
	assert(this!=NULL);
	return (this->Data[index]);
}

void _denstructor(Array *this) //析构函数
{
	int i=0;
	assert(this!=NULL);
	for(i=0;i<this->max_size;i++)
		this->Data[i]=0;
	free(this->Data);
}

int main()
{
	Array MyArray;
	Init(&MyArray);
	MyArray.Input(1,&MyArray);
	MyArray.Input(3,&MyArray);
	MyArray.Input(5,&MyArray);	
	MyArray.Input(4,&MyArray);
	MyArray.Input('c',&MyArray);//只能单一类型
	MyArray.Input(7,&MyArray);
	MyArray.print(&MyArray);
	printf("the array size is:%d\n",MyArray.get_array_size(&MyArray));
	printf("the index 3 value in array is:%d\n",MyArray.return_index_value(&MyArray,3));
	MyArray.Destructor(&MyArray);
	return 0;
}




 