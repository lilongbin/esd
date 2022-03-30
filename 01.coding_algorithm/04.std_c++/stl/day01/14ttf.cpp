#include <iostream>
using namespace std;
template<typename K>
class A{
	public:
	A(T const& data):m_data(data){}
	template<typename V>
	void foo(V const& data){
		cout << m_data << '=' << data << endl;
	}
	K m_data;
};
int main(){
	A<string> a("PAI");
	a.foo(3.14);
	return 0;
}
