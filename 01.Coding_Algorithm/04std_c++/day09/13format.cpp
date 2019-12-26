#include <iostream>
#include <iomanip>
using namespace std;
int main(){
	int x = 1234;
	cout << x << endl;
	cout << hex << x << endl;
	int y = 456;
	cout << y << endl;
	cout << dec << y << endl;
	cout << setfill('0') << setw(6) << y << endl;
	bool f = false;
	cout << f << endl;
	cout << boolalpha << f << endl;
}
