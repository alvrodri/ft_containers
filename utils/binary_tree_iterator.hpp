#pragma once

#include "./binary_tree.hpp"
#include "./iterator_traits.hpp"
#include "./iterator.hpp"
#include "./pair.hpp"

namespace ft {
	template<typename T, typename Pair>
	class	binary_tree_iterator : public ft::s_iterator<std::bidirectional_iterator_tag, T> {
		public:
			typedef T				iterator_type;
			typedef Pair			value_type;
			typedef value_type*		pointer;
			typedef value_type&		reference;
			typedef ptrdiff_t		difference_type;

			binary_tree_iterator(): _p(NULL), _root(NULL) {}
			explicit binary_tree_iterator(iterator_type x, iterator_type root): _p(x), _root(root) {
			}

			template<class U, class U2> 
			binary_tree_iterator(const binary_tree_iterator<U, U2> &other): _p(other.getCurrent()), _root(other.getRoot()) {
			}

			T			getCurrent() const { return this->_p;}
			T			getRoot() const { return this->_root; }

			reference	operator*() const { return (this->_p->data); }
			pointer		operator->() const { return (&(this->_p->data)); }

			reference	operator[](difference_type index) const { return (*((this->_p + index)->data)); }

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

	template<class A, class B, class P1, class P2>
	bool	operator==(const binary_tree_iterator<A, P1>& lhs, const binary_tree_iterator<B, P2>& rhs) {
		return lhs.getCurrent() == rhs.getCurrent();
	}

	template<class A, class B, class P1, class P2>
	bool	operator!=(const binary_tree_iterator<A, P1>& lhs, const binary_tree_iterator<B, P2>& rhs) {
		return lhs.getCurrent() != rhs.getCurrent();
	}
};
