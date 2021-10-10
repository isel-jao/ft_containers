#include <fstream>
#include <map>
#include <math.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <string.h>
#include <deque>

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

#define ALLOCATOR Alloc = std::allocator<T>

namespace ft
{
	
	template <class T, class ALLOCATOR>
	class vector
	{
		typedef T value_type;
		typedef Alloc allocator_type;
		// typedef allocator_type::reference reference;
		// typedef allocator_type::const_reference const_reference;
		// typedef allocator_type::pointer pointer;
		// typedef allocator_type::const_pointer const_pointer;
		typedef size_t size_type;

	private:
		allocator_type _allocator;
		size_type _capacity;
		size_type _size;
		value_type *arr;

	public:
		//////// constructors ////////
		vector(const allocator_type &alloc = allocator_type())
			: _allocator(alloc), _capacity(0), _size(0), arr(NULL) {}
		vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
			: _allocator(alloc), _capacity(n), _size(n)
		{
			if (n)
			{
				arr = _allocator.allocate(_size);
				for (size_t i = 0; i < _size; i++)
					_allocator.construct(arr + i, val);
			}
			else
				arr = NULL;
		}
		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type())
			: _allocator(alloc)
		{
			InputIterator tmp = first;
			_capacity = 0;
			while (tmp != last)
			{
				tmp++;
				_capacity++;
			}
			_size = _capacity;
			arr = _allocator.allocate(_size);
			for (size_t i = 0; i < _size; i++)
				_allocator.construct(arr + i, *(first++));
		}

		//////// copy constructors ////////
		vector(const vector &x) : _size(x._size), _capacity(x._capacity)
		{
			if (_capacity)
			{
				arr = _allocator.allocate(_capacity);
				for (size_t i = 0; i < _size; i++)
					_allocator.construct(arr + i);
			}
		}

		//////// destructors ////////
		~vector()
		{
			for (size_t i = 0; i < _capacity; i++)
				_allocator.destroy(arr + i);
		}
	};
}

#ifndef NAMESPACE
#define NAMESPACE std
#endif

int main()
{
	std::cout << "hello world!" << std::endl;
	std::map<int, int> m;
	for (int i = 0; i < 10; i++)
		m.insert(std::pair<int, int>(i + 1, (i + 1) * 2)) ;
	std::map<int, int>::iterator it1 , it2;
	it1 = m.begin();
	it2 = it1;
	for(int i = 0 ; i < 6; i++)
		it2++;
	NAMESPACE::vector<std::pair<int, int> > v1(it1, it2);
	return 0;
}