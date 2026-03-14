#include "../../include/test_suite.hpp"
#include "../include/bst.hpp"
#include <deque>
#include <limits>
#include <stack>
#include <string>

class FromPreV3 : public BST<FromPreV3> {
  public:
	using BST<FromPreV3>::BST;

	static FromPreV3 *fromPre(const std::deque<int> &pre, int &idx,
							  int min = std::numeric_limits<int>::min(),
							  int max = std::numeric_limits<int>::max()) {
		if (pre.empty())
			return nullptr;

		if (idx >= pre.size()) {
			return nullptr;
		}

		auto data = pre[idx];

		if (data < min || data > max) {
			return nullptr;
		}

		auto root = new FromPreV3(pre[idx++]);

		root->left = fromPre(pre, idx, min, root->data);
		root->right = fromPre(pre, idx, root->data, max);

		return root;
	}
};

static std::string build_inorder_from_pre(const std::deque<int> &pre) {
	int idx = 0;
	FromPreV3 *root = FromPreV3::fromPre(pre, idx);
	if (!root) {
		return "";
	}

	std::string result = root->print_inorder();
	delete root;
	return result;
}

int main() {
	TestSuite<std::string> suite;

	suite.addTest(
		"empty preorder returns nullptr",
		[]() { return build_inorder_from_pre({}); }, "");

	suite.addTest(
		"single node tree", []() { return build_inorder_from_pre({42}); },
		"42 ");

	suite.addTest(
		"balanced-like preorder reconstructs expected bst",
		[]() { return build_inorder_from_pre({8, 4, 2, 6, 12, 10, 14}); },
		"2 4 6 8 10 12 14 ");

	suite.addTest(
		"right skewed preorder",
		[]() { return build_inorder_from_pre({1, 2, 3, 4, 5}); }, "1 2 3 4 5 ");

	suite.addTest(
		"left skewed preorder",
		[]() { return build_inorder_from_pre({5, 4, 3, 2, 1}); }, "1 2 3 4 5 ");

	suite.addTest(
		"Course Example",
		[]() {
			std::deque<int> pre{50, 20, 15, 14, 16, 45, 35, 36, 60, 58, 70, 73};
			return build_inorder_from_pre(pre);
		},
		"14 15 16 20 35 36 45 50 58 60 70 73 ");

	suite.run();
}
