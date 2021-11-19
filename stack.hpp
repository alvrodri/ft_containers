#pragma once

#include "vector.hpp"

namespace ft {
	template<class T, class Container = ft::vector<T> >
	class stack {
		public:
			typedef Container									container_type;
			typedef typename container_type::value_type			value_type;
			typedef typename container_type::size_type			size_type;
			typedef typename container_type::reference			reference;
			typedef typename container_type::const_reference	const_reference;

			explicit	stack(const Container &cont = Container()) {
				this->_c = cont;
			}

			stack(const stack &other) {
				this->_c = other;
			}

			~stack() {
				
			}

			stack	&operator=(const stack &other) {
				this->_c = other._c;
				return (*this);
			}

			/* element access */
			reference	top() {
				return (this->_c.back());
			}

			const_reference	top() const {
				return (this->_c.back());
			}
			/* element access */

			/* capacity */
			bool	empty() const {
				return (this->_c.empty());
			}

			size_type	size() const {
				return (this->_c.size());
			}
			/* capacity */

			/* modifiers */
			void	push(const value_type &value) {
				this->_c.push_back(value);
			}

			void	pop() {
				this->_c.pop_back();
			}
			/* modifiers */

			/* non-member */
			friend bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
				return (lhs._c == rhs._c);
			}

			friend bool operator!=(const stack<T,Container> &lhs, const stack<T, Container> &rhs) {
				return (lhs._c != rhs._c);
			}

			friend bool operator<(const stack<T,Container> &lhs, const stack<T, Container> &rhs) {
				return (lhs._c < rhs._c);
			}

			friend bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
				return (lhs._c <= rhs._c);
			}

			friend bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
				return (lhs._c > rhs._c);
			}

			friend bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
				return (lhs._c >= rhs._c);
			}
			/* non-member */
		protected:
			container_type	_c;
	};
};