#include <fstream>
#include <map>
#include <math.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <string.h>
#include <deque>

namespace ft
{
	template <class Category,			  // iterator::iterator_category
			  class T,					  // iterator::value_type
			  class Distance = ptrdiff_t, // iterator::difference_type
			  class Pointer = T *,		  // iterator::pointer
			  class Reference = T &		  // iterator::reference
			  >
	struct iterator
	{
	public:
		typedef Category iterator_category;
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
	};

	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	template <class T>
	struct iterator_traits<T *>
	{

		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef std::random_access_iterator_tag iterator_category;
	};
	template <class T>
	struct iterator_traits<const T *>
	{

		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T *pointer;
		typedef const T &reference;
		typedef std::random_access_iterator_tag iterator_category;
	};
	template <typename T>
	class vector_iterator : iterator<std::random_access_iterator_tag, typename iterator_traits<T>::value_type>
	{
	public:
		typedef T iterator_type;
		typedef typename ft::iterator_traits<T>::iterator_category iterator_category;
		typedef typename ft::iterator_traits<T>::value_type value_type;
		typedef typename ft::iterator_traits<T>::difference_type difference_type;
		typedef typename ft::iterator_traits<T>::pointer pointer;
		typedef typename ft::iterator_traits<T>::reference reference;

		vector_iterator(iterator_type ptr = NULL) : m_ptr(ptr) {}
		vector_iterator(vector_iterator const &other) : m_ptr(other.m_ptr) {}
		~vector_iterator() {}
		vector_iterator &operator=(vector_iterator const &other)
		{
			if (*this == other)
				return (*this);
			m_ptr = other.m_ptr;
			return (*this);
		}
		// pointer get_addr() { return m_ptr; };
		reference operator*() const { return *m_ptr; }
		pointer operator->() { return m_ptr; }
		reference operator[](size_t index) { return *(m_ptr + index); }

		vector_iterator &operator+=(size_t index)
		{
			m_ptr += index;
			return (*this);
		}
		vector_iterator &operator-=(size_t index)
		{
			m_ptr -= index;
			return (*this);
		}

		vector_iterator operator+(size_t index) { return vector_iterator(m_ptr + index); }
		vector_iterator operator-(size_t index) { return vector_iterator(m_ptr - index); }

		bool operator==(const vector_iterator &other) { return m_ptr == other.m_ptr; };
		bool operator!=(const vector_iterator &other) { return m_ptr != other.m_ptr; };
		bool operator<(const vector_iterator &other) { return m_ptr < other.m_ptr; };
		bool operator>(const vector_iterator &other) { return m_ptr > other.m_ptr; };
		bool operator<=(const vector_iterator &other) { return m_ptr <= other.m_ptr; };
		bool operator>=(const vector_iterator &other) { return m_ptr >= other.m_ptr; };

		vector_iterator &operator++()
		{
			m_ptr++;
			return *this;
		}
		vector_iterator operator++(int)
		{
			vector_iterator tmp = *this;
			++(*this);
			return tmp;
		}
		vector_iterator &operator--()
		{
			m_ptr--;
			return *this;
		}
		vector_iterator operator--(int)
		{
			vector_iterator tmp = *this;
			--(*this);
			return tmp;
		}

	private:
		iterator_type m_ptr;
	};
}

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
	public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename ft::vector_iterator<pointer> iterator;
		typedef typename ft::vector_iterator<const pointer> const_iterator;
		typedef size_t size_type;

	private:
		allocator_type _allocator;
		size_type _capacity;
		size_type _size;
		value_type *arr;
		void checkRange(const size_type &n) const
		{
			if (n >= _size)
				// throw(std::out_of_range("vector::checkRange: n (which is " + std::to_string(n) + ") >= this->size() (which is " + std::to_string(_size) + ")"));
				throw(std::out_of_range("vector"));
		}

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
		//  the new contents are elements constructed from each of the elements in the range between first and last, in the same order.
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			for (size_t i = 0; i < _size; i++)
				_allocator.destroy(arr + i);
			_size = 0;
			InputIterator tmp = first;
			while (tmp++ < last)
				_size++;
			if (_size > _capacity)
			{
				_allocator.deallocate(arr, _capacity);
				arr = _allocator.allocate(_size);
				_capacity = _size;
			}
			for (_size = 0; first < last; _size++)
			{
				arr[_size] = *first;
				first++;
			}
		}
		// the new contents are n elements, each initialized to a copy of val.
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
		// The function automatically checks whether n is within the bounds of valid elements in the vector, throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its size). This is in contrast with member operator[], that does not check against bounds.
		reference at(size_type n)
		{
			checkRange(n);
			return *(arr + n);
		}
		const_reference at(size_type n) const
		{
			checkRange(n);
			return *(arr + n);
		}
		// Returns a reference to the last element in the vector.
		reference back() { return *(arr + _size - 1); }
		const_reference back() const { return *(arr + _size - 1); }

		// Returns an iterator pointing to the first element in the vector.
		iterator begin() { return iterator(arr); }
		const_iterator begin() const { return iterator(arr); }

		size_type capacity() const { return _capacity; }
	};
}

#ifndef NAMESPACE
#define NAMESPACE std
#endif

int main()
{
	try
	{
		int arr[] = {1, 2, 4, 5, 6, 7, 8, 9};
		NAMESPACE::vector<int> v;
		v.assign(arr, arr + 8);
		std::cout << "vector::at()\t" << v.at(3) << std::endl;
		std::cout << "vector::back()\t" << v.back() << std::endl;
		std::cout << "vector::capaci ()\t" << * << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}

	return 0;
}
