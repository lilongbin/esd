/*
 * 函数重载
 */
#include <iostream>
using namespace std;
int getmax(int x, int y) {
	cout << "getmax(int,int)" << endl;
	return x > y ? x : y;
}
double getmax(int x, double y) {
	cout << "getmax(int,double)" << endl;
	return x > y ? x : y;
}
double getmax(double x, int y) {
	cout << "getmax(double,int)" << endl;
	return x > y ? x : y;
}
double getmax(double x, double y) {
	cout << "getmax(double,double)" << endl;
	return x > y ? x : y;
}
int main() {
	cout << getmax(10, 20) << endl;
	cout << getmax(10, 20.1) << endl;
	cout << getmax(10.1, 20) << endl;
	cout << getmax(10.1, 20.1) << endl;
}
