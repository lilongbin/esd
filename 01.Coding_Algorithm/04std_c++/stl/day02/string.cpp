/*****************************************
 * Copyright (C) 2018 * Ltd. All rights reserved.
 *
 * File name   : string.cpp
 * Author      : longbin
 * Created date: 2018-08-01 19:01:50
 * Description :
 *
 *******************************************/
#include <cstring>
#include <cstdlib>
#include <iostream>

#include <string>
#include <vector>
using namespace std;

#define print(s) do {cout << "[" << __func__ << "] " << #s << ": "  << s << endl;} while (0);

typedef struct {
	int type;
	int status;
	string number;
} CallInfo;

void string_construct()
{
	// default (1)    string();
	// copy (2)       string (const string& str);
	// substring (3)  string (const string& str, size_t pos, size_t len = npos);
	// from c-string (4) string (const char* s);
	// from sequence (5) string (const char* s, size_t n);
	// fill (6)          string (size_t n, char c);
	// range (7) template <class InputIterator>
	//                   string  (InputIterator first, InputIterator last);

	string str0("hello c++ string");
	print(str0);
	// 1 empty string constructor (default constructor)
	// Constructs an empty string, with a length of zero characters.
	string str1;
	print(str1);
	// strcpy(str1, "hello c++ string str1."); // error
	// str1 = str0; // OK

	// 2 copy constructor
	// Constructs a copy of str.
	string str2(str0);
	print(str2);

	// 3 substring constructor
	string str3(str0, 3, 5); // 位置+长度
	print(str3);

	// 4 from c-string
	// Copies the null-terminated character sequence (C-string) pointed by s.
	string str4("hello c++ string from c-string");
	print(str4);

	// 5 from buffer
	// Copies the first n characters from the array of characters pointed by s.
	string str5("hello c++ string from c-string buf", 20); //长度
	print(str5);

	// 6 fill constructor
	// Fills the string with n consecutive copies of character c.
	string str6(6, 's');
	print(str6);

	// 7 range constructor
	// Copies the sequence of characters in the range [first,last), in the same order.
	string str7(str0.begin(), str0.begin()+5);
	print(str7);
	// string_construct>>30>>str0# hello c++ string
	// string_construct>>34>>str1#
	// string_construct>>41>>str2# hello c++ string
	// string_construct>>45>>str3# lo c+
	// string_construct>>50>>str4# hello c++ string from c-string
	// string_construct>>55>>str5# hello c++ string fro
	// string_construct>>60>>str6# ssssss
	// string_construct>>65>>str7# hello
}

void string_assign()
{
	//string (1)      string& operator= (const string& str);
	//c-string (2)    string& operator= (const char* s);
	//character (3)   string& operator= (char c);
	string s1, s2, s3;
	s1 = "string test"; // (2)
	s2 = 't';           // (3)
	s3 = s1 + s2;       // (1)
	string s = "hello"; // 1 empty string constructor 2. c-string assign;

	// string (1)     string& assign (const string& str);
	// substring (2)  string& assign (const string& str, size_t subpos, size_t sublen);
	// c-string (3)   string& assign (const char* s);
	// buffer (4)     string& assign (const char* s, size_t n);
	// fill (5)       string& assign (size_t n, char c);
	// range (6)  template <class InputIterator>
	//                string& assign (InputIterator first, InputIterator last);

	string base = "c++ string assign test";
	string str;
	char str7[] = "hello str7.";

	str.assign(base);                   // (1)
	print(str);
	str.assign(base, 4, 6);             // (2) 位置+长度
	print(str);
	str.assign("assign from c-string"); // (3)
	print(str);
	str.assign(str7);                   // (3)
	print(str);

	str.assign("assign from buffer", 20); // (4) 长度
	print(str); // assign from bufferh
	str.assign(8, '*');                   // (5)
	print(str);
	str.assign<int>(10, 0x2D);            // (5)
	print(str); // ----------
	str.assign(base.begin()+4, base.end()-1); // (6)
	print(str);
}

