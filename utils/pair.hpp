#pragma once

namespace ft {
	template<class T1, class T2>
	struct pair {
		typedef T1	first_type;
		typedef T2	second_type;
		
		first_type	first;
		second_type	second;

		pair(): first(first_type()), second(second_type()) {}

		template<class U, class V>
		pair(const pair<U, V> &pr): first(pr.first), second(pr.second) {}

		pair(const first_type &a, const second_type &b): first(a), second(b) {}

		pair	&operator=(const pair &other) {
			this->first = other.first;
			this->second = other.second;

			return (*this);
		}
	};

	template<class T1, class T2>
	pair<T1, T2>	make_pair(T1 t, T2 u) {
		return (pair<T1, T2>(t, u));
	}

	template<class T1, class T2>
	bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template<class T1, class T2>
	bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return (!(lhs == rhs));
	}

	template<class T1, class T2>
	bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		if (lhs.first < rhs.first)
			return (true);
		if (rhs.first < lhs.first)
			return (false);
		if (lhs.second < rhs.second)
			return (true);
		if (rhs.second < lhs.second)
			return (false);
		return (false);
	}

	template<class T1, class T2>
	bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return (!(rhs < lhs));
	}

	template<class T1, class T2>
	bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return (rhs < lhs);
	}

	template<class T1, class T2>
	bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return (!(lhs < rhs));
	}
};