#include <fstream>
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
		vector(size_t const n = 0, T value = T()) : lenght(n), allocated(n)
		{
			if (allocated)
			{
				arr = myAllocator.allocate(allocated);
				for (size_t i = 0; i < allocated; i++)
					myAllocator.construct(arr + i, value);
			}
		}
		vector(vector<T> &other) : lenght(other.lenght), allocated(other.allocated)
		{
			if (allocated)
			{
				arr = myAllocator.allocate(allocated);
				for (size_t i = 0; i < lenght; i++)
					myAllocator.construct(arr + i);
			}
		}
		// template <class InputIterator>
		// vector(InputIterator first, InputIterator last, const std::allocator<T> &alloc = allocator_type()){}
		~vector()
		{
			for (size_t i = 0; i < allocated; i++)
				myAllocator.destroy(arr + i);
		}
		class iterator
		{
		public:
			iterator(T *ptr = NULL) : m_ptr(ptr) {}
			iterator(iterator const &other) : m_ptr(other.m_ptr) {}
			~iterator() {}
			iterator &operator=(iterator const &other)
			{
				if (*this == other)
					return (*this);
				m_ptr = other.m_ptr;
				return (*this);
			}

			T *get_addr() { return m_ptr; };
			T &operator*() const { return *m_ptr; }
			T *operator->() { return m_ptr; }
			T &operator[](size_t index) { return *(m_ptr + index); }

			iterator &operator+=(size_t index)
			{
				m_ptr += index;
				return (*this);
			}
			iterator &operator-=(size_t index)
			{
				m_ptr -= index;
				return (*this);
			}

			iterator operator+(size_t index) { return iterator(m_ptr + index); }
			iterator operator-(size_t index) { return iterator(m_ptr - index); }

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
			T *m_ptr;
		};

		iterator begin() { return iterator(arr); }
		iterator end() { return iterator(arr + lenght); }

		void push_back(T val)
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
			myAllocator.construct(arr + lenght, val);
			myAllocator.construct(arr + lenght, val);
			lenght++;
		}
		iterator insert(iterator position, const T &val)
		{
			T value_at_position;
			size_t i;
			size_t new_position;
			if (position == vector::end())
			{
				vector::push_back(val);
				return (vector::begin());
			}
			if (lenght >= allocated)
			{
				value_at_position = *position;
				T *new_arr = myAllocator.allocate(allocated * 2);
				for (i = 0; arr[i] != value_at_position; i++)
					myAllocator.construct(new_arr + i, arr[i]);
				for (i = 0; arr[i] != value_at_position; i++)
					myAllocator.destroy(arr + i);
				myAllocator.construct(new_arr + i, val);
				new_position = i;
				for (; i < lenght; i++)
				{
					myAllocator.construct(new_arr + i + 1, arr[i]);
				}
				for (i = new_position; i < lenght; i++)
					myAllocator.destroy(arr + i);
				myAllocator.deallocate(arr, allocated);
				arr = new_arr;
				allocated *= 2;
				lenght += 1;
			}
			else
			{
				myAllocator.construct(arr + lenght, arr[lenght - 1]);
				for (i = lenght - 1; arr[i] != *position; i--)
				{
					myAllocator.destroy(arr + i);
					myAllocator.construct(arr + i, arr[i - 1]);
				}
				new_position = i;
				myAllocator.destroy(arr + i);
				myAllocator.construct(arr + i, val);
			}
			return (vector::begin() + new_position);
		}
		void insert(iterator position, size_t n, const T &val)
		{
			T value_at_position;
			size_t i;
			size_t new_position;
			if (position == vector::end())
			{
				while (n--)
					vector::push_back(val);
				return;
			}
			if (lenght + n > allocated)
			{
				value_at_position = *position;
				T *new_arr = myAllocator.allocate(allocated + n);
				for (i = 0; arr[i] != value_at_position; i++)
					myAllocator.construct(new_arr + i, arr[i]);
				for (i = 0; arr[i] != value_at_position; i++)
					myAllocator.destroy(arr + i);
				new_position = i;
				for (size_t j = 0; j < n; j++)
					myAllocator.construct(new_arr + i + j, val);
				for (; i < lenght; i++)
				{
					myAllocator.construct(new_arr + i + n, arr[i]);
				}
				for (i = new_position; i < lenght; i++)
					myAllocator.destroy(arr + i);
				myAllocator.deallocate(arr, allocated);
				arr = new_arr;
				allocated += n;
				lenght += n;
			}
			else
			{
				std::cout << "wazaaaaaaaaaaa" << std::endl;
				myAllocator.construct(arr + lenght + n - 1, arr[lenght - 1]);
				for (i = lenght + n - 1; arr[i - n + 1] != *position; i--)
				{
					myAllocator.destroy(arr + i);
					myAllocator.construct(arr + i, arr[i - n]);
				}
				lenght += n;
				while (n-- > 0)
				{
					myAllocator.destroy(arr + i);
					myAllocator.construct(arr + i, val);
					i--;
				}
			}
		}
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last)
		{
			size_t n = 0;
			T value_at_position;
			size_t i;
			size_t new_position;
			while (first + n < last)
				n++;
			if (position == vector::end())
			{
				while (n--)
					vector::push_back(*first++);
				return;
			}
			if (lenght + n > allocated)
			{
				value_at_position = *position;
				T *new_arr = myAllocator.allocate(allocated + n);
				for (i = 0; arr[i] != value_at_position; i++)
					myAllocator.construct(new_arr + i, arr[i]);
				for (i = 0; arr[i] != value_at_position; i++)
					myAllocator.destroy(arr + i);
				new_position = i;
				for (size_t j = 0; j < n; j++)
					myAllocator.construct(new_arr + i + j, *first++);
				for (; i < lenght; i++)
					myAllocator.construct(new_arr + i + n, arr[i]);
				for (i = new_position; i < lenght; i++)
					myAllocator.destroy(arr + i);
				myAllocator.deallocate(arr, allocated);
				arr = new_arr;
				allocated += n;
				std::cout << allocated << std::endl;
				lenght += n;
			}
			else
			{
				myAllocator.construct(arr + lenght + n - 1, arr[lenght - 1]);
				for (i = lenght + n - 1; arr[i - n + 1] != *position; i--)
				{
					myAllocator.destroy(arr + i);
					myAllocator.construct(arr + i, arr[i - n]);
				}
				lenght += n;
				while (n-- > 0)
				{
					myAllocator.destroy(arr + i);
					myAllocator.construct(arr + i, *(first + n));
					i--;
				}
			}
		}
		void assign(size_t n, T val)
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
				myAllocator.construct(arr + i, val);
			lenght = n;
		}
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			for (size_t i = 0; i < lenght; i++)
				myAllocator.destroy(arr + i);
			lenght = 0;
			while (first + lenght < last)
				lenght++;
			std::cout << lenght << std::endl;
			if (lenght > allocated)
			{
				myAllocator.deallocate(arr, allocated);
				arr = myAllocator.allocate(lenght);
				allocated = lenght;
			}
			for (lenght = 0; first + lenght < last; lenght++)
			{
				arr[lenght] = first[lenght];
				lenght++;
			}
		}
		T &at(size_t index) { return *(arr + index); }
		const T &at(size_t index) const { return *(arr + index); }
		T &back() { return *(arr + lenght - 1); }
		const T &back() const { return *(arr + lenght - 1); }
		T &fornt() { return *(arr); }

		void clear()
		{
			for (size_t i = 0; i < lenght; i++)
				myAllocator.destroy(arr + i);
			lenght = 0;
		}

		iterator erase(iterator first, iterator last = NULL)
		{
			size_t count = 0;

			if (last == NULL)
				last = first + 1;
			if (last < first)
				return first;
			if (last > vector::end())
				last = vector::end();
			for (; first + count < last; count++)
				;
			for (size_t i = 0; last + i < vector::end(); i++)
			{
				*(first + i) = *(last + i);
			}
			for (size_t i = 0; i < count; i++)
				myAllocator.destroy(arr + lenght - 1 - i);
			lenght -= count;
			return (first);
		}
		bool empty() const { return lenght == 0; }
		size_t size() const { return lenght; }
		size_t capacity() const { return allocated; }
		T &operator[](size_t d) const { return arr[d]; }
		std::allocator<T> get_allocator() const { return vector::myAllocator; }
	};

};

#ifndef NAMESPACE
#define NAMESPACE std
#endif

#endif

#define log(x) std::cout << x << std::endl

using namespace NAMESPACE;
template <typename T>
void print_vector(vector<T> &v)
{
	std::cout << "s: " << v.size() << ", c: " << v.capacity() << "| ";
	if (v.size() <= 0)
		return;
	std::cout << v[0];
	for (size_t i = 1; i < v.size(); i++)
		std::cout << ", " << v[i];
	std::cout << std::endl;
}
// iterator insert (iterator position, const value_type& val);
int main()
{
	NAMESPACE::vector<int> v1(5);
	int arr[10];
	for (int i = 0; i < 10; i++)
		arr[i] = i * 11;
	for (size_t i = 1; i < 5; i++)
		v1[i] = (i + 1) * 10;
	// v1.push_back(666);
	v1.insert(v1.begin() + 2, arr + 1, arr + 7);
	print_vector(v1);
	return 0;
}