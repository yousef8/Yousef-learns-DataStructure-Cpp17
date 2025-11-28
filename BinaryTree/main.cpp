#include "../include/test_suite.hpp"
#include "./include/binary_tree.hpp"

class MainBinaryTree : public BinaryTree<MainBinaryTree, int> {
  public:
	using BinaryTree<MainBinaryTree>::BinaryTree;
};

void testPreOrder() {
	std::cout << "\n========== Testing preOrder() ==========\n";
	TestSuite<std::string> suite;

	suite.addTest(
		"Single node",
		[]() {
			MainBinaryTree tree(1);
			return tree.preOrder();
		},
		"1 ");

	suite.addTest(
		"Left-only linear tree",
		[]() {
			MainBinaryTree tree(1);
			tree.add({2, 3, 4}, {'L', 'L', 'L'});
			return tree.preOrder();
		},
		"1 2 3 4 ");

	suite.addTest(
		"Right-only linear tree",
		[]() {
			MainBinaryTree tree(1);
			tree.add({2, 3, 4}, {'R', 'R', 'R'});
			return tree.preOrder();
		},
		"1 2 3 4 ");

	suite.addTest(
		"Complete binary tree",
		[]() {
			MainBinaryTree tree(1);
			tree.add({2, 4}, {'L', 'L'});
			tree.add({2, 5}, {'L', 'R'});
			tree.add({3, 6}, {'R', 'L'});
			tree.add({3, 7}, {'R', 'R'});
			return tree.preOrder();
		},
		"1 2 4 5 3 6 7 ");

	suite.addTest(
		"Left-skewed with right child",
		[]() {
			MainBinaryTree tree(1);
			tree.add({2, 3}, {'L', 'L'});
			tree.add({2, 4}, {'L', 'R'});
			return tree.preOrder();
		},
		"1 2 3 4 ");

	suite.addTest(
		"Complex unbalanced tree",
		[]() {
			MainBinaryTree tree(10);
			tree.add({5, 3, 1}, {'L', 'L', 'L'});
			tree.add({5, 7, 6}, {'L', 'R', 'L'});
			tree.add({15, 12}, {'R', 'L'});
			tree.add({15, 20}, {'R', 'R'});
			return tree.preOrder();
		},
		"10 5 3 1 7 6 15 12 20 ");

	suite.run();
}

void testInOrder() {
	std::cout << "\n========== Testing inOrder() ==========\n";
	TestSuite<std::string> suite;

	suite.addTest(
		"Single node",
		[]() {
			MainBinaryTree tree(1);
			return tree.inOrder();
		},
		"1 ");

	suite.addTest(
		"Left-only linear tree",
		[]() {
			MainBinaryTree tree(1);
			tree.add({2, 3, 4}, {'L', 'L', 'L'});
			return tree.inOrder();
		},
		"4 3 2 1 ");

	suite.addTest(
		"Right-only linear tree",
		[]() {
			MainBinaryTree tree(1);
			tree.add({2, 3, 4}, {'R', 'R', 'R'});
			return tree.inOrder();
		},
		"1 2 3 4 ");

	suite.addTest(
		"Complete binary tree",
		[]() {
			MainBinaryTree tree(1);
			tree.add({2, 4}, {'L', 'L'});
			tree.add({2, 5}, {'L', 'R'});
			tree.add({3, 6}, {'R', 'L'});
			tree.add({3, 7}, {'R', 'R'});
			return tree.inOrder();
		},
		"4 2 5 1 6 3 7 ");

	suite.addTest(
		"Left-skewed with right child",
		[]() {
			MainBinaryTree tree(1);
			tree.add({2, 3}, {'L', 'L'});
			tree.add({2, 4}, {'L', 'R'});
			return tree.inOrder();
		},
		"3 2 4 1 ");

	suite.addTest(
		"Complex unbalanced tree",
		[]() {
			MainBinaryTree tree(10);
			tree.add({5, 3, 1}, {'L', 'L', 'L'});
			tree.add({5, 7, 6}, {'L', 'R', 'L'});
			tree.add({15, 12}, {'R', 'L'});
			tree.add({15, 20}, {'R', 'R'});
			return tree.inOrder();
		},
		"1 3 5 6 7 10 12 15 20 ");

	suite.run();
}

