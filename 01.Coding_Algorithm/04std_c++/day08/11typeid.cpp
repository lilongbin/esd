#include <iostream>
#include <typeinfo>
class A{
	public:
	virtual void fun(){}//如果没有这个虚函数，*pb就是A类型的
};
class B:public A{
	
};
using namespace std;
int main(){
	int a;
	double p;
	int data[10];
	int *pi;
	cout << typeid(a).name() << endl;
	cout << typeid(p).name() << endl;
	cout << typeid(data).name() << endl;
	cout << typeid(pi).name() << endl;
	A oa;
	B ob;
	A *pb = new B();
	cout << typeid(oa).name() << endl;
	cout << typeid(ob).name() << endl;
	cout << typeid(pb).name() << endl;//
	cout << typeid(*pb).name() << endl;
	if(typeid(*pb)== typeid(A)){
		cout << "*pb is A" << endl;
	}else if(typeid(*pb) == typeid(B)){
		cout << "*pb is B" << endl;
	}
}
