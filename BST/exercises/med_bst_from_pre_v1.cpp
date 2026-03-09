#include "../../include/test_suite.hpp"
#include "../include/bst.hpp"
#include <deque>
#include <string>

class FromPreV1 : public BST<FromPreV1> {
  public:
	using BST<FromPreV1>::BST;

	static FromPreV1 *fromPre(const std::deque<int> &pre) {
		if (pre.empty()) {
			return nullptr;
		}

		auto it = pre.begin();

		FromPreV1 *root = new FromPreV1(*it++);
		for (; it != pre.end(); ++it) {
			root->insert(*it);
		}
		return root;
	}
};

static std::string build_inorder_from_pre(const std::deque<int> &pre) {
	FromPreV1 *root = FromPreV1::fromPre(pre);
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
		"duplicates are ignored by insert semantics",
		[]() { return build_inorder_from_pre({8, 5, 5, 5, 10, 10, 2}); },
		"2 5 8 10 ");

	suite.run();
}
