#include <iostream>
using namespace std;
int getmax(int, int);
int main() {
	cout << getmax(10, 20) << endl;
}
int getmax(int x, int y) {
	return x > y ? x : y;
}
