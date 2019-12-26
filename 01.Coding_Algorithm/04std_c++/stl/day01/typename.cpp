#include <iostream>
using namespace std;
class A {
public:
	class B {};
	typedef int BOOL;
};
template<typename T>
void foo (T t) {
	typename T::B x;
	typename T::BOOL y;
}
int main (void) {
	A a;
	foo (a);
	return 0;
}
