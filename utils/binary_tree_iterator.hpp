#pragma once

#include "./binary_tree.hpp"
#include "./iterator_traits.hpp"
#include "./iterator.hpp"

namespace ft {
	template<typename T>
	class	binary_tree_iterator : public ft::s_iterator<std::bidirectional_iterator_tag, T> {
		public:
			typedef typename ft::iterator_traits<T>				iterator_traits;
			typedef typename iterator_traits::pointer			pointer;
			typedef typename iterator_traits::reference			reference;
			typedef typename iterator_traits::difference_type	difference_type;
			typedef pointer										iterator_type;

			binary_tree_iterator(): _p(NULL) {}
			explicit binary_tree_iterator(iterator_type x, iterator_type root): _p(x), _root(root) {
				while (_p->left != NULL)
					_p = _p->left;
			}

			template<class U> 
			binary_tree_iterator(const binary_tree_iterator<U> &other) {
				this->_p = other.base();
				this->_root = other.getRoot();
			}

			iterator_type	base() const { return (this->_p); }

			reference	operator*() const { return (*this->_p); }
			pointer		operator->() const { return (this->_p); }

			reference	operator[](difference_type index) const { return (*(_p + index)); }

			binary_tree_iterator	&operator++() {
				iterator_type	p;

				if (this->_p == NULL) {
					this->_p = this->_root;
					if (this->_p == NULL)
						return *this; // arbol vacío
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

			binary_tree_iterator	operator++(int) {binary_tree_iterator tmp(*this); operator++(); return (tmp); }
			/*binary_tree_iterator	&operator+=(difference_type n) { this->_p += n; return (*this); }
			binary_tree_iterator	operator+(difference_type n) const { binary_tree_iterator tmp(*this); tmp._p += n; return (tmp);}*/

			binary_tree_iterator	&operator--() {
				iterator_type	p;

				if (this->_p == NULL) {
					this->_p = this->_root;
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

			
			binary_tree_iterator	operator--(int) { binary_tree_iterator tmp(*this); operator--(); return (tmp); }
			/*binary_tree_iterator	&operator-=(difference_type n) { this->_p -= n; return (*this); }
			binary_tree_iterator	operator-(difference_type n) const { binary_tree_iterator tmp(*this); tmp._p -= n; return (tmp);}*/

			iterator_type	min(iterator_type node) {
				iterator_type	ret;

				ret = node;
				while (ret->left)
					ret = ret->left;
				return ret;
			}

			iterator_type	max(iterator_type node) {
				iterator_type	ret;

				ret = node;
				while (ret->right)
					ret = ret->right;
				return ret;
			}
		private:
			iterator_type	_p;
			iterator_type	_root;
	};
};
