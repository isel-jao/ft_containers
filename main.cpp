#include <fstream>
#include <math.h>
#include <algorithm>
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
		class iterator
		{
			// Iterator tags
			// using iterator_category = std::random_access_iterator_tag;
			// using difference_type = std::ptrdiff_t;
		public:
			using value_type = T;
			using pointer = T *;   // or also value_type*
			using reference = T &; // or also value_type&

			iterator(pointer ptr = nullptr) : m_ptr(ptr) {}
			iterator(iterator const &other) : m_ptr(other.m_ptr) {}
			~iterator() {}
			iterator &operator=(iterator const &other)
			{
				if (*this == other)
					return (*this);
				m_ptr = other.m_ptr;
				return (*this);
			}
			iterator &operator+=(size_t index)
			{
				m_ptr += index;
				return (*this);
			}

			reference operator*() const { return *m_ptr; }
			pointer operator->() { return m_ptr; }
			reference &operator[](size_t index) { return *(m_ptr + index); }
			// reference &operator+(size_t index) {
			// 	std::cout << "hellooooo"  << std::endl;
			// 	return *(m_ptr + index);
			// 	}

			bool operator==(const iterator &other) { return m_ptr == other.m_ptr; };
			bool operator!=(const iterator &other) { return m_ptr != other.m_ptr; };
			bool operator<(const iterator &other) { return m_ptr < other.m_ptr; };
			bool operator>(const iterator &other) { return m_ptr > other.m_ptr; };
			bool operator<=(const iterator &other) { return m_ptr <= other.m_ptr; };
			bool operator>=(const iterator &other) { return m_ptr >= other.m_ptr; };

			iterator &operator++()
			{
				m_ptr++;
				return *this;
			}
			iterator operator++(int)
			{
				iterator tmp = *this;
				++(*this);
				return tmp;
			}
			iterator &operator--()
			{
				m_ptr--;
				return *this;
			}
			iterator operator--(int)
			{
				iterator tmp = *this;
				--(*this);
				return tmp;
			}

		private:
			pointer m_ptr;
		};

		iterator begin() { return iterator(arr); }
		iterator end() { return iterator(arr + lenght); }

		void push_back(T obj)
		{
			if (lenght >= allocated)
			{
				if (allocated)
				{
					T *new_arr = myAllocator.allocate(allocated * 2);
					for (size_t i = 0; i < lenght; i++)
						myAllocator.construct(new_arr + i, arr[i]);
					for (size_t i = 0; i < lenght; i++)
						myAllocator.destroy(arr + i);
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
		void assign(size_t n, T obj)
		{
			for (size_t i = 0; i < lenght; i++)
				myAllocator.destroy(arr + i);
			if (n && n > allocated)
			{
				myAllocator.deallocate(arr, allocated);
				arr = myAllocator.allocate(n);
				allocated = n;
			}
			for (size_t i = 0; i < n; i++)
				myAllocator.construct(arr + i, obj);
			lenght = n;
		}

		size_t size() const
		{
			return lenght;
		}
		size_t capacity() const
		{
			return allocated;
		}
		T &operator[](size_t d) const
		{
			return arr[d];
		}
		friend T operator+(T value, iterator it);
	};

};
#ifndef NAMESPACE
#define NAMESPACE std
#endif

#endif

int main()
{
	NAMESPACE::vector<int> v;
	NAMESPACE::vector<int>::iterator it1;
	NAMESPACE::vector<int>::iterator it2;
	NAMESPACE::vector<int>::iterator *it3;

	int i = 0;
	for (; i < 20; i++)
	{
		v.push_back(i * 2);
	}
	it1 = v.begin();
	it2 = it1 += 3;
	it3 = &it2;

}