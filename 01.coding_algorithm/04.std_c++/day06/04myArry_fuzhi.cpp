#include <iostream>
using namespace std;
class Arry{
	//真正存储数据的空间
	int *data;
	int len;//数组长度
	int size;//数组中当前元素个数
	public:
	Arry(int le = 5):size(0){//构造函数
		/*this->*/len = le;
		data = new int[len];//根据传入的长度分配空间
	}
	~Arry(){//析构
		if(data){//防止重复调用析构导致的崩溃
		delete[] data;
		data = NULL;
		}
	}
	//拷贝构造函数
	Arry(const Arry& arr){//拷贝出一个新对象
		len = arr.len;
		size = arr.size;
		data = new int[len];//根据长度开辟新空间
		//拷贝值
		for(int i = 0;i <= size - 1 ;i++){
			//data[i] = arr.data[i];
			*(data + i) = *(arr.data + i);//与上句等效;
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
	Arry& operator=(const Arry& arr){//两个对象都已经存在
		if(this != &arr){//防止自赋值
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
	
};

int main(){
	Arry arr;
	arr.push_data(9);
	arr.push_data(5);
	arr.push_data(2);
	arr.push_data(7);
	arr.push_data(9);
	arr.push_data(5);
	arr.push_data(2);
	arr.push_data(7);
	//Arry arr2 = arr;
	Arry arr2;//arr2已经通过拷贝构造得到内存空间
	//赋值=会默认调用拷贝构造，arr2的内存会成无法使用的空间且找不到入口；
	//浅拷贝会把数据包括地址都给arr2，arr2和arr都用arr的内存；
	arr2 = arr;//arr2自己的空间无法释放，arr2指向arr的内存;arr的内存会重复释放;//需要定义赋值运算符重载
	cout << arr << endl;
	cout << arr2 << endl;
}
