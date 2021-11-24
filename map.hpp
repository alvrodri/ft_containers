#pragma once

#include "./utils/pair.hpp"
#include "./utils/utils.hpp"

namespace ft {
	template<
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<ft::pair<const Key, T> > >
		class map {
			public:
				typedef Key								key_type;
				typedef T								mapped_type;
				typedef ft::pair<const Key, T>			value_type;
				typedef size_t							size_type;
				typedef ptrdiff_t						difference_type;
				typedef Compare							key_compare;
				typedef Allocator						allocator_type;
				typedef allocator_type::reference		reference;
				typedef allocator_type::const_reference	const_reference;
				typedef allocator_type::pointer			pointer;
				typedef allocator_type::const_pointer	const_pointer;
		};
};