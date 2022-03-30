#include <iostream>
#include <cstring>
using namespace std;
// 类模板/模板类
template<typename T>
class Comparator {
public:
	Comparator (T x, T y) : m_x (x), m_y (y) {}
	T max (void) const {
		return m_x < m_y ? m_y : m_x;
	}
	T min (void) const {
		return m_x < m_y ? m_x : m_y;
	}
private:
	T m_x;
	T m_y;
};
// 针对char const*类型的全类特化版本
/*
template<>
class Comparator<char const*> {
public:
	Comparator (char const* x, char const* y) :
		m_x (x), m_y (y) {}
	char const* max (void) const {
		return strcmp (m_x, m_y) < 0 ? m_y : m_x;
	}
	char const* min (void) const {
		return strcmp (m_x, m_y) < 0 ? m_x : m_y;
	}
private:
	char const* m_x;
	char const* m_y;
};
*/
// 针对char const*类型的成员特化版本
template<>
char const* Comparator<char const*>::max (
	void) const {
	return strcmp (m_x, m_y) < 0 ? m_y : m_x;
}
template<>
char const* Comparator<char const*>::min (
	void) const {
	return strcmp (m_x, m_y) < 0 ? m_x : m_y;
}
/*
template<typename T>
Comparator<T>::Comparator (T x, T y) :
	m_x (x), m_y (y) {}
template<typename T>
T Comparator<T>::max (void) const {
	return m_x < m_y ? m_y : m_x;
}
template<typename T>
T Comparator<T>::min (void) const {
	return m_x < m_y ? m_x : m_y;
}
*/
int main (void) {
	Comparator<int> ci (123, 456);
	cout << ci.max() << ' ' << ci.min() << endl;
	Comparator<double> cd (1.23, 4.56);
	cout << cd.max() << ' ' << cd.min() << endl;
	Comparator<string> cs ("hello", "world");
	cout << cs.max() << ' ' << cs.min() << endl;
	Comparator<char const*> cp("hello","world");
	cout << cp.max() << ' ' << cp.min() << endl;
	return 0;
}
