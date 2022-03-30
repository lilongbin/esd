#include <iostream>
using namespace std;
template<typename T>
class A{
	public:
	A (T const& data):m_data(data){}
	T m_data;
};
template<typename K,typename V,template<typename T> class C>
//C是一个单模板参数的模板
class B{
	public:
	B(K const& k,V const& v):m_k(k),m_v(v){}
	C<K> m_k;
	C<K> m_v;
};
int main(void){
	B<string,double,A> b ("PAI",3.14);
	cout << b.m_k.m_data << '=' << b.m_v.m_data << endl;
	return 0;
}
