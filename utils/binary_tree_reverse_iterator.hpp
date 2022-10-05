namespace ft {
	template<class Iterator>
	class reverse_iterator {
	public:
		typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename ft::iterator_traits<Iterator>::reference			reference;
		typedef typename ft::iterator_traits<Iterator>::pointer				pointer;

		reverse_iterator(): _iterator(Iterator()) {}
		
		reverse_iterator(Iterator it): _iterator(it) {}

		template<class Iter> 
		reverse_iterator(const reverse_iterator<Iter> &other) {
			this->_iterator = other.getIterator();
		}

		reverse_iterator	&operator=(const reverse_iterator &src) {
			if (this != &src) {
				this->_iterator = src.getIterator();
			}
			return *this;
		}

		reference	operator*() const {
			Iterator tmp = this->_iterator;
			return *--tmp;
		}

		pointer		operator->() const { return (&(this->operator*())); }

		reference	operator[](difference_type index) const { return (*((this->_p + index)->data)); }

		reverse_iterator	&operator++() {
			this->_iterator--;
			return *this;
		}

		reverse_iterator	operator++(int) {reverse_iterator tmp(*this); operator++(); return (tmp); }

		reverse_iterator	&operator--() {
			this->_iterator++;
			return *this;
		}

		reverse_iterator	operator--(int) { reverse_iterator tmp(*this); operator--(); return (tmp); }

		bool	operator==(const reverse_iterator &a) const {
			return this->_iterator == a.base();
		}
		
		bool	operator!=(const reverse_iterator &a) const {
			return this->_iterator != a.base();
		}

		Iterator	getIterator() const {
			return _iterator;
		}

		Iterator base() const {
			return Iterator(_iterator);
		}

		private:
			Iterator	_iterator;
	};
};
