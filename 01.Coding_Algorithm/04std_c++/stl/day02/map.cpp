/*****************************************
 * Copyright (C) 2018 * Ltd. All rights reserved.
 * 
 * File name   : map.cpp
 * Author      : longbin
 * Created date: 2018-08-07 10:42:02
 * Description : 
 *
 *******************************************/

#include <iostream>

#include <string>
#include <map>
#include <vector>
using namespace std;

#define printvar(x)    do { cout << "[" << __func__ << "] " << #x << ": " << (x) << endl; } while (0);
#define printmap(x) do { cout << "[" << __func__ << "] " << #x << ": "; show(x); } while (0);

template <typename K, typename V>
using MapIterator_T = typename std::map<K, V>::iterator;
//typename std::map<K, V>::iterator MapIterator_T;  //error

	template <typename K, typename V>
void show(map<K, V>& m)
{
	cout << "[" << __func__ << "] ";
	// auto it = m.begin();
	MapIterator_T<K, V> it = m.begin();
	for (it = m.begin(); it != m.end();)
	{
		cout <<  it->first << ": " << it->second;
		it++;
		if (it != m.end())
		{
			cout << ", ";
		}
	}
	cout << endl;
}

void map_construct()
{
	// empty (1)    explicit map (const key_compare& comp = key_compare(),
	//                            const allocator_type& alloc = allocator_type());
	// range (2) template <class InputIterator>
	//              map (InputIterator first, InputIterator last,
	//                      const key_compare& comp = key_compare(),
	//                         const allocator_type& alloc = allocator_type());
	// copy (3)     map (const map& x);
	// move (4)     map (map&& x); //c++11
	//              map (map&& x, const allocator_type& alloc); //c++11
	// initializer list (5)	 map (initializer_list<value_type> il,
	//                            const key_compare& comp = key_compare(),
	//                            const allocator_type& alloc = allocator_type()); //c++11

	// (1) empty container constructor (default constructor)
	// (2) range constructor // Constructs a container with as many elements as the range [first,last).
	// (3) copy constructor // Constructs a container with a copy of each of the elements in x.
	// (4) move constructor (and moving with allocator) // Constructs a container that acquires the elements of x.
	// (5) initializer list constructor // Constructs a container with a copy of each of the elements in il.

	map<int, string> mis1;     // (1)
	printmap(mis1);
	mis1[1] = "good";
	mis1[3] = "value";
	mis1[6] = "c++";
	mis1[9] = "map";
	printmap(mis1);            //1: good, 3: value, 6: c++, 9: map

	map<int, string> mis2(mis1.begin(), mis1.end()); // (2)
	printmap(mis2);            //1: good, 3: value, 6: c++, 9: map

	map<int, string> mis3(mis2); // (3)
	printmap(mis3);            //1: good, 3: value, 6: c++, 9: map

	map<int, string> mis5({
			{1, "good"}, {3, "value"}, {6, "c++"}, {9, "map"}
			});                // (5) c++11
	printmap(mis5);            //1: good, 3: value, 6: c++, 9: map
}

void map_OperatorEQ()
{
	// copy (1)  map& operator= (const map& x);
	// move (2)	 map& operator= (map&& x); //c++11
	// initializer list (3)	map& operator= (initializer_list<value_type> il);//c++11
	// Copy container content
	// Assigns new contents to the container, replacing its current content.

	cout << "[" << __func__ << "]" << endl;
	map<int, string> mis1;
	map<int, string> mis2;
	mis1[1] = "good";
	mis1[3] = "value";
	mis1[6] = "c++";
	mis1[9] = "map";

	mis2 = mis1;     // (1)
	printmap(mis2);  //1: good, 3: value, 6: c++, 9: map
	mis1 = map<int, string>();
	printmap(mis1);  //mis1 is now empty

	map<int, string> mis3 = {
		{1, "good"}, {3, "value"}, {6, "c++"}, {9, "map"},
	};               // (3) c++11
	printmap(mis3);  //1: good, 3: value, 6: c++, 9: map
	printmap(mis3);  //1: good, 3: value, 6: c++, 9: map
}

