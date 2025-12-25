#include "../../include/test_suite.hpp"
#include "../include/binary_tree.hpp"
#include <deque>
#include <utility>

class FullTreeFromPreorder : public BinaryTree<FullTreeFromPreorder> {
  public:
	using BinaryTree<FullTreeFromPreorder>::BinaryTree;

	FullTreeFromPreorder(const std::deque<std::pair<int, int>> &preOrder)
		: BinaryTree<FullTreeFromPreorder>(0) {
		int idx{0};
		buildTree(preOrder, idx);
	}

  private:
	void buildTree(const std::deque<std::pair<int, int>> &preOrder, int &idx) {
		auto [val, isLeaf] = preOrder[idx];

		this->data = val;

		if (isLeaf) {
			return;
		}

		this->left = new FullTreeFromPreorder(0);
		this->left->buildTree(preOrder, ++idx);

		this->right = new FullTreeFromPreorder(0);
		this->right->buildTree(preOrder, ++idx);
	}
};

int main() {
	TestSuite<std::string> suite;

	suite.addTest(
		"Single node leaf",
		[]() {
			std::deque<std::pair<int, int>> preOrder = {{1, 1}};
			FullTreeFromPreorder tree(preOrder);
			return tree.preOrder();
		},
		"1 ");

	suite.addTest(
		"Root with two leaf children",
		[]() {
			std::deque<std::pair<int, int>> preOrder = {
				{1, 0}, // root, non-leaf
				{2, 1}, // left child, leaf
				{3, 1}	// right child, leaf
			};
			FullTreeFromPreorder tree(preOrder);
			return tree.preOrder();
		},
		"1 2 3 ");

	suite.addTest(
		"Multi-level tree with mixed leaves",
		[]() {
			std::deque<std::pair<int, int>> preOrder = {
				{1, 0}, // root, non-leaf
				{2, 0}, // left child of 1, non-leaf
				{4, 1}, // left child of 2, leaf
				{5, 1}, // right child of 2, leaf
				{3, 0}, // right child of 1, non-leaf
				{6, 1}, // left child of 3, leaf
				{7, 1}	// right child of 3, leaf
			};
			FullTreeFromPreorder tree(preOrder);
			return tree.preOrder();
		},
		"1 2 4 5 3 6 7 ");

	suite.addTest(
		"Inorder traversal verification",
		[]() {
			std::deque<std::pair<int, int>> preOrder = {
				{1, 0}, // root, non-leaf
				{2, 0}, // left child of 1, non-leaf
				{4, 1}, // left child of 2, leaf
				{5, 1}, // right child of 2, leaf
				{3, 0}, // right child of 1, non-leaf
				{6, 1}, // left child of 3, leaf
				{7, 1}	// right child of 3, leaf
			};
			FullTreeFromPreorder tree(preOrder);
			return tree.inOrder();
		},
		"4 2 5 1 6 3 7 ");

	suite.addTest(
		"Deep tree with multiple levels",
		[]() {
			std::deque<std::pair<int, int>> preOrder = {
				{1, 0}, // root
				{2, 0}, // left of 1
				{4, 0}, // left of 2
				{8, 1}, // left of 4
				{9, 1}, // right of 4
				{5, 1}, // right of 2
				{3, 0}, // right of 1
				{6, 1}, // left of 3
				{7, 1}	// right of 3
			};
			FullTreeFromPreorder tree(preOrder);
			return tree.preOrder();
		},
		"1 2 4 8 9 5 3 6 7 ");

	suite.addTest(
		"Breadth first single node",
		[]() {
			std::deque<std::pair<int, int>> preOrder = {{42, 1}};
			FullTreeFromPreorder tree(preOrder);
			return tree.breadthFirst();
		},
		"42");

	suite.addTest(
		"Breadth first multi-level tree",
		[]() {
			std::deque<std::pair<int, int>> preOrder = {
				{1, 0}, // root
				{2, 0}, // left of 1
				{4, 1}, // left of 2
				{5, 1}, // right of 2
				{3, 0}, // right of 1
				{6, 1}, // left of 3
				{7, 1}	// right of 3
			};
			FullTreeFromPreorder tree(preOrder);
			return tree.breadthFirst();
		},
		"1 2 3 4 5 6 7");

	suite.addTest(
		"Postorder traversal",
		[]() {
			std::deque<std::pair<int, int>> preOrder = {
				{1, 0}, // root
				{2, 0}, // left of 1
				{4, 1}, // left of 2
				{5, 1}, // right of 2
				{3, 0}, // right of 1
				{6, 1}, // left of 3
				{7, 1}	// right of 3
			};
			FullTreeFromPreorder tree(preOrder);
			return tree.postOrder();
		},
		"4 5 2 6 7 3 1 ");

	suite.run();
	return 0;
}
