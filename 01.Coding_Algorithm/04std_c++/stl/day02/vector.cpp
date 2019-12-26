/*****************************************
* Copyright (C) 2018 * Ltd. All rights reserved.
* 
* File name   : vector.cpp
* Author      : longbin
* Created date: 2018-08-02 19:18:13
* Description : 
*
*******************************************/

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

void vec_construct()
{
	// default (1)  explicit vector (const allocator_type& alloc = allocator_type());
	// fill (2)     explicit vector (size_type n, const value_type& val = value_type(),
	//                                  const allocator_type& alloc = allocator_type());
	// range (3) template <class InputIterator>
	//              vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
	// copy (4)	    vector (const vector& x);

	// (1) empty container constructor (default constructor) // Constructs an empty container, with no elements.
	// (2) fill constructor // Constructs a container with n elements. Each element is a copy of val.
	// (3) range constructor // Constructs a container with as many elements as the range [first,last).
	// (4) copy constructor // Constructs a container with a copy of each of the elements in x, in the same order.

	vector<int> vi;                // (1) empty vector of ints;
	vector<string> vs;             // (1) empty vector of strings;
	vector<int> vi2(6, 258);       // (2) 6 ints with value 258;
	vector<int> vi20(6);           // (2) 6 ints with value 0;
	vector<string> vs2(3, "c++");  // (2) 3 strings with value of "c++";
	vector<int> vi3(vi2.begin()+1, vi2.begin()+3); // (3) iteratoring from vi2;
	vector<string> vs3(vs2.begin(), vs2.end());    // (3) iteratoring from vi2;
	vector<int> vi4(vi2);          // (4) a copy of vi2;
	vector<string> vs4(vs2);       // (4) a copy of vs2;

	int arr[] = {1,2,3,4,5,6};
	vector<int> vi5 (arr, arr+sizeof(arr)/sizeof(int)); // initializer list (6) //c++11

	show(vi);   // show: 
	show(vs);   // show: 
	show(vi2);  // show: 258, 258, 258, 258, 258, 258
	show(vi20); // show: 0, 0, 0, 0, 0, 0
	show(vs2);  // show: c++, c++, c++
	show(vi3);  // show: 258, 258
	show(vs3);  // show: c++, c++, c++
	show(vi4);  // show: 258, 258, 258, 258, 258, 258
	show(vs4);  // show: c++, c++, c++
	show(vi5);  // show: 1, 2, 3, 4, 5, 6
}

void vec_OperatorEQ()
{
	// Assign content
	// Assigns new contents to the container, replacing its current contents, and modifying its size accordingly.

	// copy (1)	            vector& operator= (const vector& x);
	// move (2)             vector& operator= (vector&& x); //c++11
	// initializer list (3)	vector& operator= (initializer_list<value_type> il); //c++11

	vector<int> vi1(5, 0);
	vector<int> vi2(6, 0);

	vi2 = vi1;
	vi1 = vector<int>();
	print(vi1.size());
	print(vi2.size());

	vector<int> vi3 = {1,2,3,4,5,6}; // c++11 要求类型相容
	vector<int> vi31  {1,2,3,4,5,6}; // c++11 =可省略
	show(vi3);  // show: 1, 2, 3, 4, 5, 6
	show(vi31); // show: 1, 2, 3, 4, 5, 6
}

void vec_begin_end()
{
	// iterator begin();
	// const_iterator begin() const;
	// Return iterator to beginning // Returns an iterator pointing to the first element in the vector.

	// iterator end();
	// const_iterator end() const;
	// Return iterator to end // Returns an iterator referring to the past-the-end element in the vector container.
	// vector,string,deque的迭代器有加减法;但list,map,set,multimap,multiset的迭代器是没有加减法的(+n/-n),只有++和--;
	vector<int> vi;
	vector<int>::iterator it;
	int i = 0;
	for (i = 1; i <= 9; i++)
	{
		vi.push_back(i);
	}

	cout << "[" << __func__ << "]: ";
	for (it = vi.begin(); it != vi.end(); it++)
	{
		cout << *it;
		if (it != vi.end() - 1)
		{
			cout << ", ";
		}
	}
	cout << endl;
}

void vec_size()
{
	// Return size // Returns the number of elements in the vector.
	// size_type size() const;

	vector<int> vi;
	print(vi.size()); //0

	int i = 0;
	for (i = 1; i <= 9; i++)
	{
		vi.push_back(i);
	}
	print(vi.size()); //9
	vi.insert(vi.end(), 10, 100);
	print(vi.size()); //19
	vi.pop_back();
	print(vi.size()); //18
}

