#ifndef MAP_HPP
#define MAP_HPP

#include "ft_containers.hpp"

namespace ft
{
	template <class Key,											// map::key_type
			  class T,												// map::mapped_type
			  class Compare = std::less<Key>,						// map::key_compare
			  class Alloc = std::allocator<ft::pair<const Key, T> > // map::allocator_type
			  >
	class map
	{
		typedef Key key_type;
		typedef T mapped_type;
		typedef	typename ft::pair<const key_type,mapped_type> value_type;
		typedef	Compare key_compare;
		// value_compare not found
		typedef	Alloc allocator_type;
		typedef typename allocator_type::reference	reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer	pointer;
		typedef typename allocator_type::const_pointer	const_pointer;
		
	};

}

#endif

// Member type  value_compare missing