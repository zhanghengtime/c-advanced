//��c����ʵ��Vector �ó�Աָ��ķ��� ������:������ʽ��û��ʵ��

//����һ:
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

typedef int DataType; //��������int

typedef struct array
{
	DataType *Data; 
	int size,max_size;  //max_szieΪvector������� szieΪ��ǰ��С
    void (*Constructor)(struct array *); //���캯��
	void (*Input)(DataType,struct array*); //��������
	int (*get_array_size)(struct array *); //��ȡarray�Ĵ�С
	int (*return_index_value)(struct array*,int); //�����±�Ϊindex��ֵ
	void (*print)(struct array*);  //��ӡ���
	void (*Destructor)(struct array *);  //��������
}Array;

void Init(Array *this);
void _print(struct array *this);
void _constructor(Array *this);
void _denstructor(Array *this);
void _input(DataType data,Array *this);
int _get_size(Array *this);
int _return_index_value(Array *this,int index);

void Init(Array *this) //���캯��
{
	this->Input = _input;
	this->print = _print;
	this->get_array_size = _get_size;
	this->return_index_value = _return_index_value;
	this->Constructor = _constructor;
	this->Destructor= _denstructor;
	this->Constructor(this);
}

void _constructor(Array *this)  //���캯��
{
	this->size=0;
	this->max_size=10;  //Ĭ���������Ϊ10
	this->Data=(DataType *)malloc(this->max_size*sizeof(DataType));
	memset(this->Data,0,10*sizeof(DataType)); //��ʼ������
}

void _input(DataType data,Array *this) //���뺯��
{
	int i;
	DataType *ptr;
	if(this->size>=this->max_size)
	{
		ptr=(DataType *)malloc(this->max_size*sizeof(DataType));
		for(i=0;i<this->size;i++)
			ptr[i]=this->Data[i];
		free(this->Data); //�ͷ�֮ǰ�ռ�
		this->Data=ptr;
	}
	this->Data[this->size]=data;
    this->size+=1;
}

void _print(struct array *this)  //�������
{
	int i=0;
	struct array *ptr=this;
	assert(this!=NULL);
	for(i=0;i<ptr->size;i++)
		printf("data is %d\n",ptr->Data[i]);
	return;
}

int  _get_size(Array *this) //��ȡarray��С
{
	assert(this!=NULL);
	return this->size;
}

int _return_index_value(Array *this,int index) //�����±�Ϊindex��ֵ
{
	assert(this!=NULL);
	return (this->Data[index]);
}

void _denstructor(Array *this) //��������
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
	MyArray.Input('c',&MyArray);//ֻ�ܵ�һ����
	MyArray.Input(7,&MyArray);
	MyArray.print(&MyArray);
	printf("the array size is:%d\n",MyArray.get_array_size(&MyArray));
	printf("the index 3 value in array is:%d\n",MyArray.return_index_value(&MyArray,3));
	MyArray.Destructor(&MyArray);
	return 0;
}




 