#include <iostream>
using namespace std;
class A{
	private:
	int a;//私有的
	void funprivate(){
		cout << "funprivate" << endl;
	}
	protected:
	void funprotected(){
		cout << "funprotected" << endl;
	}
	public:
	void funpublic(){
		cout << "funpublic" << endl;
	}
	//访问A类型中的私有数据？做一个公开接口
	//private ---> public
	void showAprivate(){
		funprivate();
	}
};
class B:public A{
	//在类外可以访问保护的数据
	public:
	void showAprotected(){
		funprotected();
	}
	friend void useFriendshow();
	friend void useFriendshow2(B& b);
};
//使用友元函数调用B中的保护函数
void useFriendshow(){
	B b;
	b.funprotected();
}
void useFriendshow2(B& b){
	b.funprotected();
}

int main(){
	B b;
	//A类中的公开数据到子类是公开的
	b.funpublic();
	//A类中的保护数据到子类是保护的
	//b.funprotected();//受保护的只能在类内和子类中访问，现在已出类到main中
	//A类中的私有数据到子类是隐藏的;因为私有成员只能在类内访问
	//b.funprivate();
	b.showAprotected();
	b.showAprivate();
	cout << sizeof(B) << endl;
	//int a虽然是A的私有，在B中不能访问，但却占B的空间
	cout << sizeof(b) << endl;
	useFriendshow();
	useFriendshow2(b);
}
