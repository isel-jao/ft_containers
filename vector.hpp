#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "ft_containers.hpp"

#define ALLOCATOR Alloc = std::allocator<T>

namespace ft
{

	template <class T, class ALLOCATOR>
	class vector
	{
	public:
		typedef T value_type;											  // T
		typedef Alloc allocator_type;									  // std::allocator
		typedef typename allocator_type::reference reference;			  // T&
		typedef typename allocator_type::const_reference const_reference; // const T&
		typedef typename allocator_type::pointer pointer;				  // T*
		typedef typename allocator_type::const_pointer const_pointer;	  // const T*
		typedef typename ft::vector_iterator<pointer> iterator;
		typedef typename ft::vector_iterator<const_pointer> const_iterator;
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
		vector(const vector &x) : _capacity(x._capacity), _size(x._size)
		{
			if (_capacity)
			{
				arr = _allocator.allocate(_capacity);
				for (size_t i = 0; i < _size; i++)
					_allocator.construct(arr + i, x[i]);
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
		const_iterator begin() const { return const_iterator(arr); }

		// Returns the size of the storage space currently allocated for the vector,
		size_type capacity() const { return _capacity; }

		// Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
		void clear()
		{
			for (size_t i = 0; i < _size; i++)
				_allocator.destroy(arr + i);
			_size = 0;
		}

		// Returns whether the vector is empty (i.e. whether its size is 0).
		bool empty() const { return _size == 0; }

		// Returns an iterator referring to the past-the-end element in the vector container.
		iterator end() { return iterator(arr + _size); }
		const_iterator end() const { return const_iterator(arr + _size); }

		// Removes from the vector either a single element (position) or a range of elements ([first,last)).
		iterator erase(iterator first, iterator last)
		{
			size_t count = 0;

			if (last < first)
				return first;
			if (last > vector::end())
				last = vector::end();
			for (; first + count != last; count++)
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
		iterator erase(iterator position)
		{
			return vector::erase(position, position + 1);
		}

		// Returns a reference to the first element in the vector.
		reference front() { return *arr; }
		const_reference front() const { return *arr; }

		// Returns a copy of the allocator object associated with the vector.
		allocator_type get_allocator() const { return _allocator; }

		iterator insert(iterator position, const value_type &val)
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
				_size += 1;
			}
			return (vector::begin() + new_position);
		}

		void insert(iterator position, size_type n, const value_type &val)
		{
			value_type value_at_position;
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
				_size += n;
				_capacity = _size;
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
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type
		insert(iterator position, InputIterator first, InputIterator last)
		{
			size_type n = 0;
			value_type value_at_position;
			size_type i;
			size_type new_position;
			InputIterator tmp = first;
			while (tmp++ != last)
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
				_size += n;
				_capacity = _size;
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

		// Returns the maximum number of elements that the vector can hold.
		size_type max_size(void) const { return allocator_type().max_size(); }

		// Removes the last element in the vector, effectively reducing the container size by one.
		void pop_back()
		{
			if(_size == 0)
				return;
			allocator_type().destroy(arr + --_size);
		}


		//Returns a reference to the element at position n in the vector container.
		reference operator[](size_type n) { return arr[n]; }
		const_reference operator[](size_type n) const { return arr[n]; }

		// Adds a new element at the end of the vector, after its current last element. The content of val is copied (or moved) to the new element.
		void push_back(const value_type &val)
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

		size_type size() const { return _size; }
	};
}

#endif