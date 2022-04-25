#pragma once

#include "./utils.hpp"
#include "./pair.hpp"
#include "./binary_tree_iterator.hpp"

namespace ft {
	template<class T1, class T2, class Allocator>
	class binary_tree {
		private:
			typedef enum {
				RED,
				BLACK
			}		e_color;

			typedef struct	s_node {
				ft::pair<T1, T2>	data;
				struct s_node		*parent;
				struct s_node		*left;
				struct s_node		*right;
				e_color				color;

				s_node(ft::pair<T1, T2> data): data(data), parent(NULL), left(NULL), right(NULL), color(RED) {}
			}				t_node;

			typedef Allocator											allocator;
			typedef typename allocator::template rebind<t_node>::other	node_allocator;
			typedef typename node_allocator::pointer					node_pointer;
			typedef typename node_allocator::const_pointer				node_const_pointer;
			typedef typename node_allocator::reference					node_reference;

			node_allocator	_allocator;
			node_pointer	_root;
			node_pointer	_nil;
		public:
			typedef binary_tree_iterator<node_pointer, ft::pair<T1, T2> >		iterator;
			typedef binary_tree_iterator<node_const_pointer, ft::pair<T1, T2> >	const_iterator;

			binary_tree(): _root(NULL) {
				this->_nil = _allocator.allocate(1);
				this->_allocator.construct(_nil, ft::pair<T1, T2>());
				this->_nil->color = BLACK;
				this->_nil->left = _nil;
				this->_nil->right = _nil;
			}

			node_pointer	createNode(ft::pair<T1, T2> &data) {
				node_pointer	node = this->_allocator.allocate(1);

				this->_allocator.construct(node, data);
				node->parent = this->_nil;
				node->left = this->_nil;
				node->right = this->_nil;

				return node;
			}

			// Add insert fix
			iterator	insert(node_pointer node, ft::pair<T1, T2> &data) {
				if (this->_root == NULL) {
					this->_root = this->createNode(data);
					this->_root->color = BLACK;
					return iterator(this->_root);
				}

				if (node == NULL) {
					node = this->createNode(data);
					return iterator(node);
				}

				if (data.first < node->data.first) {
					return this->insert(node->left, data);
				} else {
					return this->insert(node->right, data);
				}
				return this->end();
			}

			iterator		lookup(node_pointer node, const T1 &key) {
				if (node == this->_nil) {
					return (this->end());
				} else {
					if (key == node->data.first) {
						return (iterator(node, this->_root));
					} else {
						if (key < node->data.first)
							return (this->lookup(node->left, key));
						else
							return (this->lookup(node->right, key));
					}
				}
				return (this->end());
			}

			const_iterator		lookup(node_pointer node, const T1 &key) const {
				if (node == this->_nil) {
					return (this->end());
				} else {
					if (key == node->data.first)
						return (iterator(node, this->_root));
					else {
						if (key < node->data.first)
							return (this->lookup(node->left, key));
						else
							return (this->lookup(node->right, key));
					}
				}
				return (this->end());
			}

			iterator	erase(iterator position) {
				return iterator(deleteNode(this->_root, this->lookup(this->_root, position->first)->first), this->_root);
			}

			void	clear() {

			}

			node_pointer	getRoot() {
				return (this->_root);
			}

			const node_pointer	getRoot() const {
				return (this->_root);
			}

			iterator	begin() {
				return (iterator(min(this->_root), this->_root));
			}

			const_iterator	begin() const {
				return (const_iterator(min(this->_root), this->_root));
			}

			iterator	end() {
				return iterator(NULL, this->_root);
			}

			const_iterator	end() const {
				return const_iterator(NULL, this->_root);
			}
		private:
			node_pointer	min(node_pointer hint) {
				node_pointer	tmp = hint;

				while (tmp->left) {
					tmp = tmp->left;
				}
				return tmp;
			}

			const node_pointer	min(node_pointer hint) const {
				node_pointer	tmp = hint;

				while (tmp->left) {
					tmp = tmp->left;
				}
				return tmp;
			}

			node_pointer	max(node_pointer hint) {
				node_pointer	tmp = hint;

				while (tmp->right) {
					tmp = tmp->right;
				}
				return tmp;
			}

			const node_pointer	max(node_pointer hint) const {
				node_pointer	tmp = hint;

				while (tmp->right) {
					tmp = tmp->right;
				}
				return tmp;
			}
	};
};