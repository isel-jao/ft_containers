#include <fstream>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <map>
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

// namespace ft
// {
// 	template <typename T1, typename T2>
// 	struct pair
// 	{
// 		T1 first;
// 		T2 second;

// 		pair(T1 f = T1(), T2 s = T2()) : first(f), second(s) {}
// 		pair(pair &val) : first(val.first), second(val.second) {}
// 		pair &operator=(pair &val)
// 		{
// 			std::cout << "wazaaaaaaaaaaaaa" << std::endl;
// 			first = val.first;
// 			second = val.second;
// 			return *this;
// 		}
// 		~pair() {}
// 	};

// }
#define value_type pair<T1, T2>
#define key_type T1

typedef size_t size_type;

namespace ft
{
	using std::pair;
	template <typename T1, typename T2>
	class map
	{
	private:
		std::allocator<value_type> myAllocator;
		value_type *pairs;
		size_t _size;
		size_t _capacity;

	public:
		map() : pairs(NULL), _size(0), _capacity(0) {}
		~map() {}

		class iterator
		{
		public:
			iterator(value_type *ptr = NULL) : m_ptr(ptr) {}
			iterator(iterator const &other) : m_ptr(other.m_ptr) {}
			~iterator() {}
			iterator &operator=(iterator const &other)
			{
				if (*this == other)
					return (*this);
				m_ptr = other.m_ptr;
				return (*this);
			}

			value_type *get_addr() { return m_ptr; };
			value_type &operator*() const { return *m_ptr; }
			value_type *operator->() { return m_ptr; }
			value_type &operator[](size_t index) { return *(m_ptr + index); }

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
			value_type *m_ptr;
		};

		iterator begin() const { return iterator(pairs); }
		iterator end() const { return iterator(pairs + _size); }
		size_t size() const { return this->_size; }
		bool empty() const { return this->_size == 0; }

		iterator find(const key_type &k) const
		{
			iterator it = map::begin();
			while (it != map::end() && it->first != k)
				it++;
			return it;
		}
		pair<iterator, bool> insert(const value_type &val)
		{
			pair<iterator, bool> p;
			if (map::find(val.first) != map::end())
				return (p);
			if (_size >= _capacity)
			{
				if (_capacity)
				{
					value_type *new_pairs = myAllocator.allocate(_capacity * 2);
					for (size_t i = 0; i < _size; i++)
						myAllocator.construct(new_pairs + i, pairs[i]);
					for (size_t i = 0; i < _size; i++)
						myAllocator.destroy(pairs + i);
					myAllocator.deallocate(pairs, _capacity);
					pairs = new_pairs;
					_capacity *= 2;
				}
				else
				{
					_capacity *= 2;
					pairs = myAllocator.allocate(1);
					_capacity = 1;
				}
			}
			myAllocator.construct(pairs + _size, val);
			myAllocator.construct(pairs + _size, val);
			_size++;
			return (p);
		}
		iterator insert (iterator position, const value_type& val)
		{
			value_type value_at_position;
			size_type i;
			size_type new_position;
			if (position == map::end())
			{
				map::insert(val);
				return (map::begin());
			}
			if (_size >= _capacity)
			{
				value_at_position = *position;
				value_type *new_pairs = myAllocator.allocate(_capacity * 2);
				for (i = 0; pairs[i] != value_at_position; i++)
					myAllocator.construct(new_pairs + i, pairs[i]);
				for (i = 0; pairs[i] != value_at_position; i++)
					myAllocator.destroy(pairs + i);
				myAllocator.construct(new_pairs + i, val);
				new_position = i;
				for (; i < _size; i++)
				{
					myAllocator.construct(new_pairs + i + 1, pairs[i]);
				}
				for (i = new_position; i < _size; i++)
					myAllocator.destroy(pairs + i);
				myAllocator.deallocate(pairs, _capacity);
				pairs = new_pairs;
				_capacity *= 2;
				_size += 1;
			}
			else
			{
				myAllocator.construct(pairs + _size, pairs[_size - 1]);
				for (i = _size - 1; pairs[i] != *position; i--)
				{
					myAllocator.destroy(pairs + i);
					myAllocator.construct(pairs + i, pairs[i - 1]);
				}
				new_position = i;
				myAllocator.destroy(pairs + i);
				myAllocator.construct(pairs + i, val);
			}
			return (map::begin() + new_position);
		}
		void clear()
		{
			for (size_type i = 0; i < _size; i++)
				myAllocator.destroy(pairs + i);
			_size = 0;
		}
		size_type count(const key_type &k) const
		{
			if (map::find(k) != map::end())
				return 1;
			return 0;
		}
		std::allocator<value_type> get_allocator() const { return map::myAllocator; }
	};
}

#ifndef NAMESPACE
#define NAMESPACE std
#endif

#define log(x) std::cout << x << std::endl

using namespace NAMESPACE;

template <typename T1, typename T2>
void print_map(map<T1, T2> &m)
{
	std::cout << "s: " << m.size() << ", c: " << m.capacity() << "| ";
	if (m.size() <= 0)
	{
		std::cout << std::endl;
		return;
	}
	for (size_t i = 0; i < m.size(); i++)
		std::cout << "(" << m[0].first << ", " << m[0].second << ") ";
	std::cout << std::endl;
}

int main()
{
	NAMESPACE::map<std::string, int> m;
	// NAMESPACE::map<std::string, int> m;

	m.insert(std::pair<std::string, int>("isel", 28));
	m.insert(std::pair<std::string, int>("isel", 29));
	m.insert(std::pair<std::string, int>("karim", 25));
	NAMESPACE::map<std::string, int>::iterator it = m.find("karim");
	if (it != m.end())
		std::cout << "s: " << m.size() << ", " << it->first << ", " << it->second << std::endl;
	std::cout << m.count("mona") << std::endl;
	return 0;
}
