#include "./stack.hpp"
#include "./utils/iterator_traits.hpp"
#include "./utils/pair.hpp"
#include "./utils/binary_tree.hpp"
#include "./utils/binary_tree_iterator.hpp"
#include <vector>
#include <map>
#include "./map.hpp"

int	main() {
	ft::map<std::string, int>	persons;

	persons.insert(ft::make_pair("Álvaro", 20));
	std::cout << persons.begin()->first << std::endl;
}