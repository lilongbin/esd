/*****************************************
* Copyright (C) 2018 * Ltd. All rights reserved.
* File name   : test.cpp
* Author      : longbin
* Created date: 2018-07-18 23:44:33
*******************************************/

#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main()
{
	int age;
	string name;

	cout << "Please input name: ";
	cin >> name;
	cout << "please input age: ";
	cin >> age;

	cout << "name: " << name << endl;
	cout << "age:  " << age  << endl;

	return 0;
}
