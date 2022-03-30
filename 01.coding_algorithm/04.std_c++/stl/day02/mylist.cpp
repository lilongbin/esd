/*****************************************
* Copyright (C) 2018 * Ltd. All rights reserved.
* 
* File name   : list.cpp
* Author      : longbin
* Created date: 2018-08-02 19:18:13
* Description : 
*
*******************************************/

#include <iostream>
#include <string>
#include <list>

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

void lst_construct()
{
	// default (1)   explicit list (const allocator_type& alloc = allocator_type());
	// fill (2)      explicit list (size_type n, const value_type& val = value_type(),
	//                 const allocator_type& alloc = allocator_type());
	// range (3)	 template <class InputIterator>
	//   list (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
	// copy (4)      list (const list& x);

	// (1) empty container constructor (default constructor)
	// (2) fill constructor Constructs a container with n elements. Each element is a copy of val.
	// (3) range constructor Constructs a container with as many elements as the range [first,last)
	// (4) copy constructor Constructs a container with a copy of each of the elements in x, in the same order.

	list<int> li;                // (1) empty list of ints;
	list<string> ls;             // (1) empty list of strings;
	list<int> li2(6, 258);       // (2) 6 ints with value 258;
	list<int> li20(6);           // (2) 6 ints with value 0;
	list<string> ls2(3, "c++");  // (2) 3 strings with value of "c++";
	list<int> li3(li2.begin(), li2.end());     // (3) iteratoring from li2;
	list<string> ls3(ls2.begin(), ls2.end());  // (3) iteratoring from li2;
	list<int> li4(li2);          // (4) a copy of li2;
	list<string> ls4(ls2);       // (4) a copy of ls2;

	int arr[] = {1,2,3,4,5,6};
	list<int> li5 (arr, arr+sizeof(arr)/sizeof(int)); // initializer list (6) //c++11

	show(li);   // show: 
	show(ls);   // show: 
	show(li2);  // show: 258, 258, 258, 258, 258, 258
	show(li20); // show: 0, 0, 0, 0, 0, 0
	show(ls2);  // show: c++, c++, c++
	show(li3);  // show: 258, 258, 258, 258, 258, 258
	show(ls3);  // show: c++, c++, c++
	show(li4);  // show: 258, 258, 258, 258, 258, 258
	show(ls4);  // show: c++, c++, c++
	show(li5);  // show: 1, 2, 3, 4, 5, 6
}

void lst_OperatorEQ()
{
	// Assign content
	// Assigns new contents to the container, replacing its current contents, and modifying its size accordingly.

	// copy (1)	            list& operator= (const list& x);
	// move (2)             list& operator= (list&& x); //c++11
	// initializer list (3)	list& operator= (initializer_list<value_type> il); //c++11

	list<int> li1(5);
	list<int> li2(6, 1);
	show(li1);  //0, 0, 0, 0, 0
	show(li2);  //1, 1, 1, 1, 1, 1

	li2 = li1;
	li1 = list<int>();
	print(li1.size()); //0
	print(li2.size()); //5

	list<int> li3 = {1,2,3,4,5,6}; // c++11 要求类型相容
	list<int> li31  {1,2,3,4,5,6}; // c++11 =可省略
	show(li3);  // show: 1, 2, 3, 4, 5, 6
	show(li31); // show: 1, 2, 3, 4, 5, 6
}

void lst_begin_end()
{
	// iterator begin();
	// const_iterator begin() const;
	// Return iterator to beginning // Returns an iterator pointing to the first element in the list.

	// iterator end();
	// const_iterator end() const;
	// Return iterator to end // Returns an iterator referring to the past-the-end element in the list container.
	// vector,string,deque的迭代器有加减法;但list,map,set,multimap,multiset的迭代器是没有加减法的(+n/-n),只有++和--;
	list<int> li;
	list<int>::iterator it;
	int i = 0;
	for (i = 1; i <= 9; i++)
	{
		li.push_back(i);
	}

	cout << "[" << __func__ << "]: ";
	for (it = li.begin(); it != li.end();)
	{
		cout << *it;
		it++;
		if (it != li.end())
		{
			cout << ", ";
		}
	}
	cout << endl;
}

