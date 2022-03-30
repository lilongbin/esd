#include <iostream>
using namespace std;
class A{
	private:
	void fun_private(){
		cout << "fun_private" << endl;
	}
	protected:
	void fun_protected(){
		cout << "fun_protected" << endl;
	}
	public:
	void fun_public(){
		cout << "fun_public" << endl;
	}
	friend void show_private();
};
void show_private(){
	A a;
	a.fun_private();
}
//让B类私有继承A类
class B:private A{
	public:
	void showA_protected_public(){
		fun_protected();
		fun_public();
	}
	friend void showA_private();
};
void showA_private(){
	show_private();
}
int main(){
	B b;
	b.showA_protected_public();
	showA_private();
}
