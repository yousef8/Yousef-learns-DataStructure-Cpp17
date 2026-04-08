#include "./include/bst_cnc.hpp"
#include <iostream>
#include <string>

int main() {
	auto root = BST();
	root.insert(10);
	root.insert(5);
	root.insert(15);
	root.insert(3);
	root.insert(7);
	root.insert(12);
	root.insert(20);

	std::cout << "        10\n";
	std::cout << "       /  \\\n";
	std::cout << "      5    15\n";
	std::cout << "     / \\   / \\\n";
	std::cout << "    3   7 12  20\n\n";
	std::cout << "In-order: " << root.inorder_traversal() << "\n";
	std::cout << "Level-order: " << root.level_order_traversal() << "\n";

	std::cout << "Minimum value: " << root.min() << "\n";

	std::cout << "Search for 7: " << (root.search(7) ? "Found" : "Not Found")
			  << "\n";

	std::cout << "Removing leaf node 20...\n";
	root.remove(20);
	std::cout << "In-order after deletion: " << root.inorder_traversal()
			  << "\n";
	std::cout << "Level-order after deletion: " << root.level_order_traversal()
			  << "\n";

	std::cout << "Removing node with one child 15...\n";
	root.remove(15);
	std::cout << "In-order after deletion: " << root.inorder_traversal()
			  << "\n";
	std::cout << "Level-order after deletion: " << root.level_order_traversal()
			  << "\n";

	std::cout << "Removing node with 2 children 5...\n";
	root.remove(5);
	std::cout << "In-order after deletion: " << root.inorder_traversal()
			  << "\n";
	std::cout << "Level-order after deletion: " << root.level_order_traversal()
			  << "\n";

	return 0;
}