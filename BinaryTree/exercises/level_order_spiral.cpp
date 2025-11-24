#include "../../include/test_suite.hpp"
#include "../include/binary_tree.hpp"
#include <deque>
#include <string>

class LevelOrderSpiralBT : public BinaryTree<LevelOrderSpiralBT, int> {
  public:
	using BinaryTree<LevelOrderSpiralBT, int>::BinaryTree;

	std::string levelOrderSpiralTraversal() const {
		std::deque<const LevelOrderSpiralBT *> q;
		std::string res;

		q.push_front(this);

		bool LTR = true;

		while (!q.empty()) {
			int level_size = q.size();

			while (level_size--) {
				auto node = LTR ? q.front() : q.back();

				LTR ? q.pop_front() : q.pop_back();

				res.append(std::to_string(node->data) + " ");

				if (LTR) {
					if (node->left)
						q.push_back(node->left);

					if (node->right)
						q.push_back(node->right);

				} else {
					if (node->right)
						q.push_front(node->right);

					if (node->left)
						q.push_front(node->left);
				}
			}
			LTR = !LTR;
		}

		if (!res.empty()) {
			res.pop_back();
		}

		return res;
	}
};

int main() {
	TestSuite<std::string> suite;

	// Edge Case 1: Single node tree (root only)
	suite.addTest(
		"Single node tree",
		[]() {
			LevelOrderSpiralBT tree(1);
			return tree.levelOrderSpiralTraversal();
		},
		"1");

	// Edge Case 2: Two nodes (root + left child)
	suite.addTest(
		"Two nodes - root and left child",
		[]() {
			LevelOrderSpiralBT tree(1);
			tree.add({2}, {'L'});
			return tree.levelOrderSpiralTraversal();
		},
		"1 2");

	// Edge Case 3: Two nodes (root + right child)
	suite.addTest(
		"Two nodes - root and right child",
		[]() {
			LevelOrderSpiralBT tree(1);
			tree.add({2}, {'R'});
			return tree.levelOrderSpiralTraversal();
		},
		"1 2");

	// Edge Case 4: Complete binary tree (3 nodes)
	// Level 0 (even): 1 - print L->R
	// Level 1 (odd): 2,3 - print R->L: 3 2
	suite.addTest(
		"Complete binary tree (3 nodes)",
		[]() {
			LevelOrderSpiralBT tree(1);
			tree.add({2}, {'L'});
			tree.add({3}, {'R'});
			return tree.levelOrderSpiralTraversal();
		},
		"1 3 2");

	// Edge Case 5: Left-skewed tree (3 levels)
	suite.addTest(
		"Left-skewed tree (3 levels)",
		[]() {
			LevelOrderSpiralBT tree(1);
			tree.add({2}, {'L'});
			tree.add({2, 3}, {'L', 'L'});
			return tree.levelOrderSpiralTraversal();
		},
		"1 2 3");

	// Edge Case 6: Right-skewed tree (3 levels)
	suite.addTest(
		"Right-skewed tree (3 levels)",
		[]() {
			LevelOrderSpiralBT tree(1);
			tree.add({2}, {'R'});
			tree.add({2, 3}, {'R', 'R'});
			return tree.levelOrderSpiralTraversal();
		},
		"1 2 3");

	// Edge Case 7: Perfect binary tree (4 levels, 15 nodes)
	// Level 0 (even): 1 - print L->R: 1
	// Level 1 (odd): 2,3 - print R->L: 3 2
	// Level 2 (even): 4,5,6,7 - print L->R: 4 5 6 7
	// Level 3 (odd): 8,9,10,11,12,13,14,15 - print R->L: 15 14 13 12 11 10 9 8
	suite.addTest(
		"Perfect binary tree (4 levels)",
		[]() {
			LevelOrderSpiralBT tree(1);
			// Level 1
			tree.add({2}, {'L'});
			tree.add({3}, {'R'});
			// Level 2 - left subtree
			tree.add({2, 4}, {'L', 'L'});
			tree.add({2, 5}, {'L', 'R'});
			// Level 2 - right subtree
			tree.add({3, 6}, {'R', 'L'});
			tree.add({3, 7}, {'R', 'R'});
			// Level 3 - leftmost subtree
			tree.add({2, 4, 8}, {'L', 'L', 'L'});
			tree.add({2, 4, 9}, {'L', 'L', 'R'});
			tree.add({2, 5, 10}, {'L', 'R', 'L'});
			tree.add({2, 5, 11}, {'L', 'R', 'R'});
			// Level 3 - rightmost subtree
			tree.add({3, 6, 12}, {'R', 'L', 'L'});
			tree.add({3, 6, 13}, {'R', 'L', 'R'});
			tree.add({3, 7, 14}, {'R', 'R', 'L'});
			tree.add({3, 7, 15}, {'R', 'R', 'R'});
			return tree.levelOrderSpiralTraversal();
		},
		"1 3 2 4 5 6 7 15 14 13 12 11 10 9 8");

	// Edge Case 8: Incomplete tree with mixed structure
	// Level 0 (even): 1 - print L->R: 1
	// Level 1 (odd): 2,3 - print R->L: 3 2
	// Level 2 (even): 4,5 - print L->R: 4 5
	suite.addTest(
		"Incomplete tree - only left children at level 2",
		[]() {
			LevelOrderSpiralBT tree(1);
			tree.add({2}, {'L'});
			tree.add({3}, {'R'});
			tree.add({2, 4}, {'L', 'L'});
			tree.add({3, 5}, {'R', 'L'});
			return tree.levelOrderSpiralTraversal();
		},
		"1 3 2 4 5");

	// Edge Case 9: Incomplete tree - only right children at level 2
	// Level 0 (even): 1 - print L->R: 1
	// Level 1 (odd): 2,3 - print R->L: 3 2
	// Level 2 (even): 4,5 - print L->R: 4 5
	suite.addTest(
		"Incomplete tree - only right children at level 2",
		[]() {
			LevelOrderSpiralBT tree(1);
			tree.add({2}, {'L'});
			tree.add({3}, {'R'});
			tree.add({2, 4}, {'L', 'R'});
			tree.add({3, 5}, {'R', 'R'});
			return tree.levelOrderSpiralTraversal();
		},
		"1 3 2 4 5");

	// Edge Case 10: Tree with 5 levels to test multiple spiral alternations
	// Level 0 (even): 1 - print L->R: 1
	// Level 1 (odd): 2,3 - print R->L: 3 2
	// Level 2 (even): 4,5,6,7 - print L->R: 4 5 6 7
	// Level 3 (odd): 8,9,10,11,12,13,14,15 - print R->L: 15 14 13 12 11 10 9 8
	// Level 4 (even): 16,17,18,19 - print L->R: 16 17 18 19
	suite.addTest(
		"Five-level tree with alternating spiral",
		[]() {
			LevelOrderSpiralBT tree(1);
			// Level 1
			tree.add({2}, {'L'});
			tree.add({3}, {'R'});
			// Level 2
			tree.add({2, 4}, {'L', 'L'});
			tree.add({2, 5}, {'L', 'R'});
			tree.add({3, 6}, {'R', 'L'});
			tree.add({3, 7}, {'R', 'R'});
			// Level 3 - Add all 8 nodes
			tree.add({2, 4, 8}, {'L', 'L', 'L'});
			tree.add({2, 4, 9}, {'L', 'L', 'R'});
			tree.add({2, 5, 10}, {'L', 'R', 'L'});
			tree.add({2, 5, 11}, {'L', 'R', 'R'});
			tree.add({3, 6, 12}, {'R', 'L', 'L'});
			tree.add({3, 6, 13}, {'R', 'L', 'R'});
			tree.add({3, 7, 14}, {'R', 'R', 'L'});
			tree.add({3, 7, 15}, {'R', 'R', 'R'});
			// Level 4 - Add just a few nodes
			tree.add({2, 4, 8, 16}, {'L', 'L', 'L', 'L'});
			tree.add({2, 4, 8, 17}, {'L', 'L', 'L', 'R'});
			tree.add({3, 7, 15, 18}, {'R', 'R', 'R', 'L'});
			tree.add({3, 7, 15, 19}, {'R', 'R', 'R', 'R'});
			return tree.levelOrderSpiralTraversal();
		},
		"1 3 2 4 5 6 7 15 14 13 12 11 10 9 8 16 17 18 19");

	// Edge Case 11: Asymmetric tree (deep left, shallow right)
	// Level 0 (even): 1 - print L->R: 1
	// Level 1 (odd): 2,3 - print R->L: 3 2
	// Level 2 (even): 4 - print L->R: 4
	// Level 3 (odd): 5 - print R->L: 5
	suite.addTest(
		"Asymmetric tree - deep left, shallow right",
		[]() {
			LevelOrderSpiralBT tree(1);
			tree.add({2}, {'L'});
			tree.add({3}, {'R'});
			tree.add({2, 4}, {'L', 'L'});
			tree.add({2, 4, 5}, {'L', 'L', 'L'});
			return tree.levelOrderSpiralTraversal();
		},
		"1 3 2 4 5");

	// Edge Case 12: Tree with single child nodes at different levels
	// Level 0 (even): 1 - print L->R: 1
	// Level 1 (odd): 2 - print R->L: 2
	// Level 2 (even): 3 - print L->R: 3
	// Level 3 (odd): 4 - print R->L: 4
	// Level 4 (even): 5 - print L->R: 5
	suite.addTest(
		"Zigzag tree structure",
		[]() {
			LevelOrderSpiralBT tree(1);
			tree.add({2}, {'L'});
			tree.add({2, 3}, {'L', 'R'});
			tree.add({2, 3, 4}, {'L', 'R', 'L'});
			tree.add({2, 3, 4, 5}, {'L', 'R', 'L', 'R'});
			return tree.levelOrderSpiralTraversal();
		},
		"1 2 3 4 5");

	suite.run();
	return 0;
}
