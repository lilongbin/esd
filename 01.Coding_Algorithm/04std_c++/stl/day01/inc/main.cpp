#include <iostream>
#include "07clstmpl.hpp"
using namespace std;
int main(){
	Comparator<int> ci(123,456);
	cout << ci.max() << ' ' << ci.min() << endl;
	Comparator<double> cd(1.23,4.56);
	cout << cd.max() << ' ' << cd.min() << endl;
	Comparator<string> cs("hello","world");
	cout << cs.max() << ' ' << cs.min() << endl;
	Comparator<char const*> cp("hello","world");//需要特化模板
	cout << cp.max() << ' ' << cp.min() << endl;
	return 0;
}
