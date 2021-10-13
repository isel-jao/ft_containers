#ifndef PAIR_HPP
#define PAIR_HPP

#include "ft_containers.hpp"

#define waza() std::cout << "WAZAAAAAAAA,\t\tline: " << __LINE__ << ",\tfunc: " << __FUNCTION__ << std::endl

namespace ft
{
	template <class T1, class T2>
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		first_type first;
		second_type second;

		//default constructor
		pair() : first(first_type()), second(second_type()) {}
		// copy constructor
		pair(const pair &pr) : first(pr.first), second(pr.second) {}
		// initialization
		pair(const first_type &a, const second_type &b)
			: first(a), second(b) {}

		// Assigns pr as the new content for the pair object.
		pair &operator=(const pair &pr)
		{
			if (this == &pr)
				return *this;
			this->first = pr.first;
			this->second = pr.second;
			return *this;
		}
	};

}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////  relational operators  ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
template <class T1, class T2>
bool operator==(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
{
	return lhs.first == rhs.first && lhs.second == rhs.second;
}

template <class T1, class T2>
bool operator!=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
{
	return !(lhs == rhs);
}

template <class T1, class T2>
bool operator<(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
{
	return lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second);
}


template <class T1, class T2>
bool operator>(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
{
	return lhs.first > rhs.first || (lhs.first == rhs.first && lhs.second > rhs.second);
}

template <class T1, class T2>
bool operator<=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
{
	return !(lhs > rhs);
}
template <class T1, class T2>
bool operator>=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
{
	return !(lhs < rhs);
}





#endif