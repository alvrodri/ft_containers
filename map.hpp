#pragma once

#include "./utils/pair.hpp"
#include "./utils/utils.hpp"
#include "./utils/binary_tree.hpp"
#include "./utils/binary_tree_iterator.hpp"
#include "./utils/binary_tree_reverse_iterator.hpp"

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

				typedef binary_tree<value_type, value_compare, key_compare, allocator_type>				tree_type;

				typedef typename ft::binary_tree_iterator<value_type, value_compare, key_compare>		iterator;
				typedef typename ft::binary_tree_const_iterator<value_type, value_compare, key_compare>	const_iterator;

				typedef typename ft::reverse_iterator<iterator>											reverse_iterator;
				typedef typename ft::reverse_iterator<const_iterator>									const_reverse_iterator;

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
				this->insert(first, last);
			}

			map(const map &copy) {
				this->_allocator = allocator_type();
				this->_tree = tree_type();
				this->_size = 0;
				*this = copy;
			}

			map	&operator=(const map &src) {
				this->_allocator = src._allocator;
				this->clear();
				this->insert(src.begin(), src.end());
				this->_size = src._size;
				return *this;
			}

			~map(void) {
				// borrar todo TODO
			}

			/* ELEMENT ACCESS */
			T	&operator[](const Key &key) {
				typename tree_type::node_pointer	node = this->_tree.find(ft::make_pair(key, mapped_type()));
				
				if (!node) {
					return this->insert(ft::make_pair(key, mapped_type())).first->second;
				}
				return node->value.second;
			}

			T	&at(const Key &key) {
				typename tree_type::node_pointer	node = this->_tree.find(ft::make_pair(key, mapped_type()));

				if (!node) {
					throw std::out_of_range("at out of range");
				}

				return node->value.second;
			}

			const T	&at(const Key &key) const {
				typename tree_type::node_pointer	node = this->_tree.find(ft::make_pair(key, mapped_type()));

				if (!node) {
					throw std::out_of_range("at out of range");
				}

				return node->value.second;
			}
			/* ELEMENT ACCESS */

			/* ITERATORS */
			iterator	begin() {
				return iterator(this->_tree.smallest(this->_tree._root), &this->_tree);
			}

			const_iterator	begin() const {
				return const_iterator(this->_tree.smallest(this->_tree._root), &this->_tree);
			}

			iterator	end() {
				return iterator(NULL, &this->_tree);
			}

			const_iterator	end() const {
				return const_iterator(NULL, &this->_tree);
			}

			reverse_iterator rbegin() {
				return reverse_iterator(this->end());
			}

			const_reverse_iterator rbegin() const {
				return const_reverse_iterator(this->end());
			}

			reverse_iterator rend() {
				return reverse_iterator(this->begin());
			}

			const_reverse_iterator rend() const {
				return const_reverse_iterator(this->begin());
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
				while (this->_size > 0) {
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
				(void)hint;
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

			iterator erase(iterator first, iterator last) {
				iterator temp = first;

				while (first != last) {
					temp = first;
					first++;
					this->_tree.delete_node(*temp);
					--this->_size;
				}
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

			void swap(map &other) {
				tree_type	tree_ = other._tree;
				size_type	size_ = other._size;

				other._tree = this->_tree;
				other._size = this->_size;

				this->_tree = tree_;
				this->_size = size_;
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

			const_iterator	find(const Key &key) const {
				typename tree_type::node_pointer	node = this->_tree.find(ft::make_pair(key, mapped_type()));

				if (node) {
					return const_iterator(node, &this->_tree);
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

			const_iterator	lower_bound(const key_type &key) const {
				for (const_iterator it = this->begin(); it != this->end(); it++) {
					if (value_comp()(ft::make_pair(key, mapped_type()), *it) || it->first == key)
						return it;
				}
				return this->end();
			}

			const_iterator	upper_bound(const key_type &key) const {
				for (const_iterator it = this->begin(); it != this->end(); it++) {
					if (value_comp()(ft::make_pair(key, mapped_type()), *it))
						return it;
				}
				return this->end();
			}

			iterator	upper_bound(const key_type &key) {
				for (iterator it = this->begin(); it != this->end(); it++) {
					if (value_comp()(ft::make_pair(key, mapped_type()), *it))
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
			/* LOOKUP */

			/* OBSERVERS */
			key_compare	key_comp() const {
				return key_compare();
			}

			value_compare	value_comp() const {
				return value_compare(key_comp());
			}
			/* OBSERVERS */

			void print(const std::string& prefix, typename tree_type::node_pointer node, bool isLeft) {
				if (node != NULL) {
					std::cout << prefix;
					std::cout << (isLeft ? "├──" : "└──" );
					std::cout << node->value.first << "\033[0m" << " (" << node->value.second << ")" << std::endl;

					this->print(prefix + (isLeft ? "│   " : "    "), node->left, true);
					this->print(prefix + (isLeft ? "│   " : "    "), node->right, false);
				}
			}

			void print(typename tree_type::node_pointer node) {
				this->print("", node, false);
			}

			void print() {
				this->print(this->_tree._root);
			}

			private:
				size_type		_size;
				allocator_type	_allocator;
				tree_type		_tree;
		};

		template<class Key, class T, class Compare, class Alloc>
		void swap(ft::map<Key,T,Compare,Alloc> &lhs, ft::map<Key,T,Compare,Alloc> &rhs) {
			ft::map<Key,T,Compare,Alloc>	tmp = lhs;

			lhs = rhs;
			rhs = tmp;
		}

		template<class Key, class T, class Compare, class Alloc>
		bool operator==(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) {
			if (lhs.size() != rhs.size())
				return false;
			return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		}

		template<class Key, class T, class Compare, class Alloc>
		bool operator!=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) {
			return !(lhs == rhs);
		}

		template<class Key, class T, class Compare, class Alloc>
		bool operator<(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc>&  rhs) {
			return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

		template<class Key, class T, class Compare, class Alloc>
		bool operator<=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) {
			return lhs < rhs || lhs == rhs;
		}

		template<class Key, class T, class Compare, class Alloc>
		bool operator>(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) {
			return !(lhs <= rhs);
		}

		template<class Key, class T, class Compare, class Alloc>
		bool operator>=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) {
			return !(lhs < rhs);
		}
};