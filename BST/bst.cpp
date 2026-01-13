#include "./include/bst.hpp"
#include "../include/test_suite.hpp"
#include <iostream>

class MainBST : public BST<MainBST> {
  public:
	using BST<MainBST>::BST;
};

int main() {
	TestSuite<std::string> suite;

	suite.addTest(
		"InOrder traversal of BST",
		[]() {
			MainBST tree(50);
			tree.insert(20);
			tree.insert(45);
			tree.insert(70);
			tree.insert(73);
			tree.insert(35);
			tree.insert(15);
			tree.insert(60);
			return tree.print_inorder();
		},
		"15 20 35 45 50 60 70 73 ");

	suite.run();

	std::cout << "bye\n";

	return 0;
}
