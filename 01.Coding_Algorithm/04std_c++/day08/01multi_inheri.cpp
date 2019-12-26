#include <iostream>
using namespace std;
class Phone{
	double price;
	public:
	Phone(double price = 0):price(price){}
	double getPrice(){
		return price;
	}
	void phoneCall(){
		cout << "使用phone打电话" << endl;
	}
};
class Camera{
	double price;
	public:
	Camera(double price = 0):price(price){}
	double getPrice(){
		return price;
	}
	void cameraFun(){
		cout << "使用camera拍照" << endl;
	}
};
class Mp3{
	double price;
	public:
	Mp3(double price = 0):price(price){}
	double getPrice(){
		return price;
	}
	void mp3Fun(){
		cout << "使用mp3听音乐" << endl;
	}
};
//IPhone继承多个类
//多继承的构造顺序和继承顺序一致
class IPhone:public Phone,public Camera,public Mp3{
	//名字隐藏
	public:
	IPhone(double p=0,double c=0,double m=0):Mp3(m),Camera(c),Phone(p){}
	double getPrice(){//注意名字隐藏
		return Mp3::getPrice()+Camera::getPrice()+Phone::getPrice();
	}
};
int main(){
	IPhone iphone;
	//iphone.getPrice();//歧义
	iphone.Phone::getPrice();//加上类名作用域
	iphone.Camera::getPrice();
	iphone.Mp3::getPrice();
	iphone.phoneCall();
	iphone.cameraFun();
	iphone.mp3Fun();
	cout << "---------" << endl;
	IPhone iphone4(1000,1001,28);
	cout << iphone4.Phone::getPrice() << endl;
	cout << iphone4.Mp3::getPrice()<< endl;
	cout << iphone4.getPrice() << endl;//名字隐藏
}