void string_clear()
{
	return;
	// Erases the contents of the string, which becomes an empty string (with a length of 0 characters).
	char c;
	std::string str;
	std::cout << "Please type some lines of text. Enter a dot (.) to finish:\n";
	do {
		c = std::cin.get();
		str += c;
		if (c=='\n')
		{
			std::cout << str;
			str.clear();
		}
	} while (c!='.');
}

void string_c_str()
{
	// Get C string equivalent
	// Returns a pointer to an array that contains a null-terminated sequence of characters (i.e., a C-string) representing the current value of the string object.
	// This array includes the same sequence of characters that make up the value of the string object plus an additional terminating null-character ('\0') at the end.
	string str1 = "hello c++ string c_str()";
	print(str1);
	print(str1.c_str());

	char buf[128] = {0};
	// strcpy(buf, str1); // error
	strcpy(buf, str1.c_str()); // OK
	print(buf);

	char * cstr = new char[str1.length() + 1];
	strcpy(cstr, str1.c_str()); // cstr now contains a c-string copy of str
	print(cstr);
}

void string_data()
{
	// c_str() 返回的字符串数组以'\0'结尾, data()难以保证，不一定以'\0'结尾，慎用；
	// Returns a pointer to an array that contains the same sequence of characters as the characters that make up the value of the string object.
	// Accessing the value at data()+size() produces undefined behavior: There are no guarantees that a null character terminates the character sequence pointed by the value returned by this function. See string::c_str for a function that provides such guarantee.
	string str = "hello c++ string";
	const char *p = "hello c++ string";

	if (str.length() == strlen(p))
	{
		cout << "str and p have the same length." << endl;
		if (memcmp(p, str.data(), str.length()))
		{
			cout << "str and p have the same content." << endl;
		}
	}
}

void string_at()
{
	// Get character in string
	// Returns a reference to the character at position pos in the string.
	string str1 = "1234567890";

	print(str1);       //1234567890
	print(str1.at(3)); //4
	// print(str1.at(str1.length())); // out of range

	print(str1[3]);
	// print(str1[-1]); //空
}

void string_begin_end()
{
	string str1 = "1234567890";

	string::iterator it;
	for (it = str1.begin(); it != str1.end(); it++)
	{
		print(*it);
	}
	print(*str1.begin());   //1
	print(*str1.end());     //
	print(*(str1.end()-1)); //0
}

void string_append()
{
	// string (1)    string& append (const string& str);
	// substring (2) string& append (const string& str, size_t subpos, size_t sublen);
	// c-string (3)	 string& append (const char* s);
	// buffer (4)    string& append (const char* s, size_t n);
	// fill (5)	     string& append (size_t n, char c);
	// range (6) template <class InputIterator>
	//               string& append (InputIterator first, InputIterator last);
	string str1 = "hello ";
	string str2 = "c++ ";
	print(str1);
	print(str2);

	str1.append(str2);                                   // (1)
	cout << "str1.append(str2): " << str1 << endl;       //hello c++

	str1.append(str2, 1, 2);                             // (2)
	cout << "str1.append(str2, 1, 2): " << str1 << endl; //hello c++ ++

	str1.append("good");                                 // (3)
	cout << "str1.append(\"good\"): " << str1 << endl;   //hello c++ ++good

	str1.append("good", 3);                              // (4)
	cout << "str1.append(\"good\", 3): " << str1 << endl;//hello c++ ++goodgoo

	str1.append(5, '-');                                 // (5)
	cout << "str1.append(5, '-'): " << str1 << endl;     //hello c++ ++goodgoo-----

	str1.append(str2.begin()+1, str2.end()-1);           // (6)
	cout << "str1.append(str2.begin()+1, str2.end()-1): " << str1 << endl; //hello c++ ++goodgoo-----++
}

