#pragma once

#include <iostream>
#include "./iterator_traits.hpp"
#include "./iterator.hpp"

namespace ft {
	template<typename T>
	class	VectorReverseIterator : public ft::s_iterator<std::random_access_iterator_tag, T> {
		private:
			T	*_p;
		public:
			typedef typename ft::s_iterator<std::random_access_iterator_tag, T>::pointer			pointer;
			typedef typename ft::s_iterator<std::random_access_iterator_tag, T>::reference			reference;
			typedef typename ft::s_iterator<std::random_access_iterator_tag, T>::difference_type	difference_type;
			typedef T*																				iterator_type;

			VectorReverseIterator(): _p(NULL) {}
			VectorReverseIterator(T *x): _p(x) {}
			VectorReverseIterator(const VectorIterator<T> it): _p(it.base()) {}
			VectorReverseIterator(const VectorReverseIterator<T> &copy): _p(copy._p) {}

			iterator_type	base() const { return (this->_p); }

			reference	operator*() const { return (*this->_p); }
			pointer		operator->() const { return (this->_p); }

			reference	operator[](difference_type index) const { return (*(_p + index)); }

			VectorReverseIterator	&operator++() { --_p; return (*this); }
			VectorReverseIterator	operator++(int) { VectorReverseIterator tmp(*this); operator--(); return (tmp); }
			VectorReverseIterator	&operator+=(difference_type n) { this->_p -= n; return (*this); }
			VectorReverseIterator	operator+(difference_type n) const { VectorReverseIterator tmp(*this); tmp._p -= n; return (tmp);}

			VectorReverseIterator	&operator--() { ++_p; return (*this); }
			VectorReverseIterator	operator--(int) { VectorReverseIterator tmp(*this); operator++(); return (tmp); }
			VectorReverseIterator	&operator-=(difference_type n) { this->_p += n; return (*this); }
			VectorReverseIterator	operator-(difference_type n) const { VectorReverseIterator tmp(*this); tmp._p += n; return (tmp);}
	};

	template<class Iterator1, class Iterator2>
	bool	operator==(const VectorReverseIterator<Iterator1>& lhs, const VectorReverseIterator<Iterator2>& rhs) {
		return lhs.base() == rhs.base();
	}

	template<class Iterator1, class Iterator2>
	bool	operator!=(const VectorReverseIterator<Iterator1>& lhs, const VectorReverseIterator<Iterator2>& rhs) {
		return lhs.base() != rhs.base();
	}

	template<class Iterator1, class Iterator2>
	bool	operator>(const VectorReverseIterator<Iterator1>& lhs, const VectorReverseIterator<Iterator2>& rhs) {
		return lhs.base() > rhs.base();
	}

	template<class Iterator1, class Iterator2>
	bool	operator>=(const VectorReverseIterator<Iterator1>& lhs, const VectorReverseIterator<Iterator2>& rhs) {
		return lhs.base() >= rhs.base();
	}

	template<class Iterator1, class Iterator2>
	bool	operator<(const VectorReverseIterator<Iterator1>& lhs, const VectorReverseIterator<Iterator2>& rhs) {
		return lhs.base() < rhs.base();
	}

	template<class Iterator1, class Iterator2>
	bool	operator<=(const VectorReverseIterator<Iterator1>& lhs, const VectorReverseIterator<Iterator2>& rhs) {
		return lhs.base() <= rhs.base();
	}

	template<class Iterator>
	VectorReverseIterator<Iterator> operator+(typename VectorReverseIterator<Iterator>::difference_type n, const VectorReverseIterator<Iterator> &it) {
		VectorReverseIterator<Iterator>	tmp(it.base() + n);
		return (tmp);
	}

	template<class Iterator>
	typename VectorReverseIterator<Iterator>::difference_type operator-(const VectorReverseIterator<Iterator>& lhs, const VectorReverseIterator<Iterator>& rhs) {
		return (lhs.base() - rhs.base());
	}
};