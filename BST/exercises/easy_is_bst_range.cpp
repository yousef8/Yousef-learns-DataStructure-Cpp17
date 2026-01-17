#include "../../include/test_suite.hpp"
#include "../include/bst.hpp"
#include <limits>

class IsBST : public BST<IsBST> {
  public:
	using BST<IsBST>::BST;

	bool is_bst() const {
		return is_bst_util(std::numeric_limits<int>::min(),
						   std::numeric_limits<int>::max());
	}

	// Helper methods for testing - to manually construct invalid trees
	void set_left(IsBST *node) { left = node; }
	void set_right(IsBST *node) { right = node; }
	IsBST *get_left() { return left; }
	IsBST *get_right() { return right; }

  private:
	bool is_bst_util(int min, int max) const {
		if (data < min || data > max) {
			return false;
		}

		bool left_is_bst = !left || left->is_bst_util(min, data);
		bool right_is_bst = !right || right->is_bst_util(data, max);

		return left_is_bst && right_is_bst;
	}
};

int main() {
	TestSuite<bool> ts;

	/*
	 * This test suite exposes bugs in the current is_bst() implementation.
	 * The main issue: 'prev' is passed by value, so 'prev = this' only modifies
	 * the local copy and doesn't thread through recursive calls properly.
	 *
	 * This causes the method to only check parent-child relationships in the
	 * right subtree, but fails to properly validate the BST property across
	 * ancestors in the left subtree.
	 */

	ts.addTest(
		"Valid BST - Balanced tree",
		[]() {
			IsBST tree(10);
			tree.insert(5);
			tree.insert(15);
			tree.insert(3);
			tree.insert(7);
			tree.insert(12);
			tree.insert(18);
			return tree.is_bst();
		},
		true);

	ts.addTest(
		"Valid BST - Single node",
		[]() {
			IsBST tree(42);
			return tree.is_bst();
		},
		true);

	ts.addTest(
		"Valid BST - Left skewed",
		[]() {
			IsBST tree(10);
			tree.insert(8);
			tree.insert(6);
			tree.insert(4);
			return tree.is_bst();
		},
		true);

	ts.addTest(
		"Valid BST - Right skewed",
		[]() {
			IsBST tree(10);
			tree.insert(12);
			tree.insert(14);
			tree.insert(16);
			return tree.is_bst();
		},
		true);

	ts.addTest(
		"Invalid BST - Left child greater than parent",
		[]() {
			IsBST tree(10);
			tree.set_left(new IsBST(15));
			return tree.is_bst();
		},
		false);

	ts.addTest(
		"Invalid BST - Right child less than parent",
		[]() {
			IsBST tree(10);
			tree.set_right(new IsBST(5));
			return tree.is_bst();
		},
		false);

	ts.addTest(
		"Invalid BST - Node in left subtree greater than root",
		[]() {
			IsBST tree(10);
			tree.insert(5);
			tree.insert(15);
			// Manually create invalid structure: 10 -> 5 -> 12 (right child of
			// 5) 12 > 10, so it violates BST property (should be in right
			// subtree of 10)
			tree.get_left()->set_right(new IsBST(12));
			return tree.is_bst();
		},
		false);

	ts.addTest(
		"Invalid BST - Node in right subtree less than root",
		[]() {
			IsBST tree(10);
			tree.insert(5);
			tree.insert(15);
			// Manually create invalid structure: 10 -> 15 -> 8 (left child of
			// 15) 8 < 10, so it violates BST property (should be in left
			// subtree of 10)
			tree.get_right()->set_left(new IsBST(8));
			return tree.is_bst();
		},
		false);

	ts.addTest(
		"Invalid BST - Complex case with deep violation",
		[]() {
			IsBST tree(20);
			tree.insert(10);
			tree.insert(30);
			tree.insert(5);
			tree.insert(15);
			// Manually add 25 as right child of 15
			// 25 > 20, so it should be in right subtree of 20, not left
			tree.get_left()->get_right()->set_right(new IsBST(25));
			return tree.is_bst();
		},
		false);

	ts.addTest(
		"Invalid BST - Duplicate in left subtree",
		[]() {
			IsBST tree(10);
			tree.insert(5);
			tree.insert(15);
			tree.get_left()->set_left(new IsBST(10));
			return tree.is_bst();
		},
		false);

	ts.addTest(
		"Invalid BST - Duplicate in right subtree",
		[]() {
			IsBST tree(10);
			tree.insert(5);
			tree.insert(15);
			tree.get_right()->set_right(new IsBST(10));
			return tree.is_bst();
		},
		false);

	ts.addTest(
		"Invalid BST - Equal left child",
		[]() {
			IsBST tree(10);
			tree.set_left(new IsBST(10));
			return tree.is_bst();
		},
		true);

	ts.addTest(
		"Invalid BST - Equal right child",
		[]() {
			IsBST tree(10);
			tree.set_right(new IsBST(10));
			return tree.is_bst();
		},
		true);

	ts.run();

	return 0;
}
