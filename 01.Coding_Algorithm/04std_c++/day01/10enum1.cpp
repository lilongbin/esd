/*
 * enum
 */
#include <iostream>
using namespace std;

namespace Direction {
    enum Direction { D_UP, D_DOWN, D_LEFT, D_RIGHT };
}

int main() {
	//定义一个变量为Direction类型,取值只能是定义中的;
    Direction::Direction dire = Direction::D_UP;
	cout << dire << endl;
	dire = Direction::D_LEFT;
	cout << dire << endl;
	//枚举的本质就是一个整数
	int x = dire;
	cout << "x = " << x << endl;
	//dire = 1;//这里编译出错,不能把一个整数赋值给枚举类型,体现了c++类型检查严格;
}
