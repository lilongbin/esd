/*****************************************
 * Copyright (C) 2018 * Ltd. All rights reserved.
 * File name   : stringstream.cpp
 * Created date: 2018-08-10 11:16:23
 *******************************************/

#include <iostream>
#include <sstream>

using namespace std;
#define print(x) std::cout << __func__ << ">>" << __LINE__ << ">>" << #x << "# " << x << std::endl

    template <class T>
T stringToNumber(const std::string &str)
{
    /* can auto remove leading 0 */
    std::istringstream iss(str);
    T number {};
    iss >> number;
    return number;
}

    template <class T>
std::string toString(T value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

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
    std::string str = "012345";
    int value = stringToNumber<int>(str);
    print(value); //12345
    str = toString<int>(45678);
    print(str); //45678
    str = toString<int>(01234);
    print(str); //668
	return 0;
}

