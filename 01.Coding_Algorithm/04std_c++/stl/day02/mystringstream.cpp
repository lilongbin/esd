/*****************************************
 * Copyright (C) 2018 * Ltd. All rights reserved.
 * File name   : stringstream.cpp
 * Created date: 2018-08-10 11:16:23
 *******************************************/

#include <iostream>
#include <iomanip> //std::hex, std::setw, std::setfill
#include <sstream>

using namespace std;
#define print(x) std::cout << __func__ << ">>" << __LINE__ << ">>" << #x << "# " << x << std::endl

    template <class T>
T stringToNumber(const std::string str)
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

void toHexString()
{
    std::ostringstream oss {};
    char buff[20] = "0123456789abcdef";
    std::string payload;
    int i = 0;
    for (i = 0; i < 16; i++) {
        oss << std::hex << std::setw(2) << std::setfill('0') << buff[i];
        oss << " ";
    }
    payload = oss.str();
    print(payload);
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
    str = "043414.00";
    long li = stringToNumber<long>(str);
    print(li);

    toHexString();
	return 0;
}

