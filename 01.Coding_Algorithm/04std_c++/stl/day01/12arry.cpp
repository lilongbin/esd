#include <iostream>
#include <typeinfo>
using namespace std;
template<typename T = int,size_t S = 256>//可以带缺省参数
class Arry{
	public:
	T& operator[](size_t i){
		return m_arry[i];
	}
	const T& operator[](size_t i)const{
		return const_cast<Arry> (*this)[i];
	}
	size_t size(void)const{
		return sizeof(m_arry)/sizeof(m_arry[0]);
	}

	private:
	T m_arry[S];
};
//模板的非类型参数不能是浮点类型
/*template<double VAT>
void foo(void){
	cout << VAT << endl;
}*/
//模板的非类型参数不能是类类型
/*template<string VAT>
void bar(void){
	cout << VAT << endl;
}*/
template<char const* VAT>
void hum(void){
	cout << VAT << endl;
}
char const* g_global = "global";
extern const char g_extern[] = "extern";
int main(){
	Arry<int,10> ai;
	cout << typeid(ai[0]).name() << ' ' << ai.size() << endl;
	//Arry<double,20> ad;
	Arry<double,15+5> ad;
	/*int x = 5;//error,编译器只负责翻译，没有内存，不知道x是多少，模板实例化失败
	Arry<double,15+x> ad;*/
	/*const int x = 5;//编译器会做常量优化；但不能加volatile
	Arry<double,15+x> ad;*/
	cout << typeid(ad[0]).name() << ' ' << ad.size() << endl;
	Arry<> an;
	cout << typeid(an[0]).name() << ' ' << an.size() << endl;
	//foo();
	//bar<"class"> ();
	//hum<"literal"> ();//模板的非类型实参不能是字符串字面值
	//hum<g_global> ();//模板的非类型实参不能是全局指针；
	hum<g_extern> ();//模板的非类型实参可以是外部变量;
	Arry<Arry<int,4>,3> aa;//3行4列的二维数组
	for(size_t i = 0;i < 3 ;i++){
		for(size_t j = 0;j < 4 ;j++){
			aa[i][j] = (i+1)*10+(j+1);
			//aa.operator[](i).operator[](j) = ...
		}
	}
	for(size_t i = 0;i < 3 ;i++){
		for(size_t j = 0;j < 4 ;j++){
			cout << aa[i][j] << ' ' ;
		}
		cout << endl;
	}
	Arry<Arry<> > a2;
	return 0;
}
