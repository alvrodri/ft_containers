#pragma once

#include <iostream>

namespace ft {
	template<class T>
	struct	is_integral { const static bool	value = false; };

	template<>
	struct	is_integral<bool> { const static bool	value = true; };

	template<>
	struct	is_integral<char> { const static bool	value = true; };

	template<>
	struct	is_integral<unsigned char> { const static bool	value = true; };

	template<>
	struct	is_integral<char16_t> { const static bool	value = true; };

	template<>
	struct	is_integral<char32_t> { const static bool	value = true; };

	template<>
	struct	is_integral<wchar_t> { const static bool	value = true; };

	template<>
	struct	is_integral<short> { const static bool	value = true; };

	template<>
	struct	is_integral<int> { const static bool	value = true; };

	template<>
	struct	is_integral<long> { const static bool	value = true; };

	template<>
	struct	is_integral<long long> { const static bool	value = true; };

	template<bool B, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> { typedef T type; };

	template<class InputIt1, class InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
		for (; first1 != last1; ++first1, ++first2) {
			if (!(*first1 == *first2)) {
				return false;
			}
		}
		return true;
	}
};