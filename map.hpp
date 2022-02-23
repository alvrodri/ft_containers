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
					typedef Compare	comp;

					bool	operator()(const value_type &x, const value_type &y) const {
						return (comp()(x.first, y.first));
					}
			};

			/* constructors */
			explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) {
				this->_key_compare = comp;
				this->_value_compare = value_compare();
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
			mapped_type	&operator[](const key_type &k) {
				iterator	lookup = this->_tree.lookup(this->_tree.getRoot(), k);

				if (lookup == this->end()) {
					return this->insert(ft::make_pair(k, T())).first->second;
				}
				return lookup->second;
			}
			/* element access */

			/* modifiers */
			ft::pair<iterator, bool>	insert(const value_type &val) {
				iterator	lookup = this->_tree.lookup(this->_tree.getRoot(), val.first);

				if (lookup != this->end()) {
					return ft::make_pair(lookup, false);
				}

				return ft::make_pair(this->_tree.insert(this->_tree.getRoot(), val), true);
			}

			iterator	insert(iterator position, const value_type &val) {
				iterator	lookup = this->_tree.lookup(this->_tree.getRoot(), val.first);

				if (lookup != this->end()) {
					return lookup;
				}

				return this->_tree.insert(position.base(), val);
			}

			template<class InputIterator>
			void	insert(InputIterator first, InputIterator last) {
				while (first != last) {
					this->insert(*first);
					first++;
				}
			}

			/*void	erase(iterator position) {

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

			/* lookup */
			size_type count(const key_type &key) const {
				return this->_tree.lookup(this->_tree.getRoot(), key) == this->end() ? 0 : 1;
			}

			iterator	find(const key_type &key) {
				return this->_tree.lookup(this->_tree.getRoot(), key);
			}

			const_iterator	find(const key_type &key) const {
				return this->_tree.lookup(this->_tree.getRoot(), key);
			}

			iterator	lower_bound(const key_type &key) {
				for (iterator it = this->begin(); it != this->end(); it++) {
					if (value_comp()(ft::make_pair(key, mapped_type()), *it) || it->first == key)
						return it;
				}
				return this->end();
			}

			const_iterator	lower_bound(const key_type &key) const {
				for (iterator it = this->begin(); it != this->end(); it++) {
					if (value_comp()(ft::make_pair(key, mapped_type()), *it) || it->first == key)
						return it;
				}
				return this->end();
			}

			iterator	upper_bound(const key_type &key) {
				for (iterator it = this->begin(); it != this->end(); it++) {
					if (!value_comp()(ft::make_pair(key, mapped_type()), *it))
						return it;
				}
				return this->end();
			}

			const_iterator	upper_bound(const key_type &key) const {
				for (iterator it = this->begin(); it != this->end(); it++) {
					if (!value_comp()(ft::make_pair(key, mapped_type()), *it))
						return it;
				}
				return this->end();
			}

			ft::pair<iterator, iterator> equal_range(const key_type &key) {
				return ft::make_pair(this->lower_bound(key), this->upper_bound(key));
			}

			ft::pair<const_iterator, const_iterator> equal_range(const key_type &key) const {
				return ft::make_pair(this->lower_bound(key), this->upper_bound(key));
			}
			/* lookup */

			iterator	begin() {
				return this->_tree.begin();
			}

			const_iterator	begin() const {
				return this->_tree.begin();
			}

			iterator	end() {
				return this->_tree.end();
			}

			const_iterator	end() const {
				return this->_tree.end();
			}

			binary_tree<Key, T, allocator_type>	getTree() {
				return this->_tree;
			}

			key_compare	key_comp() const {
				return _key_compare;
			}

			value_compare	value_comp() const {
				return _value_compare;
			}

			private:
				size_type		_size;
				size_type		_capacity;
				allocator_type	_allocator;
				key_compare		_key_compare;
				value_compare	_value_compare;
				tree_type		_tree;
		};
};