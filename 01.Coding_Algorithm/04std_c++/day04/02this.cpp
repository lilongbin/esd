#include <iostream>
#include <string>
using namespace std;
class Animal{
	string name;
	int age;
	public:
	Animal(string name = "",int age = 0):name(name),age(age){//name编译器是可以区分的
		cout << "Animal()" << this << endl;//this指针指向当前对象的地址
	}
	void show(){//实际上是有参数传进来的
	//void show(Animal *this){//实际形式
		cout << "show() " << this << endl;
		cout << name << "," << age << endl;//下面一行是其原始的写法，本行是简写;
		cout << this->name << "," << this->age << endl;//本来面目
	}
};
extern "C" void _ZN6Animal4showEv(Animal* mythis);//直接调用汇编之后的函数名；
//show()函数其实是有参数的，汇编时会自动加上
int main(){
	Animal dog("xiaoqiang",2);
	cout << "&dog: " << &dog << endl;
	dog.show();
	_ZN6Animal4showEv(&dog);//试调用汇编后的函数
	cout << endl;
	Animal dog1("xiaoxiao",3);
	cout << "&dog1: " << &dog1 << endl;
	dog1.show();

}

