#pragma once

#include <iostream>

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

			typedef typename allocator_type::pointer			iterator;
			typedef typename allocator_type::const_pointer		const_iterator;

			/* functions */
			vector(): _size(0), _capacity(0),  _start(NULL), _end(NULL) { }

			vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator()) {
				this->_allocator = alloc;
				for (size_type i = 0; i < count; i++) {
					this->push_back(value);
				}
			}

			~vector() {
				for (iterator it = this->begin(); it != this->end(); it++) {
					this->_allocator.destroy(it);
				}
			}

			vector	&operator=(const vector &other) {
				this->_size = other._size;
				this->_capacity = other._capacity;
				this->_allocator = other._allocator;
				this->_start = other._start;
				this->_end = other._end;

				iterator	newit = this->begin();
				for (iterator it = other.begin(); it != other.end(); it++) {
					*newit = *it;
					newit++;
				}
				return (*this);
			}

			void	assign(size_type count, const_reference value) {
				if (count > this->_capacity)
					return ;
				for (size_type i = 0; i < count; i++) {
					this->_start[i] = value;
				}
				this->_end = this->_start + count;
			}

			allocator_type	get_allocator() const {
				retuern (this->_allocator);
			}
			/* functions */

			/* element access */
			reference	at(size_type pos) {
				if (!(pos < this->size()) || pos < 0)
					throw (std::out_of_range("vector"));
				return (*(this->_start + pos));
			}

			const_reference	at(size_type pos) const {
				if (!(pos < this->size()) || pos < 0)
					throw (std::out_of_range("vector"));
				return (*(this->_start + pos));
			}

			reference	front() {
				return (*this->_start);
			}

			const_reference	front() const {
				return (*this->_start);
			}

			reference	back() {
				return (*this->_end);
			}

			const_reference	back() const {
				return (*this->_end);
			}

			reference	operator[](size_type pos) {
				return this->_start[pos];
			}

			const_reference	operator[](size_type pos) const {
				return this->_start[pos];
			}
			/* element access */

			/* capacity */
			bool	empty() {
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
				tmp = this->_start;
				this->_start = this->_allocator.allocate(new_cap);
				for (size_type i = 0; i < this->_size; i++) {
					this->_allocator.construct(this->_start + i, *(tmp + i));
				}
				this->_end = this->_start + this->_size - 1;
				this->_capacity = new_cap;
			}

			size_type	capacity() const {
				return (this->_capacity);
			}
			/* capacity */

			/* modifiers */
			void	clear() {
				for (iterator it = this->begin(); it != this->end(); it++) {
					*it = 0;
				}
				this->_size = 0;
				this->_end = this->_start;
			}

			iterator	insert(iterator pos, const_reference value) {
				//iterator	dealloc = this->begin();
				iterator	it = this->begin();
				iterator	ite = this->end();
				this->_capacity *= 2;
				this->_size++;
				this->_start = this->_allocator.allocate(this->_capacity);
				this->_end = this->_start + this->_size;
				iterator	begin = this->begin();
				while (it != pos) {
					*begin = *it;
					begin++;
					it++;
				}
				*begin = value;
				iterator	tmp;
				iterator	end = this->end() - 1;
				while (ite != pos) {
					tmp = ite - 1;
					*end = *tmp;
					end--;
					ite--;
				}
				return begin;
			}

			void	insert(iterator pos, size_type count, const_reference value) {
				for (size_type i = 0; i < count; i++) {
					pos = this->insert(pos, value);
				}
			}

			void	insert(iterator pos, iterator first, iterator last) {
				while (first != last) {
					pos = this->insert(pos, *first);
					pos++;
					first++;
				}
			}

			void	push_back(const const_reference &val) {
				pointer	tmp;

				if (this->_start == NULL) {
					this->_start = this->_allocator.allocate(1);
					this->_end = this->_start + 1;
					this->_allocator.construct(this->_start, val);
					this->_size = 1;
					this->_capacity = 1;
				} else {
					if (this->_size + 1 > this->_capacity) {
						tmp = this->_start;
						this->_capacity *= 2;
						this->_start = this->_allocator.allocate(this->_capacity);
						for (size_type i = 0; i < this->_size; i++) {
							this->_allocator.construct(this->_start + i, *(tmp + i));
						}
						this->_allocator.construct(this->_start + this->_size, val);
						this->_allocator.deallocate(tmp, this->_capacity / 2);
						this->_end = this->_start + this->_size;
						this->_size++;
					} else {
						this->_allocator.construct(this->_start + this->_size, val);
						this->_end = this->_start + this->_size;
						this->_size++;
					}
				}
				this->_end++;
			}

			void	pop_back() {
				this->_size--;
			}

			void	resize(size_type count, T value = T()) {
				pointer	tmp;

				if (this->_size > count) {
					tmp = this->_start;
					this->_start = this->_allocator.allocate(count);
					for (size_type i = 0; i < count; i++) {
						this->_allocator.construct(this->_start + i, *(tmp + i));
					}
					this->_allocator.deallocate(tmp, this->_capacity);
					this->_end = this->_start + count;
					this->_capacity = count;
					this->_size = count;
				} else {
					tmp = this->_start;
					this->_start = this->_allocator.allocate(count);
					for (size_type i = 0; i < this->_size; i++) {
						this->_allocator.construct(this->_start + i, *(tmp + i));
					}
					for (size_type i = this->_size; i < count; i++) {
						this->_allocator.construct(this->_start + i, value);
					}
					this->_allocator.deallocate(tmp, this->_capacity);
					this->_end = this->_start + count;
					this->_size = count;
					this->_capacity = count;
				}
			}
			/* modifiers */

			/* iterators */
			iterator	begin() {
				return (this->_start);
			}

			const_iterator	begin() const {
				return (this->_start);
			}

			iterator	end() {
				return (this->_end);
			}

			const_iterator	end() const {
				return (this->end);
			}
			/* iterators */
		private:
			size_type		_size;
			size_type		_capacity;
			allocator_type	_allocator;
			pointer			_start;
			pointer			_end;
	};
};