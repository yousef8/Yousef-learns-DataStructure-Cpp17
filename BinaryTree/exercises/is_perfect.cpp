#include "../../include/test_suite.hpp"
#include "../include/binary_tree.hpp"
#include <algorithm>

class PerfectBT : public BinaryTree<PerfectBT> {
  public:
	using BinaryTree<PerfectBT>::BinaryTree;

	int height() const {
		int h{0};

		if (left)
			h = 1 + left->height();

		if (right)
			h = std::max(h, 1 + right->height());

		return h;
	}

	bool isPerfect(int h = -1) const {
		if (h == -1) {
			h = height();
		}

		if (h == 0) {
			return true;
		}

		if (!left || !right) {
			return false;
		}

		return left->isPerfect(h - 1) && right->isPerfect(h - 1);
	}
};

int main() {
	TestSuite<bool> suite;

	suite.addTest(
		"Single node tree",
		[]() {
			PerfectBT root(1);
			return root.isPerfect();
		},
		true);

	suite.addTest(
		"Two nodes - left child only",
		[]() {
			PerfectBT root(1);
			root.add({2}, {'L'});
			return root.isPerfect();
		},
		false);

	suite.addTest(
		"Two nodes - right child only",
		[]() {
			PerfectBT root(1);
			root.add({2}, {'R'});
			return root.isPerfect();
		},
		false);

	suite.addTest(
		"Three nodes - perfect tree",
		[]() {
			PerfectBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			return root.isPerfect();
		},
		true);

	suite.addTest(
		"Four nodes - missing one child",
		[]() {
			PerfectBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 4}, {'L', 'L'});
			return root.isPerfect();
		},
		false);

	suite.addTest(
		"Perfect binary tree (7 nodes)",
		[]() {
			PerfectBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 4}, {'L', 'L'});
			root.add({2, 5}, {'L', 'R'});
			root.add({3, 6}, {'R', 'L'});
			root.add({3, 7}, {'R', 'R'});
			return root.isPerfect();
		},
		true);

	suite.addTest(
		"Complete but not perfect",
		[]() {
			PerfectBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 4}, {'L', 'L'});
			root.add({2, 5}, {'L', 'R'});
			root.add({3, 6}, {'R', 'L'});
			return root.isPerfect();
		},
		false);

	suite.addTest(
		"Perfect binary tree (15 nodes)",
		[]() {
			PerfectBT root(1);
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
			return root.isPerfect();
		},
		true);

	suite.addTest(
		"Almost perfect - missing one node",
		[]() {
			PerfectBT root(1);
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
			return root.isPerfect();
		},
		false);

	suite.addTest(
		"Left-skewed tree",
		[]() {
			PerfectBT root(1);
			root.add({2}, {'L'});
			root.add({2, 3}, {'L', 'L'});
			root.add({2, 3, 4}, {'L', 'L', 'L'});
			return root.isPerfect();
		},
		false);

	suite.addTest(
		"Right-skewed tree",
		[]() {
			PerfectBT root(1);
			root.add({2}, {'R'});
			root.add({2, 3}, {'R', 'R'});
			root.add({2, 3, 4}, {'R', 'R', 'R'});
			return root.isPerfect();
		},
		false);

	suite.addTest(
		"Unbalanced tree - left heavy",
		[]() {
			PerfectBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 4}, {'L', 'L'});
			root.add({2, 5}, {'L', 'R'});
			root.add({2, 4, 6}, {'L', 'L', 'L'});
			root.add({2, 4, 7}, {'L', 'L', 'R'});
			return root.isPerfect();
		},
		false);

	suite.addTest(
		"Unbalanced tree - right heavy",
		[]() {
			PerfectBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({3, 6}, {'R', 'L'});
			root.add({3, 7}, {'R', 'R'});
			root.add({3, 7, 8}, {'R', 'R', 'L'});
			root.add({3, 7, 9}, {'R', 'R', 'R'});
			return root.isPerfect();
		},
		false);

	suite.addTest(
		"Left subtree complete only",
		[]() {
			PerfectBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 4}, {'L', 'L'});
			root.add({2, 5}, {'L', 'R'});
			return root.isPerfect();
		},
		false);

	suite.addTest(
		"Right subtree complete only",
		[]() {
			PerfectBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({3, 6}, {'R', 'L'});
			root.add({3, 7}, {'R', 'R'});
			return root.isPerfect();
		},
		false);

	suite.addTest(
		"Sparse tree with gaps",
		[]() {
			PerfectBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 4}, {'L', 'L'});
			root.add({3, 7}, {'R', 'R'});
			return root.isPerfect();
		},
		false);

	suite.addTest(
		"Zigzag pattern",
		[]() {
			PerfectBT root(1);
			root.add({2}, {'L'});
			root.add({2, 3}, {'L', 'R'});
			root.add({2, 3, 4}, {'L', 'R', 'L'});
			root.add({2, 3, 4, 5}, {'L', 'R', 'L', 'R'});
			return root.isPerfect();
		},
		false);

	suite.addTest(
		"Five nodes - one subtree deeper",
		[]() {
			PerfectBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 4}, {'L', 'L'});
			root.add({2, 5}, {'L', 'R'});
			return root.isPerfect();
		},
		false);

	suite.addTest(
		"Six nodes - missing two",
		[]() {
			PerfectBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 4}, {'L', 'L'});
			root.add({2, 5}, {'L', 'R'});
			root.add({3, 6}, {'R', 'L'});
			return root.isPerfect();
		},
		false);

	suite.addTest(
		"Asymmetric depths",
		[]() {
			PerfectBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 4}, {'L', 'L'});
			root.add({3, 6}, {'R', 'L'});
			root.add({3, 6, 8}, {'R', 'L', 'L'});
			return root.isPerfect();
		},
		false);

	suite.addTest(
		"Perfect tree (31 nodes)",
		[]() {
			PerfectBT root(1);
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
			root.add({2, 4, 8, 16}, {'L', 'L', 'L', 'L'});
			root.add({2, 4, 8, 17}, {'L', 'L', 'L', 'R'});
			root.add({2, 4, 9, 18}, {'L', 'L', 'R', 'L'});
			root.add({2, 4, 9, 19}, {'L', 'L', 'R', 'R'});
			root.add({2, 5, 10, 20}, {'L', 'R', 'L', 'L'});
			root.add({2, 5, 10, 21}, {'L', 'R', 'L', 'R'});
			root.add({2, 5, 11, 22}, {'L', 'R', 'R', 'L'});
			root.add({2, 5, 11, 23}, {'L', 'R', 'R', 'R'});
			root.add({3, 6, 12, 24}, {'R', 'L', 'L', 'L'});
			root.add({3, 6, 12, 25}, {'R', 'L', 'L', 'R'});
			root.add({3, 6, 13, 26}, {'R', 'L', 'R', 'L'});
			root.add({3, 6, 13, 27}, {'R', 'L', 'R', 'R'});
			root.add({3, 7, 14, 28}, {'R', 'R', 'L', 'L'});
			root.add({3, 7, 14, 29}, {'R', 'R', 'L', 'R'});
			root.add({3, 7, 15, 30}, {'R', 'R', 'R', 'L'});
			root.add({3, 7, 15, 31}, {'R', 'R', 'R', 'R'});
			return root.isPerfect();
		},
		true);

	suite.addTest(
		"31 nodes minus one",
		[]() {
			PerfectBT root(1);
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
			root.add({2, 4, 8, 16}, {'L', 'L', 'L', 'L'});
			root.add({2, 4, 8, 17}, {'L', 'L', 'L', 'R'});
			root.add({2, 4, 9, 18}, {'L', 'L', 'R', 'L'});
			root.add({2, 4, 9, 19}, {'L', 'L', 'R', 'R'});
			root.add({2, 5, 10, 20}, {'L', 'R', 'L', 'L'});
			root.add({2, 5, 10, 21}, {'L', 'R', 'L', 'R'});
			root.add({2, 5, 11, 22}, {'L', 'R', 'R', 'L'});
			root.add({2, 5, 11, 23}, {'L', 'R', 'R', 'R'});
			root.add({3, 6, 12, 24}, {'R', 'L', 'L', 'L'});
			root.add({3, 6, 12, 25}, {'R', 'L', 'L', 'R'});
			root.add({3, 6, 13, 26}, {'R', 'L', 'R', 'L'});
			root.add({3, 6, 13, 27}, {'R', 'L', 'R', 'R'});
			root.add({3, 7, 14, 28}, {'R', 'R', 'L', 'L'});
			root.add({3, 7, 14, 29}, {'R', 'R', 'L', 'R'});
			root.add({3, 7, 15, 30}, {'R', 'R', 'R', 'L'});
			return root.isPerfect();
		},
		false);

	suite.addTest(
		"Original test case",
		[]() {
			PerfectBT tree(2);
			tree.add({3}, {'L'});
			tree.add({13, 7}, {'R', 'L'});
			tree.add({13, 8}, {'R', 'R'});
			return tree.isPerfect();
		},
		false);

	suite.addTest(
		"Tree up to height 3",
		[]() {
			PerfectBT root(1);
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
			return root.isPerfect();
		},
		true);

	suite.addTest(
		"One grandchild only",
		[]() {
			PerfectBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 4}, {'L', 'L'});
			root.add({2, 4, 8}, {'L', 'L', 'L'});
			return root.isPerfect();
		},
		false);

	suite.run();
	return 0;
}