#include "./stack.hpp"
#include "./utils/iterator_traits.hpp"
#include "./utils/pair.hpp"
#include "./utils/binary_tree.hpp"
#include "./utils/binary_tree_iterator.hpp"
#include <vector>
#include <map>
#include "./map.hpp"

int	main() {
	/*ft::map<int, int>	persons;

	persons.insert(ft::make_pair(10, 10));
	persons.insert(ft::make_pair(11, 5));
	persons.insert(ft::make_pair(12, 4));
	persons.insert(ft::make_pair(13, 3));

	persons.erase(++persons.begin());

	for (ft::map<int, int>::iterator it = persons.begin(); it != persons.end(); it++) {
		std::cout << "(" << it->first << ", " << it->second << ")" << std::endl;
	}*/
	ft::binary_tree<int, int, std::allocator<ft::pair<int, int> > >	tree;

	tree.insert()
}