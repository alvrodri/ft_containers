#pragma once

#include "./utils/pair.hpp"
#include "./utils/utils.hpp"
#include "./utils/binary_tree.hpp"

namespace ft {
	template<
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<ft::pair<const Key, T> > >
		class map {
			public:
				typedef Key															key_type;
				typedef T															mapped_type;
				typedef ft::pair<const Key, T>										value_type;
				typedef size_t														size_type;
				typedef ptrdiff_t													difference_type;
				typedef Compare														key_compare;
				typedef Allocator													allocator_type;
				typedef typename allocator_type::reference							reference;
				typedef typename allocator_type::const_reference					const_reference;
				typedef typename allocator_type::pointer							pointer;
				typedef typename allocator_type::const_pointer						const_pointer;
				typedef binary_tree<key_type, mapped_type, allocator_type>			tree_type;

				typedef typename tree_type::iterator		iterator;
				typedef typename tree_type::const_iterator	const_iterator;

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
			};

			/* constructors */
			explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) {
				this->_key_compare = comp;
				this->_allocator = alloc;
				this->_tree = binary_tree<key_type, mapped_type, allocator_type>();
			}

			/*template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type& alloc = allocator_type()) {
				
			}*/
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

			/* element access */
			/*mapped_type	&operator[](const key_type &k) {

			}*/
			/* element access */

			/* modifiers */
			ft::pair<iterator, bool>	insert(const value_type &val) {
				//iterator	lookup = this->_tree.lookup(this->_tree.getRoot(), val.first);

				/*if (lookup != this->end()) {
					return (ft::make_pair(lookup, false));
				}*/
				this->_tree.insert(this->_tree.getRoot(), val);
				return ft::make_pair(this->_tree.lookup(this->_tree.getRoot(), val.first), true);
			}

			/*iterator	insert(iterator position, const value_type &val) {

			}

			template<class InputIterator>
			void	insert(InputIterator first, InputIterator last) {

			}

			void	erase(iterator position) {

			}

			size_type	erase(const key_type &k) {

			}

			void	erase(iterator first, iterator last) {

			}

			void	swap(ft::map &x) {

			}

			void	clear() {

			}*/
			/* modifiers */

			iterator	begin() {
				return this->_tree.begin();
			}

			iterator	end() {
				return this->_tree.end();
			}

			binary_tree<Key, T, allocator_type>	getTree() {
				return this->_tree;
			}

			private:
				size_type		_size;
				size_type		_capacity;
				allocator_type	_allocator;
				key_compare		_key_compare;
				tree_type		_tree;
		};
};