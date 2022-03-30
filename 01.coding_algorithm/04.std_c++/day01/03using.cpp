/*
 * using namespace声明
 */
#include <iostream>
using namespace std;
namespace IBM {
	int age = 100;
	void show() {
		cout << "IBM's age is " << age << endl;
	}
}
namespace school {
	int age = 12;
	void show();
}
namespace school {
	void show() {
		cout << "School's age is " << age << endl;
	}
}
/*使用using声明*/ using IBM::age;
using IBM::show;
//using school::age;//冲突了
//using school::show;
int main() {
	IBM::show();		//第1种方式;
	show();			//第2种方式,有可能会出现冲突;
	show();
}
