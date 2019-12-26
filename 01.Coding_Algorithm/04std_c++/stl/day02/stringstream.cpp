/*****************************************
 * Copyright (C) 2018 * Ltd. All rights reserved.
 * 
 * File name   : stringstream.cpp
 * Author      : longbin
 * Created date: 2018-08-10 11:16:23
 * Description : 
 *
 *******************************************/

#include <iostream>
#include <sstream>

using namespace std;

int stringstream_test()
{
	stringstream stream;
	int a, b;

	// string to int
	stream << "80";
	stream >> a;
	cout << "length() of stream: " << stream.str().length() << endl; //2

	stream.clear(); //clear error state flag;
	stream.str(""); //copy "" to string object;

	cout << "length() of stream: " << stream.str().length() << endl; //0

	stream << "90";
	stream >> b;

	cout << "length() of stream: " << stream.str().length() << endl; //2

	cout << a << endl; //80
	cout << b << endl; //90

	return 0;
}

int main() {
	stringstream_test();
	return 0;
}

