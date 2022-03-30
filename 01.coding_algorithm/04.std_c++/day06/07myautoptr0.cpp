#include <iostream>
using namespace std;
class A{
	public:
	A(){
		cout << "A()" << endl;
	}
	~A(){
		cout << "~A()" << endl;
	}
};

class myauto_ptr{
	A *data;
	public:
	myauto_ptr(A *data = NULL):data(data){}
	~myauto_ptr(){//析构的时候，自动回收A类对象的内存
		if(data){
			delete data;
			data = NULL;
		}
	}
};
void foo(){
	A *pa = new A();
	myauto_ptr var_a(pa);//var_a的生命周期是函数的作用期，结束后自动析构
}
int main(){
	foo();
}
