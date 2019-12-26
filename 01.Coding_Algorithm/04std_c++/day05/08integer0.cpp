#include <iostream>
using namespace std;
class Integer{
	int data;
	public:
	Integer(int data = 0):data(data){}
	void show(){
		cout << "data = " << data << endl;
	}
	// i1.operator+(i2)
	const Integer operator+(const Integer& i2){
		cout << "mem operator+" << endl;
		return Integer(this->data+i2.data);//this->在此可以省略
	}
};

int main(){
	Integer a(100);
	Integer b(200);
	Integer c = a + b;
	c.show();
}