void lst_size()
{
	// Return size // Returns the number of elements in the list.
	// size_type size() const;

	list<int> li;
	print(li.size()); //0

	int i = 0;
	for (i = 1; i <= 9; i++)
	{
		li.push_back(i);
	}
	print(li.size()); //9
	li.insert(li.end(), 10, 100);
	print(li.size()); //19
	li.pop_back();
	print(li.size()); //18
}

void lst_capacity()
{
	cout << "capacity no such function for list" << endl;
}

void lst_empty()
{
	// bool empty() const;
	// Test whether list is empty
	// Returns whether the list is empty (i.e. whether its size is 0).
	// This function does not modify the container in any way. To clear the content of a list, see list::clear.

	list<int> li;
	int i = 0;
	int sum = 0;

	print(li.empty());  //1
	for (i = 1; i <= 9; i++)
	{
		li.push_back(i);
	}
	print(li.empty());  //0

	while (!li.empty())
	{
		sum += li.back();
		li.pop_back();
	}
	print(li.empty());  //1
	print(sum);         //45
}

void lst_OperatorAT()
{
	cout << "[] was not supported for list" << endl;
}

void lst_at()
{
	cout << "at() was not supported for list" << endl;
}

void lst_front()
{
	//  reference front();
	//  const_reference front() const;
	//  Access first element //  Returns a reference to the first element in the list.

	list<int> li;

	li.push_back(10);
	li.push_back(20);
	// now front equals 10, and back 20
	li.front() += li.back();
	print(li.front()); //30
}

void lst_back()
{
	// reference back();
	// const_reference back() const;
	// Access last element // Returns a reference to the last element in the list.

	list<int> li;
	li.push_back(10);
	print(li.back());
	while (0 != li.back())
	{
		li.push_back(li.back() - 1);
	}
	show(li); //10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
}

void lst_assign()
{
	// range (1)       template <class InputIterator>
	//                      void assign (InputIterator first, InputIterator last);
	// fill (2)        void assign (size_type n, const value_type& val);
	// initializer list (3)	void assign (initializer_list<value_type> il); //c++11

	// Assign list content
	// Assigns new contents to the list, replacing its current contents, and modifying its size accordingly.

	list<int> li1;
	list<int> li2;
	list<int> li3;

	li1.assign(6, 8);          // (2)
	show(li1);                 //8, 8, 8, 8, 8, 8

	li2.assign(li1.begin(), li1.end()); // (1)
	// li2.assign(li1.begin()+1, li1.begin()+3); // error, not support it+n/-n;
	show(li2);                 //8, 8, 8, 8, 8, 8

	int arr[] = {3, 6, 9, 2, 5, 8};
	li3.assign(arr, arr+3);    // (3) assign from array
	show(li3);                 //3, 6, 9
}

void lst_push_back()
{
	// void push_back (const value_type& val);
	// Add element at the end
	// Adds a new element at the end of the list, after its current last element.
	// The content of val is copied (or moved) to the new element.

	list<int> li;
	unsigned int i = 0;

	for (i = 0; i <= 9; i++)
	{
		cout << "[" << __func__ << "]: push_back " << i << endl;
		li.push_back(i);
	}
	show(li); //0, 1, 2, 3, 4, 5, 6, 7, 8, 9
}

void lst_pop_back()
{
	// void pop_back();
	// Delete last element
	// Removes the last element in the list, effectively reducing the container size by one.

	list<int> li;
	unsigned int i = 0;

	for (i = 0; i <= 9; i++)
	{
		li.push_back(i);
	}
	show(li);

	while (!li.empty())
	{
		cout << "[" << __func__ << "]: pop_back " << li.back() << endl;
		li.pop_back();
	}
}

