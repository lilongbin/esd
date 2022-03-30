/*
 * extern "C"
 */
#include <iostream>
using namespace std;
extern "C" void *memcpy(void *, void *, size_t);
int main() {
	int var_x = 9527;
	int var_y = 2014;
	memcpy(&var_y, &var_x, 4);
	cout << " var_y = " << var_y << endl;
}