void string_replace()
{
	// string (1)	string& replace (size_t pos,  size_t len,  const string& str);
	//              string& replace (iterator i1, iterator i2, const string& str);
	// substring (2)  string& replace (size_t pos,  size_t len,  const string& str, size_t subpos, size_t sublen);
	// c-string (3)   string& replace (size_t pos,  size_t len,  const char* s);
	//                string& replace (iterator i1, iterator i2, const char* s);
	// buffer (4)	string& replace (size_t pos,  size_t len,  const char* s, size_t n);
	//              string& replace (iterator i1, iterator i2, const char* s, size_t n);
	// fill (5)	      string& replace (size_t pos,  size_t len,  size_t n, char c);
	//                string& replace (iterator i1, iterator i2, size_t n, char c);
	// range (6)  template <class InputIterator>
	//                string& replace (iterator i1, iterator i2, InputIterator first, InputIterator last);

	//                  0123456789*23456789*123
	std::string base = "this is a test string.";
	std::string str2 = "n example";
	std::string str3 = "sample phrase";
	std::string str4 = "useful.";

	// replace signatures used in the same order as described above:
	// 位置参数的前2个表示替换范围,后面是使用的字符串
	// Using positions:                   0123456789*123456789*12345
	std::string str = base;           // "this is a test string."
	str.replace(9, 5, str2);          // "this is an example string." (1) str[9:+5]   <-- str2;
	str.replace(19, 6, str3, 7, 6);   // "this is an example phrase." (2) str[19:+6]  <-- str3[7:+6];
	str.replace(8, 10, "just a");     // "this is just a phrase."     (3) str[8:+10]  <-- "just a";
	str.replace(8, 6, "a shorty", 7); // "this is a short phrase."    (4) str[8:+6]   <-- "a shorty"[:+7];
	str.replace(22, 1, 3, '!');       // "this is a short phrase!!!"  (5) str[22:+1]  <-- 3*'!';

	// Using iterators:                                                  0123456789*123456789*
	str.replace(str.begin(), str.end()-3, str3);                     // "sample phrase!!!"      (1)
	str.replace(str.begin(), str.begin()+6, "replace");              // "replace phrase!!!"     (3)
	str.replace(str.begin()+8, str.begin()+14,"is coolness", 7);     // "replace is cool!!!"    (4)
	str.replace(str.begin()+12, str.end()-4, 4, 'o');                // "replace is cooool!!!"  (5)
	str.replace(str.begin()+11, str.end(), str4.begin(), str4.end());// "replace is useful."    (6)
	print(str); // replace is useful.
}

void string_capacity()
{
	// Return size of allocated storage
	//     Returns the size of the storage space currently allocated for the string, expressed in terms of bytes.
	// The capacity of a string can be explicitly altered by calling member reserve.
	string str1 = "hello c++ string.";

	print(str1.length());
	print(str1.size()); // <==> length()
	print(str1.capacity());
	print(str1.max_size());

	str1 = "0123456789*123456789*123456789*123456789";
	print(str1.length());   //40
	print(str1.capacity()); //40

	str1 = "hello c++";
	print(str1.length());   //9
	print(str1.capacity()); //40

	CallInfo info;
	// c++ string 作为结构体时, 需要使用new而不是malloc来申请空间
	info.type = 5;
	info.status = 6;
	info.number = "123456789012";
	print(sizeof(info)); //16

	string str_hello = "hello world";
	print(str_hello);
	print(sizeof(str_hello)); //8

	string crash = "hello";
	print(crash);
	crash.clear();
	print(crash);
	// 用sizeof来返回类型以及静态分配的对象/结构/数组所占的空间,返回值跟对象/结构/数组所存储的内容没有关系;
	// 当参数分别如下时,sizeof返回的值表示的含义如下:
	//     数组——编译时分配的数组空间大小;
	//     指针——存储该指针所用的空间大小(存储该指针的地址的长度，是长整型，应该为4);
	//     类型——该类型所占的空间大小;
	//     对象——对象的实际占用空间大小;
	//     函数——函数的返回类型所占的空间大小。函数的返回类型不能是void;
	char arr0[20] = "hello arr0";
	char arr1[]   = "hello arr1";
	char *pstr = new char[20];
	strcpy(pstr, arr0);
	//sizeof不是一个函数,sizeof可以不加括号;sizeof更像一个特殊的宏,它是在编译阶段求值的;
	//注意sizeof()中的语句不会生效;
	//sizeof(string)和字符串的长度是无关的,在一个系统中所有的sizeof(string)是一个固定值;
	//这个和编译器相关,string字符串是存储在堆上,这个属于动态分配的空间;
	string sstr = "hello sstr";

	print(sizeof(arr0)); //20
	print(sizeof(arr1)); //11
	print(sizeof(pstr)); //8
	print(sizeof(sstr)); //8
	print(sstr);
	sizeof(sstr = "sizeof expr");
	print(sstr); //"hello sstr"
}

