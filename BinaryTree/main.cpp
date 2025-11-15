#include "./include/binary_tree.hpp"

int main() {
	BinaryTree tree(1);

	tree.add({2, 4, 7}, {'L', 'L', 'L'});
	tree.add({2, 4, 8}, {'L', 'L', 'R'});
	tree.add({2, 5, 9}, {'L', 'R', 'R'});
	tree.add({3, 6, 10}, {'R', 'R', 'L'});

	tree.printInOrder();
	// 7 4 8 2 5 9 1 3 10 6

	std::cout << std::endl;

	return 0;
}
