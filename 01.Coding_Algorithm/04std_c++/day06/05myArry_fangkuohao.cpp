#include <iostream>
using namespace std;
class Arry{
	//真正存储数据的空间
	int *data;
	int len;//数组长度
	int size;//数组中当前元素个数
	public:
	explicit Arry(int len = 5):size(0){//构造函数
		this->len = len;//注意，为区分两个len
		data = new int[len];//根据传入的长度分配空间
	}
	~Arry(){//析构
		if(data){//防止重复调用析构导致的崩溃
		delete[] data;
		data = NULL;
		}
	}
	//拷贝构造函数
	Arry(const Arry& arr){
		len = arr.len;
		size = arr.size;
		data = new int[len];//根据长度开辟新空间
		//拷贝值
		for(int i = 0;i <= size - 1 ;i++){
			//data[i] = arr.data[i];
			*(data + i) = *(arr.data + i);//与上等效;
			//data不是成员指针,不用arr.*data
		}
	}
	void push_data(const int& d){
		if(size >= len){
			//扩容
			expend();
		}
		data[size++] = d;//data[size] = d;size++;
	}
	private:
	void expend(){//扩容函数
		len = 2 * len + 1;
		int *temp = data;//保留原来的数据地址
		data = new int[len];//申请新内存
		//复制原来的数据
		for(int i = 0;i <= size - 1;i++){
			data[i] = temp[i];
		}
		//释放原来的空间
		delete[] temp;
	}
	friend ostream& operator<<(ostream& os,const Arry& arr){
		for(int i = 0;i <= arr.size - 1;i++){
			os << arr.data[i] << " ";
		}
		return os;
	}
	public:
	//赋值运算符重载
	//考虑返回值，自赋值，被赋值对象的空间处理，原来对象数据的处理
	Arry& operator=(const Arry& arr){
		if(this != &arr){
			int *temp =  data;
			len = arr.len;
			size = arr.size;
			//申请内存
			data = new int[len];
			//复制数据
			for(int i = 0;i <= size - 1;i++){
				data[i] = arr.data[i];
			}
			//释放原来的空间
			delete[] temp;
		}
		return *this;
	}
	// []运算符
	int operator[](int ind){//基本类型默认是const
		if(ind > size - 1){//处理访问越界问题
			throw "out of range ind>size";//抛出信息
		}
		return data[ind];
	}
	
};

int main(){
	Arry arr(10);
	//Arry arr2 = 10;//只有一个参数的构造函数，会把int当成参数传入；
	//在构造函数前加explicit关键字会禁止int转换为Arry
	arr.push_data(9);
	arr.push_data(5);
	arr.push_data(2);
	arr.push_data(7);
	arr.push_data(9);
	arr.push_data(5);
	arr.push_data(2);
	arr.push_data(7);
	cout << "------" << endl;
	cout << arr[0] << endl;
	cout << arr[1] << endl;
	cout << arr[2] << endl;
	cout << arr[3] << endl;
	try{
		cout << arr[10] << endl;
	}catch(const char* msg){
		cout << msg << endl;
	}
	//Arry arr2 = arr;
	Arry arr2;
	arr2 = arr;//arr2自己的空间无法释放，arr2指向arr的内存;arr的内存会重复释放;//需要定义赋值运算符重载
	cout << arr << endl;
	cout << arr2 << endl;
}
