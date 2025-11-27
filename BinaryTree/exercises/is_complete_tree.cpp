#include "../../include/test_suite.hpp"
#include "../include/binary_tree.hpp"
#include <queue>
#include <string>

class CompleteTree : public BinaryTree<CompleteTree, int> {
  public:
	using BinaryTree<CompleteTree>::BinaryTree;

	bool isCompleteTree() const {
		std::queue<const CompleteTree *> q;

		q.push(this);

		bool end = false;
		while (!q.empty()) {
			const CompleteTree *current = q.front();
			q.pop();

			if (current == nullptr) {
				end = true;
			} else {
				if (end) {
					return false;
				}
				q.push(current->left);
				q.push(current->right);
			}
		}

		return true;
	}
};

int main() {
	TestSuite<bool> suite;

	suite.addTest(
		"Single node tree", []() { return CompleteTree(1).isCompleteTree(); },
		true);

	suite.addTest(
		"Perfect tree (3 nodes)",
		[]() {
			CompleteTree tree(1);
			tree.add({2}, {'L'});
			tree.add({3}, {'R'});
			return tree.isCompleteTree();
		},
		true);

	suite.addTest(
		"Tree with only left child",
		[]() {
			CompleteTree tree(1);
			tree.add({2}, {'L'});
			return tree.isCompleteTree();
		},
		true);

	suite.addTest(
		"Tree with only right child",
		[]() {
			CompleteTree tree(1);
			tree.add({3}, {'R'});
			return tree.isCompleteTree();
		},
		false);

	suite.addTest(
		"Perfect tree (7 nodes)",
		[]() {
			CompleteTree tree(1);
			tree.add({2}, {'L'});
			tree.add({3}, {'R'});
			tree.add({2, 4}, {'L', 'L'});
			tree.add({2, 5}, {'L', 'R'});
			tree.add({3, 6}, {'R', 'L'});
			tree.add({3, 7}, {'R', 'R'});
			return tree.isCompleteTree();
		},
		true);

	suite.addTest(
		"Complete tree (5 nodes)",
		[]() {
			CompleteTree tree(1);
			tree.add({2}, {'L'});
			tree.add({3}, {'R'});
			tree.add({2, 4}, {'L', 'L'});
			tree.add({2, 5}, {'L', 'R'});
			return tree.isCompleteTree();
		},
		true);

	suite.addTest(
		"Complete tree (6 nodes)",
		[]() {
			CompleteTree tree(1);
			tree.add({2}, {'L'});
			tree.add({3}, {'R'});
			tree.add({2, 4}, {'L', 'L'});
			tree.add({2, 5}, {'L', 'R'});
			tree.add({3, 6}, {'R', 'L'});
			return tree.isCompleteTree();
		},
		true);

	suite.addTest(
		"Incomplete - gap in level (missing node 4)",
		[]() {
			CompleteTree tree(1);
			tree.add({2}, {'L'});
			tree.add({3}, {'R'});
			tree.add({2, 5}, {'L', 'R'});
			return tree.isCompleteTree();
		},
		false);

	suite.addTest(
		"Incomplete - right child of level before left is full",
		[]() {
			CompleteTree tree(1);
			tree.add({2}, {'L'});
			tree.add({3}, {'R'});
			tree.add({2, 4}, {'L', 'L'});
			tree.add({3, 7}, {'R', 'R'});
			return tree.isCompleteTree();
		},
		false);

	suite.addTest(
		"Incomplete - left child missing at node 3",
		[]() {
			CompleteTree tree(1);
			tree.add({2}, {'L'});
			tree.add({3}, {'R'});
			tree.add({2, 4}, {'L', 'L'});
			tree.add({2, 5}, {'L', 'R'});
			tree.add({3, 7}, {'R', 'R'});
			return tree.isCompleteTree();
		},
		false);

	suite.addTest(
		"Left-skewed tree",
		[]() {
			CompleteTree tree(1);
			tree.add({2}, {'L'});
			tree.add({2, 3}, {'L', 'L'});
			return tree.isCompleteTree();
		},
		false);

	suite.addTest(
		"Right-skewed tree",
		[]() {
			CompleteTree tree(1);
			tree.add({2}, {'R'});
			tree.add({2, 3}, {'R', 'R'});
			return tree.isCompleteTree();
		},
		false);

	suite.addTest(
		"Complete tree (4 nodes)",
		[]() {
			CompleteTree tree(1);
			tree.add({2}, {'L'});
			tree.add({3}, {'R'});
			tree.add({2, 4}, {'L', 'L'});
			return tree.isCompleteTree();
		},
		true);

	suite.addTest(
		"Incomplete - node exists after first non-full node",
		[]() {
			CompleteTree tree(1);
			tree.add({2}, {'L'});
			tree.add({3}, {'R'});
			tree.add({2, 4}, {'L', 'L'});
			tree.add({3, 6}, {'R', 'L'});
			tree.add({3, 7}, {'R', 'R'});
			return tree.isCompleteTree();
		},
		false);

	suite.addTest(
		"Large perfect tree (15 nodes)",
		[]() {
			CompleteTree tree(1);
			tree.add({2}, {'L'});
			tree.add({3}, {'R'});
			tree.add({2, 4}, {'L', 'L'});
			tree.add({2, 5}, {'L', 'R'});
			tree.add({3, 6}, {'R', 'L'});
			tree.add({3, 7}, {'R', 'R'});
			tree.add({2, 4, 8}, {'L', 'L', 'L'});
			tree.add({2, 4, 9}, {'L', 'L', 'R'});
			tree.add({2, 5, 10}, {'L', 'R', 'L'});
			tree.add({2, 5, 11}, {'L', 'R', 'R'});
			tree.add({3, 6, 12}, {'R', 'L', 'L'});
			tree.add({3, 6, 13}, {'R', 'L', 'R'});
			tree.add({3, 7, 14}, {'R', 'R', 'L'});
			tree.add({3, 7, 15}, {'R', 'R', 'R'});
			return tree.isCompleteTree();
		},
		true);

	suite.run();

	return 0;
}