void string_length()
{
	// Return length of string
	//     Returns the length of the string, in terms of bytes.

	//          0123456789*12345
	string str("hello c++ string");
	print(str.length()); //16
}

void string_size()
{
	// Return length of string
	//     Returns the length of the string, in terms of bytes.

	//          0123456789*12345
	string str("hello c++ string");
	print(str.size()); //16
	// length是因为沿用C语言的习惯而保留下来的,string类最初只有length;
	// 引入STL之后,为了兼容又加入了size,它是作为STL容器的属性存在的,便于符合STL的接口规则,以便用于STL的算法;
	// string类的size()/length()方法返回的是字节数,不管是否有汉字;
}

void string_erase()
{
	// sequence (1)    string& erase (size_t pos = 0, size_t len = npos);
	//           Erases the portion of the string value that begins at the character position pos and spans len characters;
	//           or until the end of the string, if either the content is too short or if len is string::npos.
	//           Notice that the default argument erases all characters in the string (like member function clear).
	//  character (2)  iterator erase (iterator p);
	//           Erases the character pointed by p.
	//  range (3)	   iterator erase (iterator first, iterator last);
	//           Erases the sequence of characters in the range [first,last).

	//          0123456789*123456789*123
	string str("hello c++ string example");
	print(str);

	str.erase(17, 7);             // (1)
	print(str); //hello c++ string
	str.erase(str.begin()+10);    // (2) Erases the character pointed by p.
	print(str); //hello c++ tring
	str.erase(str.begin()+6, str.begin()+8); // (3)
	print(str); //hello + tring
	str.erase();                  // (1) <==> str.clear();
	print(str); //
}

void string_insert()
{
	// string (1)     string& insert (size_t pos, const string& str);
	// substring (2)  string& insert (size_t pos, const string& str, size_t subpos, size_t sublen);
	// c-string (3)   string& insert (size_t pos, const char* s);
	// buffer (4)     string& insert (size_t pos, const char* s, size_t n);
	// fill (5)     string& insert (size_t pos, size_t n, char c);
	//                 void insert (iterator p, size_t n, char c);
	// single character (6)	iterator insert (iterator p, char c);
	// range (7)	template <class InputIterator>
	//                 void insert (iterator p, InputIterator first, InputIterator last);

	//                  0123456789*123
	std::string str  = "to be question";
	std::string str2 = "the ";
	std::string str3 = "or not to be";
	std::string::iterator it;

	// used in the same order as described above:
	//                                             0123456789*123456789*123456789
	str.insert(6, str2);                 // (1) // to be the question
	print(str);
	str.insert(6, str3, 3, 4);           // (2) // to be not the question
	str.insert(10, "that is cool", 8);   // (4) // to be not that is the question
	str.insert(10, "to be ");            // (3) // to be not to be that is the question
	str.insert(15, 1, ':');              // (5) // to be not to be: that is the question
	it = str.insert(str.begin()+5, ','); // (6) // to be, not to be: that is the question
	str.insert(str.end(), 3, '.');       // (5) // to be, not to be: that is the question...
	str.insert(it+2, str3.begin(), str3.begin()+3); // (7) // to be, or not to be: that is the question...
	print(str);
}

void string_empty()
{
	// Test if string is empty
	//     Returns whether the string is empty (i.e. whether its length is 0).
	string str0 = "hello c++ string";
	string str1 = str0;
	string str2 = "";
	string str3;

	print(str0.empty()); // 0
	print(str1.empty()); // 0
	print(str2.empty()); // 1
	print(str3.empty()); // 1

	str0.erase();
	print(str0.empty()); // 1
	str1.clear();
	print(str1.empty()); // 1
}

