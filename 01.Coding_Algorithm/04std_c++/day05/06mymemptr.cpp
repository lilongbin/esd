#include <iostream>
using namespace std;
class Date {
	int year;
	int month;
	int day;
	public:
	Date(int year,int month,int day):year(year),month(month),day(day){}
	
};

int main(){
	Date date(2014,10,1);
	int *mypm = reinterpret_cast<int*>(&date);//不按类型访问，不守规矩的访问
	cout << *mypm << endl;
	cout << *(mypm+1) << endl;
	cout << *(mypm+2) << endl;

}
