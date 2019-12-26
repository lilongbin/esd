//const int *p 等价于const int* p 等价于int const *p,
//const修饰的是int,因此*p只读,普通变量不可通过指针p更改
//而int* const p,const修饰的是int*,指针只读,p指向不可改;
//
#include <iostream>
using namespace std;
int main() {
	int i = 100;
	const int *pi = &i;
	//*pi = 200;//错误,不可以通过*pi修改变量的值;
	int j = 300;
	pi = &j;

	//数组名和对应的内存的关系;
	int* const myref = &i;	//指向不能改,i的值可以改;
	*myref = 12345;
	cout << *myref << endl;
	char data1[20] = "abc123";
	char data2[20] = "open123";
	//data1 = data2; //不合法
}
