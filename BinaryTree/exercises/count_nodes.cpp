#include "../../include/test_suite.hpp"
#include "../include/binary_tree.hpp"

class NodesCountBT : public BinaryTree<NodesCountBT> {
  public:
	using BinaryTree<NodesCountBT>::BinaryTree;

	int countNodes() const {
		int count{1};

		if (left)
			count += left->countNodes();

		if (right)
			count += right->countNodes();

		return count;
	}
};

int main() {
	TestSuite<int> suite;

	suite.addTest(
		"Single node tree",
		[]() {
			NodesCountBT root(1);
			return root.countNodes();
		},
		1);

	suite.addTest(
		"Two nodes - left child",
		[]() {
			NodesCountBT root(1);
			root.add({2}, {'L'});
			return root.countNodes();
		},
		2);

	suite.addTest(
		"Two nodes - right child",
		[]() {
			NodesCountBT root(1);
			root.add({2}, {'R'});
			return root.countNodes();
		},
		2);

	suite.addTest(
		"Three nodes - both children",
		[]() {
			NodesCountBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			return root.countNodes();
		},
		3);

	suite.addTest(
		"Left-skewed tree",
		[]() {
			NodesCountBT root(1);
			root.add({2}, {'L'});
			root.add({2, 3}, {'L', 'L'});
			root.add({2, 3, 4}, {'L', 'L', 'L'});
			return root.countNodes();
		},
		4);

	suite.addTest(
		"Right-skewed tree",
		[]() {
			NodesCountBT root(1);
			root.add({2}, {'R'});
			root.add({2, 3}, {'R', 'R'});
			root.add({2, 3, 4}, {'R', 'R', 'R'});
			root.add({2, 3, 4, 5}, {'R', 'R', 'R', 'R'});
			return root.countNodes();
		},
		5);

	suite.addTest(
		"Complete binary tree (7 nodes)",
		[]() {
			NodesCountBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 4}, {'L', 'L'});
			root.add({2, 5}, {'L', 'R'});
			root.add({3, 6}, {'R', 'L'});
			root.add({3, 7}, {'R', 'R'});
			return root.countNodes();
		},
		7);

	suite.addTest(
		"Large balanced tree (15 nodes)",
		[]() {
			NodesCountBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 4}, {'L', 'L'});
			root.add({2, 5}, {'L', 'R'});
			root.add({3, 6}, {'R', 'L'});
			root.add({3, 7}, {'R', 'R'});
			root.add({2, 4, 8}, {'L', 'L', 'L'});
			root.add({2, 4, 9}, {'L', 'L', 'R'});
			root.add({2, 5, 10}, {'L', 'R', 'L'});
			root.add({2, 5, 11}, {'L', 'R', 'R'});
			root.add({3, 6, 12}, {'R', 'L', 'L'});
			root.add({3, 6, 13}, {'R', 'L', 'R'});
			root.add({3, 7, 14}, {'R', 'R', 'L'});
			root.add({3, 7, 15}, {'R', 'R', 'R'});
			return root.countNodes();
		},
		15);

	suite.addTest(
		"Unbalanced tree - left heavy",
		[]() {
			NodesCountBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 4}, {'L', 'L'});
			root.add({2, 5}, {'L', 'R'});
			root.add({2, 4, 6}, {'L', 'L', 'L'});
			root.add({2, 4, 7}, {'L', 'L', 'R'});
			return root.countNodes();
		},
		7);

	suite.addTest(
		"Unbalanced tree - right heavy",
		[]() {
			NodesCountBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({3, 6}, {'R', 'L'});
			root.add({3, 7}, {'R', 'R'});
			root.add({3, 7, 8}, {'R', 'R', 'L'});
			root.add({3, 7, 9}, {'R', 'R', 'R'});
			return root.countNodes();
		},
		7);

	suite.addTest(
		"Sparse tree with gaps",
		[]() {
			NodesCountBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 4}, {'L', 'L'});
			root.add({3, 7}, {'R', 'R'});
			return root.countNodes();
		},
		5);

	suite.addTest(
		"Only left subtree",
		[]() {
			NodesCountBT root(1);
			root.add({2}, {'L'});
			root.add({2, 4}, {'L', 'L'});
			root.add({2, 5}, {'L', 'R'});
			root.add({2, 5, 10}, {'L', 'R', 'L'});
			return root.countNodes();
		},
		5);

	suite.addTest(
		"Only right subtree",
		[]() {
			NodesCountBT root(1);
			root.add({3}, {'R'});
			root.add({3, 6}, {'R', 'L'});
			root.add({3, 7}, {'R', 'R'});
			root.add({3, 7, 14}, {'R', 'R', 'L'});
			return root.countNodes();
		},
		5);

	suite.addTest(
		"Zigzag pattern",
		[]() {
			NodesCountBT root(1);
			root.add({2}, {'L'});
			root.add({2, 3}, {'L', 'R'});
			root.add({2, 3, 4}, {'L', 'R', 'L'});
			root.add({2, 3, 4, 5}, {'L', 'R', 'L', 'R'});
			root.add({2, 3, 4, 5, 6}, {'L', 'R', 'L', 'R', 'L'});
			return root.countNodes();
		},
		6);

	suite.addTest(
		"Deep chain (10 nodes)",
		[]() {
			NodesCountBT root(1);
			root.add({2}, {'L'});
			root.add({2, 3}, {'L', 'L'});
			root.add({2, 3, 4}, {'L', 'L', 'L'});
			root.add({2, 3, 4, 5}, {'L', 'L', 'L', 'L'});
			root.add({2, 3, 4, 5, 6}, {'L', 'L', 'L', 'L', 'L'});
			root.add({2, 3, 4, 5, 6, 7}, {'L', 'L', 'L', 'L', 'L', 'L'});
			root.add({2, 3, 4, 5, 6, 7, 8},
					 {'L', 'L', 'L', 'L', 'L', 'L', 'L'});
			root.add({2, 3, 4, 5, 6, 7, 8, 9},
					 {'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L'});
			root.add({2, 3, 4, 5, 6, 7, 8, 9, 10},
					 {'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L'});
			return root.countNodes();
		},
		10);

	suite.addTest(
		"Asymmetric tree",
		[]() {
			NodesCountBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 4}, {'L', 'L'});
			root.add({3, 6}, {'R', 'L'});
			root.add({3, 6, 8}, {'R', 'L', 'L'});
			root.add({3, 6, 8, 9}, {'R', 'L', 'L', 'R'});
			root.add({2, 4, 5}, {'L', 'L', 'R'});
			return root.countNodes();
		},
		8);

	suite.addTest(
		"Partial complete tree (6 nodes)",
		[]() {
			NodesCountBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 4}, {'L', 'L'});
			root.add({2, 5}, {'L', 'R'});
			root.add({3, 6}, {'R', 'L'});
			return root.countNodes();
		},
		6);

	suite.addTest(
		"Complex structure (11 nodes)",
		[]() {
			NodesCountBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 4}, {'L', 'L'});
			root.add({2, 5}, {'L', 'R'});
			root.add({3, 6}, {'R', 'L'});
			root.add({2, 4, 8}, {'L', 'L', 'L'});
			root.add({2, 4, 9}, {'L', 'L', 'R'});
			root.add({2, 5, 10}, {'L', 'R', 'L'});
			root.add({3, 6, 12}, {'R', 'L', 'L'});
			root.add({3, 6, 12, 13}, {'R', 'L', 'L', 'R'});
			return root.countNodes();
		},
		11);

	suite.run();
	return 0;
}
