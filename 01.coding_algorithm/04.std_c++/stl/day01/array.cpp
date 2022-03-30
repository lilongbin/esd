#include <iostream>
#include <typeinfo>
using namespace std;
template<typename T = int, size_t S = 256>
class Array {
public:
	T& operator[] (size_t i) {
		return m_array[i];
	}
	const T& operator[] (size_t i) const {
		return const_cast<Array> (*this) [i];
	}
	size_t size (void) const {
		return sizeof (m_array) /
			sizeof (m_array[0]);
	}
private:
	T m_array[S];
};
// 模板的非类型参数不能是浮点类型
/*
template<double VAT>
void foo (void) {
	cout << VAT << endl;
}
*/
// 模板的非类型参数不能是类类型
/*
template<string VAT>
void bar (void) {
	cout << VAT << endl;
}
*/
template<char const* VAT>
void hum (void) {
	cout << VAT << endl;
}
char const* g_global = "global";
extern const char g_extern[] = "extern";
int main (void) {
	Array<int, 10> ai;
	cout << typeid (ai[0]).name () << ' '
		<< ai.size () << endl;
//Array<double, 20> ad;
//Array<double, 15+5> ad;
//int x = 5;
	const int x = 5;
//const volatile int x = 5;
	Array<double, 15+x> ad;
	cout << typeid (ad[0]).name () << ' '
		<< ad.size () << endl;
	Array<> an;
	cout << typeid (an[0]).name () << ' '
		<< an.size () << endl;
//foo<3.14> ();
//bar<"class"> ();
	// 模板的非类型实参不能是字符串字面值
//hum<"literal"> ();
	// 模板的非类型实参不能是全局指针
//hum<g_global> ();
	// 模板的非类型实参可以是外部变量
	hum<g_extern> ();
	Array<Array<int, 4>, 3> aa;
	for (size_t i = 0; i < 3; ++i)
		for (size_t j = 0; j < 4; ++j)
			aa[i][j] = (i+1)*10+(j+1);
//		aa.operator[](i).operator[](j) = ...;
	for (size_t i = 0; i < 3; ++i) {
		for (size_t j = 0; j < 4; ++j)
			cout << aa[i][j] << ' ';
		cout << endl;
	}
	Array<Array<> > a2;
	return 0;
}
