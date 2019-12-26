#include <iostream>
using namespace std;
class A{
	public:
	//补充系统的默认构造函数
	A(){cout << "A()" << endl;}
	~A(){cout << "~A()" << endl;}
	A(const A& a){//有拷贝构造，最好补充上系统的默认构造函数
		cout << "拷贝构造A(const A&)" << endl;
	}
	A& operator=(const A& a){
		cout << "A operator=" << endl;
		return *this;
	}
};
class B:public A{
	public:
	B(){cout << "B()"<<endl;}
	//调用A类的拷贝构造;把b对象当成A类型的对象来看;子类可以充当父类	
	B(const B& b):A(b){cout << "拷贝构造B(const B&)" << endl;}
	B& operator=(const B& b){
		//要调用A类型的赋值运算符operator=
		A::operator=(b);
		cout << "B operator=" << endl;
		return *this;
	}
};
void foo(){
	B b;
	B c = b;
	B d;
	d = b;
}
int main(){
	foo();
}