void testPostOrder() {
	std::cout << "\n========== Testing postOrder() ==========\n";
	TestSuite<std::string> suite;

	suite.addTest(
		"Single node",
		[]() {
			MainBinaryTree tree(1);
			return tree.postOrder();
		},
		"1 ");

	suite.addTest(
		"Left-only linear tree",
		[]() {
			MainBinaryTree tree(1);
			tree.add({2, 3, 4}, {'L', 'L', 'L'});
			return tree.postOrder();
		},
		"4 3 2 1 ");

	suite.addTest(
		"Right-only linear tree",
		[]() {
			MainBinaryTree tree(1);
			tree.add({2, 3, 4}, {'R', 'R', 'R'});
			return tree.postOrder();
		},
		"4 3 2 1 ");

	suite.addTest(
		"Complete binary tree",
		[]() {
			MainBinaryTree tree(1);
			tree.add({2, 4}, {'L', 'L'});
			tree.add({2, 5}, {'L', 'R'});
			tree.add({3, 6}, {'R', 'L'});
			tree.add({3, 7}, {'R', 'R'});
			return tree.postOrder();
		},
		"4 5 2 6 7 3 1 ");

	suite.addTest(
		"Left-skewed with right child",
		[]() {
			MainBinaryTree tree(1);
			tree.add({2, 3}, {'L', 'L'});
			tree.add({2, 4}, {'L', 'R'});
			return tree.postOrder();
		},
		"3 4 2 1 ");

	suite.addTest(
		"Complex unbalanced tree",
		[]() {
			MainBinaryTree tree(10);
			tree.add({5, 3, 1}, {'L', 'L', 'L'});
			tree.add({5, 7, 6}, {'L', 'R', 'L'});
			tree.add({15, 12}, {'R', 'L'});
			tree.add({15, 20}, {'R', 'R'});
			return tree.postOrder();
		},
		"1 3 6 7 5 12 20 15 10 ");

	suite.run();
}

void testBreadthFirst() {
	std::cout << "\n========== Testing breadthFirst() ==========\n";
	TestSuite<std::string> suite;

	suite.addTest(
		"Single node",
		[]() {
			MainBinaryTree tree(1);
			return tree.breadthFirst();
		},
		"1");

	suite.addTest(
		"Left-only linear tree",
		[]() {
			MainBinaryTree tree(1);
			tree.add({2, 3, 4}, {'L', 'L', 'L'});
			return tree.breadthFirst();
		},
		"1 2 3 4");

	suite.addTest(
		"Right-only linear tree",
		[]() {
			MainBinaryTree tree(1);
			tree.add({2, 3, 4}, {'R', 'R', 'R'});
			return tree.breadthFirst();
		},
		"1 2 3 4");

	suite.addTest(
		"Complete binary tree",
		[]() {
			MainBinaryTree tree(1);
			tree.add({2, 4}, {'L', 'L'});
			tree.add({2, 5}, {'L', 'R'});
			tree.add({3, 6}, {'R', 'L'});
			tree.add({3, 7}, {'R', 'R'});
			return tree.breadthFirst();
		},
		"1 2 3 4 5 6 7");

	suite.addTest(
		"Left-skewed with right child",
		[]() {
			MainBinaryTree tree(1);
			tree.add({2, 3}, {'L', 'L'});
			tree.add({2, 4}, {'L', 'R'});
			return tree.breadthFirst();
		},
		"1 2 3 4");

	suite.addTest(
		"Complex unbalanced tree",
		[]() {
			MainBinaryTree tree(10);
			tree.add({5, 3, 1}, {'L', 'L', 'L'});
			tree.add({5, 7, 6}, {'L', 'R', 'L'});
			tree.add({15, 12}, {'R', 'L'});
			tree.add({15, 20}, {'R', 'R'});
			return tree.breadthFirst();
		},
		"10 5 15 3 7 12 20 1 6");

	suite.addTest(
		"Two-level tree with one child",
		[]() {
			MainBinaryTree tree(1);
			tree.add({2}, {'L'});
			return tree.breadthFirst();
		},
		"1 2");

	suite.addTest(
		"Two-level tree with both children",
		[]() {
			MainBinaryTree tree(1);
			tree.add({2}, {'L'});
			tree.add({3}, {'R'});
			return tree.breadthFirst();
		},
		"1 2 3");

	suite.run();
}

int main() {
	testPreOrder();
	testInOrder();
	testPostOrder();
	testBreadthFirst();

	return 0;
}
