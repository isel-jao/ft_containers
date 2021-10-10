#include <fstream>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <map>
#include <deque>
#include <stack>

#define waza() std::cout << "WAZAAAAAAAA,\t\tline: " << __LINE__ << ",\tfunc: " << __FUNCTION__ << std::endl

struct vec
{
	int x, y, z;
	vec(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z)
	{
		std::cout << "constructor called" << std::endl;
	}
	vec(vec const &obj) : x(obj.x), y(obj.y), z(obj.z)
	{
		std::cout << "copy constructor called" << std::endl;
	}
	vec &operator=(vec &obj)
	{
		std::cout << "oparetor = is called" << std::endl;
		x = obj.x;
		y = obj.y;
		z = obj.z;
		return *this;
	}
	~vec()
	{
		std::cout << "vec deconstructor called" << std::endl;
	}
};

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
			return lhs.value == rhs.value;
		}
		friend bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
		{
			return lhs.value != rhs.value;
		}
		friend bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
		{
			return lhs.value < rhs.value;
		}
		friend bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
		{
			return lhs.value <= rhs.value;
		}
		friend bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
		{
			return lhs.value > rhs.value;
		}
		friend bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
		{
			return lhs.value >= rhs.value;
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

	s2.push(34);
	s1.push(4);
	s1.push(14);
	s1.push(54);
	while (!s1.empty())
	{
		std::cout << s1.top() << std::endl;
		s1.pop();
	}
	std::cout << (s1 == s2) << std::endl;
	std::cout << (s1 != s2) << std::endl;
	std::cout << (s1 > s2) << std::endl;
	std::cout << (s1 >= s2) << std::endl;
	std::cout << (s1 < s2) << std::endl;
	std::cout << (s1 <= s2) << std::endl;
	return 0;
}