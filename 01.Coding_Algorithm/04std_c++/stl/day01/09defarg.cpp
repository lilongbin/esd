#include <iostream>
#include <typeinfo>
using namespace std;
//类模板的模板参数可以带缺省值
//参数默认值仍然遵循右对齐
template<typename X = int,typename Y = double,typename Z = string>
class A{
	public:
	A(void){
		cout << typeid(m_x).name() << ' ' << typeid(m_y).name() << ' ' << typeid(m_z).name() << endl;
	}
	private:
	X m_x;
	Y m_y;
	Z m_z;
};
int main(){
	A<char,short,float> a1;
	A<char,short> a2;
	A<char> a3;
	A<> a4;//虽然没有参数但<>不能省;
	return 0;
}
