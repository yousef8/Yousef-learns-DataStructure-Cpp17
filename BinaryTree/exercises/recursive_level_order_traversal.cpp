#include "../../include/test_suite.hpp"
#include "../include/binary_tree.hpp"
#include <string>

/*
// ********************* This Implementation is BETTER ********************
class RecursiveLevelOrderBT : public BinaryTree<RecursiveLevelOrderBT> {
  public:
	using BinaryTree<RecursiveLevelOrderBT>::BinaryTree;

	void traverseLevel(int level, std::vector<int> &res) const {
		if (level == 0) {
			res.push_back(data);
			return;
		}

		if (left) {
			left->traverseLevel(level - 1, res);
		}

		if (right) {
			right->traverseLevel(level - 1, res);
		}
	}

	std::vector<int> recursiveLevelOrderTraversal() const {
		std::vector<int> res;
		int h = height();

		for (int level = 0; level <= h; ++level) {
			traverseLevel(level, res);
		}

		return res;
	}
};
*/

class RecursiveLevelOrderBT : public BinaryTree<RecursiveLevelOrderBT, int> {
  public:
	using BinaryTree<RecursiveLevelOrderBT, int>::BinaryTree;

	int height() const {
		int h{0};

		if (left)
			h = 1 + left->height();

		if (right)
			h = std::max(h, 1 + right->height());

		return h;
	}

	std::string recursiveLevelOrderTraversal(int l = 0, int dl = 0) const {
		std::string res{};

		if (l == 0) {
			int h = height();
			dl = 1;
			res += "Level 0: " + std::to_string(data) + '\n';

			while (dl <= h) {
				res += "Level " + std::to_string(dl) + ": ";
				if (left) {
					res += left->recursiveLevelOrderTraversal(l + 1, dl);
				}
				if (right) {
					res += right->recursiveLevelOrderTraversal(l + 1, dl);
				}
				res.pop_back();
				res += '\n';
				dl++;
			}
		} else if (l == dl) {
			return std::to_string(data) + " ";
		} else {
			if (left) {
				res += left->recursiveLevelOrderTraversal(l + 1, dl);
			}
			if (right) {
				res += right->recursiveLevelOrderTraversal(l + 1, dl);
			}
		}

		return res;
	}
};

