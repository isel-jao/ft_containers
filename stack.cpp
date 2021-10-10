#include <fstream>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <map>
#include <deque>
#include <stack>


#define value_type T
#define container_type Container
#define size_type size_t
namespace ft
{
	template <class T, class Container = std::deque<T> >
	class stack
	{
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
	NAMESPACE::stack<int,std::deque<int> > s1;
	NAMESPACE::stack<int,std::deque<int> > s2;

	s2.push(34);
	s1.push(4);
	s1.push(14);
	s1.push(54);
	std::cout << "s1.size: " << s1.size() << std::endl;
	while (!s1.empty())
	{
		std::cout << s1.top() << std::endl;
		s1.pop();
	}
	std::cout << "s2.size: " << s2.size() << std::endl;
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