#pragma once

#include <iostream>
#include "./iterator_traits.hpp"
#include "./iterator.hpp"

namespace ft {
	template<typename T>
	class	VectorReverseIterator : public ft::s_iterator<std::random_access_iterator_tag, T> {
		public:
			typedef typename ft::s_iterator<std::random_access_iterator_tag, T>::pointer			pointer;
			typedef typename ft::s_iterator<std::random_access_iterator_tag, T>::reference			reference;
			typedef typename ft::s_iterator<std::random_access_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::VectorIterator<T>													iterator_type;

			VectorReverseIterator(): _iterator(NULL) {}
			VectorReverseIterator(T *x): _iterator(x) {}
			VectorReverseIterator(const VectorIterator<T> it): _iterator(it.base()) {}
			VectorReverseIterator(const VectorReverseIterator<T> &copy): _iterator(copy._iterator) {}

			iterator_type	base() const { return (this->_iterator); }

			reference	operator*() const { return (*this->_iterator); }
			pointer		operator->() const { return (&(*this->_iterator)); }

			reference	operator[](difference_type index) const { return (*(_iterator + index)); }

			VectorReverseIterator	&operator++() { --_iterator; return (*this); }
			VectorReverseIterator	operator++(int) { VectorReverseIterator tmp(*this); operator--(); return (tmp); }
			VectorReverseIterator	&operator+=(difference_type n) { this->_iterator -= n; return (*this); }
			VectorReverseIterator	operator+(difference_type n) const { VectorReverseIterator tmp(*this); tmp._iterator -= n; return (tmp);}

			VectorReverseIterator	&operator--() { ++_iterator; return (*this); }
			VectorReverseIterator	operator--(int) { VectorReverseIterator tmp(*this); operator++(); return (tmp); }
			VectorReverseIterator	&operator-=(difference_type n) { this->_iterator += n; return (*this); }
			VectorReverseIterator	operator-(difference_type n) const { VectorReverseIterator tmp(*this); tmp._iterator += n; return (tmp);}
			private:
				iterator_type	_iterator;
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