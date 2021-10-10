#include <fstream>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <map>
#include <deque>
#include <stack>

namespace ft
{
	template <class T, class Container = std::deque<T> >
	class stack
	{
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;

	private:
		value_type value;
		container_type containter;

	public:
		stack(const container_type &ctnr = container_type())
			: containter(ctnr) {}
		bool empty() const { return containter.empty(); }
		void pop() { containter.pop_back(); }
		void push(const value_type &val) { containter.push_back(val); }
		size_type size() const { return containter.size(); }
		value_type &top() { return *(--containter.end()); }
		const value_type &top() const { return *(--containter.end()); }
		
		//Each of these operator overloads calls the same operator on the underlying container objects.
		friend bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
		{
			return lhs.containter == rhs.containter;
		}
		friend bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
		{
			return lhs.containter != rhs.containter;
		}
		friend bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
		{
			return lhs.containter < rhs.containter;
		}
		friend bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
		{
			return lhs.containter <= rhs.containter;
		}
		friend bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
		{
			return lhs.containter > rhs.containter;
		}
		friend bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
		{
			return lhs.containter >= rhs.containter;
		}
	};
}

#ifndef NAMESPACE
#define NAMESPACE std
#endif

int main()
{
	NAMESPACE::stack<int> s1;
	NAMESPACE::stack<int> s2;

	s2.push(42);
	s2.push(1337);
	s1.push(17);
	s1.push(11);
	s1.push(12);
	s1.push(9);
	s1.push(8);
	std::cout << "s1.size\t=" << s1.size() << std::endl;
	while (!s1.empty())
	{
		std::cout << s1.top() << std::endl;
		s1.pop();
	}
	std::cout << "\ns2.size\t=" << s2.size() << std::endl;
	while (!s2.empty())
	{
		std::cout << s2.top() << std::endl;
		s2.pop();
	}
	std::cout << "s1 == s2:\t" << (s1 == s2) << std::endl;
	std::cout << "s1 != s2:\t" << (s1 != s2) << std::endl;
	std::cout << "s1 > s2:\t" << (s1 > s2) << std::endl;
	std::cout << "s1 >= s2:\t" << (s1 >= s2) << std::endl;
	std::cout << "s1 < s2:\t" << (s1 < s2) << std::endl;
	std::cout << "s1 <= s2:\t" << (s1 <= s2) << std::endl;
	return 0;
}