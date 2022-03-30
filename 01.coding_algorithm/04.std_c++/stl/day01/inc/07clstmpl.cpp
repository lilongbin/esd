//#include "07clstmpl.hpp"
#include <cstring>
#include <iostream>
using namespace std;
template<typename T>
Comparator<T>::Comparator(T x,T y):m_x(x),m_y(y){}
template<typename T>
T Comparator<T>::max(void)const{
	return m_x < m_y ? m_y :m_x;
}
template<typename T>
T Comparator<T>::min(void)const{
	return m_x < m_y ? m_x :m_y;
}
//成员特化,只需要定义，不需要再声明
template<>
char const* Comparator<char const*>::max(void)const{
	return strcmp(m_x,m_y) < 0 ? m_y :m_x;
}
template<>
char const* Comparator<char const*>::min(void)const{
	return strcmp(m_x,m_y) < 0 ? m_x :m_y;
}
