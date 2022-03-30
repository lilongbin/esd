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
	virtual void show(){}
};
class B:public A{
	public:
	B(){
		cout << "B()" << endl;
	}
	~B(){
		cout << "~B()" << endl;
	}
};
int main(){
	A *pa = new B();
	delete pa;//没有调用B的析构
	pa = NULL;
}
