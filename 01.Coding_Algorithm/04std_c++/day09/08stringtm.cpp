#include <ctime>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;
int main(){
	string filename = "wtmpx";
	time_t t = time(NULL);
	struct tm* mytm = localtime(&t);
	ostringstream ostr;
	ostr << setfill('0') <<mytm->tm_year+1900
		<< setw(2) << mytm->tm_mon +1
		<< setw(2) << mytm->tm_mday << "-"
		<< setw(2) << mytm->tm_hour << ":"
		<< setw(2) << mytm->tm_min << ":"
		<< setw(2) << mytm->tm_sec
		<< filename;
	filename = ostr.str();
	cout << filename << endl;
}