void string_compare()
{
	// Compare strings
	//Compares the value of the string object (or a substring) to the sequence of characters specified by its arguments.

	// string (1)       int compare (const string& str) const;
	// substrings (2)   int compare (size_t pos, size_t len, const string& str) const;
	//                  int compare (size_t pos, size_t len, const string& str, size_t subpos, size_t sublen) const;
	// c-string (3)     int compare (const char* s) const;
	//                  int compare (size_t pos, size_t len, const char* s) const;
	// buffer (4)       int compare (size_t pos, size_t len, const char* s, size_t n) const;
	string str0 = "hello c++ string 0";
	string str1 = "hello c++ string 1";
	string str2 = "hello c++ string 2";
	string str3 = "hello c++ string 0";
	string str4 = "c++";

	print(str1.compare(str2));                  // (1) // <0
	print(str0.compare(str3));                  // (1) // ==0
	print(str2.compare(str1));                  // (1) // >0
	print(str0.compare(6, 3, str4));            // (2) // ==0
	print(str0.compare(6, 3, str1, 6, 3));      // (2) // ==0
	print(str0.compare("hello c++ string 0"));  // (3) // ==0
	print(str0.compare(6, 3, "c++"));           // (3) // ==0
	print(str0.compare(6, 3, "c++ good", 3));   // (4) // ==0
}

void string_copy()
{
	// size_t copy (char* s, size_t len, size_t pos = 0) const;
	// Copy sequence of characters from string
	// The function does not append a null character at the end of the copied content.
	char buf[128] = "9876543210";
	string str1 = "0123456789";
	print(str1);

	size_t size = str1.copy(buf, 4, 3); //str len index
	print(buf);         // 3456543210
	print(strlen(buf)); // 10
	print(size);        // 4
	buf[size] = '\0';
	print(buf);         // 3456
	print(strlen(buf)); // 4

	// std::copy()
	// template <class InputIterator, class OutputIterator>
	//          OutputIterator copy (InputIterator first, InputIterator last, OutputIterator result);
	// Copy range of elements
	//   Copies the elements in the range [first,last) into the range beginning at result.]
	string str = "9876543210";
	std::copy(str1.begin()+3, str1.begin()+7, str.begin()); // [3, 7); // no '\0' end;
	print(str);                // 3456543210
	print(strlen(str.data())); // 10
	print(str.length());       // 10

	str.assign(str1, 3, 4);
	print(str);                // 3456
	print(strlen(str.data())); // 4
	print(str.length());       // 4
}

void string_find()
{
	// Find content in string
	//   Searches the string for the first occurrence of the sequence specified by its arguments.
	// Return Vaulue:
	//   The position of the first character of the first match.
	//   If no matches were found, the function returns string::npos.
	// string (1)    size_t find (const string& str, size_t pos = 0) const;
	// c-string (2)  size_t find (const char* s, size_t pos = 0) const;
	// buffer (3)    size_t find (const char* s, size_t pos, size_t n) const;
	// character (4) size_t find (char c, size_t pos = 0) const;
	string str = "hello c++ string find c++";
	string f1 = "c++";
	size_t fpos = 0;

	fpos = str.find(f1);                             // (1)
	cout << "first c++ found at: " << fpos << endl;
	fpos = str.find(f1, fpos+1);                     // (1)
	cout << "second c++ found at: " << fpos << endl;

	fpos = str.find("c++");                          // (2)
	cout << "c++ found at: " << fpos << endl;
	fpos = str.find("c++", 2);                       // (2)
	cout << "c++ found at: " << fpos << endl;

	fpos = str.find("c++ good", 7, 3);               // (3) //str[pos:] "c++ good"[:3]
	cout << "c++ found at: " << fpos << endl;// 22   // found "c++" from "hello c(++ string find c++)"

	fpos = str.find('+', 15);                        // (4)
	cout << "+ found at: " << fpos << endl;  // 23   // found '+' from "hello c++ strin(g find c++)"
}