void lst_insert()
{
	// single element (1)   iterator insert (iterator position, const value_type& val);
	// fill (2)             void insert (iterator position, size_type n, const value_type& val);
	// range (3)	template <class InputIterator>
	//                      void insert (iterator position, InputIterator first, InputIterator last);
	// move (4)             iterator insert (const_iterator position, value_type&& val); //c++11
	// initializer list (5)	iterator insert (const_iterator position, initializer_list<value_type> il); //c++11
	// Insert elements
	// The list is extended by inserting new elements before the element at the specified position,
	// effectively increasing the container size by the number of elements inserted.

	list<int> li(3, 9);
	list<int>::iterator it;
	show(li);              //9, 9, 9

	it = li.begin();
	++it;
	// it = it + 1;  //no match for ‘operator+’ in ‘it + 1’ in list;
	it = li.insert(it, 1); // (1)
	show(li);              //9, 1, 9, 9

	li.insert(it, 2, 6);   // (2)
	show(li);              //9, 6, 6, 1, 9, 9
	// "it" maybe valid, get a new one
	it = li.begin();
	it++;
	// If a reallocation happens, all iterators, pointers and references related to the container are invalidated.
	// Otherwise, only those pointing to position and beyond are invalidated, with all iterators, pointers and
	// references to elements before position guaranteed to keep referring to the same elements they were referring
	// to before the call.

	list<int> li2(2, 7);
	it++;
	it++;
	li.insert(it, li2.begin(), li2.end()); // (3)
	show(li);              //9, 6, 6, 7, 7, 1, 9, 9

	int arr[] = {0, 1, 2, 3};
	li.insert(li.begin(), arr, arr+3);     // (5)
	show(li);              //0, 1, 2, 9, 6, 6, 7, 7, 1, 9, 9
}

void lst_erase()
{
	// iterator erase (iterator position);
	// iterator erase (iterator first, iterator last);
	// Erase elements
	// Removes from the list either a single element (position) or a range of elements ([first,last)).

	list<int> li;
	list<int>::iterator it1, it2;
	unsigned int i = 0;
	for (i = 1; i <= 9; i++)
	{
		li.push_back(i * 10);
	}
	show(li);   //10, 20, 30, 40, 50, 60, 70, 80, 90

	                            // 10 20 30 40 50 60 70 80 90
	it1 = it2 = li.begin();     // ^^
	advance(it2, 6);            // ^                 ^
	++it1;                      //    ^              ^

	it1 = li.erase(it1); // (1) // 10 30 40 50 60 70 80 90
	                            //    ^           ^
	it2 = li.erase(it2); // (1) // 10 30 40 50 60 80 90
	                            //    ^           ^
	++it1;                      //       ^        ^
	--it2;                      //       ^     ^
	li.erase(it1, it2);  // (2) // 10 30 60 80 90
	                            //       ^
	// print(*it1);//40 //invalid
	print(*it2);//60
	show(li);   //10, 30, 60, 80, 90
}

void lst_clear()
{
	// void clear();
	// Clear content
	// Removes all elements from the list (which are destroyed), lealing the container with a size of 0.

	list<int> li;
	unsigned int i = 0;
	for (i = 0; i <= 9; i++)
	{
		li.push_back(i);
	}
	show(li);         //0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	print(li.size()); //10
	print(li.empty());//0

	li.clear();
	show(li);         //
	print(li.size()); //0
	print(li.empty());//1
}

int main() {
	lst_construct();
	lst_OperatorEQ(); //=

	lst_begin_end();

	lst_size();
	lst_capacity();   //list invalid
	lst_empty();

	lst_OperatorAT(); //[] list invalid
	lst_at();         // list invalid
	lst_front();
	lst_back();

	lst_assign();
	lst_push_back();
	lst_pop_back();
	lst_insert();
	lst_erase();
	lst_clear();
	return 0;
}

