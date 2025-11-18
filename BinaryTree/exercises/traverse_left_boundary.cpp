#include "../../include/test_suite.hpp"
#include "../include/binary_tree.hpp"

class LeftBoundaryTraversal : public BinaryTree<LeftBoundaryTraversal> {
  public:
	using BinaryTree<LeftBoundaryTraversal>::BinaryTree;

	int traverseLeftBoundary() const {
		if (!left && !right) {
			return data;
		}

		if (left)
			return left->traverseLeftBoundary();

		return right->traverseLeftBoundary();
	}
};

int main() {
	TestSuite<int> suite;

	suite.addTest(
		"Single node tree",
		[]() {
			LeftBoundaryTraversal tree(42);
			return tree.traverseLeftBoundary();
		},
		42);

	suite.addTest(
		"Root with only left child",
		[]() {
			LeftBoundaryTraversal tree(10);
			tree.add({5}, {'L'});
			return tree.traverseLeftBoundary();
		},
		5);

	suite.addTest(
		"Root with only right child",
		[]() {
			LeftBoundaryTraversal tree(10);
			tree.add({15}, {'R'});
			return tree.traverseLeftBoundary();
		},
		15);

	suite.addTest(
		"Root with both children",
		[]() {
			LeftBoundaryTraversal tree(10);
			tree.add({5}, {'L'});
			tree.add({15}, {'R'});
			return tree.traverseLeftBoundary();
		},
		5);

	suite.addTest(
		"Deep left path",
		[]() {
			LeftBoundaryTraversal tree(10);
			tree.add({5, 3, 1}, {'L', 'L', 'L'});
			return tree.traverseLeftBoundary();
		},
		1);

	suite.addTest(
		"Left then right at leaf",
		[]() {
			LeftBoundaryTraversal tree(10);
			tree.add({5, 3}, {'L', 'L'});
			tree.add({5, 7}, {'L', 'R'});
			return tree.traverseLeftBoundary();
		},
		3);

	suite.addTest(
		"Right path only",
		[]() {
			LeftBoundaryTraversal tree(10);
			tree.add({15, 20, 25}, {'R', 'R', 'R'});
			return tree.traverseLeftBoundary();
		},
		25);

	suite.addTest(
		"Mixed path: L, then R when no L",
		[]() {
			LeftBoundaryTraversal tree(10);
			tree.add({5}, {'L'});
			tree.add({5, 8, 7}, {'L', 'R', 'L'});
			return tree.traverseLeftBoundary();
		},
		7);

	suite.addTest(
		"Left path ignores right subtrees",
		[]() {
			LeftBoundaryTraversal tree(10);
			tree.add({5, 3}, {'L', 'L'});
			tree.add({15}, {'R'});
			tree.add({5, 7}, {'L', 'R'});
			return tree.traverseLeftBoundary();
		},
		3);

	suite.addTest(
		"Zigzag: L-R-leaf",
		[]() {
			LeftBoundaryTraversal tree(10);
			tree.add({5}, {'L'});
			tree.add({5, 7}, {'L', 'R'});
			tree.add({5, 7, 6}, {'L', 'R', 'L'});
			return tree.traverseLeftBoundary();
		},
		6);

	suite.addTest(
		"L-R path to leaf",
		[]() {
			LeftBoundaryTraversal tree(100);
			tree.add({50}, {'L'});
			tree.add({50, 75}, {'L', 'R'});
			return tree.traverseLeftBoundary();
		},
		75);

	suite.addTest(
		"Large tree with deep left boundary",
		[]() {
			LeftBoundaryTraversal tree(50);
			tree.add({25, 12, 6, 3, 1}, {'L', 'L', 'L', 'L', 'L'});
			// Add right subtrees that should be ignored
			tree.add({75}, {'R'});
			tree.add({25, 37}, {'L', 'R'});
			return tree.traverseLeftBoundary();
		},
		1);

	suite.addTest(
		"Negative values in tree",
		[]() {
			LeftBoundaryTraversal tree(-10);
			tree.add({-20, -30}, {'L', 'L'});
			return tree.traverseLeftBoundary();
		},
		-30);

	suite.addTest(
		"R-L path to leaf",
		[]() {
			LeftBoundaryTraversal tree(10);
			tree.add({20}, {'R'});
			tree.add({20, 15}, {'R', 'L'});
			return tree.traverseLeftBoundary();
		},
		15);

	suite.addTest(
		"Course Example",
		[]() {
			LeftBoundaryTraversal tree(2);
			tree.add({3, 5, 8, 6, 7, 15}, {'L', 'L', 'R', 'R', 'L', 'R'});
			tree.add({13, 8}, {'R', 'L'});
			tree.add({13, 7}, {'R', 'R'});

			return tree.traverseLeftBoundary();
		},
		15);

	suite.run();

	return 0;
}
