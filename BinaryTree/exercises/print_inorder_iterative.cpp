#include "../../include/test_suite.hpp"
#include "../include/binary_tree.hpp"
#include <iostream>
#include <stack>
#include <string>

class InorderIterativeBT : public BinaryTree<InorderIterativeBT> {
  public:
	using BinaryTree<InorderIterativeBT>::BinaryTree;

	std::string printInOrderIterative() const {
		std::stack<InorderIterativeBT *> stk;

		auto current = static_cast<const InorderIterativeBT *>(this);
		stk.push(const_cast<InorderIterativeBT *>(current));
		std::string res{};

		while (!stk.empty()) {
			if (current && current->left) {
				stk.push(current->left);
				current = current->left;
				continue;
			}
			current = nullptr;
			auto node = stk.top();
			stk.pop();

			res.append(std::to_string(node->data) + " ");

			if (node->right) {
				stk.push(node->right);
				current = node->right;
				continue;
			}
		}

		if (!res.empty()) {
			res.pop_back();
		}

		return res;
	}
};

void test_print_inorder_iterative() {

	TestSuite<std::string> suite;

	suite.addTest(
		"Single node tree",
		[]() {
			InorderIterativeBT root(1);
			return root.printInOrderIterative();
		},
		"1");

	suite.addTest(
		"Two nodes - left child only",
		[]() {
			InorderIterativeBT root(2);
			root.add({1}, {'L'});
			return root.printInOrderIterative();
		},
		"1 2");

	suite.addTest(
		"Two nodes - right child only",
		[]() {
			InorderIterativeBT root(1);
			root.add({2}, {'R'});
			return root.printInOrderIterative();
		},
		"1 2");

	suite.addTest(
		"Three nodes - complete tree",
		[]() {
			InorderIterativeBT root(2);
			root.add({1}, {'L'});
			root.add({3}, {'R'});
			return root.printInOrderIterative();
		},
		"1 2 3");

	suite.addTest(
		"Left-skewed tree",
		[]() {
			InorderIterativeBT root(5);
			root.add({4}, {'L'});
			root.add({4, 3}, {'L', 'L'});
			root.add({4, 3, 2}, {'L', 'L', 'L'});
			root.add({4, 3, 2, 1}, {'L', 'L', 'L', 'L'});
			return root.printInOrderIterative();
		},
		"1 2 3 4 5");

	suite.addTest(
		"Right-skewed tree",
		[]() {
			InorderIterativeBT root(1);
			root.add({2}, {'R'});
			root.add({2, 3}, {'R', 'R'});
			root.add({2, 3, 4}, {'R', 'R', 'R'});
			root.add({2, 3, 4, 5}, {'R', 'R', 'R', 'R'});
			return root.printInOrderIterative();
		},
		"1 2 3 4 5");

	suite.addTest(
		"Complete binary tree (7 nodes)",
		[]() {
			InorderIterativeBT root(4);
			root.add({2}, {'L'});
			root.add({6}, {'R'});
			root.add({2, 1}, {'L', 'L'});
			root.add({2, 3}, {'L', 'R'});
			root.add({6, 5}, {'R', 'L'});
			root.add({6, 7}, {'R', 'R'});
			return root.printInOrderIterative();
		},
		"1 2 3 4 5 6 7");

	suite.addTest(
		"Balanced tree with 15 nodes",
		[]() {
			InorderIterativeBT root(8);
			root.add({4}, {'L'});
			root.add({12}, {'R'});
			root.add({4, 2}, {'L', 'L'});
			root.add({4, 6}, {'L', 'R'});
			root.add({12, 10}, {'R', 'L'});
			root.add({12, 14}, {'R', 'R'});
			root.add({4, 2, 1}, {'L', 'L', 'L'});
			root.add({4, 2, 3}, {'L', 'L', 'R'});
			root.add({4, 6, 5}, {'L', 'R', 'L'});
			root.add({4, 6, 7}, {'L', 'R', 'R'});
			root.add({12, 10, 9}, {'R', 'L', 'L'});
			root.add({12, 10, 11}, {'R', 'L', 'R'});
			root.add({12, 14, 13}, {'R', 'R', 'L'});
			root.add({12, 14, 15}, {'R', 'R', 'R'});
			return root.printInOrderIterative();
		},
		"1 2 3 4 5 6 7 8 9 10 11 12 13 14 15");

	suite.addTest(
		"Unbalanced tree - left heavy",
		[]() {
			InorderIterativeBT root(10);
			root.add({5}, {'L'});
			root.add({15}, {'R'});
			root.add({5, 3}, {'L', 'L'});
			root.add({5, 7}, {'L', 'R'});
			root.add({5, 3, 1}, {'L', 'L', 'L'});
			root.add({5, 3, 4}, {'L', 'L', 'R'});
			root.add({5, 7, 6}, {'L', 'R', 'L'});
			root.add({5, 7, 8}, {'L', 'R', 'R'});
			return root.printInOrderIterative();
		},
		"1 3 4 5 6 7 8 10 15");

	suite.addTest(
		"Unbalanced tree - right heavy",
		[]() {
			InorderIterativeBT root(5);
			root.add({3}, {'L'});
			root.add({10}, {'R'});
			root.add({10, 8}, {'R', 'L'});
			root.add({10, 15}, {'R', 'R'});
			root.add({10, 15, 12}, {'R', 'R', 'L'});
			root.add({10, 15, 20}, {'R', 'R', 'R'});
			return root.printInOrderIterative();
		},
		"3 5 8 10 12 15 20");

	suite.addTest(
		"Zigzag pattern (left-right-left-right)",
		[]() {
			InorderIterativeBT root(1);
			root.add({2}, {'L'});
			root.add({2, 3}, {'L', 'R'});
			root.add({2, 3, 4}, {'L', 'R', 'L'});
			root.add({2, 3, 4, 5}, {'L', 'R', 'L', 'R'});
			return root.printInOrderIterative();
		},
		"2 4 5 3 1");

	suite.addTest(
		"Zigzag pattern (right-left-right-left)",
		[]() {
			InorderIterativeBT root(5);
			root.add({4}, {'R'});
			root.add({4, 3}, {'R', 'L'});
			root.add({4, 3, 2}, {'R', 'L', 'R'});
			root.add({4, 3, 2, 1}, {'R', 'L', 'R', 'L'});
			return root.printInOrderIterative();
		},
		"5 3 1 2 4");

	suite.addTest(
		"Tree with selective left children",
		[]() {
			InorderIterativeBT root(4);
			root.add({2}, {'L'});
			root.add({5}, {'R'});
			root.add({2, 1}, {'L', 'L'});
			root.add({5, 3}, {'R', 'L'});
			return root.printInOrderIterative();
		},
		"1 2 4 3 5");

	suite.addTest(
		"Tree with selective right children",
		[]() {
			InorderIterativeBT root(3);
			root.add({2}, {'L'});
			root.add({5}, {'R'});
			root.add({2, 4}, {'L', 'R'});
			root.add({5, 6}, {'R', 'R'});
			return root.printInOrderIterative();
		},
		"2 4 3 5 6");

	suite.addTest(
		"Deep left branch with right nodes",
		[]() {
			InorderIterativeBT root(10);
			root.add({5}, {'L'});
			root.add({5, 3}, {'L', 'L'});
			root.add({5, 3, 1}, {'L', 'L', 'L'});
			root.add({5, 8}, {'L', 'R'});
			root.add({15}, {'R'});
			return root.printInOrderIterative();
		},
		"1 3 5 8 10 15");

	suite.addTest(
		"Sparse tree",
		[]() {
			InorderIterativeBT root(8);
			root.add({4}, {'L'});
			root.add({12}, {'R'});
			root.add({4, 2}, {'L', 'L'});
			root.add({12, 10}, {'R', 'L'});
			root.add({4, 2, 1}, {'L', 'L', 'L'});
			root.add({4, 2, 3}, {'L', 'L', 'R'});
			return root.printInOrderIterative();
		},
		"1 2 3 4 8 10 12");

	suite.addTest(
		"Very deep left-skewed tree",
		[]() {
			InorderIterativeBT root(10);
			root.add({9}, {'L'});
			root.add({9, 8}, {'L', 'L'});
			root.add({9, 8, 7}, {'L', 'L', 'L'});
			root.add({9, 8, 7, 6}, {'L', 'L', 'L', 'L'});
			root.add({9, 8, 7, 6, 5}, {'L', 'L', 'L', 'L', 'L'});
			root.add({9, 8, 7, 6, 5, 4}, {'L', 'L', 'L', 'L', 'L', 'L'});
			root.add({9, 8, 7, 6, 5, 4, 3},
					 {'L', 'L', 'L', 'L', 'L', 'L', 'L'});
			root.add({9, 8, 7, 6, 5, 4, 3, 2},
					 {'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L'});
			root.add({9, 8, 7, 6, 5, 4, 3, 2, 1},
					 {'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L'});
			return root.printInOrderIterative();
		},
		"1 2 3 4 5 6 7 8 9 10");

	suite.addTest(
		"Mixed structure tree",
		[]() {
			InorderIterativeBT root(7);
			root.add({3}, {'L'});
			root.add({11}, {'R'});
			root.add({3, 1}, {'L', 'L'});
			root.add({3, 5}, {'L', 'R'});
			root.add({3, 5, 4}, {'L', 'R', 'L'});
			root.add({3, 5, 6}, {'L', 'R', 'R'});
			root.add({11, 9}, {'R', 'L'});
			root.add({11, 9, 8}, {'R', 'L', 'L'});
			root.add({11, 9, 10}, {'R', 'L', 'R'});
			root.add({11, 13}, {'R', 'R'});
			root.add({11, 13, 12}, {'R', 'R', 'L'});
			return root.printInOrderIterative();
		},
		"1 3 4 5 6 7 8 9 10 11 12 13");

	suite.addTest(
		"Deep left, shallow right",
		[]() {
			InorderIterativeBT root(5);
			root.add({2}, {'L'});
			root.add({6}, {'R'});
			root.add({2, 1}, {'L', 'L'});
			root.add({2, 1, 0}, {'L', 'L', 'L'});
			root.add({2, 3}, {'L', 'R'});
			root.add({2, 3, 4}, {'L', 'R', 'R'});
			return root.printInOrderIterative();
		},
		"0 1 2 3 4 5 6");

	suite.addTest(
		"Shallow left, deep right",
		[]() {
			InorderIterativeBT root(5);
			root.add({4}, {'L'});
			root.add({8}, {'R'});
			root.add({8, 6}, {'R', 'L'});
			root.add({8, 6, 7}, {'R', 'L', 'R'});
			root.add({8, 10}, {'R', 'R'});
			root.add({8, 10, 9}, {'R', 'R', 'L'});
			root.add({8, 10, 11}, {'R', 'R', 'R'});
			return root.printInOrderIterative();
		},
		"4 5 6 7 8 9 10 11");

	suite.run();
}

int main() {
	test_print_inorder_iterative();
	return 0;
}
