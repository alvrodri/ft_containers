#pragma once

#include <iostream>
#include "./utils/iterator_traits.hpp"
#include "./utils/iterator.hpp"
#include "./utils/vector_iterator.hpp"
#include "./utils/vector_reverse_iterator.hpp"
#include "./utils/utils.hpp"

namespace ft {
	template <class T, class Allocator = std::allocator<T> >
	class vector {
		public:
			typedef T											value_type;
			typedef Allocator									allocator_type;
			typedef	typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef	typename allocator_type::pointer			pointer;
			typedef	typename allocator_type::const_pointer		const_pointer;
			typedef	ptrdiff_t									difference_type;
			typedef	size_t										size_type;

			typedef VectorIterator<pointer>						iterator;
			typedef VectorIterator<const_pointer>				const_iterator;

			typedef VectorReverseIterator<iterator>				reverse_iterator;
			typedef VectorReverseIterator<const_iterator>		const_reverse_iterator;

			/* functions */
			vector(): _size(0), _capacity(1) {
				this->_pointer = this->_allocator.allocate(1);
			}

			explicit vector(const Allocator &alloc) {
				this->_allocator = alloc;
				this->_pointer = this->_allocator.allocate(1);
			}

			explicit vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator()) {
				this->_size = 0;
				this->_capacity = count;
				this->_allocator = alloc;
				this->_pointer = this->_allocator.allocate(this->_capacity);
				for (size_type i = 0; i < count; i++) {
					this->push_back(value);
				}
			}

			template<class InputIt >
			vector(InputIt first, InputIt last, const Allocator &alloc = Allocator(),
					typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type * = NULL) {
				this->_size = 0;
				this->_allocator = alloc;
				this->_capacity = 1;
				this->_pointer = this->_allocator.allocate(this->_capacity);
				while (first != last) {
					this->push_back(*first);
					first++;
				}
			}

			vector(const vector &other): _size(other._size), _capacity(other._capacity), _allocator(other._allocator) {
				this->_pointer = this->_allocator.allocate(this->_capacity);
				for (size_type i = 0; i < this->_size; i++)
					this->_allocator.construct(&this->_pointer[i], other[i]);
			}

			~vector() {
				this->_allocator.deallocate(this->_pointer, this->_capacity);
			}

			vector	&operator=(const vector &other) {
				this->clear();
				this->_allocator.deallocate(this->_pointer, this->_capacity);
				this->_size = other._size;
				this->_capacity = other._capacity;
				this->_pointer = this->_allocator.allocate(this->_capacity);
				for (size_type i = 0; i < other._size; i++) {
					this->_allocator.construct(&this->_pointer[i], other[i]);
				}
				return (*this);
			}

			void	assign(size_type count, const_reference value) {
				this->clear();
				for (size_type i = 0; i < count; i++) {
					this->push_back(value);
				}
			}

			template<class InputIt>
			void	assign(InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type * = NULL) {
				this->clear();
				while (first != last) {
					this->push_back(*first);
					first++;
				}
			}

			allocator_type	get_allocator() const {
				return (this->_allocator);
			}
			/* functions */

			/* element access */
			reference	at(size_type pos) {
				if (!(pos < this->size()) || pos < 0)
					throw (std::out_of_range("vector"));
				return (*(this->_pointer + pos));
			}

			const_reference	at(size_type pos) const {
				if (!(pos < this->size()) || pos < 0)
					throw (std::out_of_range("vector"));
				return (*(this->_pointer + pos));
			}

			reference	front() {
				return (*this->_pointer);
			}

			const_reference	front() const {
				return (*this->_pointer);
			}

			reference	back() {
				return (this->_pointer[this->_size - 1]);
			}

			const_reference	back() const {
				return (this->_pointer[this->_size - 1]);
			}

			reference	operator[](size_type pos) {
				return this->_pointer[pos];
			}

			const_reference	operator[](size_type pos) const {
				return this->_pointer[pos];
			}
			/* element access */

			/* capacity */
			bool	empty() const {
				return (this->_size == 0);
			}

			size_type	size() const {
				return (this->_size);
			}

			size_type	max_size() const {
				return (this->_allocator.max_size());
			}

			void	reserve(size_type new_cap) {
				pointer	tmp;
				
				if (new_cap <= this->_capacity)
					return ;
				tmp = this->_pointer;
				this->_pointer = this->_allocator.allocate(new_cap);
				for (size_type i = 0; i < this->_size; i++) {
					this->_allocator.construct(this->_pointer + i, *(tmp + i));
				}
				this->_capacity = new_cap;
			}

			size_type	capacity() const {
				return (this->_capacity);
			}
			/* capacity */

			/* modifiers */
			void	clear() {
				while (this->_size > 0) {
					this->pop_back();
				}
			}

			iterator	insert(iterator pos, const_reference value) {
				vector		tmp;
				iterator	ret;
				iterator	it = this->begin();

				for (; it != pos; it++) {
					tmp.push_back(*it);
				}
				tmp.push_back(value);
				ret = tmp.end() - 1;
				for (; it != this->end(); it++) {
					tmp.push_back(*it);
				}
				this->swap(tmp);
				return (ret);
			}