void vec_capacity()
{
	// size_type capacity() const;
	// Return size of allocated storage capacity
	// Returns the size of the storage space currently allocated for the vector, expressed in terms of elements.

	vector<int> vi;
	int i = 0;
	for (i = 1; i <= 9; i++)
	{
		vi.push_back(i);
	}
	print(vi.size());     //9
	print(vi.capacity()); //16
	print(vi.max_size()); //4611686018427387903
	vi.insert(vi.end(), 10, 100);
	print(vi.size());     //19
	print(vi.capacity()); //19
	print(vi.max_size()); //4611686018427387903
}

void vec_empty()
{
	// bool empty() const;
	// Test whether vector is empty
	// Returns whether the vector is empty (i.e. whether its size is 0).
	// This function does not modify the container in any way. To clear the content of a vector, see vector::clear.

	vector<int> vi;
	int i = 0;
	int sum = 0;

	print(vi.empty());  //1
	for (i = 1; i <= 9; i++)
	{
		vi.push_back(i);
	}
	print(vi.empty());  //0

	while (!vi.empty())
	{
		sum += vi.back();
		vi.pop_back();
	}
	print(vi.empty());  //1
	print(sum);         //45
}

void vec_OperatorAT()
{
	// reference operator[] (size_type n);
	// const_reference operator[] (size_type n) const;
	// Access element
	// Returns a reference to the element at position n in the vector container.

	// A similar member function, vector::at, has the same behavior as this operator function,
	// except that vector::at is bound-checked and signals if the requested position is out of
	// range by throwing an out_of_range exception. 
	// Notice that the first element has a position of 0 (not 1).

	vector<int> vi(10);           //10 zero-initialized elements
	vector<int>::size_type size = vi.size();
	unsigned int i = 0;

	for (i = 0; i < size; i++)
	{
		vi[i] = i;
	}

	show(vi);
	// reverse vector using operator[]
	for (i = 0; i < size/2; i++)
	{
		vi[i]        ^= vi[size-1-i];
		vi[size-1-i] ^= vi[i];
		vi[i]        ^= vi[size-1-i];
	}

	cout << "[" << __func__ << "]: ";
	for (i = 0; i < size; i++)
	{
		cout << vi[i];
		if (i != size - 1)
		{
			cout << ", ";
		}
	}
	cout << endl;
}

void vec_at()
{
	// reference at (size_type n);
	// const_reference at (size_type n) const;
	// Access element
	// Returns a reference to the element at position n in the vector.
	// The function automatically checks whether n is within the bounds of valid elements in the vector,
	// throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its size).
	// This is in contrast with member operator[], that does not check against bounds.

	vector<int> vi(10);
	vector<int>::size_type size = vi.size();
	unsigned int i = 0;

	for (i = 0; i < vi.size(); i++)
	{
		vi.at(i) = i;
	}
	show(vi);

	cout << "[" << __func__ << "]: ";
	for (i = 0; i < size; i++)
	{
		cout << vi.at(i);
		if (i != size - 1)
		{
			cout << ", ";
		}
	}
	cout << endl;
}

void vec_front()
{
	//  reference front();
	//  const_reference front() const;
	//  Access first element //  Returns a reference to the first element in the vector.

	vector<int> vi;

	vi.push_back(10);
	vi.push_back(20);
	// now front equals 10, and back 20
	vi.front() += vi.back();
	print(vi.front()); //30
}

void vec_back()
{
	// reference back();
	// const_reference back() const;
	// Access last element // Returns a reference to the last element in the vector.

	vector<int> vi;
	vi.push_back(10);
	while (0 != vi.back())
	{
		vi.push_back(vi.back() - 1);
	}
	show(vi); //10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
}

void vec_assign()
{
	// range (1)       template <class InputIterator>
	//                      void assign (InputIterator first, InputIterator last);
	// fill (2)        void assign (size_type n, const value_type& val);
	// initializer list (3)	void assign (initializer_list<value_type> il); //c++11

	// Assign vector content
	// Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.

	vector<int> vi1;
	vector<int> vi2;
	vector<int> vi3;

	vi1.assign(6, 8);          // (2)
	show(vi1);                 //8, 8, 8, 8, 8, 8

	vi2.assign(vi1.begin()+1, vi1.begin()+3); // (1)
	show(vi2);                 //8, 8

	int arr[] = {3, 6, 9, 2, 5, 8};
	vi3.assign(arr, arr+3);    // (3) assign from array
	show(vi3);                 //3, 6, 9
}

