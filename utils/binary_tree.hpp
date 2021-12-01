#pragma once

#include "./utils.hpp"
#include "./pair.hpp"

namespace ft {
	template<class T1, class T2, class Allocator>
	class binary_tree {
		private:
			typedef struct	s_node {
				ft::pair<T1, T2>	data;
				struct s_node		*left;
				struct s_node		*right;

				s_node(ft::pair<T1, T2> data): data(data), left(NULL), right(NULL) {}
			}				t_node;

			typedef Allocator											allocator;
			typedef typename allocator::template rebind<t_node>::other	node_allocator;
			typedef typename node_allocator::pointer					node_pointer;
			typedef typename node_allocator::reference					node_reference;

			node_allocator	_allocator;
			node_pointer	_root;
			int				_size;
		public:
			binary_tree() {
				this->_root = this->_allocator.allocate(1);
				this->_allocator.construct(this->_root, t_node(ft::make_pair<T1, T2>(T1(), T2())));
				this->_size++;
			}

			binary_tree(t_node *node): _root(node), _size(0) {}

			virtual ~binary_tree() {
				this->_allocator.deallocate(this->_root, this->_size);
			}

			ft::pair<T1, T2>		*lookup(node_pointer node, const T1 &key) {
				if (node == NULL) {
					return (NULL);
				} else {
					if (key == node->data.first)
						return (&node->data);
					else {
						if (key < node->data.first)
							return (this->lookup(node->left, key));
						else
							return (this->lookup(node->right, key));
					}
				}
			}

			node_pointer	insert(node_pointer root, ft::pair<T1, T2> data) {
				if (root == NULL) {
					root = this->_allocator.allocate(1);
					this->_allocator.construct(root, t_node(data));
					this->_size++;
				} else {
					if (data.first <= root->data.first)
						root->left = this->insert(root->left, data);
					else
						root->right = this->insert(root->right, data);
					return (root);
				}
				return (root);
			}

			node_pointer	getRoot() const {
				return (this->_root);
			}

			t_node	*getNode(void *pointer) const {
				return (reinterpret_cast<t_node *>(pointer));
			}
	};
};