#include <iostream>
#include <typeinfo>
#include <cstring>
using namespace std;
//两个任意类型值的最大值
template<typename T>
T const& max(T const& x,T const y){
	cout << "<1" << typeid(x).name() << ">" << flush;
	return x < y ? y : x;
}
//两个任意类型指针所指向的目标的最大值
template<typename T>
T* const& max (T* const& x,T* const& y){
	cout << "<2" << typeid(x).name() << ">" << flush;
	return *x < *y ? y : x;
}
//两个c风格字符串的最大值
const char* const& max(const char* const& x,const char* const& y){
	cout << "<3" << typeid(x).name() << ">" << flush;
	return strcmp(x,y) < 0 ? y :x;
}
//三个任意类型值的最大值
template<typename T>
T const& max (T const& x,T const& y,T const& z){
	cout << "<4" << typeid(x).name() << ">" << flush;
	return ::max(::max(x,y),z);
	
}
int main(void){
	char const* x = "ABC";
	char const* y = "AB";
	char const* z = "A";
	cout << ::max(x,y) << endl;	//3
	cout << ::max<>(x,y) << endl;//2
	cout << ::max<char const*>(y,z) << endl;//1
	cout << ::max(x,y,z) << endl;
	return 0;
}
