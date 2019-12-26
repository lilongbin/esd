#include <iostream>
#include <sstream>
#include <iomanip>//io manipulator
using namespace std;
int main(){
	string filename = "wtmpx";
	int year = 2014;
	int month = 3;
	int day = 8;
	ostringstream ostr;//创建输出流对象
	ostr << filename;
	/*设置显示固定宽度，不够就补0*/
	ostr << setfill('0')
		<< year << "-" 
		<< setw(2) << month << "-" 
		<< setw(2) << day;
	string mystr = ostr.str();
	cout << mystr << endl;
}
