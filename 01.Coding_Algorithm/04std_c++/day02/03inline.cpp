/*
 * inline函数
 */
#include <iostream>
using namespace std;
inline int getmax(int x, int y) {
	return x > y ? x : y;
}
int getmin(int x, int y) {
	return x < y ? x : y;
}
int main() {
	getmax(1, 2);
	getmin(1, 2);
}
