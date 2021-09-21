#include <fstream>
#include <math.h>
#include <vector>
#include <iostream>
#include <string.h>

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
std::ostream &operator<<(std::ostream &out, vec &v)
{
	out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return out;
}

#if 1

namespace ft
{

	template <typename T>
	class vector
	{
	private:
		std::allocator<T> myAllocator;
		T *arr;
		size_t lenght;
		size_t allocated;

	public:
		vector(size_t const n = 0) : lenght(n), allocated(n)
		{
			// std::cout << "wazaaaaaaaaaaaaaa" << std::endl;
			if (allocated)
			{
				arr = myAllocator.allocate(allocated);
				for (size_t i = 0; i < allocated; i++)
					myAllocator.construct(arr + i);
			}
		}
		~vector()
		{
			for (size_t i = 0; i < allocated; i++)
				myAllocator.destroy(arr + i);
			myAllocator.deallocate(arr, allocated);
		}

		void push_back(T &obj)
		{
			if (lenght >= allocated)
			{
				if (allocated)
				{
					T *new_arr = myAllocator.allocate(allocated * 2);
					for (size_t i = 0; i < lenght; i++)
						myAllocator.construct(new_arr + i, arr[i]);
					myAllocator.deallocate(arr, allocated);
					arr = new_arr;
					allocated *= 2;
				}
				else
				{
					allocated *= 2;
					arr = myAllocator.allocate(1);
					allocated = 1;
				}
			}
			myAllocator.construct(arr + lenght, obj);
			lenght++;
		}
		ssize_t size() const
		{
			return lenght;
		}
		ssize_t capacity() const
		{
			return allocated;
		}
		T &operator[](size_t d) const
		{
			return arr[d];
		}
	};
};
#ifndef NAMESPACE
#define NAMESPACE std
#endif

#endif
int main()
{
	NAMESPACE::vector<vec> v(10); // sed
	// vec vec1(0, 1, 2);
	// v.push_back(vec1);

	// for (int i = 0; i < 10; i++)
	// {
	// 	vec vec1(0, 1, 2);
	// 	std::cout << "size: " << v.size() << ", capacity: " << v.capacity() << std::endl;
	// 	v.push_back(vec1);
	// }
	// for (int i = 0; i < 10; i++)
	// {
	// 	std::cout << v[i] << std::endl;
	// }
	return 0;
}