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

			class	value_compare {
				public:
					typedef bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;

					bool	operator()(const value_type &x, const value_type &y) const {
						return (comp(x.first, y.first));
					}
				protected:
					Compare	comp;
					value_compare(Compare c): comp(c) { }
			}

			/* constructors */
			explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) {
				this->_allocator = alloc;
			}

			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type& alloc = allocator_type()) {
				
			}
			/* constructors */

			/* capacity */
			bool		empty() const {
				return (this->_size == 0);
			}

			size_type	size() const {
				return (this->_size);
			}

			size_type	max_size() const {
				return (this->_allocator.max_size());
			}
			/* capacity */
			private:
				size_type		_size;
				size_type		_capacity;
				allocator_type	_allocator;
				pointer			_data;
		};
};