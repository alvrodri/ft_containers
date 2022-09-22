#include "./stack.hpp"
#include "./utils/iterator_traits.hpp"
#include "./utils/pair.hpp"
#include "./utils/binary_tree.hpp"
#include "./utils/binary_tree_iterator.hpp"
#include <vector>
#include <map>
#include "./vector.hpp"

int	main() {
	typedef ft::pair<int, int>	value_type;

	ft::binary_tree<value_type, std::less<value_type> >	tree;

	tree.insert(ft::make_pair(8, 0));
	tree.insert(ft::make_pair(3, 0));
	tree.insert(ft::make_pair(1, 0));
	tree.insert(ft::make_pair(6, 0));
	tree.insert(ft::make_pair(7, 0));
	tree.insert(ft::make_pair(10, 0));
	tree.insert(ft::make_pair(14, 0));
	tree.insert(ft::make_pair(4, 0));

	tree.inorder(tree._root);

	tree.delete_node(ft::make_pair(3, 0));
	std::cout << "\n" << std::endl;

	tree.inorder(tree._root);
}