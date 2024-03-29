#pragma once

#include "./utils.hpp"
#include "./pair.hpp"

namespace ft {
	enum Color {
		RED,
		BLACK
	};

	template<class T>
	struct	s_node {
		T				value;

		struct s_node	*parent;
		struct s_node	*left;
		struct s_node	*right;

		enum Color		color;

		s_node(void): parent(NULL), left(NULL), right(NULL), color(RED) {}
		s_node(const T &value): value(value), parent(NULL), left(NULL), right(NULL), color(RED) {}

		s_node	&operator=(const s_node &node) {
			this->value = node.value;
			return *this;
		}

		s_node	*getUncle() {
			if (!this->parent || !this->parent->parent) {
				return NULL;
			}

			if (this->parent->parent->left == this->parent) {
				return this->parent->parent->right;
			} else {
				return this->parent->parent->left;
			}
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
			binary_tree(): _allocator(allocator_type()), _root(NULL), _compare(KeyCompare()) { }
			binary_tree(const compare_type &comp): _allocator(allocator_type()), _root(NULL), _compare(comp) { }

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

			~binary_tree(void) {
				
			}

			node_pointer	insert(const T &value) {
				node_pointer 	parent;
				node_pointer 	tmp = this->_root;
				node_pointer	to_insert = this->_allocator.allocate(1);

				this->_allocator.construct(to_insert, ft::s_node<T>(value));

				if (!this->_root) {
					this->_root = to_insert;
					this->_root->color = BLACK;
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

				this->insertFix(to_insert);

				return to_insert;
			}

			void	insertFix(node_pointer inserted) {
				node_pointer	uncle;

				while (inserted->parent->color == RED) {
					uncle = inserted->getUncle();

					if (inserted->parent == inserted->parent->parent->left) {
						if (uncle && uncle->color == RED) {
							this->switchColor(inserted);

							inserted = inserted->parent->parent;
						} else {
							if (inserted == inserted->parent->right) {
								inserted = inserted->parent;

								leftRotate(inserted);
							}

							inserted->parent->color = BLACK;
							inserted->parent->parent->color = RED;

							rightRotate(inserted->parent->parent);
						}
					} else {
						if (uncle && uncle->color == RED) {
							this->switchColor(inserted);

							inserted = inserted->parent->parent;
						} else {
							if (inserted == inserted->parent->left) {
								inserted = inserted->parent;

								this->rightRotate(inserted);
							}

							inserted->parent->color = BLACK;
							inserted->parent->parent->color = RED;

							this->leftRotate(inserted->parent->parent);
						}
					}

					if (inserted == this->_root) {
						break ;
					}
				}
				
				this->_root->color = BLACK;
			}

			void			delete_node(const T &value) {
				this->delete_node(this->find(value));
			}

			void			delete_node(node_pointer node) {
				node_pointer	parent = node->parent;
				node_pointer	child;

				if (!node->left && !node->right) {
					if (node != this->_root && node == node->parent->left) {
						node->parent->left = NULL;
					} else if (node != this->_root && node == node->parent->right) {
						node->parent->right = NULL;
					}
					if (node == this->_root) {
						this->_root = NULL;
					}
					this->_allocator.destroy(node);
					this->_allocator.deallocate(node, 1);
				} else if ((node->left && !node->right) || (node->right && !node->left)) {
					if (node->right) {
						child = node->right;
					} else {
						child = node->left;
					}
					if (node == this->_root) {
						this->_root = child;
					} else {
						if (node == parent->right) {
							parent->right = child;
						} else {
							parent->left = child;
						}
					}
					child->parent = parent;
					this->_allocator.destroy(node);
					this->_allocator.deallocate(node, 1);
				} else {
					child = this->bigger(node->left);

					swap(node, child);
					parent = child->parent;

					node = child;
					if (node->left) {
						if (node == node->parent->right) {
							node->parent->right = node->left;
						} else {
							node->parent->left = node->left;
						}
						node->left->parent = node->parent;
					} else {
						if (node->parent->left == node) {
							node->parent->left = NULL;
						} else {
							node->parent->right = NULL;
						}
					}
					this->_allocator.destroy(node);
					this->_allocator.deallocate(node, 1);
				}
				node = NULL;
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

			const_node_pointer	smallest(const_node_pointer node) const {
				const_node_pointer current = node;

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

			const_node_pointer	bigger(const_node_pointer node) {
				const_node_pointer current = node;

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

			void	leftRotate(node_pointer node) {
				node_pointer	y = node->right;

				if (y == NULL) {
					return ;
				}

				node->right = y->left;
				if (y->left != NULL) {
					y->left->parent = node;
				}
				y->parent = node->parent;
				if (node->parent == NULL) {
					this->_root = y;
				} else if (node == node->parent->left) {
					node->parent->left = y;
				} else {
					node->parent->right = y;
				}
				y->left = node;
				node->parent = y;
			}

			void	rightRotate(node_pointer node) {
				node_pointer	y = node->left;

				if (y == NULL) {
					return ;
				}

				node->left = y->right;
				if (y->right != NULL) {
					y->right->parent = node;
				}
				y->parent = node->parent;
				if (node->parent == NULL) {
					this->_root = y;
				} else if (node == node->parent->right) {
					node->parent->right = y;
				} else {
					node->parent->left = y;
				}
				y->right = node;
				node->parent = y;
			}

			void	switchColor(node_pointer node) {
				node_pointer uncle = node->getUncle();

				if (uncle) {
					uncle->color = BLACK;
				}

				node->parent->color = BLACK;
				node->parent->parent->color = RED;
			}
	};
};