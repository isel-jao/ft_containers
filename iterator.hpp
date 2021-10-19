#ifndef ETERATOR_HPP
#define ETERATOR_HPP

#include "ft_containers.hpp"

typedef std::ptrdiff_t ptrdiff_t;

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

	//////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////// vector_random_access_iterator /////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////
	template <typename T>
	struct vector_iterator : iterator<std::random_access_iterator_tag, typename iterator_traits<T>::value_type>
	{
	public:
		typedef T iterator_type;
		typedef typename ft::iterator_traits<T>::iterator_category iterator_category;
		typedef typename ft::iterator_traits<T>::value_type value_type;
		typedef typename ft::iterator_traits<T>::difference_type difference_type;
		typedef typename ft::iterator_traits<T>::pointer pointer;
		typedef typename ft::iterator_traits<T>::reference reference;
		typedef size_t size_type;

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
		reference operator[](size_type index) { return *(m_ptr + index); }

		vector_iterator &operator+=(size_type index)
		{
			m_ptr += index;
			return (*this);
		}
		vector_iterator &operator-=(size_type index)
		{
			m_ptr -= index;
			return (*this);
		}

		vector_iterator operator+(size_type index) { return vector_iterator(m_ptr + index); }
		vector_iterator operator-(size_type index) { return vector_iterator(m_ptr - index); }

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

	///////////////////////////////////////////////////////////////////////
	///////////////////////// reverse iterator ////////////////////////////
	///////////////////////////////////////////////////////////////////////
	template <class Iterator>
	struct reverse_iterator
	{
	public:
		////////////////////////// Member types //////////////////////////
		typedef Iterator iterator_type;
		typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;
		typedef typename ft::iterator_traits<Iterator>::value_type value_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
		typedef typename ft::iterator_traits<Iterator>::pointer pointer;
		typedef typename ft::iterator_traits<Iterator>::reference reference;

		//////////////////////// Member functions ////////////////////////

		// /^(con|de)structor&/
		reverse_iterator() : _iterator() {}
		explicit reverse_iterator(iterator_type it) : _iterator(it) {}
		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter> &rev_it) : _iterator(rev_it.base()) {}
		virtual ~reverse_iterator() {}

		// Returns a copy of the base iterator.
		iterator_type base() const { return (_iterator); }

		reference operator*() const
		{
			iterator_type tmp = _iterator;
			return (*(--tmp));
		}

		reverse_iterator operator+(difference_type n) const
		{
			return (reverse_iterator(_iterator - n));
		}

		reverse_iterator &operator++()
		{
			--_iterator;
			return (*this);
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator tmp = *this;
			++(*this);
			return (tmp);
		}

		reverse_iterator &operator+=(difference_type n)
		{
			_iterator -= n;
			return (*this);
		}

		reverse_iterator operator-(difference_type n) const { return (reverse_iterator(_iterator + n)); }

		reverse_iterator &operator--()
		{
			++_iterator;
			return (*this);
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator tmp = *this;
			--(*this);
			return (tmp);
		}

		reverse_iterator &operator-=(difference_type n)
		{
			_iterator += n;
			return (*this);
		}

		pointer operator->() const { return &(operator*()); }

		reference operator[](difference_type n) const { return (this->base()[-n - 1]); }

	private:
		iterator_type _iterator;
	};

	//////////////// relational operators (reverse_iterator) ////////////////
	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iterator_L, class Iterator_R>
	bool operator==(const reverse_iterator<Iterator_L> &lhs, const reverse_iterator<Iterator_R> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iterator_L, class Iterator_R>
	bool operator!=(const reverse_iterator<Iterator_L> &lhs, const reverse_iterator<Iterator_R> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iterator_L, class Iterator_R>
	bool operator<(const reverse_iterator<Iterator_L> &lhs, const reverse_iterator<Iterator_R> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator_L, class Iterator_R>
	bool operator<=(const reverse_iterator<Iterator_L> &lhs, const reverse_iterator<Iterator_R> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() < rhs.bash());
	}

	template <class Iterator_L, class Iterator_R>
	bool operator>(const reverse_iterator<Iterator_L> &lhs, const reverse_iterator<Iterator_R> &rhs)
	{
		return (lhs.base() < rhs.base());
	}
	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator_L, class Iterator_R>
	bool operator>=(const reverse_iterator<Iterator_L> &lhs, const reverse_iterator<Iterator_R> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

}

#endif
