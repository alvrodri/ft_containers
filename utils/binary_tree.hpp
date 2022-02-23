#pragma once

#include "./utils.hpp"
#include "./pair.hpp"
#include "./binary_tree_iterator.hpp"

namespace ft {
	template<class T1, class T2, class Allocator>
	class binary_tree {
		private:
			typedef enum	e_color {
				RED,
				BLACK
			}				t_color;

			typedef struct	s_node {
				ft::pair<T1, T2>	data;
				struct s_node		*parent;
				struct s_node		*left;
				struct s_node		*right;
				t_color				color;

				s_node(ft::pair<T1, T2> data): data(data), parent(NULL), left(NULL), right(NULL), color(BLACK) {}
				s_node(ft::pair<T1, T2> data, t_color color): data(data), parent(NULL), left(NULL), right(NULL), color(color) {}
			}				t_node;

			typedef Allocator											allocator;
			typedef typename allocator::template rebind<t_node>::other	node_allocator;
			typedef typename node_allocator::pointer					node_pointer;
			typedef typename node_allocator::reference					node_reference;

			node_allocator	_allocator;
			node_pointer	_root;
			int				_size;
		public:
			typedef binary_tree_iterator<node_pointer, ft::pair<T1, T2> >		iterator;
			typedef binary_tree_iterator<const node_pointer, ft::pair<T1, T2> >	const_iterator;

			binary_tree(): _root(NULL), _size(0) {}

			binary_tree(t_node *node): _root(node), _size(0) {}

			binary_tree(ft::pair<T1, T2> pair): _size(1) {
				this->_root = this->_allocator.allocate(1);
				this->_allocator.construct(this->_root, t_node(pair));
			}

			virtual ~binary_tree() {
				this->_allocator.deallocate(this->_root, this->_size);
			}

			iterator		lookup(node_pointer node, const T1 &key) const {
				if (node == NULL) {
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

			iterator	insert(node_pointer	root, ft::pair<T1, T2> pair) {
				node_pointer	node = this->_allocator.allocate(1);
				this->_allocator.construct(node, t_node(pair));

				if (root == NULL) {
					this->_root = node;
					return (iterator(node, this->_root));
				}
				node_pointer	parent = root->parent, current = root;
				while (current != NULL) {
					parent = current;
					if (current->data.first <= pair.first) {
						current = current->right;
					} else {
						current = current->left;
					}
				}
				if (parent->data.first <= pair.first) {
					parent->right = node;
				} else {
					parent->left = node;
				}
				node->parent = parent;
				return (iterator(root, this->_root));
			}

			void	insert(ft::pair<T1, T2> pair) {
				this->insert(this->_root, pair);
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

			void print(const std::string& prefix, const t_node *node, bool isLeft) {
				if (node != NULL) {
					std::cout << prefix;
					std::cout << (isLeft ? "├──" : "└──" );
					std::cout << (node->color == RED ? "\033[31m" : "") << node->data.first << "\033[0m" << " (" << node->data.second << ")" << std::endl;
					print( prefix + (isLeft ? "│   " : "    "), node->left, true);
					print( prefix + (isLeft ? "│   " : "    "), node->right, false);
				}
			}

			void print(const t_node *node) {
				print("", node, false);
			}

			int	size() const {
				return (this->_size);
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