void map_begin_end()
{
	// iterator begin();
	// const_iterator begin() const;
	// Return iterator to beginning
	// Returns an iterator referring to the first element in the map container.

	// iterator end();
	// const_iterator end() const;
	// Return iterator to end
	// Returns an iterator referring to the past-the-end element in the map container.

	map<int, string> mis;
	mis[1] = "good";
	mis[3] = "value";
	mis[6] = "c++";
	mis[9] = "map";

	map<int, string>::iterator it;
	for (it = mis.begin(); it != mis.end(); it++)
	{
		printvar(it->first);
		printvar(it->second);
	}
}

void map_empty()
{
	// bool empty() const;
	// Test whether container is empty
	// Returns whether the map container is empty (i.e. whether its size is 0).

	map<int, string> mis;
	printvar(mis.empty()); //1
	mis[1] = "good";
	mis[3] = "value";
	mis[6] = "c++";
	mis[9] = "map";

	while (!mis.empty())
	{
		printvar(mis.begin()->first);
		printvar(mis.begin()->second);
		cout << "mis.erase(mis.begin())" << endl;
		mis.erase(mis.begin());
	}
}

void map_size()
{
	// size_type size() const;
	// Return container size
	// Returns the number of elements in the map container.

	map<int, string> mis;
	printvar(mis.size()); //0
	mis[1] = "good";
	mis[3] = "value";
	mis[6] = "c++";
	mis[9] = "map";
	printvar(mis.size()); //4
}

void map_OperatorAt()
{
	// mapped_type& operator[] (const key_type& k);
	// Access element
	// If k matches the key of an element in the container, the function returns a reference to its mapped value.
	// If k does not match the key of any element in the container, the function inserts a new element
	// with that key and returns a reference to its mapped value. Notice that this always increases the
	// container size by one, even if no mapped value is assigned to the element (the element is constructed
	// using its default constructor).
	// A similar member function, map::at, has the same behavior when an element with the key exists,
	// but throws an exception when it does not.

	map<int, string> mis;
	mis[1] = "good";
	mis[3] = "value";
	mis[6] = "c++";
	printmap(mis); //1: good, 3: value, 6: c++

	printvar(mis[9]); //inserts a new element with 9 and returns a reference to its value;
	printmap(mis); //1: good, 3: value, 6: c++, 9: 
}

void map_at()
{
	//c++11
	// mapped_type& at (const key_type& k);
	// const mapped_type& at (const key_type& k) const;

	// Access element
	// Returns a reference to the mapped value of the element identified with key k.
	// If k does not match the key of any element in the container, the function throws an out_of_range exception.

	map<int, string> mis;
	mis[1] = "good";
	mis[3] = "value";
	mis[6] = "c++";
	printmap(mis);
	mis.at(3) = "at(3)";
	printmap(mis);
	// mis.at(9) = "map"; //std::out_of_range
}

void map_insert()
{
	// single element (1)  pair<iterator,bool> insert (const value_type& val);
	// with hint (2)       iterator insert (iterator position, const value_type& val);
	// range (3)      template <class InputIterator>
	//                     void insert (InputIterator first, InputIterator last);
	// Insert elements
	// Extends the container by inserting new elements, effectively increasing the container size
	// by the number of elements inserted.

	// Member type value_type is the type of the elements in the container, defined in map
	// as pair<const key_type, mapped_type> (see map member types).

	map<int, string> mis1;
	mis1.insert(std::pair<int, string>(1, "good"));  // (1)
	mis1.insert(std::pair<int, string>(3, "value")); // (1)
	printmap(mis1);

	std::pair<std::map<int, string>::iterator, bool> ret;
	ret = mis1.insert(std::pair<int, string>(3, "insert")); // (1)
	cout << "[" << __func__ << "] insert ret.second: " << ret.second << endl; //1
	if (ret.second)
	{
		cout << "[" << __func__ << "] insert successfully" << endl;
	}
	else
	{
		cout << "[" << __func__ << "] key: " << ret.first->first
			<< " already existed, with a value of: " << ret.first->second << endl;
		//key: 3 already existed, with a value of: value
	}

	std::map<int, string>::iterator it = mis1.begin();
	mis1.insert(it, std::pair<int, string>(6, "c++")); // (2)
	mis1.insert(it, std::pair<int, string>(9, "map")); // (2)
	printmap(mis1); //1: good, 3: value, 6: c++, 9: map

	std::map<int, string> mis2;
	mis2.insert(mis1.begin(), mis1.find(6));           // (3)
	printmap(mis2); //1: good, 3: value
}

