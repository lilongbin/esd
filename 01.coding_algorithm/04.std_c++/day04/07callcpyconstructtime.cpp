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
	A(const A& a){//定义拷贝构造
		cout << "A(const A&)" << endl;
	}
};
void showA(A pa){}
void showA1(A& pa){}
A& showA2(A& pa){
	return pa;
}
A showA3(){
	//A temp;
	//return temp;
	return A();//使用匿名临时对象，简化编程;
}
int main(){
	//拷贝构造函数的调用时机
	A a;
	A b = a;//用同类型的对象初始化会调用拷贝构造；
	cout << "showA(a) >>" ;
	showA(a);//传入a的同时进行拷贝值传递，调用指针或引用就不会调用拷贝构造；
	cout << "showA1(a)>>" ;
	showA1(a);//引用不调用拷贝
	cout << "showA2(a)>>" ;
	showA2(a);//不调用拷贝；
	cout << "showA3(a)>>" ;
	showA3();//函数返回对象类型时，调用拷贝构造；
	cout << endl;
}
