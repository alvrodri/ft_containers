#pragma once

#include "./utils.hpp"
#include "./pair.hpp"

namespace ft {
	template<class T>
	struct	s_node {
		T				value;

		struct s_node	*parent;
		struct s_node	*left;
		struct s_node	*right;

		s_node(void): parent(NULL), left(NULL), right(NULL) {}
		s_node(const T &value): value(value), parent(NULL), left(NULL), right(NULL) {}

		s_node	&operator=(const s_node &node) {
			this->value = node.value;
			return *this;
		}
	};

	template<class T, class ValueCompare, class KeyCompare, class Allocator = std::allocator<T> >
	class binary_tree {
		public:
			typedef	T																	value_type;
			typedef typename Allocator::template rebind<ft::s_node<value_type> >::other	allocator_type;
			typedef typename ft::s_node<value_type>										*node_pointer;
			typedef const typename ft::s_node<value_type>								*const_node_pointer;
			typedef ValueCompare														compare_type;

			allocator_type	_allocator;
			node_pointer	_root;
			compare_type	_compare;

		public:
			binary_tree(): _root(NULL), _allocator(allocator_type()), _compare(KeyCompare()) { }
			binary_tree(const compare_type &comp): _root(NULL), _allocator(allocator_type()), _compare(comp) { }

			binary_tree(const T &val, const compare_type &comp = compare_type()): _allocator(allocator_type()), _compare(comp) {
				this->_root = this->_allocator.allocate(1);
				this->_allocator.construct(this->_root, val);
				this->_root->parent = NULL;
				this->_root->left = NULL;
				this->_root->right = NULL;
			}

			binary_tree(node_pointer node, const compare_type &comp = compare_type()) :  _root(node), _allocator(allocator_type()), _compare(comp) {
				this->_root->parent = NULL;
				this->_root->left = NULL;
				this->_root->right = NULL;
			}

			~binary_tree(void) {}

			node_pointer	insert(const T &value) {
				node_pointer 	parent;
				node_pointer 	tmp = this->_root;
				node_pointer	to_insert = this->_allocator.allocate(1);

				this->_allocator.construct(to_insert, ft::s_node<T>(value));

				if (!this->_root) {
					this->_root = to_insert;
					return this->_root;
				}

				while (tmp) {
					parent = tmp;

					if (_compare(parent->value, value)) {
						tmp = tmp->right;
					} else {
						tmp = tmp->left;
					}
				}

				if (_compare(parent->value, value)) {
					parent->right = to_insert;
				} else {
					parent->left = to_insert;
				}

				to_insert->parent = parent;
				to_insert->right = NULL;
				to_insert->left = NULL;

				return to_insert;
			}

			void			delete_node(const T &value) {
				this->delete_node(this->find(value));
			}

			void			delete_node(node_pointer node) {
				// CRASH SI SE BORRA EL ROOT.

				node_pointer	parent = node->parent;
				node_pointer	tmp;

				if (node == NULL) {
					return ;
				}

				if (node->left == NULL && node->right == NULL) {
					this->_allocator.destroy(node);
					this->_allocator.deallocate(node, 1);
					
					if (parent != NULL) {
						parent->left == node ? parent->left = NULL : parent->right = NULL;
					}
					return ;
				}

				if ((node->left != NULL && node->right == NULL) || (node->right != NULL && node->left == NULL)) {
					if (node->left) {
						tmp = node->left;
					} else {
						tmp = node->right;
					}

					if (node == this->_root) {
						this->_root = tmp;
					} else {
						parent->left == node ? parent->left = tmp : parent->right = tmp;
					}
					tmp->parent = parent;

					this->_allocator.destroy(node);
					this->_allocator.deallocate(node, 1);
					return ;
				}

				if (node->left != NULL && node->right != NULL) {
					tmp = this->get_next(node->right);

					if (parent->left == node) {
						parent->left = tmp;
					} else {
						parent->right = tmp;
					}
					tmp->left = node->left;
					tmp->right = node->right;
					if (tmp->parent->left == tmp) {
						tmp->parent->left = NULL;
					} else {
						tmp->parent->right = NULL;
					}
					tmp->parent = parent;

					this->_allocator.destroy(node);
					this->_allocator.deallocate(node, 1);
					return ;
				}
				return ;
			}

			node_pointer	find(const T &value) const {
				node_pointer node = this->_root;
	
				while (node) {
					if (_compare(value, node->value)) {
						node = node->left;
					} else if (_compare(node->value, value)) {
						node = node->right;
					} else {
						return node;
					}
				}
				return NULL;
			}

			node_pointer	smallest(node_pointer node) {
				node_pointer current = node;

				while (current && current->left != NULL ){
					current = current->left;
				}

				return current;
			}

			node_pointer	bigger(node_pointer node) {
				node_pointer current = node;

				while (current && current->right != NULL) {
					current = current->right;
				}
				
				return current;
			}

			void	swap(node_pointer a, node_pointer b) {
				value_type value = a->value;

				a->value = b->value;
				b->value = value;
			}
	};
};