			void	insert(iterator pos, size_type count, const_reference value) {
				vector		tmp;
				iterator	it = this->begin();

				for (; it != pos; it++) {
					tmp.push_back(*it);
				}
				for (size_type i = 0; i < count; i++) {
					tmp.push_back(value);
				}
				for (; it != this->end(); it++) {
					tmp.push_back(*it);
				}
				this->swap(tmp);
			}

			template<class InputIt>
			void	insert(iterator pos, InputIt first, InputIt last,
					typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type * = NULL) {
				vector		tmp;
				iterator	it = this->begin();

				for (; it != pos; it++) {
					tmp.push_back(*it);
				}
				while (first != last) {
					tmp.push_back(*first);
					first++;
				}
				for (; it != this->end(); it++) {
					tmp.push_back(*it);
				}
				this->swap(tmp);
			}

			iterator	erase(iterator pos) {
				if (pos != this->end()) {
					iterator	ret;

					ret = iterator(&(*pos));
					for (iterator it = pos; it != this->end() - 1; it++) {
						this->_allocator.construct(&(*it), *(&(*it) + 1));
						this->_allocator.destroy(&(*it) + 1);
					}
					this->_size--;
					return (ret);
				}
				return (this->end());
			}

			iterator	erase(iterator first, iterator last) {
				size_type	i = 0;
				size_type	diff = last - first;

				while (i < diff) {
					this->erase(first);
					i++;
				}
				return (first);
			}

			void	push_back(const const_reference &val) {
				pointer	tmp;

				if (this->_size + 1 > this->_capacity) {
					tmp = this->_pointer;
					this->_capacity *= 2;
					this->_pointer = this->_allocator.allocate(this->_capacity);
					for (size_type i = 0; i < this->_size; i++) {
						this->_allocator.construct(this->_pointer + i, *(tmp + i));
					}
					this->_allocator.construct(this->_pointer + this->_size, val);
					this->_allocator.deallocate(tmp, this->_capacity / 2);
				} else {
					this->_allocator.construct(this->_pointer + this->_size, val);
				}
				this->_size++;
			}

			void	pop_back() {
				if (this->_size)
					this->_allocator.destroy(&this->_pointer[--this->_size]);
			}

			void	resize(size_type count, T value = T()) {
				pointer	tmp;

				if (this->_size > count) {
					tmp = this->_pointer;
					this->_pointer = this->_allocator.allocate(count);
					for (size_type i = 0; i < count; i++) {
						this->_allocator.construct(this->_pointer + i, *(tmp + i));
					}
					this->_allocator.deallocate(tmp, this->_capacity);
					this->_capacity = count;
					this->_size = count;
				} else {
					tmp = this->_pointer;
					this->_pointer = this->_allocator.allocate(count);
					for (size_type i = 0; i < this->_size; i++) {
						this->_allocator.construct(this->_pointer + i, *(tmp + i));
					}
					for (size_type i = this->_size; i < count; i++) {
						this->_allocator.construct(this->_pointer + i, value);
					}
					this->_allocator.deallocate(tmp, this->_capacity);
					this->_size = count;
					this->_capacity = count;
				}
			}

			void	swap(vector &other) {
				ft_swap(this->_size, other._size);
				ft_swap(this->_capacity, other._capacity);
				ft_swap(this->_allocator, other._allocator);
				ft_swap(this->_pointer, other._pointer);
			}
			/* modifiers */

			/* iterators */
			iterator	begin() {
				return (iterator(&this->_pointer[0]));
			}

			const_iterator	begin() const {
				return (const_iterator(&this->_pointer[0]));
			}

			iterator	end() {
				return (iterator(&this->_pointer[this->_size]));
			}

			const_iterator	end() const {
				return (const_iterator(&this->_pointer[this->_size]));
			}

			reverse_iterator	rbegin() {
				return (reverse_iterator(this->end() - 1));
			}

			const_reverse_iterator	rbegin() const {
				return (const_reverse_iterator(this->end() - 1));
			}

			reverse_iterator	rend() {
				return (reverse_iterator(this->begin() - 1));
			}

			const_reverse_iterator	rend() const {
				return (const_reverse_iterator(this->begin() - 1));
			}
			/* iterators */
		private:
			size_type		_size;
			size_type		_capacity;
			allocator_type	_allocator;
			pointer			_pointer;

			template<typename K>
			void	ft_swap(K &a, K &b) {
				K	tmp;

				tmp = a;
				a = b;
				b = tmp;
			}
	};

	template<class T, class Alloc>
	bool operator==(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return (false);
		for (typename ft::vector<T>::size_type i = 0; i < lhs.size(); i++) {
			if (lhs[i] != rhs[i])
				return (false);
		}
		return (true);
	}

	template<class T, class Alloc>
	bool operator!=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs) {
		return (!(lhs == rhs));
	}

	template<class T, class Alloc>
	bool operator<(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs) {
		return (std::lexicographical_compare(lhs.begin().base(), lhs.end().base(), rhs.begin().base(), rhs.end().base()));
	}

	template<class T, class Alloc>
	bool operator<=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs) {
		return (!(rhs < lhs));
	}

	template<class T, class Alloc>
	bool operator>(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs) {
		return (rhs < lhs);
	}

	template<class T, class Alloc>
	bool operator>=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs) {
		return (!(lhs < rhs));
	}
};