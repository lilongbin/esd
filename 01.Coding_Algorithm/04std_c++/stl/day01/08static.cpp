#include <iostream>
using namespace std;
template<typename T>
class A{
	public:
	static void print(void){
		cout << &m_i << ' '<< &m_t << endl;
	}
	private:
	static int m_i;
	static T m_t;
};
template<typename T>
int A<T>::m_i;
template<typename T>
T A<T>::m_t;
int main(void){
	A<int>::print();
	A<double>::print();
	A<string>::print();
	return 0;
}
