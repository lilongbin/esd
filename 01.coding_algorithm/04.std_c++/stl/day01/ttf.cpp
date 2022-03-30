#include <iostream>
using namespace std;
template<typename K>
class A {
public:
	A (K const& data) : m_data (data) {}
	/*
	template<typename V>
	void foo (V const& data) {
		cout << m_data << '=' << data << endl;
	}
	*/
	template<typename V>
	void foo (V const& data);
	K m_data;
};
template<typename K>
	template<typename V>
void A<K>::foo (V const& data) {
	cout << m_data << '=' << data << endl;
}
int main (void) {
	A<string> a ("PAI");
	a.foo (3.14);
	return 0;
}
