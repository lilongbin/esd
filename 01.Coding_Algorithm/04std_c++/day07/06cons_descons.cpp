#include <iostream>
using namespace std;
class A{
	public:
	A(){
		cout << "A()" << endl;
	}
	A(int a){
		cout << "A(int)" << endl;
	}
	~A(){
		cout << "~A()" << endl;
	}
};
class B:public A{
	public:
	//指定调用A类型的构造函数
	//B(int x = 10):A(x){
	B():A(10){//调用A的有参构造
		cout << "B()" << endl;
	}
	~B(){
		cout << "~B()" << endl;
	}
};
void foo(){
	B b;
}
int main(){
	foo();
}