void vec_push_back()
{
	// void push_back (const value_type& val);
	// Add element at the end
	// Adds a new element at the end of the vector, after its current last element.
	// The content of val is copied (or moved) to the new element.

	vector<int> vi;
	unsigned int i = 0;

	for (i = 0; i <= 9; i++)
	{
		cout << "[" << __func__ << "]: push_back " << i << endl;
		vi.push_back(i);
	}
	show(vi); //0, 1, 2, 3, 4, 5, 6, 7, 8, 9
}

void vec_pop_back()
{
	// void pop_back();
	// Delete last element
	// Removes the last element in the vector, effectively reducing the container size by one.

	vector<int> vi;
	unsigned int i = 0;

	for (i = 0; i <= 9; i++)
	{
		vi.push_back(i);
	}
	show(vi);

	while (!vi.empty())
	{
		cout << "[" << __func__ << "]: pop_back " << vi.back() << endl;
		vi.pop_back();
	}
}

void vec_insert()
{
	// single element (1)   iterator insert (iterator position, const value_type& val);
	// fill (2)             void insert (iterator position, size_type n, const value_type& val);
	// range (3)	template <class InputIterator>
	//                      void insert (iterator position, InputIterator first, InputIterator last);
	// move (4)             iterator insert (const_iterator position, value_type&& val); //c++11
	// initializer list (5)	iterator insert (const_iterator position, initializer_list<value_type> il); //c++11
	// Insert elements
	// The vector is extended by inserting new elements before the element at the specified position,
	// effectively increasing the container size by the number of elements inserted.

	vector<int> vi(3, 9);
	vector<int>::iterator it;
	show(vi);              //9, 9, 9

	it = vi.begin() + 1;
	it = vi.insert(it, 1); // (1)
	show(vi);              //9, 1, 9, 9

	vi.insert(it, 2, 6);   // (2)
	show(vi);              //9, 6, 6, 1, 9, 9
	// "it" maybe valid, get a new one
	it = vi.begin() + 1;
	// If a reallocation happens, all iterators, pointers and references related to the container are invalidated.
	// Otherwise, only those pointing to position and beyond are invalidated, with all iterators, pointers and
	// references to elements before position guaranteed to keep referring to the same elements they were referring
	// to before the call.

	vector<int> vi2(2, 7);
	vi.insert(it+2, vi2.begin(), vi2.end()); // (3)
	show(vi);              //9, 6, 6, 7, 7, 1, 9, 9

	int arr[] = {0, 1, 2, 3};
	vi.insert(vi.begin(), arr, arr+3);       // (5)
	show(vi);              //0, 1, 2, 9, 6, 6, 7, 7, 1, 9, 9
}

void vec_erase()
{
	// iterator erase (iterator position);
	// iterator erase (iterator first, iterator last);
	// Erase elements
	// Removes from the vector either a single element (position) or a range of elements ([first,last)).

	vector<int> vi;
	unsigned int i = 0;
	for (i = 0; i <= 9; i++)
	{
		vi.push_back(i);
	}
	show(vi);   //0, 1, 2, 3, 4, 5, 6, 7, 8, 9

	vi.erase(vi.begin() + 8);             // (1)
	show(vi);   //0, 1, 2, 3, 4, 5, 6, 7, 9

	vi.erase(vi.begin()+1, vi.begin()+4); // (2)
	show(vi);   //0, 4, 5, 6, 7, 9
}

void vec_clear()
{
	// void clear();
	// Clear content
	// Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.

	vector<int> vi;
	unsigned int i = 0;
	for (i = 0; i <= 9; i++)
	{
		vi.push_back(i);
	}
	show(vi);         //0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	print(vi.size()); //10

	vi.clear();
	show(vi);         //
	print(vi.size()); //0
}

int main() {
	vec_construct();
	vec_OperatorEQ(); //=

	vec_begin_end();

	vec_size();
	vec_capacity();
	vec_empty();

	vec_OperatorAT(); //[]
	vec_at();
	vec_front();
	vec_back();

	vec_assign();
	vec_push_back();
	vec_pop_back();
	vec_insert();
	vec_erase();
	vec_clear();
	return 0;
}

