/*
 * 命名空间可以分段定义
 */
#include <iostream>
using namespace std;
namespace IBM {
	int age = 100;
	void show() {
		cout << "IBM's age is" << age << endl;
	}
}
namespace school {
	int age = 12;
	void show();
}
namespace school {
	void show() {
		cout << "School's age is" << age << endl;
	}
}
int main() {
	/*使用命名空间IBM下的show() */
	IBM::age = 60;
	IBM::show();
	/*把命名空间school下的age改成13,调用这个空间下的show */
	school::age = 13;
	school::show();
}