int main() {
	TestSuite<std::string> suite;

	suite.addTest(
		"Single node",
		[]() {
			RecursiveLevelOrderBT root(1);
			return root.recursiveLevelOrderTraversal();
		},
		"Level 0: 1\n");

	suite.addTest(
		"Two nodes - left child only",
		[]() {
			RecursiveLevelOrderBT root(10);
			root.add({5}, {'L'});
			return root.recursiveLevelOrderTraversal();
		},
		"Level 0: 10\nLevel 1: 5\n");

	suite.addTest(
		"Two nodes - right child only",
		[]() {
			RecursiveLevelOrderBT root(10);
			root.add({15}, {'R'});
			return root.recursiveLevelOrderTraversal();
		},
		"Level 0: 10\nLevel 1: 15\n");

	suite.addTest(
		"Three nodes - complete tree",
		[]() {
			RecursiveLevelOrderBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			return root.recursiveLevelOrderTraversal();
		},
		"Level 0: 1\nLevel 1: 2 3\n");

	suite.addTest(
		"Four nodes - only left subtree",
		[]() {
			RecursiveLevelOrderBT root(1);
			root.add({2}, {'L'});
			root.add({2, 3}, {'L', 'L'});
			root.add({2, 4}, {'L', 'R'});
			return root.recursiveLevelOrderTraversal();
		},
		"Level 0: 1\nLevel 1: 2\nLevel 2: 3 4\n");

	suite.addTest(
		"Four nodes - only right subtree",
		[]() {
			RecursiveLevelOrderBT root(1);
			root.add({2}, {'R'});
			root.add({2, 3}, {'R', 'L'});
			root.add({2, 4}, {'R', 'R'});
			return root.recursiveLevelOrderTraversal();
		},
		"Level 0: 1\nLevel 1: 2\nLevel 2: 3 4\n");

	suite.addTest(
		"Five nodes - left heavy",
		[]() {
			RecursiveLevelOrderBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 4}, {'L', 'L'});
			root.add({2, 5}, {'L', 'R'});
			return root.recursiveLevelOrderTraversal();
		},
		"Level 0: 1\nLevel 1: 2 3\nLevel 2: 4 5\n");

	suite.addTest(
		"Five nodes - right heavy",
		[]() {
			RecursiveLevelOrderBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({3, 6}, {'R', 'L'});
			root.add({3, 7}, {'R', 'R'});
			return root.recursiveLevelOrderTraversal();
		},
		"Level 0: 1\nLevel 1: 2 3\nLevel 2: 6 7\n");

	suite.addTest(
		"Complete binary tree - 7 nodes",
		[]() {
			RecursiveLevelOrderBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 4}, {'L', 'L'});
			root.add({2, 5}, {'L', 'R'});
			root.add({3, 6}, {'R', 'L'});
			root.add({3, 7}, {'R', 'R'});
			return root.recursiveLevelOrderTraversal();
		},
		"Level 0: 1\nLevel 1: 2 3\nLevel 2: 4 5 6 7\n");

	suite.addTest(
		"Complete binary tree - 15 nodes",
		[]() {
			RecursiveLevelOrderBT root(1);
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
			return root.recursiveLevelOrderTraversal();
		},
		"Level 0: 1\nLevel 1: 2 3\nLevel 2: 4 5 6 7\nLevel 3: 8 9 10 11 12 13 "
		"14 15\n");

	suite.addTest(
		"Left-skewed tree - 3 levels",
		[]() {
			RecursiveLevelOrderBT root(1);
			root.add({2}, {'L'});
			root.add({2, 3}, {'L', 'L'});
			return root.recursiveLevelOrderTraversal();
		},
		"Level 0: 1\nLevel 1: 2\nLevel 2: 3\n");

	suite.addTest(
		"Left-skewed tree - 5 levels",
		[]() {
			RecursiveLevelOrderBT root(1);
			root.add({2}, {'L'});
			root.add({2, 3}, {'L', 'L'});
			root.add({2, 3, 4}, {'L', 'L', 'L'});
			root.add({2, 3, 4, 5}, {'L', 'L', 'L', 'L'});
			return root.recursiveLevelOrderTraversal();
		},
		"Level 0: 1\nLevel 1: 2\nLevel 2: 3\nLevel 3: 4\nLevel 4: 5\n");

	suite.addTest(
		"Right-skewed tree - 3 levels",
		[]() {
			RecursiveLevelOrderBT root(1);
			root.add({2}, {'R'});
			root.add({2, 3}, {'R', 'R'});
			return root.recursiveLevelOrderTraversal();
		},
		"Level 0: 1\nLevel 1: 2\nLevel 2: 3\n");

	suite.addTest(
		"Right-skewed tree - 5 levels",
		[]() {
			RecursiveLevelOrderBT root(1);
			root.add({2}, {'R'});
			root.add({2, 3}, {'R', 'R'});
			root.add({2, 3, 4}, {'R', 'R', 'R'});
			root.add({2, 3, 4, 5}, {'R', 'R', 'R', 'R'});
			return root.recursiveLevelOrderTraversal();
		},
		"Level 0: 1\nLevel 1: 2\nLevel 2: 3\nLevel 3: 4\nLevel 4: 5\n");

	suite.addTest(
		"Zigzag pattern - left-right-left",
		[]() {
			RecursiveLevelOrderBT root(1);
			root.add({2}, {'L'});
			root.add({2, 3}, {'L', 'R'});
			root.add({2, 3, 4}, {'L', 'R', 'L'});
			return root.recursiveLevelOrderTraversal();
		},
		"Level 0: 1\nLevel 1: 2\nLevel 2: 3\nLevel 3: 4\n");

	suite.addTest(
		"Zigzag pattern - right-left-right",
		[]() {
			RecursiveLevelOrderBT root(1);
			root.add({2}, {'R'});
			root.add({2, 3}, {'R', 'L'});
			root.add({2, 3, 4}, {'R', 'L', 'R'});
			return root.recursiveLevelOrderTraversal();
		},
		"Level 0: 1\nLevel 1: 2\nLevel 2: 3\nLevel 3: 4\n");

	suite.addTest(
		"Sparse tree - missing middle nodes",
		[]() {
			RecursiveLevelOrderBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 4}, {'L', 'L'});
			root.add({3, 7}, {'R', 'R'});
			return root.recursiveLevelOrderTraversal();
		},
		"Level 0: 1\nLevel 1: 2 3\nLevel 2: 4 7\n");

	suite.addTest(
		"Sparse tree - only leftmost and rightmost leaves",
		[]() {
			RecursiveLevelOrderBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 4}, {'L', 'L'});
			root.add({2, 4, 8}, {'L', 'L', 'L'});
			root.add({3, 7}, {'R', 'R'});
			root.add({3, 7, 15}, {'R', 'R', 'R'});
			return root.recursiveLevelOrderTraversal();
		},
		"Level 0: 1\nLevel 1: 2 3\nLevel 2: 4 7\nLevel 3: 8 15\n");

	suite.addTest(
		"Asymmetric tree - deeper left branch",
		[]() {
			RecursiveLevelOrderBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 4}, {'L', 'L'});
			root.add({2, 4, 8}, {'L', 'L', 'L'});
			root.add({2, 4, 8, 16}, {'L', 'L', 'L', 'L'});
			return root.recursiveLevelOrderTraversal();
		},
		"Level 0: 1\nLevel 1: 2 3\nLevel 2: 4\nLevel 3: 8\nLevel 4: 16\n");

	suite.addTest(
		"Asymmetric tree - deeper right branch",
		[]() {
			RecursiveLevelOrderBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({3, 7}, {'R', 'R'});
			root.add({3, 7, 15}, {'R', 'R', 'R'});
			root.add({3, 7, 15, 31}, {'R', 'R', 'R', 'R'});
			return root.recursiveLevelOrderTraversal();
		},
		"Level 0: 1\nLevel 1: 2 3\nLevel 2: 7\nLevel 3: 15\nLevel 4: 31\n");

	suite.addTest(
		"Negative values",
		[]() {
			RecursiveLevelOrderBT root(-1);
			root.add({-2}, {'L'});
			root.add({-3}, {'R'});
			root.add({-2, -4}, {'L', 'L'});
			root.add({-2, -5}, {'L', 'R'});
			return root.recursiveLevelOrderTraversal();
		},
		"Level 0: -1\nLevel 1: -2 -3\nLevel 2: -4 -5\n");

	suite.addTest(
		"Zero and negative values",
		[]() {
			RecursiveLevelOrderBT root(0);
			root.add({-5}, {'L'});
			root.add({5}, {'R'});
			root.add({-5, -10}, {'L', 'L'});
			root.add({5, 10}, {'R', 'R'});
			return root.recursiveLevelOrderTraversal();
		},
		"Level 0: 0\nLevel 1: -5 5\nLevel 2: -10 10\n");

	suite.addTest(
		"Large values",
		[]() {
			RecursiveLevelOrderBT root(1000);
			root.add({500}, {'L'});
			root.add({2000}, {'R'});
			root.add({500, 250}, {'L', 'L'});
			root.add({2000, 5000}, {'R', 'R'});
			return root.recursiveLevelOrderTraversal();
		},
		"Level 0: 1000\nLevel 1: 500 2000\nLevel 2: 250 5000\n");

	suite.addTest(
		"Same values at different levels",
		[]() {
			RecursiveLevelOrderBT root(5);
			root.add({5}, {'L'});
			root.add({5}, {'R'});
			root.add({5, 5}, {'L', 'L'});
			root.add({5, 5}, {'L', 'R'});
			return root.recursiveLevelOrderTraversal();
		},
		"Level 0: 5\nLevel 1: 5 5\nLevel 2: 5 5\n");

	suite.addTest(
		"Partial level - left side filled",
		[]() {
			RecursiveLevelOrderBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 4}, {'L', 'L'});
			root.add({2, 5}, {'L', 'R'});
			root.add({3, 6}, {'R', 'L'});
			return root.recursiveLevelOrderTraversal();
		},
		"Level 0: 1\nLevel 1: 2 3\nLevel 2: 4 5 6\n");

	suite.addTest(
		"Partial level - right side filled",
		[]() {
			RecursiveLevelOrderBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 5}, {'L', 'R'});
			root.add({3, 6}, {'R', 'L'});
			root.add({3, 7}, {'R', 'R'});
			return root.recursiveLevelOrderTraversal();
		},
		"Level 0: 1\nLevel 1: 2 3\nLevel 2: 5 6 7\n");

	suite.addTest(
		"Deep tree with mixed structure",
		[]() {
			RecursiveLevelOrderBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 4}, {'L', 'L'});
			root.add({3, 7}, {'R', 'R'});
			root.add({2, 4, 8}, {'L', 'L', 'L'});
			root.add({3, 7, 15}, {'R', 'R', 'R'});
			root.add({2, 4, 8, 16}, {'L', 'L', 'L', 'L'});
			return root.recursiveLevelOrderTraversal();
		},
		"Level 0: 1\nLevel 1: 2 3\nLevel 2: 4 7\nLevel 3: 8 15\nLevel 4: 16\n");

	suite.addTest(
		"Single left branch with right leaves",
		[]() {
			RecursiveLevelOrderBT root(1);
			root.add({2}, {'L'});
			root.add({2, 3}, {'L', 'R'});
			root.add({2, 3, 4}, {'L', 'R', 'R'});
			root.add({2, 3, 4, 5}, {'L', 'R', 'R', 'R'});
			return root.recursiveLevelOrderTraversal();
		},
		"Level 0: 1\nLevel 1: 2\nLevel 2: 3\nLevel 3: 4\nLevel 4: 5\n");

	suite.addTest(
		"Single right branch with left leaves",
		[]() {
			RecursiveLevelOrderBT root(1);
			root.add({2}, {'R'});
			root.add({2, 3}, {'R', 'L'});
			root.add({2, 3, 4}, {'R', 'L', 'L'});
			root.add({2, 3, 4, 5}, {'R', 'L', 'L', 'L'});
			return root.recursiveLevelOrderTraversal();
		},
		"Level 0: 1\nLevel 1: 2\nLevel 2: 3\nLevel 3: 4\nLevel 4: 5\n");

	suite.run();
	return 0;
}
