#include "../../include/test_suite.hpp"
#include "../include/bst.hpp"

class IterativeSearchBST : public BST<IterativeSearchBST> {
  public:
	using BST<IterativeSearchBST>::BST;

	bool search_iterative(int value) const {

		auto current = this;

		while (current) {
			if (value == current->data) {
				return true;
			}

			if (value < current->data)
				current = current->left;
			else
				current = current->right;
		}

		return false;
	}
};

int main() {
	TestSuite<bool> suite;

	suite.addTest(
		"Single node: search for root value",
		[]() {
			IterativeSearchBST tree(10);
			return tree.search_iterative(10);
		},
		true);

	suite.addTest(
		"Single node: search for smaller value",
		[]() {
			IterativeSearchBST tree(10);
			return tree.search_iterative(5);
		},
		false);

	suite.addTest(
		"Single node: search for larger value",
		[]() {
			IterativeSearchBST tree(10);
			return tree.search_iterative(15);
		},
		false);

	suite.addTest(
		"Multi-node tree: search for root",
		[]() {
			IterativeSearchBST tree(50);
			tree.insert(30);
			tree.insert(70);
			tree.insert(20);
			tree.insert(40);
			return tree.search_iterative(50);
		},
		true);

	suite.addTest(
		"Multi-node tree: search for left child",
		[]() {
			IterativeSearchBST tree(50);
			tree.insert(30);
			tree.insert(70);
			return tree.search_iterative(30);
		},
		true);

	suite.addTest(
		"Multi-node tree: search for right child",
		[]() {
			IterativeSearchBST tree(50);
			tree.insert(30);
			tree.insert(70);
			return tree.search_iterative(70);
		},
		true);

	suite.addTest(
		"Deep left node search",
		[]() {
			IterativeSearchBST tree(50);
			tree.insert(30);
			tree.insert(20);
			tree.insert(10);
			tree.insert(5);
			return tree.search_iterative(5);
		},
		true);

	suite.addTest(
		"Deep right node search",
		[]() {
			IterativeSearchBST tree(50);
			tree.insert(70);
			tree.insert(80);
			tree.insert(90);
			tree.insert(100);
			return tree.search_iterative(100);
		},
		true);

	suite.addTest(
		"Balanced tree: left subtree leaf",
		[]() {
			IterativeSearchBST tree(50);
			tree.insert(30);
			tree.insert(70);
			tree.insert(20);
			tree.insert(40);
			tree.insert(60);
			tree.insert(80);
			return tree.search_iterative(20);
		},
		true);

	suite.addTest(
		"Balanced tree: right subtree leaf",
		[]() {
			IterativeSearchBST tree(50);
			tree.insert(30);
			tree.insert(70);
			tree.insert(20);
			tree.insert(40);
			tree.insert(60);
			tree.insert(80);
			return tree.search_iterative(80);
		},
		true);

	suite.addTest(
		"Non-existent: smaller than minimum",
		[]() {
			IterativeSearchBST tree(50);
			tree.insert(30);
			tree.insert(70);
			tree.insert(20);
			return tree.search_iterative(10);
		},
		false);

	suite.addTest(
		"Non-existent: larger than maximum",
		[]() {
			IterativeSearchBST tree(50);
			tree.insert(30);
			tree.insert(70);
			tree.insert(80);
			return tree.search_iterative(100);
		},
		false);

	suite.addTest(
		"Non-existent: value between existing nodes",
		[]() {
			IterativeSearchBST tree(50);
			tree.insert(30);
			tree.insert(70);
			tree.insert(40);
			return tree.search_iterative(35);
		},
		false);

	suite.addTest(
		"Left-heavy tree: search deep left node",
		[]() {
			IterativeSearchBST tree(100);
			tree.insert(80);
			tree.insert(60);
			tree.insert(40);
			tree.insert(20);
			tree.insert(10);
			return tree.search_iterative(10);
		},
		true);

	suite.addTest(
		"Left-heavy tree: search non-existent",
		[]() {
			IterativeSearchBST tree(100);
			tree.insert(80);
			tree.insert(60);
			tree.insert(40);
			tree.insert(20);
			return tree.search_iterative(50);
		},
		false);

	suite.addTest(
		"Right-heavy tree: search deep right node",
		[]() {
			IterativeSearchBST tree(10);
			tree.insert(20);
			tree.insert(30);
			tree.insert(40);
			tree.insert(50);
			tree.insert(60);
			return tree.search_iterative(60);
		},
		true);

	suite.addTest(
		"Right-heavy tree: search non-existent",
		[]() {
			IterativeSearchBST tree(10);
			tree.insert(20);
			tree.insert(30);
			tree.insert(40);
			tree.insert(50);
			return tree.search_iterative(35);
		},
		false);

	suite.addTest(
		"Complex tree: search middle-level node",
		[]() {
			IterativeSearchBST tree(50);
			tree.insert(30);
			tree.insert(70);
			tree.insert(20);
			tree.insert(40);
			tree.insert(60);
			tree.insert(80);
			tree.insert(35);
			tree.insert(45);
			return tree.search_iterative(35);
		},
		true);

	suite.addTest(
		"Left subtree, right branch",
		[]() {
			IterativeSearchBST tree(50);
			tree.insert(30);
			tree.insert(70);
			tree.insert(40);
			tree.insert(45);
			return tree.search_iterative(45);
		},
		true);

	suite.addTest(
		"Right subtree, left branch",
		[]() {
			IterativeSearchBST tree(50);
			tree.insert(30);
			tree.insert(70);
			tree.insert(60);
			tree.insert(55);
			return tree.search_iterative(55);
		},
		true);

	suite.addTest(
		"Zigzag: left-right-left pattern",
		[]() {
			IterativeSearchBST tree(50);
			tree.insert(30);
			tree.insert(40);
			tree.insert(35);
			return tree.search_iterative(35);
		},
		true);

	suite.addTest(
		"Zigzag: right-left-right pattern",
		[]() {
			IterativeSearchBST tree(50);
			tree.insert(70);
			tree.insert(60);
			tree.insert(65);
			return tree.search_iterative(65);
		},
		true);

	suite.addTest(
		"Large tree: search existing node",
		[]() {
			IterativeSearchBST tree(50);
			for (int i :
				 {25, 75, 12, 37, 62, 87, 6, 18, 31, 43, 56, 68, 81, 93}) {
				tree.insert(i);
			}
			return tree.search_iterative(31);
		},
		true);

	suite.addTest(
		"Large tree: search non-existent node",
		[]() {
			IterativeSearchBST tree(50);
			for (int i :
				 {25, 75, 12, 37, 62, 87, 6, 18, 31, 43, 56, 68, 81, 93}) {
				tree.insert(i);
			}
			return tree.search_iterative(99);
		},
		false);

	suite.addTest(
		"After duplicate insertion attempt",
		[]() {
			IterativeSearchBST tree(50);
			tree.insert(30);
			tree.insert(30);
			tree.insert(70);
			return tree.search_iterative(30);
		},
		true);

	suite.run();

	return 0;
}
