#include <iostream>
using namespace std;
class A{
public:
	A(){
		cout << "A()" << endl;
	}
	~A(){//析构函数
		cout << "~A()" << endl;
	}
};
void foo(){
	A a;
}
int main(){
	foo();	
	A *a = new A();
	delete a;
	A *parr = new A[3];
	delete[] parr;
}
