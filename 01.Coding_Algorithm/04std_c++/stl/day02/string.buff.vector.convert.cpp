/*****************************************
* Copyright (C) 2020 * Ltd. All rights reserved.
* File name   : string.buff.vector.convert.cpp
*******************************************/

/*
 * #include <cstdio>
 * #include <cstdlib>
 * #include <cstring>
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define print(s) do {cout << "[" << __func__ << "] " << #s << ": "  << s << endl;} while (0);

template <class T>
void show(T& val)
{
	typename T::iterator it;
	cout << "[" << __func__ << "]: ";
	for (it = val.begin(); it != val.end();)
	{
		cout << *it;
		it++;
		if (it != val.end()) {
			cout << ", ";
		}
	}
	cout << endl;
}

void buffer2string()
{
	char buffer[] = "hello 1234567890";
	string str(buffer);
	print(str);

	string str0;
	str0.assign(buffer);
	print(str0);

	string str1;
	str1.assign(buffer, sizeof(buffer)/sizeof(buffer[0])-1);
	print(str1);
}

void string2buffer()
{
	char buffer[20] = { 0 };
	string str = "hello 1234567890";

	/*
	 * strncpy(buffer, str.c_str(), str.size()+1);
	 * print(buffer);
	 */

	char buffer2[20] = { 0 };
	std::copy(str.begin(), str.end(), buffer2);
	print(buffer2);
}

void buffer2vector()
{
	char buffer[] = "hello 1234567890";
	vector<char> vec(buffer, buffer+sizeof(buffer)/sizeof(buffer[0])-1);
	show(vec);

	vector<char> vec2;
	vec2.assign(buffer, buffer+sizeof(buffer)/sizeof(buffer[0])-1);
	show(vec2);
}

void vector2buffer()
{
	char tmp[20] = "hello 1234567890";
	vector<char> vec(tmp, tmp+sizeof(tmp)/sizeof(tmp[0]));

	char buffer[20];
	std::copy(vec.begin(), vec.end(), buffer);
	print(buffer);
}

void string2vector()
{
	string str = "hello 1234567890";
	vector<char> vec(str.begin(), str.end());
	show(vec);

	vector<char> vec2;
	vec2.assign(str.begin(), str.end());
	show(vec2);
}

void vector2string()
{
	string tmp = "hello 1234567890";
	vector<char> vec(tmp.begin(), tmp.end());

	string str(vec.begin(), vec.end());
	print(str);

	string str2;
	str2.assign(vec.begin(), vec.end());
	print(str2);
}

int main() {
	buffer2string();
	string2buffer();
	buffer2vector();
	vector2buffer();
	string2vector();
	vector2string();
	return 0;
}
