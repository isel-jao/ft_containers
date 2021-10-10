#include <fstream>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <map>
#include <deque>

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


#ifndef NAMESPACE
#define NAMESPACE std
#endif

int main()
{
	std::cout << "hello world" << std::endl;
	return 0;
}