void string_substr()
{
	// string substr (size_t pos = 0, size_t len = npos) const;
	// Generate substring
	// Returns a newly constructed string object with its value initialized to a copy of a substring of this object.
	string str1 = "hello c++ string substr.";
	string sub;
	size_t pos;

	pos = str1.find("c++", 0);
	sub = str1.substr(pos);
	print(sub);

	sub = str1.substr(pos, 3);
	print(sub);

	string info(17, '6');
	size_t step = 6;
	// string info(20, '6');
	// size_t step = 20;
	for (pos = 0; pos < info.length(); pos+=step)
	{
		cout << pos << ": " << info.substr(pos, step) << endl;
	}
}

vector<string> split(string &src, const string & delim)
{
	vector<string> lst;
	size_t pos1 = 0;
	size_t pos2 = 0;
	string sstr;

	// print(src);
	// print(delim);
	while (string::npos != (pos2 = src.find(delim, pos1)))
	{
		sstr = src.substr(pos1, pos2-pos1);
		// print(sstr);
		lst.push_back(sstr);
		pos1 = pos2 + delim.size();
	}

	if (src.length() != pos1)
	{
		lst.push_back(src.substr(pos1));
	}
	return lst;
}

	template <class T>
string join(T& val, string delim)
{
	string str;
	string ele;
	typename T::iterator it;
	for (it = val.begin(); it != val.end(); it++)
	{
		ele = *it;
		str.append(ele);
		if (it != val.end()-1)
		{
			str.append(delim);
		}
	}
	return str;
}

string strip(string str, const string delim="")
{
	string chr;
	string::iterator it;
	string sp = delim;

	if (0 == sp.length())
	{
		//print(sp);
		sp = " \t\n\v\f\r";
	}
	while (string::npos != sp.find(str.at(0)))
	{
		str.erase(0, 1);
	}
	while (string::npos != sp.find(str.at(str.length()-1)))
	{
		str.erase(str.length()-1, 1);
	}
	return str;
}

string mask(const string &src, int pos, int masklen)
{
	string ret = src;
	string mask = "";
	int length = (int)ret.length();
	int replen = 0;
	if (pos < 0)
	{
		// mask from tail
		pos = length + pos;
	}
	if ((pos < 0) || (length <= pos))
	{
		// pos is out of range
		return ret;
	}
	if (masklen >= 0)
	{
		replen = ((length - pos) > masklen) ? masklen : (length - pos);
	}
	else
	{
		// mask from tail
		replen = ((pos + 1) > -masklen) ? -masklen : (pos + 1);
		pos = (pos + 1) - replen;
	}

	if ((pos >= 0) && (pos < length))
	{
		// cout << "true" << endl;
		mask.assign(replen, '*');
		ret = ret.replace(pos, replen, mask);
	}
	return ret;
}

int main() {
	string split_line(30, '#');
	cout << split_line << endl;

	string_construct();
	string_assign();
	string_clear();

	string_c_str();
	string_data();

	string_at();
	string_begin_end();

	string_append();
	string_erase();
	string_insert();
	string_replace();

	string_capacity();
	string_length();
	string_size();
	string_empty();

	string_compare();
	string_copy();
	string_find();
	string_substr();

	// extended function
	// join(str, delim);
	vector<string> vec(4, "good");
	print(join(vec, "/"));
	string jstr(6, '0');
	print(join(jstr, "-"));

	// split(str, delim);
	string str = "/usr/local/bin/python";
	vector<string> vt = split(str, "/");
	vector<string>::iterator it;
	for (it = vt.begin(); it != vt.end(); it++)
	{
		print(*it);
	}

	// strip(str, chars);
	str = "  0hello good 0  ";
	str = strip(str, "0 ");
	print(str);
	print(str.length());
	// strip(str);
	str = "  0hello good 0  ";
	str = strip(str);
	print(str);
	print(str.length());

	// mask
	string test = "01234567890";
	print(test);
	print(mask(test, 1, 3));   //0***4567890
	print(mask(test, 0, 4));   //****4567890
	print(mask(test, -1, -3)); //01234567***

	cout << split_line << endl;
	return 0;
}
