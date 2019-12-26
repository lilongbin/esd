/*
 * 函数参数默认值演示
 */
#include <iostream>
using namespace std;
int getmax(int x, int y = 0, int z = 0) {
}
int main() {
	getmax(1, 2, 0);
	getmax(1, 2);
	getmax(100);
}
