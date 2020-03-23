/*****************************************
* Copyright (C) 2018 * Ltd. All rights reserved.
* 
* File name   : deque.cpp
* Author      : longbin
* Created date: 2018-08-02 19:18:13
* Description : 
*
*******************************************/

#include <iostream>
#include <string>
#include <deque>

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

void deq_construct()
{
	// default (1)  explicit deque (const allocator_type& alloc = allocator_type());
	// fill (2)     explicit deque (size_type n, const value_type& val = value_type(),
	//                                  const allocator_type& alloc = allocator_type());
	// range (3) template <class InputIterator>
	//              deque (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
	// copy (4)	    deque (const deque& x);

	// (1) empty container constructor (default constructor) // Constructs an empty container, with no elements.
	// (2) fill constructor // Constructs a container with n elements. Each element is a copy of val.
	// (3) range constructor // Constructs a container with as many elements as the range [first,last).
	// (4) copy constructor // Constructs a container with a copy of each of the elements in x, in the same order.

	deque<int> dqi;                // (1) empty deque of ints;
	deque<string> dqs;             // (1) empty deque of strings;
	deque<int> dqi2(6, 258);       // (2) 6 ints with value 258;
	deque<int> dqi20(6);           // (2) 6 ints with value 0;
	deque<string> dqs2(3, "c++");  // (2) 3 strings with value of "c++";
	deque<int> dqi3(dqi2.begin()+1, dqi2.begin()+3); // (3) iteratoring from dqi2;
	deque<string> dqs3(dqs2.begin(), dqs2.end());    // (3) iteratoring from dqi2;
	deque<int> dqi4(dqi2);          // (4) a copy of dqi2;
	deque<string> dqs4(dqs2);       // (4) a copy of dqs2;

	int arr[] = {1,2,3,4,5,6};
	deque<int> dqi5 (arr, arr+sizeof(arr)/sizeof(int)); // initializer list (6) //c++11

	show(dqi);   // show: 
	show(dqs);   // show: 
	show(dqi2);  // show: 258, 258, 258, 258, 258, 258
	show(dqi20); // show: 0, 0, 0, 0, 0, 0
	show(dqs2);  // show: c++, c++, c++
	show(dqi3);  // show: 258, 258
	show(dqs3);  // show: c++, c++, c++
	show(dqi4);  // show: 258, 258, 258, 258, 258, 258
	show(dqs4);  // show: c++, c++, c++
	show(dqi5);  // show: 1, 2, 3, 4, 5, 6
}

void deq_OperatorEQ()
{
	// Assign content
	// Assigns new contents to the container, replacing its current contents, and modifying its size accordingly.

	// copy (1)	            deque& operator= (const deque& x);
	// move (2)             deque& operator= (deque&& x); //c++11
	// initializer list (3)	deque& operator= (initializer_list<value_type> il); //c++11

	deque<int> dqi1(5, 0);
	deque<int> dqi2(6, 0);

	dqi2 = dqi1;
	dqi1 = deque<int>();
	print(dqi1.size());
	print(dqi2.size());

	deque<int> dqi3 = {1,2,3,4,5,6}; // c++11 要求类型相容
	deque<int> dqi31  {1,2,3,4,5,6}; // c++11 =可省略
	show(dqi3);  // show: 1, 2, 3, 4, 5, 6
	show(dqi31); // show: 1, 2, 3, 4, 5, 6
}

void deq_begin_end()
{
	// iterator begin();
	// const_iterator begin() const;
	// Return iterator to beginning // Returns an iterator pointing to the first element in the deque.

	// iterator end();
	// const_iterator end() const;
	// Return iterator to end // Returns an iterator referring to the past-the-end element in the deque container.
	// deque,string,deque的迭代器有加减法;但list,map,set,multimap,multiset的迭代器是没有加减法的(+n/-n),只有++和--;
	deque<int> dqi;
	deque<int>::iterator it;
	int i = 0;
	for (i = 1; i <= 9; i++)
	{
		dqi.push_back(i);
	}

	cout << "[" << __func__ << "]: ";
	for (it = dqi.begin(); it != dqi.end(); it++)
	{
		cout << *it;
		if (it != dqi.end() - 1)
		{
			cout << ", ";
		}
	}
	cout << endl;
}

