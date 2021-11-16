#include "./vector.hpp"
#include "./utils/iterator_traits.hpp"
#include <vector>

#define LEAKS 0

int	main() {
	{
		ft::vector<int>	vec;
		vec.push_back(1);
		vec.push_back(2);
		vec.push_back(3);
		vec.push_back(4);

		vec.erase(vec.begin(), vec.begin() + 2);

		for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++) {
			std::cout << *it << std::endl;
		}
		/*ft::vector<int>	vec;

		vec.push_back(1);
		vec.push_back(2);
		vec.push_back(3);
		vec.push_back(4);
		vec.push_back(5);

		ft::vector<int>::iterator	it = vec.begin();
		ft::vector<int>::iterator	ite = vec.end();

		while (it != ite) {
			std::cout << *it << std::endl;
			it++;
		}

		try {
			std::cout << vec.at(10) << std::endl;
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}

		std::cout << "size: " << vec.size() << std::endl;
		std::cout << "max_size: " << vec.max_size() << std::endl;
		std::cout << "capacity: " <<  vec.capacity() << std::endl;

		vec.pop_back();
		std::cout << "popped: " << vec[4] << std::endl;


		std::cout << "---- RESIZE ----" << std::endl;
		vec.resize(6, 10);
		for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++) {
			std::cout << *it << std::endl;
		}
		std::cout << "size: " << vec.size() << std::endl;
		std::cout << "---- RESIZE ----" << std::endl;

		std::cout << "---- ASSIGN ----" << std::endl;
		vec.assign(4, 15);
		for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++) {
			std::cout << *it << std::endl;
		}
		std::cout << "---- ASSIGN ----" << std::endl;

		std::cout << "---- CLEAR ----" << std::endl;
		vec.clear();
		for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++) {
			std::cout << *it << std::endl;
		}
		std::cout << "size: " << vec.size() << std::endl;
		std::cout << "---- CLEAR ----" << std::endl;
*/
	}
}