/*
 * static_cast静态类型转换
 */
#include <iostream>
using namespace std;
int main() {
	int *pi = new int (100);
	void *vp = pi;
	int *pi2 = static_cast <int *>(vp);
	cout << *pi2 << endl; //100
}