void map_erase()
{
	// (1)  void erase (iterator position);
	// (2)  size_type erase (const key_type& k);
	// (3)  void erase (iterator first, iterator last);
	// Erase elements
	// Removes from the map container either a single element or a range of elements ([first,last)).

	std::map<int, string> mis;
	std::map<int, string>::iterator it;

	mis[1] = "good";
	mis[3] = "value";
	mis[6] = "c++";
	mis[9] = "map";
	printmap(mis);     //1: good, 3: value, 6: c++, 9: map

	it = mis.find(3);
	if (it != mis.end())
	{
		mis.erase(it); // (1)
	}
	printmap(mis);     //1: good, 6: c++, 9: map

	mis.erase(6);      // (2)
	printmap(mis);     //1: good, 9: map

	it = mis.find(0);
	mis.erase(it, mis.end()); // (3)
	printmap(mis);     //1: good, 9: map
	it = mis.find(1);
	mis.erase(it, mis.end()); // (3)
	printmap(mis);     //
}

void map_clear()
{
	// void clear();
	// Clear content
	// Removes all elements from the map container (which are destroyed), leaving the
	// container with a size of 0.:x

	std::map<int, string> mis;

	mis[1] = "good";
	mis[3] = "value";
	mis[6] = "c++";
	mis[9] = "map";
	printmap(mis);        //1: good, 3: value, 6: c++, 9: map

	mis.clear();
	printmap(mis);        //
	printvar(mis.size()); //0

	mis[6] = "c++";
	mis[9] = "map";
	printmap(mis);        //6: c++, 9: map
	printvar(mis.size()); //2
}

void map_find()
{
	// iterator       find (const key_type& k);
	// const_iterator find (const key_type& k) const;
	// Get iterator to element
	// Searches the container for an element with a key equivalent to k and returns an iterator to it if found,
	// otherwise it returns an iterator to map::end.
	// Two keys are considered equivalent if the container's comparison object returns false reflexively
	// (i.e., no matter the order in which the elements are passed as arguments).
	// Another member function, map::count, can be used to just check whether a particular key exists.

	map<int, string> mis;
	map<int, string>::iterator it;

	mis[1] = "good";
	mis[3] = "value";
	mis[6] = "c++";
	mis[9] = "map";
	printmap(mis); //1: good, 3: value, 6: c++, 9: map

	it = mis.find(6);
	if (it != mis.end())
	{
		cout << "[" << __func__ << "] findout: " << it->first << ", value: " << it->second << endl;
	}

	printvar( mis.end() != mis.find(0) ); //0
	printvar( mis.end() != mis.find(1) ); //1
	printvar( mis.end() != mis.find(3) ); //1
	printvar( mis.end() != mis.find(6) ); //1
	printvar( mis.end() != mis.find(9) ); //1

	printvar(mis.find(1)->second);        //good
	printvar(mis.find(3)->second);        //value
	printvar(mis.find(6)->second);        //c++
	printvar(mis.find(9)->second);        //map
}

void map_count()
{
	// size_type count (const key_type& k) const;
	// Count elements with a specific key
	// Searches the container for elements with a key equivalent to k and returns the number of matches.
	// Because all elements in a map container are unique, the function can only return 1 (if the element
	// is found) or zero (otherwise).
	// Two keys are considered equivalent if the container's comparison object returns false reflexively
	// (i.e., no matter the order in which the keys are passed as arguments).

	std::map<int, string> mis;
	mis[1] = "good";
	mis[3] = "value";
	mis[6] = "c++";
	mis[9] = "map";
	printmap(mis); //1: good, 3: value, 6: c++, 9: map

	unsigned int i;
	for (i = 0; i <= 9; i++)
	{
		cout << "[" << __func__ << "] mis.count(" << i << "): " << mis.count(i) << endl;
	}
	// mis.count(0): 0
	// mis.count(1): 1
	// mis.count(2): 0
	// mis.count(3): 1
	// mis.count(4): 0
	// mis.count(5): 0
	// mis.count(6): 1
	// mis.count(7): 0
	// mis.count(8): 0
	// mis.count(9): 1
}

int main() {
	map_construct();
	map_OperatorEQ();

	map_begin_end();

	map_empty();
	map_size();

	map_OperatorAt();
	map_at();

	map_insert();
	map_erase();
	map_clear();

	map_find();
	map_count();
	return 0;
}

