#include <iostream>
using namespace std;
class A{
	public:
	class B{};
	typename int BOOL;
};
template<typename T>
void foo(T t){
	typename T::B x;//告诉编译器T::B是一个类型
	typename T::BOOL y;
}
int main(){
	A a;
	foo(a);
	return 0;
}
