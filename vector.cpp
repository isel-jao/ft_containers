#include <fstream>
#include <map>
#include <math.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <string.h>
#include <deque>
#include "ft_containers.hpp"

#define waza() std::cout << "WAZAAAAAAAA,\t\tline: " << __LINE__ << ",\tfunc: " << __FUNCTION__ << std::endl

// struct vec
// {
// 	int x, y, z;
// 	vec(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z)
// 	{
// 		std::cout << "constructor called" << std::endl;
// 	}
// 	vec(vec const &obj) : x(obj.x), y(obj.y), z(obj.z)
// 	{
// 		std::cout << "copy constructor called" << std::endl;
// 	}
// 	vec &operator=(vec &obj)
// 	{
// 		std::cout << "oparetor = is called" << std::endl;
// 		x = obj.x;
// 		y = obj.y;
// 		z = obj.z;
// 		return *this;
// 	}
// 	~vec()
// 	{
// 		std::cout << "vec deconstructor called" << std::endl;
// 	}
// };

// std::ostream &operator<<(std::ostream &out, vec &v)
// {
// 	out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
// 	return out;
// }

#ifndef NAMESPACE
#define NAMESPACE std
#endif

template <typename ctnr>
void print_container(ctnr const &container, std::string sep = "\n")
{
	// waza();
	std::cout << "size: " << container.size() << sep;
	try
	{
		std::cout << "capacity: " << container.capacity() << "\t" << sep;
	}
	catch (const std::exception &e)
	{
	}

	typedef typename ctnr::const_iterator it;
	it first = container.begin();
	it last = container.end();
	while (first != last)
	{
		std::cout << *first;
		std::cout << sep;
		first++;
	}
	if (sep != "\n")
		std::cout << std::endl;
	else
		std::cout << std::flush;
}

int main()
{
	try
	{
		int arr[] = {1, 2, 4, 5, 6, 7, 8, 9};
		NAMESPACE::vector<int> v;
		NAMESPACE::vector<int>::iterator it;
		v.assign(arr, arr + 8);
		// std::cout << "vector::at(): " << v.at(3) << std::endl;
		// std::cout << "vector::back(): " << v.back() << std::endl;
		// std::cout << "vector::begin(): " << *(v.begin()) << std::endl;
		// std::cout << "vector::capacity(): " << v.capacity() << std::endl;
		// std::cout << "vector::end(): " << *(v.end() - 1) << std::endl;
		v.erase(v.begin() + 2);
		v.erase(v.begin() + 1, v.begin() + 4);
		it = v.insert(v.begin() + 1, 1337);
		std::cout << *it << std::endl;
		// int arr2[] = {11, 22, 33, 44, 55, 66, 77, 88, 99, 111, 222, 333, 4444};
		// v.insert(v.begin() + 1, arr2 + 1, arr2 + 7);
		// print_container(v, " ");
		// v.insert(v.begin() + 2, 5, 4);
		// print_container(v, " ");
		v.pop_back();
		v.push_back(1992);
		NAMESPACE::vector<int>::reverse_iterator rb = v.rbegin();
		NAMESPACE::vector<int>::reverse_iterator re = v.rend();
		while (rb != re)
		{
			std::cout << *rb << " ";
			rb++;
		}
		std::cout << std::endl;
		v.reserve(4);
		v.reserve(30);
		v.resize(10);
		v.resize(3);
		NAMESPACE::vector<int> v2(v);
		v.push_back(9);
		v.push_back(9);
		v.push_back(9);
		// std::cout << "(v == v2): " << (v == v2) << std::endl;
		// std::cout << "(v != v2): " << (v != v2) << std::endl;
		// std::cout << "(v < v2): " << (v < v2) << std::endl;
		// std::cout << "(v <= v2): " << (v <= v2) << std::endl;
		// std::cout << "(v > v2): " << (v > v2) << std::endl;
		// std::cout << "(v >= v2): " << (v >= v2) << std::endl;

		// v[2] = -1;
		// v[1] = 99999999;
		// std::cout << "(v == v2): " << (v == v2) << std::endl;
		// std::cout << "(v != v2): " << (v != v2) << std::endl;
		// std::cout << "(v < v2): " << (v < v2) << std::endl;
		// std::cout << "(v <= v2): " << (v <= v2) << std::endl;
		// std::cout << "(v > v2): " << (v > v2) << std::endl;
		// std::cout << "(v >= v2): " << (v >= v2) << std::endl;
		std::cout << "==================================================================================" << std::endl;
		// print_container(v, " ");
		// print_container(v2, " ");
		v2.swap(v);
		print_container(v, " ");
		print_container(v2, " ");
		NAMESPACE::swap(v, v2);
		print_container(v, " ");
		print_container(v2, " ");
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}

	return 0;
}

//////// bugs ////////
// after insert copacity is set to a wrong value