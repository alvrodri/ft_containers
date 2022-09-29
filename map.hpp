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

				class	value_compare {
					protected:
						Compare	comp;
					public:
						typedef bool		result_type;
						typedef value_type	first_argument_type;
						typedef value_type	second_argument_type;

						value_compare(Compare c): comp(c) {}

						bool	operator()(const value_type &x, const value_type &y) const {
							return (comp(x.first, y.first));
						}
				};

				typedef binary_tree<value_type, value_compare, key_compare, allocator_type>			tree_type;

				typedef typename ft::binary_tree_iterator<value_type, value_compare, key_compare>	iterator;

			explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) {
				this->_size = 0;
				this->_allocator = alloc;
				this->_tree = tree_type(comp);
			}

			template<class InputIt>
			map(InputIt first, InputIt last, const key_compare &comp = key_compare(), const allocator_type &alloc = Allocator()) {
				this->_size = 0;
				this->_allocator = alloc;
				this->_tree = tree_type(comp);
				//TODO this->insert(first, last);
			}

			map(const map &copy) {
				this->_allocator = allocator_type();
				this->_tree = tree_type();
				this->_size = 0;
				*this = copy;
			}

			~map(void) {
				// borrar todo TODO
			}

			/* ITERATORS */
			iterator	begin() {
				return iterator(this->_tree.smallest(this->_tree._root), &this->_tree);
			}

			iterator	end() {
				return iterator(NULL, &this->_tree);
			}
			/* ITERATORS */

			/* CAPACITY */
			bool	empty() const {
				return this->_size == 0;
			}

			size_type	size() const {
				return this->_size;
			}

			size_type	max_size() const {
				return this->_allocator.max_size();
			}
			/* CAPACITY */

			/* MODIFIERS */
			void	clear() {
				while (this->_size != 0) {
					this->_tree.delete_node(this->_tree.smallest(this->_tree._root));
					this->_size--;
				}
			}

			ft::pair<iterator, bool>	insert(const value_type &value) {
				typename tree_type::node_pointer	node = this->_tree.find(value);

				if (node) {
					return ft::make_pair(iterator(node, &this->_tree), false);
				}

				this->_size++;
				return ft::make_pair(iterator(this->_tree.insert(value), &this->_tree), true);
			}

			iterator	insert(iterator hint, const value_type &value) {
				return this->insert(value).first;
			}

			template<class InputIt>
			void insert(InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type * = NULL) {
				while (first != last) {
					this->insert(*first);
					first++;
				}
			}

			iterator	erase(iterator pos) {
				this->_tree.delete_node(this->_tree.find(*pos));
				this->_size--;

				return this->end();
			}

			size_type	erase(const Key &key) {
				typename tree_type::node_pointer	node = this->_tree.find(ft::make_pair(key, mapped_type()));
				
				if (node) {
					this->_tree.delete_node(node);
					this->_size--;
					return 1;
				}
				return 0;
			}
			/* MODIFIERS */

			/* LOOKUP */
			size_type	count(const Key &key) const {
				return this->find(key) == this->end() ? 0 : 1;
			}

			iterator	find(const Key &key) {
				typename tree_type::node_pointer	node = this->_tree.find(ft::make_pair(key, mapped_type()));

				if (node) {
					return iterator(node, &this->_tree);
				}
				return this->end();
			}

			iterator	lower_bound(const key_type &key) {
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

			ft::pair<iterator, iterator> equal_range(const key_type &key) {
				return ft::make_pair(this->lower_bound(key), this->upper_bound(key));
			}
			/* LOOKUP */

			/* OBSERVERS */
			key_compare	key_comp() const {
				return key_compare();
			}

			value_compare	value_comp() const {
				return value_compare();
			}
			/* OBSERVERS */

			private:
				size_type		_size;
				allocator_type	_allocator;
				tree_type		_tree;
		};
};