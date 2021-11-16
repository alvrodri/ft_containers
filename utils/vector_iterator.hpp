#pragma once

#include <iostream>
#include "./iterator_traits.hpp"
#include "./iterator.hpp"

namespace ft {
	template<typename T>
	class	VectorIterator : public ft::s_iterator<std::random_access_iterator_tag, T> {
		private:
			T	*_p;
		public:
			typedef typename ft::s_iterator<std::random_access_iterator_tag, T>::pointer			pointer;
			typedef typename ft::s_iterator<std::random_access_iterator_tag, T>::reference			reference;
			typedef typename ft::s_iterator<std::random_access_iterator_tag, T>::difference_type	difference_type;

			VectorIterator(): _p(NULL) {}
			VectorIterator(T *x): _p(x) {}
			VectorIterator(const VectorIterator &copy): _p(copy._p) {}

			pointer		base() const { return (this->_p); }

			reference	operator*() const { return (*this->_p); }
			pointer		operator->() const { return (this->_p); }

			reference	operator[](difference_type index) const { return (*(_p + index)); }

			VectorIterator	&operator++() { ++_p; return (*this); }
			VectorIterator	operator++(int) { VectorIterator tmp(*this); operator++(); return (tmp); }
			VectorIterator	&operator+=(difference_type n) { this->_p += n; return (*this); }
			VectorIterator	operator+(difference_type n) const { VectorIterator tmp(*this); tmp._p += n; return (tmp);}

			VectorIterator	&operator--() { --_p; return (*this); }
			VectorIterator	operator--(int) { VectorIterator tmp(*this); operator--(); return (tmp); }
			VectorIterator	&operator-=(difference_type n) { this->_p -= n; return (*this); }
			VectorIterator	operator-(difference_type n) const { VectorIterator tmp(*this); tmp._p -= n; return (tmp);}
	};

	template<class Iterator1, class Iterator2>
	bool	operator==(const VectorIterator<Iterator1>& lhs, const VectorIterator<Iterator2>& rhs) {
		return lhs.base() == rhs.base();
	}

	template<class Iterator1, class Iterator2>
	bool	operator!=(const VectorIterator<Iterator1>& lhs, const VectorIterator<Iterator2>& rhs) {
		return lhs.base() != rhs.base();
	}

	template<class Iterator1, class Iterator2>
	bool	operator>(const VectorIterator<Iterator1>& lhs, const VectorIterator<Iterator2>& rhs) {
		return lhs.base() > rhs.base();
	}

	template<class Iterator1, class Iterator2>
	bool	operator>=(const VectorIterator<Iterator1>& lhs, const VectorIterator<Iterator2>& rhs) {
		return lhs.base() >= rhs.base();
	}

	template<class Iterator1, class Iterator2>
	bool	operator<(const VectorIterator<Iterator1>& lhs, const VectorIterator<Iterator2>& rhs) {
		return lhs.base() < rhs.base();
	}

	template<class Iterator1, class Iterator2>
	bool	operator<=(const VectorIterator<Iterator1>& lhs, const VectorIterator<Iterator2>& rhs) {
		return lhs.base() <= rhs.base();
	}

	template<class Iterator>
	VectorIterator<Iterator> operator+(typename VectorIterator<Iterator>::difference_type n, const VectorIterator<Iterator> &it) {
		VectorIterator<Iterator>	tmp(it.base() + n);
		return (tmp);
	}

	template<class Iterator>
	typename VectorIterator<Iterator>::difference_type operator-(const VectorIterator<Iterator>& lhs, const VectorIterator<Iterator>& rhs) {
		return (lhs.base() - rhs.base());
	}
};