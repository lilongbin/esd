#include <iostream>
using namespace std;
class A{
	mutable int age;
	public:
	//A(){}
	//_ZN1A4showEv
	void show(){
		age = 10;
		cout << "show()" << endl;
	}
	//_ZNK1A4showEv
	void show()const{
		age = 20;
		cout << "const show()" << endl;		
	}
};
int main(){
	A a;
	a.show();
	const A b=a;//需要初始化，或者在类中添加一个构造函数;
	b.show();
}
