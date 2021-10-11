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
		std::allocator<T> _allocator;
		T *arr;
		size_t _size;
		size_t _capacity;

	public:
		vector(size_t const n = 0, T value = T()) : _size(n), _capacity(n)
		{
			if (_capacity)
			{
				arr = _allocator.allocate(_capacity);
				for (size_t i = 0; i < _capacity; i++)
					_allocator.construct(arr + i, value);
			}
		}
		vector(vector<T> &x) : _size(x._size), _capacity(x._capacity)
		{
			if (_capacity)
			{
				arr = _allocator.allocate(_capacity);
				for (size_t i = 0; i < _size; i++)
					_allocator.construct(arr + i);
			}
		}
		// template <class InputIterator>
		// vector(InputIterator first, InputIterator last, const std::allocator<T> &alloc = allocator_type()){}
		~vector()
		{
			for (size_t i = 0; i < _capacity; i++)
				_allocator.destroy(arr + i);
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
		class reverse_iterator
		{
		public:
			reverse_iterator(T *ptr = NULL) : m_ptr(ptr) {}
			reverse_iterator(reverse_iterator const &other) : m_ptr(other.m_ptr) {}
			~reverse_iterator() {}
			reverse_iterator &operator=(reverse_iterator const &other)
			{
				if (*this == other)
					return (*this);
				m_ptr = other.m_ptr;
				return (*this);
			}

			T *get_addr() { return m_ptr; };
			T &operator*() const { return *m_ptr; }/*  */
			T &operator->() { 
				std::cout << "here" << std::endl;
				std::cout << "here" << std::endl;
				std::cout << "here" << std::endl;
				std::cout << "here" << std::endl;
				std::cout << "here" << std::endl;
				std::cout << "here" << std::endl;
				std::cout << "here" << std::endl;
				return *this; 
				}
			T &operator[](size_t index) { return *(m_ptr - index); }

			reverse_iterator &operator+=(size_t index)
			{
				m_ptr -= index;
				return (*this);
			}
			reverse_iterator &operator-=(size_t index)
			{
				m_ptr += index;
				return (*this);
			}

			reverse_iterator operator+(size_t index) { return reverse_iterator(m_ptr = index); }
			reverse_iterator operator-(size_t index) { return reverse_iterator(m_ptr + index); }

			bool operator==(const reverse_iterator &other) { return m_ptr == other.m_ptr; };
			bool operator!=(const reverse_iterator &other) { return m_ptr != other.m_ptr; };
			bool operator<(const reverse_iterator &other) { return m_ptr > other.m_ptr; };
			bool operator>(const reverse_iterator &other) { return m_ptr < other.m_ptr; };
			bool operator<=(const reverse_iterator &other) { return m_ptr >= other.m_ptr; };
			bool operator>=(const reverse_iterator &other) { return m_ptr <= other.m_ptr; };

			reverse_iterator &operator++()
			{
				m_ptr--;
				return *this;
			}
			reverse_iterator operator++(int)
			{
				reverse_iterator tmp = *this;
				--(*this);
				return tmp;
			}
			reverse_iterator &operator--()
			{
				m_ptr++;
				return *this;
			}
			reverse_iterator operator--(int)
			{
				reverse_iterator tmp = *this;
				++(*this);size_type capacity() const;
				return tmp;
			}

		private:
			T *m_ptr;
		};

		iterator begin() { return iterator(arr); }
		iterator end() { return iterator(arr + _size); }

		reverse_iterator rbegin() { return reverse_iterator(arr + _size - 1); }
		reverse_iterator rend() { return reverse_iterator(arr - 1); }
		void push_back(T val)
		{
			if (_size >= _capacity)
			{
				if (_capacity)
				{
					T *new_arr = _allocator.allocate(_capacity * 2);
					for (size_t i = 0; i < _size; i++)
						_allocator.construct(new_arr + i, arr[i]);
					for (size_t i = 0; i < _size; i++)
						_allocator.destroy(arr + i);
					_allocator.deallocate(arr, _capacity);
					arr = new_arr;
					_capacity *= 2;
				}
				else
				{
					_capacity *= 2;
					arr = _allocator.allocate(1);
					_capacity = 1;
				}
			}
			_allocator.construct(arr + _size, val);
			_allocator.construct(arr + _size, val);
			_size++;
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
			if (_size >= _capacity)
			{
				value_at_position = *position;
				T *new_arr = _allocator.allocate(_capacity * 2);
				for (i = 0; arr[i] != value_at_position; i++)
					_allocator.construct(new_arr + i, arr[i]);
				for (i = 0; arr[i] != value_at_position; i++)
					_allocator.destroy(arr + i);
				_allocator.construct(new_arr + i, val);
				new_position = i;
				for (; i < _size; i++)
				{
					_allocator.construct(new_arr + i + 1, arr[i]);
				}
				for (i = new_position; i < _size; i++)
					_allocator.destroy(arr + i);
				_allocator.deallocate(arr, _capacity);
				arr = new_arr;
				_capacity *= 2;
				_size += 1;
			}
			else
			{
				_allocator.construct(arr + _size, arr[_size - 1]);
				for (i = _size - 1; arr[i] != *position; i--)
				{
					_allocator.destroy(arr + i);
					_allocator.construct(arr + i, arr[i - 1]);
				}
				new_position = i;
				_allocator.destroy(arr + i);
				_allocator.construct(arr + i, val);
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
			if (_size + n > _capacity)
			{
				value_at_position = *position;
				T *new_arr = _allocator.allocate(_capacity + n);
				for (i = 0; arr[i] != value_at_position; i++)
					_allocator.construct(new_arr + i, arr[i]);
				for (i = 0; arr[i] != value_at_position; i++)
					_allocator.destroy(arr + i);
				new_position = i;
				for (size_t j = 0; j < n; j++)
					_allocator.construct(new_arr + i + j, val);
				for (; i < _size; i++)
				{
					_allocator.construct(new_arr + i + n, arr[i]);
				}
				for (i = new_position; i < _size; i++)
					_allocator.destroy(arr + i);
				_allocator.deallocate(arr, _capacity);
				arr = new_arr;
				_capacity += n;
				_size += n;
			}
			else
			{
				_allocator.construct(arr + _size + n - 1, arr[_size - 1]);
				for (i = _size + n - 1; arr[i - n + 1] != *position; i--)
				{
					_allocator.destroy(arr + i);
					_allocator.construct(arr + i, arr[i - n]);
				}
				_size += n;
				while (n-- > 0)
				{
					_allocator.destroy(arr + i);
					_allocator.construct(arr + i, val);
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
			if (_size + n > _capacity)
			{
				value_at_position = *position;
				T *new_arr = _allocator.allocate(_capacity + n);
				for (i = 0; arr[i] != value_at_position; i++)
					_allocator.construct(new_arr + i, arr[i]);
				for (i = 0; arr[i] != value_at_position; i++)
					_allocator.destroy(arr + i);
				new_position = i;
				for (size_t j = 0; j < n; j++)
					_allocator.construct(new_arr + i + j, *first++);
				for (; i < _size; i++)
					_allocator.construct(new_arr + i + n, arr[i]);
				for (i = new_position; i < _size; i++)
					_allocator.destroy(arr + i);
				_allocator.deallocate(arr, _capacity);
				arr = new_arr;
				_capacity += n;
				std::cout << _capacity << std::endl;
				_size += n;
			}
			else
			{
				_allocator.construct(arr + _size + n - 1, arr[_size - 1]);
				for (i = _size + n - 1; arr[i - n + 1] != *position; i--)
				{
					_allocator.destroy(arr + i);
					_allocator.construct(arr + i, arr[i - n]);
				}
				_size += n;
				while (n-- > 0)
				{
					_allocator.destroy(arr + i);
					_allocator.construct(arr + i, *(first + n));
					i--;
				}
			}
		}
		void assign(size_t n, T val)
		{
			for (size_t i = 0; i < _size; i++)
				_allocator.destroy(arr + i);
			if (n && n > _capacity)
			{
				_allocator.deallocate(arr, _capacity);
				arr = _allocator.allocate(n);
				_capacity = n;
			}
			for (size_t i = 0; i < n; i++)
				_allocator.construct(arr + i, val);
			_size = n;
		}
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			for (size_t i = 0; i < _size; i++)
				_allocator.destroy(arr + i);
			_size = 0;
			while (first + _size < last)
				_size++;
			std::cout << _size << std::endl;
			if (_size > _capacity)
			{
				_allocator.deallocate(arr, _capacity);
				arr = _allocator.allocate(_size);
				_capacity = _size;
			}
			for (_size = 0; first + _size < last; _size++)
			{
				arr[_size] = first[_size];
				_size++;
			}
		}

		T &at(size_t index) { return *(arr + index); }
		const T &at(size_t index) const { return *(arr + index); }
		T &back() { return *(arr + _size - 1); }
		const T &back() const { return *(arr + _size - 1); }
		T &fornt() { return *(arr); }

		void clear()
		{
			for (size_t i = 0; i < _size; i++)
				_allocator.destroy(arr + i);
			_size = 0;
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
				_allocator.destroy(arr + _size - 1 - i);
			_size -= count;
			return (first);
		}
		void reserve(size_t n)
		{
			if (_capacity >= n)
				return;
			T *new_arr = _allocator.allocate(n);
			for (size_t i = 0; i < _size; i++)
				_allocator.construct(new_arr + i, arr[i]);
			for (size_t i = 0; i < _size; i++)
				_allocator.destroy(arr + i);
			_allocator.deallocate(arr, _capacity);
			arr = new_arr;
			_capacity = n;
		}
		void resize(size_t n, T val = T())
		{
			size_t i;
			if (n > _capacity)
			{
				_capacity = n;
				T *new_arr = _allocator.allocate(n);
				for (size_t i = 0; i < _size; i++)
					_allocator.construct(new_arr + i, arr[i]);
				arr = new_arr;
			}
			for (i = _size; i  < n; i++)
					_allocator.construct(arr + i, val);
			_size = n;
		}
		// void swap (vector& x)
		// {
			
		// }
		size_t max_size() const { return 0; };
		bool empty() const { return _size == 0; }
		size_t size() const { return _size; }
		size_t capacity() const { return _capacity; }
		T &operator[](size_t d) const { return arr[d]; }
		std::allocator<T> get_allocator() const { return vector::_allocator; }
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
	{
		std::cout << std::endl;
		return;
	}
	std::cout << v[0];
	for (size_t i = 1; i < v.size(); i++)
		std::cout << ", " << v[i];
	std::cout << std::endl;
}
// iterator insert (iterator position, const value_type& val);
int main()
{
	NAMESPACE::vector<vec> v1;

	for (int i = 0; i < 5; i++)
		v1.push_back(i * 10);
	
	print_vector(v1);
	NAMESPACE::vector<vec>::iterator it = v1.begin();
	std::cout << it->x << std::endl;
	
	return 0;
}