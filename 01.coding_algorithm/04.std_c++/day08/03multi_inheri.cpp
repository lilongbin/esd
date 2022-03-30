#include <iostream>
using namespace std;
class Product{
	public:
	double price;
	Product(double price = 0):price(price){}
	double getPrice(){
		return price;
	}
};
class Phone:virtual public Product{
	public:
	Phone(double price = 0):Product(price){}
	void phoneCall(){
		cout << "使用phone打电话" << endl;
	}
};
class Camera:virtual public Product{
	public:
	Camera(double price = 0):Product(price){}
	void cameraFun(){
		cout << "使用camera拍照" << endl;
	}
};
class Mp3:virtual public Product{
	public:
	Mp3(double price = 0):Product(price){}
	void mp3Fun(){
		cout << "使用mp3听音乐" << endl;
	}
};
//IPhone继承多个类
//多继承的构造顺序和继承顺序一致
class IPhone:public Phone,public Camera,public Mp3{
	//名字隐藏
	public:
	IPhone(double p=0,double c=0,double m=0):Mp3(m),Camera(c),Phone(p),Product(p+c+m){}
/*	double getPrice(){//注意名字隐藏
		return Mp3::getPrice()+Camera::getPrice()+Phone::getPrice();
	}*/
};
int main(){
	IPhone iphone;
	cout << sizeof(double) << endl;//8
	cout << sizeof(Product) << endl;//8
	cout << sizeof(Phone) << endl;//12 = 8 + 4*1//虚继承由一个指针维护
	cout << sizeof(IPhone) << endl;//20 = 8 + 4*3//加三个指针
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
	Phone phone(998);
	cout << phone.getPrice() << endl;
}
