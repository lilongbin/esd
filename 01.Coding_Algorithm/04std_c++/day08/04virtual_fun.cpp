//虚函数
#include <iostream>
using namespace std;
class A{
	public:
	virtual void show(){/*当编译器检查出类中有虚函数时会自动增加一个指针来维护*/}
	virtual void show2(){}

};
int main(){
	cout << sizeof(A) << endl;
}
