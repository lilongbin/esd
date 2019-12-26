#include <iostream>
using namespace std;
class DmsClientException{
	string msg;
	public:
	DmsClientException(string msg="dms client exception"){
		this->msg = msg;
	}
	virtual const char* what()const throw(){
		return msg.c_str();
	}
};
class DmsReaderException:public DmsClientException{
	public:
	DmsReaderException(string msg="dms reader exception"):DmsClientException(msg){
		
	}
};
void readlogs()throw(DmsReaderException){
	if(1 == 1){
		throw DmsReaderException("backup file failed");
	}
}
int main(){
	try{
	try{
		readlogs();
	}catch(DmsReaderException& e){
		//cout << e.what() << endl;
		//不能处理就继续上抛
		//也可以再包装一次再上抛
		cout << "这一层处理不了，请求上级处理"<< endl;
		throw ;
	}
	cout << "app continue" << endl;
	}catch(DmsReaderException& e){
		cout << e.what() << endl;
	}
}
