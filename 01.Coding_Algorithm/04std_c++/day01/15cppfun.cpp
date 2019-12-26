#include <iostream>
using namespace std;
extern "C" int getmax(int x, int y) {
	return x > y ? x : y;
}
double getmax(int x, double y) {
	return x > y ? x : y;
}
int main() {
	getmax(1, 2);
	getmax(1, 2.1);
}
