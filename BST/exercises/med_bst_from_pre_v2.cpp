#include "../../include/test_suite.hpp"
#include "../include/bst.hpp"
#include <deque>
#include <stack>
#include <string>

class FromPreV2 : public BST<FromPreV2> {
  public:
	using BST<FromPreV2>::BST;

	static std::vector<int> getNextGreaterIdxes(const std::deque<int> &vals) {
		std::stack<int> stk;
		std::vector<int> next_idxes(vals.size(), -1);

		for (int i = vals.size() - 1; i >= 0; --i) {
			while (!stk.empty() && vals[stk.top()] <= vals[i]) {
				stk.pop();
			}

			if (!stk.empty()) {
				next_idxes[i] = stk.top();
			}

			stk.push(i);
		}

		return next_idxes;
		;
	}

	static FromPreV2 *fromPre(const std::deque<int> &pre,
							  std::vector<int> next_idxes = {}, int start = 0,
							  int end = -1) {
		if (pre.empty()) {
			return nullptr;
		}

		if (end == -1) {
			end = pre.size() - 1;
		}

		if (next_idxes.empty()) {
			next_idxes = getNextGreaterIdxes(pre);
		}

		if (start > end) {
			return nullptr;
		}

		auto root = new FromPreV2(pre[start]);

		if (next_idxes[start] != -1) {
			root->left =
				fromPre(pre, next_idxes, start + 1, next_idxes[start] - 1);
			root->right = fromPre(pre, next_idxes, next_idxes[start], end);
		} else {
			root->left = fromPre(pre, next_idxes, start + 1, end);
			root->right = nullptr;
		}

		return root;
	}
};

static std::string build_inorder_from_pre(const std::deque<int> &pre) {
	FromPreV2 *root = FromPreV2::fromPre(pre);
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

	return 0;
}
