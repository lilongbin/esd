#ifndef _07CLSTMPL_H
#define _07CLSTMPL_H
//类模板 / 模板类
template<typename T>
class Comparator{
	public:
	Comparator(T x,T y);
	T max(void) const;
	T min(void) const;
	private:
	T m_x;
	T m_y;
};
#include "07clstmpl.cpp"//包含
#endif
