#include <iostream>
#include <memory>
using namespace std;
class A{
	public:
	A(int data = 0):m_data(data){
		cout << "A()" << endl;
	}
	~A(void){
		cout << "~A()" << endl;
	}
	void print(void)const{
		cout << m_data << endl;
	}
	//private:
	int m_data;
};
template<typename T>
class good_ptr{
	public:
	good_ptr(T* p = NULL):m_p(p){}
	~good_ptr(void){
		if(m_p){
			delete m_p;
			m_p = NULL;
		}
	}
	//拷贝构造的转移寓意
	good_ptr(good_ptr& that):m_p(that.release()){}
	//赋值构造的转移寓意
	good_ptr& operator=(good_ptr& that){
		if(&that != this){
			reset(that.release());
		}
		return *this;
	}
	T& operator*(void)const{
		return *m_p;
	}
	T* operator->(void)const{
		return &**this;
	}
	private:
	T* m_p;
	T* release(void){
		T* p = m_p;
		m_p = NULL;
		return p;
	}
	void reset(T* p){
		if(p != m_p){
			delete m_p;
			m_p = p;
		}
	}
};
template<typename T>
class good_ptr<T[]>{
	public:
	good_ptr(T* p = NULL):m_p(p){}
	~good_ptr(void){
		if(m_p){
			delete[] m_p;
			m_p = NULL;
		}
	}
	//拷贝构造的转移语义
	good_ptr(good_ptr& that):m_p(that.release()){}
	//赋值构造的转移语义
	good_ptr& operator=(good_ptr& that){
		if(&that != this){
			reset(that.release());
		}
		return *this;
	}
	T& operator*(void)const{
		return *m_p;
	}
	T* operator->(void)const{
		return &*(*this);
		/*
		 * return &(*this).operator*();
		 * return &(*m_p);
		 * return m_p;
		 */
	}
	private:
	T* m_p;
	T* release(void){
		T* p = m_p;
		m_p = NULL;
		return p;
	}
	void reset(T* p){
		if(p != m_p){
			delete[] m_p;
			m_p = p;
		}
	}
};
int main(){
	//auto_ptr<A>  pa(new A);//首先实例化一个A类型的智能指针,然后实例化一个对象;
	
	/*A* pa = new A[7];
	cout << *((int*)pa -1) << endl;
	delete[] pa;
	//delete后面的[]会向后退回4个字节，拿到数组元素的个数，然后依次delete
	*/
	good_ptr<A> pa(new A(1234));
	cout <<(*pa).m_data << endl;
	pa->print();
	good_ptr<A> pb = pa;//good_ptr实际上是完成了一次转移(接管)
	cout <<(*pb).m_data << endl;
	pb->print();
	good_ptr<A[]> pc(new A[2]);
	return 0;
}