void deq_size()
{
	// Return size // Returns the number of elements in the deque.
	// size_type size() const;

	deque<int> dqi;
	print(dqi.size()); //0

	int i = 0;
	for (i = 1; i <= 9; i++)
	{
		dqi.push_back(i);
	}
	print(dqi.size()); //9
	dqi.insert(dqi.end(), 10, 100);
	print(dqi.size()); //19
	dqi.pop_back();
	print(dqi.size()); //18
}

void deq_capacity()
{
	cout << "capacity(): No such function for deque." << endl;
}

void deq_empty()
{
	// bool empty() const;
	// Test whether deque is empty
	// Returns whether the deque is empty (i.e. whether its size is 0).
	// This function does not modify the container in any way. To clear the content of a deque, see deque::clear.

	deque<int> dqi;
	int i = 0;
	int sum = 0;

	print(dqi.empty());  //1
	for (i = 1; i <= 9; i++)
	{
		dqi.push_back(i);
	}
	print(dqi.empty());  //0

	while (!dqi.empty())
	{
		sum += dqi.back();
		dqi.pop_back();
	}
	print(dqi.empty());  //1
	print(sum);         //45
}

void deq_OperatorAT()
{
	// reference operator[] (size_type n);
	// const_reference operator[] (size_type n) const;
	// Access element
	// Returns a reference to the element at position n in the deque container.

	// A similar member function, deque::at, has the same behadqior as this operator function,
	// except that deque::at is bound-checked and signals if the requested position is out of
	// range by throwing an out_of_range exception. 
	// Notice that the first element has a position of 0 (not 1).

	deque<int> dqi(10);           //10 zero-initialized elements
	deque<int>::size_type size = dqi.size();
	unsigned int i = 0;

	for (i = 0; i < size; i++)
	{
		dqi[i] = i;
	}

	show(dqi);
	// reverse deque using operator[]
	for (i = 0; i < size/2; i++)
	{
		dqi[i]        ^= dqi[size-1-i];
		dqi[size-1-i] ^= dqi[i];
		dqi[i]        ^= dqi[size-1-i];
	}

	cout << "[" << __func__ << "]: ";
	for (i = 0; i < size; i++)
	{
		cout << dqi[i];
		if (i != size - 1)
		{
			cout << ", ";
		}
	}
	cout << endl;
}

void deq_at()
{
	// reference at (size_type n);
	// const_reference at (size_type n) const;
	// Access element
	// Returns a reference to the element at position n in the deque.
	// The function automatically checks whether n is within the bounds of valid elements in the deque,
	// throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its size).
	// This is in contrast with member operator[], that does not check against bounds.

	deque<int> dqi(10);
	deque<int>::size_type size = dqi.size();
	unsigned int i = 0;

	for (i = 0; i < dqi.size(); i++)
	{
		dqi.at(i) = i;
	}
	show(dqi);

	cout << "[" << __func__ << "]: ";
	for (i = 0; i < size; i++)
	{
		cout << dqi.at(i);
		if (i != size - 1)
		{
			cout << ", ";
		}
	}
	cout << endl;
}

void deq_front()
{
	//  reference front();
	//  const_reference front() const;
	//  Access first element //  Returns a reference to the first element in the deque.

	deque<int> dqi;

	dqi.push_back(10);
	dqi.push_back(20);
	// now front equals 10, and back 20
	dqi.front() += dqi.back();
	print(dqi.front()); //30
}

void deq_back()
{
	// reference back();
	// const_reference back() const;
	// Access last element // Returns a reference to the last element in the deque.

	deque<int> dqi;
	dqi.push_back(10);
	while (0 != dqi.back())
	{
		dqi.push_back(dqi.back() - 1);
	}
	show(dqi); //10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
}

void deq_assign()
{
	// range (1)       template <class InputIterator>
	//                      void assign (InputIterator first, InputIterator last);
	// fill (2)        void assign (size_type n, const value_type& val);
	// initializer list (3)	void assign (initializer_list<value_type> il); //c++11

	// Assign deque content
	// Assigns new contents to the deque, replacing its current contents, and modifying its size accordingly.

	deque<int> dqi1;
	deque<int> dqi2;
	deque<int> dqi3;

	dqi1.assign(6, 8);          // (2)
	show(dqi1);                 //8, 8, 8, 8, 8, 8

	dqi2.assign(dqi1.begin()+1, dqi1.begin()+3); // (1)
	show(dqi2);                 //8, 8

	int arr[] = {3, 6, 9, 2, 5, 8};
	dqi3.assign(arr, arr+3);    // (3) assign from array
	show(dqi3);                 //3, 6, 9
}

