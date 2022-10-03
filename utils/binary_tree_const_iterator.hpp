#pragma once

#include "./binary_tree.hpp"
#include "./iterator_traits.hpp"
#include "./iterator.hpp"
#include "./pair.hpp"

namespace ft {
	template<typename T, typename ValueCompare, typename KeyCompare>
	class	binary_tree_const_iterator {
		public:
			typedef typename ft::s_iterator<std::bidirectional_iterator_tag, T>::iterator_category	iterator_category;
			typedef typename ft::s_iterator<std::bidirectional_iterator_tag, T>::value_type			value_type;
			typedef typename ft::s_iterator<std::bidirectional_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::s_iterator<std::bidirectional_iterator_tag, const T>::reference	reference;
			typedef typename ft::s_iterator<std::bidirectional_iterator_tag, const T>::pointer		pointer;
			typedef const typename ft::s_node<value_type>											*node_pointer;
			typedef const typename ft::binary_tree<value_type, ValueCompare, KeyCompare>			*tree_pointer;

			binary_tree_const_iterator(): _tree(NULL), _p(NULL) {}
			
			binary_tree_const_iterator(node_pointer node, tree_pointer tree): _tree(tree), _p(node) {}

			template<class A, class B, class C> 
			binary_tree_const_iterator(const binary_tree_const_iterator<A, B, C> &other) {
				this->_p = other.getPointer();
				this->_tree = other.getTree();
			}

			template<class A, class B, class C> 
			binary_tree_const_iterator(binary_tree_const_iterator<A, B, C> &other) {
				this->_p = other.getPointer();
				this->_tree = other.getTree();
			}

			reference	operator*() const { return (this->_p->value); }
			pointer		operator->() const { return (&(this->_p->value)); }

			reference	operator[](difference_type index) const { return (*((this->_p + index)->data)); }

			binary_tree_const_iterator	&operator++() {
				node_pointer	p = NULL;

				if (this->_p == NULL) {
					this->_p = this->_tree->_root;
					if (this->_p == NULL)
						return *this;
					this->_p = this->min(this->_p);
					return *this;
				}

				if (this->_p->right != NULL) {
					this->_p = this->_p->right;
					while (this->_p->left)
						this->_p = this->_p->left;
				} else {
					p = this->_p->parent;
					while (p != NULL && this->_p == p->right) {
						this->_p = p;
						p = p->parent;
					}
					this->_p = p;
				}
				return *this;
			}

			binary_tree_const_iterator	operator++(int) {binary_tree_const_iterator tmp(*this); operator++(); return (tmp); }

			binary_tree_const_iterator	&operator--() {
				node_pointer	p = NULL;

				if (this->_p == NULL) {
					this->_p = this->_tree->_root;
					if (this->_p == NULL)
						return *this; // arbol vacío
					this->_p = this->max(this->_p);
					return *this;
				}
				if (this->_p->left != NULL) {
					this->_p = this->_p->left;
					while (this->_p->right)
						this->_p = this->_p->right;
				} else {
					p = this->_p->parent;
					while (p != NULL && this->_p == p->left) {
						this->_p = p;
						p = p->parent;
					}
					this->_p = p;
				}
				return *this;
			}

			binary_tree_const_iterator	operator--(int) { binary_tree_const_iterator tmp(*this); operator--(); return (tmp); }

			node_pointer	min(node_pointer node) {
				node_pointer	ret = NULL;

				ret = node;
				while (ret->left)
					ret = ret->left;
				return ret;
			}

			node_pointer	max(node_pointer node) {
				node_pointer	ret;

				ret = node;
				while (ret->right)
					ret = ret->right;
				return ret;
			}

			bool	operator==(const binary_tree_const_iterator &a) const {
				return this->_p == a.getPointer();
			}
			
			bool	operator!=(const binary_tree_const_iterator &a) const {
				return this->_p != a.getPointer();
			}

			node_pointer	getPointer() const {
				return _p;
			}

			tree_pointer	getTree() const {
				return _tree;
			}
		private:
			tree_pointer	_tree;
			node_pointer	_p;
	};
};
