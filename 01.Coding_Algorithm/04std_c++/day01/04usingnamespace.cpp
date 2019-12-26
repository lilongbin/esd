/*
 * 使用using namespace指令
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
	double salary = 12345;
}
namespace school {
	void show() {
		cout << "School's age is" << age << endl;
	}
}
/*使用using namespace指令*/ using namespace IBM;
using namespace school;
int main() {
	//age = 101; //会发生冲突
	//show();
	cout << salary << endl;
	IBM::show();
	school::show();
}