void deq_push_back()
{
	// void push_back (const value_type& val);
	// Add element at the end
	// Adds a new element at the end of the deque, after its current last element.
	// The content of val is copied (or moved) to the new element.

	deque<int> dqi;
	unsigned int i = 0;

	for (i = 0; i <= 9; i++)
	{
		cout << "[" << __func__ << "]: push_back " << i << endl;
		dqi.push_back(i);
	}
	show(dqi); //0, 1, 2, 3, 4, 5, 6, 7, 8, 9
}

void deq_pop_back()
{
	// void pop_back();
	// Delete last element
	// Removes the last element in the deque, effectively reducing the container size by one.

	deque<int> dqi;
	unsigned int i = 0;

	for (i = 0; i <= 9; i++)
	{
		dqi.push_back(i);
	}
	show(dqi);

	while (!dqi.empty())
	{
		cout << "[" << __func__ << "]: pop_back " << dqi.back() << endl;
		dqi.pop_back();
	}
}

void deq_insert()
{
	// single element (1)   iterator insert (iterator position, const value_type& val);
	// fill (2)             void insert (iterator position, size_type n, const value_type& val);
	// range (3)	template <class InputIterator>
	//                      void insert (iterator position, InputIterator first, InputIterator last);
	// move (4)             iterator insert (const_iterator position, value_type&& val); //c++11
	// initializer list (5)	iterator insert (const_iterator position, initializer_list<value_type> il); //c++11
	// Insert elements
	// The deque is extended by inserting new elements before the element at the specified position,
	// effectively increasing the container size by the number of elements inserted.

	deque<int> dqi(3, 9);
	deque<int>::iterator it;
	show(dqi);              //9, 9, 9

	it = dqi.begin() + 1;
	it = dqi.insert(it, 1); // (1)
	show(dqi);              //9, 1, 9, 9

	dqi.insert(it, 2, 6);   // (2)
	show(dqi);              //9, 6, 6, 1, 9, 9
	// "it" maybe valid, get a new one
	it = dqi.begin() + 1;
	// If a reallocation happens, all iterators, pointers and references related to the container are invalidated.
	// Otherwise, only those pointing to position and beyond are invalidated, with all iterators, pointers and
	// references to elements before position guaranteed to keep referring to the same elements they were referring
	// to before the call.

	deque<int> dqi2(2, 7);
	dqi.insert(it+2, dqi2.begin(), dqi2.end()); // (3)
	show(dqi);              //9, 6, 6, 7, 7, 1, 9, 9

	int arr[] = {0, 1, 2, 3};
	dqi.insert(dqi.begin(), arr, arr+3);       // (5)
	show(dqi);              //0, 1, 2, 9, 6, 6, 7, 7, 1, 9, 9
}

void deq_erase()
{
	// iterator erase (iterator position);
	// iterator erase (iterator first, iterator last);
	// Erase elements
	// Removes from the deque either a single element (position) or a range of elements ([first,last)).

	deque<int> dqi;
	unsigned int i = 0;
	for (i = 0; i <= 9; i++)
	{
		dqi.push_back(i);
	}
	show(dqi);   //0, 1, 2, 3, 4, 5, 6, 7, 8, 9

	dqi.erase(dqi.begin() + 8);             // (1)
	show(dqi);   //0, 1, 2, 3, 4, 5, 6, 7, 9

	dqi.erase(dqi.begin()+1, dqi.begin()+4); // (2)
	show(dqi);   //0, 4, 5, 6, 7, 9
}

void deq_clear()
{
	// void clear();
	// Clear content
	// Removes all elements from the deque (which are destroyed), leadqing the container with a size of 0.

	deque<int> dqi;
	unsigned int i = 0;
	for (i = 0; i <= 9; i++)
	{
		dqi.push_back(i);
	}
	show(dqi);         //0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	print(dqi.size()); //10

	dqi.clear();
	show(dqi);         //
	print(dqi.size()); //0
}

int main() {
	deq_construct();
	deq_OperatorEQ(); //=

	deq_begin_end();

	deq_size();
	deq_capacity();   //deque invalid
	deq_empty();

	deq_OperatorAT(); //[]
	deq_at();
	deq_front();
	deq_back();

	deq_assign();
	deq_push_back();
	deq_pop_back();
	deq_insert();
	deq_erase();
	deq_clear();
	return 0;
}

