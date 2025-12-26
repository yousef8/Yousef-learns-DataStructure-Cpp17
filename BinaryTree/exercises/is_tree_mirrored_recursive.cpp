#include "../../include/test_suite.hpp"
#include "../include/binary_tree.hpp"

class MirroredTree : public BinaryTree<MirroredTree> {
  public:
	using BinaryTree<MirroredTree>::BinaryTree;

	bool isMirror() const { return isMirror(this->left, this->right); }

  private:
	static bool isMirror(const MirroredTree *left, const MirroredTree *right) {
		if (!left && !right) {
			return true;
		}
		if (!left || !right) {
			return false;
		}
		return (left->data == right->data) &&
			   isMirror(left->left, right->right) &&
			   isMirror(left->right, right->left);
	}
};

int main() {
	TestSuite<bool> ts;

	ts.addTest(
		"full mirrored tree",
		[]() {
			MirroredTree tree(1);
			tree.add({2, 3}, {'L', 'L'});
			tree.add({2, 4}, {'L', 'R'});
			tree.add({2, 4}, {'R', 'L'});
			tree.add({2, 3}, {'R', 'R'});
			return tree.isMirror();
		},
		true);

	ts.addTest(
		"not mirrored tree",
		[]() {
			MirroredTree tree(1);
			tree.add({2, 3}, {'L', 'L'});
			tree.add({2, 4}, {'L', 'R'});
			tree.add({2, 5}, {'R', 'L'});
			tree.add({2, 3}, {'R', 'R'});
			return tree.isMirror();
		},
		false);

	ts.addTest(
		"2 level with non-equal values",
		[]() {
			MirroredTree tree(1);
			tree.add({2}, {'L'});
			tree.add({3}, {'R'});
			return tree.isMirror();
		},
		false);

	ts.addTest(
		"single node tree",
		[]() {
			MirroredTree tree(1);
			return tree.isMirror();
		},
		true);

	ts.addTest(
		"Not complete un mirrored tree",
		[]() {
			MirroredTree tree(1);
			tree.add({2}, {'L'});
			tree.add({2}, {'R'});
			tree.add({2, 3}, {'L', 'R'});
			tree.add({2, 3}, {'R', 'R'});
			return tree.isMirror();
		},
		false);

	ts.run();

	return 0;
}