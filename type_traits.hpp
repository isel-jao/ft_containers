#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

#include "ft_containers.hpp"

namespace ft
{
	// is_pointer ==>	return true if:
	// type == pointer_type
	template <typename T>
	struct is_pointer
	{
		static const bool value = false;
	};
	template <typename T>
	struct is_pointer<T *>
	{
		static const bool value = true;
	};

	// is_void ==>	return true if:
	// type == void
	template <typename T>
	struct is_void
	{
		static const bool value = false;
	};
	template <>
	struct is_void<void>
	{
		static const bool value = true;
	};

	// is_integral ==>	return true if:
	// type == /char|unsigned char|short|unsighned short|int|unsigned int|long\unsigned long/
	template <typename T>
	struct is_integral
	{
		static const bool value = false;
	};

	template <>
	struct is_integral<bool>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<char>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned char>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<int>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned int>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<long>
	{
		static const bool value = true;
	};
	template <>
	struct is_integral<long unsigned>
	{
		static const bool value = true;
	};
	template <>
	struct is_integral<short>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<short unsigned>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<long long>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<long long unsigned>
	{
		static const bool value = true;
	};


	// The type T is enabled as member type enable_if::type if Cond is true.
	// Otherwise, enable_if::type is not defined.
	template <bool Cond, class T = void>
	struct enable_if
	{
	};
	
	template <class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};


}

#endif