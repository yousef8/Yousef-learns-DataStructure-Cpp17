#include "../../include/test_suite.hpp"
#include "../include/binary_tree.hpp"

class SearchTreeBT : public BinaryTree<SearchTreeBT> {
  public:
	using BinaryTree<SearchTreeBT>::BinaryTree;

	bool isExists(int value) const {
		if (data == value)
			return true;

		if (left && left->isExists(value))
			return true;

		if (right && right->isExists(value))
			return true;

		return false;
	}
};

int main() {
	TestSuite<bool> suite;

	suite.addTest(
		"Single node - value exists",
		[]() {
			SearchTreeBT root(10);
			return root.isExists(10);
		},
		true);

	suite.addTest(
		"Single node - value does not exist",
		[]() {
			SearchTreeBT root(10);
			return root.isExists(5);
		},
		false);

	suite.addTest(
		"Two nodes - value in root",
		[]() {
			SearchTreeBT root(10);
			root.add({5}, {'L'});
			return root.isExists(10);
		},
		true);

	suite.addTest(
		"Two nodes - value in left child",
		[]() {
			SearchTreeBT root(10);
			root.add({5}, {'L'});
			return root.isExists(5);
		},
		true);

	suite.addTest(
		"Two nodes - value in right child",
		[]() {
			SearchTreeBT root(10);
			root.add({15}, {'R'});
			return root.isExists(15);
		},
		true);

	suite.addTest(
		"Two nodes - value does not exist",
		[]() {
			SearchTreeBT root(10);
			root.add({5}, {'L'});
			return root.isExists(20);
		},
		false);

	suite.addTest(
		"Three nodes - root value exists",
		[]() {
			SearchTreeBT root(10);
			root.add({5}, {'L'});
			root.add({15}, {'R'});
			return root.isExists(10);
		},
		true);

	suite.addTest(
		"Three nodes - left value exists",
		[]() {
			SearchTreeBT root(10);
			root.add({5}, {'L'});
			root.add({15}, {'R'});
			return root.isExists(5);
		},
		true);

	suite.addTest(
		"Three nodes - right value exists",
		[]() {
			SearchTreeBT root(10);
			root.add({5}, {'L'});
			root.add({15}, {'R'});
			return root.isExists(15);
		},
		true);

	suite.addTest(
		"Three nodes - value does not exist",
		[]() {
			SearchTreeBT root(10);
			root.add({5}, {'L'});
			root.add({15}, {'R'});
			return root.isExists(20);
		},
		false);

	suite.addTest(
		"Left-skewed tree - value at bottom",
		[]() {
			SearchTreeBT root(10);
			root.add({8}, {'L'});
			root.add({8, 6}, {'L', 'L'});
			root.add({8, 6, 4}, {'L', 'L', 'L'});
			return root.isExists(4);
		},
		true);

	suite.addTest(
		"Left-skewed tree - value in middle",
		[]() {
			SearchTreeBT root(10);
			root.add({8}, {'L'});
			root.add({8, 6}, {'L', 'L'});
			root.add({8, 6, 4}, {'L', 'L', 'L'});
			return root.isExists(6);
		},
		true);

	suite.addTest(
		"Left-skewed tree - value does not exist",
		[]() {
			SearchTreeBT root(10);
			root.add({8}, {'L'});
			root.add({8, 6}, {'L', 'L'});
			root.add({8, 6, 4}, {'L', 'L', 'L'});
			return root.isExists(5);
		},
		false);

	suite.addTest(
		"Right-skewed tree - value at bottom",
		[]() {
			SearchTreeBT root(10);
			root.add({12}, {'R'});
			root.add({12, 14}, {'R', 'R'});
			root.add({12, 14, 16}, {'R', 'R', 'R'});
			return root.isExists(16);
		},
		true);

	suite.addTest(
		"Right-skewed tree - value does not exist",
		[]() {
			SearchTreeBT root(10);
			root.add({12}, {'R'});
			root.add({12, 14}, {'R', 'R'});
			root.add({12, 14, 16}, {'R', 'R', 'R'});
			return root.isExists(15);
		},
		false);

	suite.addTest(
		"Complete tree - value at leaf",
		[]() {
			SearchTreeBT root(10);
			root.add({5}, {'L'});
			root.add({15}, {'R'});
			root.add({5, 3}, {'L', 'L'});
			root.add({5, 7}, {'L', 'R'});
			root.add({15, 12}, {'R', 'L'});
			root.add({15, 20}, {'R', 'R'});
			return root.isExists(20);
		},
		true);

	suite.addTest(
		"Complete tree - value does not exist",
		[]() {
			SearchTreeBT root(10);
			root.add({5}, {'L'});
			root.add({15}, {'R'});
			root.add({5, 3}, {'L', 'L'});
			root.add({5, 7}, {'L', 'R'});
			root.add({15, 12}, {'R', 'L'});
			root.add({15, 20}, {'R', 'R'});
			return root.isExists(25);
		},
		false);

	suite.addTest(
		"Negative values - exists",
		[]() {
			SearchTreeBT root(0);
			root.add({-5}, {'L'});
			root.add({5}, {'R'});
			root.add({-5, -10}, {'L', 'L'});
			return root.isExists(-10);
		},
		true);

	suite.addTest(
		"Negative values - does not exist",
		[]() {
			SearchTreeBT root(0);
			root.add({-5}, {'L'});
			root.add({5}, {'R'});
			root.add({-5, -10}, {'L', 'L'});
			return root.isExists(-3);
		},
		false);

	suite.addTest(
		"Search for zero",
		[]() {
			SearchTreeBT root(10);
			root.add({0}, {'L'});
			root.add({15}, {'R'});
			return root.isExists(0);
		},
		true);

	suite.addTest(
		"Large values - exists",
		[]() {
			SearchTreeBT root(1000);
			root.add({500}, {'L'});
			root.add({2000}, {'R'});
			root.add({2000, 5000}, {'R', 'R'});
			return root.isExists(5000);
		},
		true);

	suite.addTest(
		"Large values - does not exist",
		[]() {
			SearchTreeBT root(1000);
			root.add({500}, {'L'});
			root.add({2000}, {'R'});
			root.add({2000, 5000}, {'R', 'R'});
			return root.isExists(3000);
		},
		false);

	suite.addTest(
		"Deep tree - value at deepest level",
		[]() {
			SearchTreeBT root(1);
			root.add({2}, {'L'});
			root.add({2, 3}, {'L', 'L'});
			root.add({2, 3, 4}, {'L', 'L', 'L'});
			root.add({2, 3, 4, 5}, {'L', 'L', 'L', 'L'});
			root.add({2, 3, 4, 5, 6}, {'L', 'L', 'L', 'L', 'L'});
			return root.isExists(6);
		},
		true);

	suite.addTest(
		"Deep tree - value does not exist",
		[]() {
			SearchTreeBT root(1);
			root.add({2}, {'L'});
			root.add({2, 3}, {'L', 'L'});
			root.add({2, 3, 4}, {'L', 'L', 'L'});
			root.add({2, 3, 4, 5}, {'L', 'L', 'L', 'L'});
			root.add({2, 3, 4, 5, 6}, {'L', 'L', 'L', 'L', 'L'});
			return root.isExists(7);
		},
		false);

	suite.addTest(
		"Zigzag pattern - value exists",
		[]() {
			SearchTreeBT root(1);
			root.add({2}, {'L'});
			root.add({2, 3}, {'L', 'R'});
			root.add({2, 3, 4}, {'L', 'R', 'L'});
			root.add({2, 3, 4, 5}, {'L', 'R', 'L', 'R'});
			return root.isExists(5);
		},
		true);

	suite.addTest(
		"Sparse tree - existing values",
		[]() {
			SearchTreeBT root(10);
			root.add({5}, {'L'});
			root.add({15}, {'R'});
			root.add({5, 2}, {'L', 'L'});
			root.add({15, 20}, {'R', 'R'});
			return root.isExists(20);
		},
		true);

	suite.addTest(
		"Sparse tree - non-existing in gaps",
		[]() {
			SearchTreeBT root(10);
			root.add({5}, {'L'});
			root.add({15}, {'R'});
			root.add({5, 2}, {'L', 'L'});
			root.add({15, 20}, {'R', 'R'});
			return root.isExists(12);
		},
		false);

	suite.addTest(
		"Duplicate values in tree",
		[]() {
			SearchTreeBT root(10);
			root.add({10}, {'L'});
			root.add({10}, {'R'});
			return root.isExists(10);
		},
		true);

	suite.addTest(
		"Only left subtree - existing values",
		[]() {
			SearchTreeBT root(20);
			root.add({10}, {'L'});
			root.add({10, 5}, {'L', 'L'});
			root.add({10, 15}, {'L', 'R'});
			return root.isExists(15);
		},
		true);

	suite.addTest(
		"Only left subtree - non-existing",
		[]() {
			SearchTreeBT root(20);
			root.add({10}, {'L'});
			root.add({10, 5}, {'L', 'L'});
			root.add({10, 15}, {'L', 'R'});
			return root.isExists(25);
		},
		false);

	suite.addTest(
		"Only right subtree - existing values",
		[]() {
			SearchTreeBT root(10);
			root.add({20}, {'R'});
			root.add({20, 15}, {'R', 'L'});
			root.add({20, 25}, {'R', 'R'});
			return root.isExists(25);
		},
		true);

	suite.addTest(
		"Only right subtree - non-existing",
		[]() {
			SearchTreeBT root(10);
			root.add({20}, {'R'});
			root.add({20, 15}, {'R', 'L'});
			root.add({20, 25}, {'R', 'R'});
			return root.isExists(5);
		},
		false);

	suite.addTest(
		"Asymmetric tree - deeper branch",
		[]() {
			SearchTreeBT root(10);
			root.add({5}, {'L'});
			root.add({15}, {'R'});
			root.add({5, 3}, {'L', 'L'});
			root.add({15, 12}, {'R', 'L'});
			root.add({15, 12, 11}, {'R', 'L', 'L'});
			root.add({15, 12, 11, 11}, {'R', 'L', 'L', 'R'});
			return root.isExists(11);
		},
		true);

	suite.addTest(
		"Multiple searches - exists",
		[]() {
			SearchTreeBT root(50);
			root.add({25}, {'L'});
			root.add({75}, {'R'});
			root.add({25, 10}, {'L', 'L'});
			root.add({25, 35}, {'L', 'R'});
			root.add({75, 60}, {'R', 'L'});
			root.add({75, 90}, {'R', 'R'});
			return root.isExists(90);
		},
		true);

	suite.addTest(
		"Multiple searches - does not exist",
		[]() {
			SearchTreeBT root(50);
			root.add({25}, {'L'});
			root.add({75}, {'R'});
			root.add({25, 10}, {'L', 'L'});
			root.add({25, 35}, {'L', 'R'});
			root.add({75, 60}, {'R', 'L'});
			root.add({75, 90}, {'R', 'R'});
			return root.isExists(100);
		},
		false);

	suite.addTest(
		"Course example - exists",
		[]() {
			SearchTreeBT root(2);
			root.add({3}, {'L'});
			root.add({13}, {'R'});
			root.add({13, 7}, {'R', 'L'});
			root.add({13, 8}, {'R', 'R'});
			return root.isExists(13);
		},
		true);

	suite.addTest(
		"Course example - does not exist",
		[]() {
			SearchTreeBT root(2);
			root.add({3}, {'L'});
			root.add({13}, {'R'});
			root.add({13, 7}, {'R', 'L'});
			root.add({13, 8}, {'R', 'R'});
			return root.isExists(70);
		},
		false);

	suite.run();
	return 0;
}
