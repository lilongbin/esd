#include <iostream>
using namespace std;
int main() {
	bool flag = false;
	//bool类型的4大假:false,0,'\0',NULL;除此之外的任何赋值都为真;
	flag = "abc";
	if (flag) {
		cout << "flag is true" << endl;
	} else {
		cout << "flag is false" << endl;
	}
	int age = 100;
	cout << age << "地址" << &age << endl;
	cout << age << "地址" << bitand(age) << endl;
}
