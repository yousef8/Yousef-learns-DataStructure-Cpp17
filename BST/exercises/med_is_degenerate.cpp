#include "../../include/test_suite.hpp"
#include "../include/bst.hpp"
#include <limits>
#include <vector>

class IsDegenerate : public BST<IsDegenerate> {
  public:
	using BST<IsDegenerate>::BST;

	static IsDegenerate *
	constructFromPreorder(const std::vector<int> &preorder) {
		int idx{0};
		return constructFromPreorderHelper(preorder, idx,
										   std::numeric_limits<int>::min(),
										   std::numeric_limits<int>::max());
	}

  private:
	static IsDegenerate *
	constructFromPreorderHelper(const std::vector<int> &preorder, int &idx,
								int min, int max) {
		if (idx >= preorder.size()) {
			return nullptr;
		}

		int value = preorder[idx];
		if (value < min || value > max) {
			return nullptr;
		}

		IsDegenerate *node = new IsDegenerate(value);
		idx++;
		node->left = constructFromPreorderHelper(preorder, idx, min, value - 1);
		node->right =
			constructFromPreorderHelper(preorder, idx, value + 1, max);
		return node;
	};
};

bool is_degenerate(std::vector<int> preorder) {
	IsDegenerate *root = IsDegenerate::constructFromPreorder(preorder);
	bool result = root->height() == preorder.size() - 1;
	delete root;
	return result;
}

int main() {
	TestSuite<bool> suite;

	suite.addTest(
		"25,8,11,13,12 -> true",
		[]() { return is_degenerate({25, 8, 11, 13, 12}); }, true);

	suite.addTest(
		"100,70,101 -> false", []() { return is_degenerate({100, 70, 101}); },
		false);

	suite.addTest(
		"100,70,60,75 -> false",
		[]() { return is_degenerate({100, 70, 60, 75}); }, false);

	suite.addTest(
		"100,70,60,65 -> true",
		[]() { return is_degenerate({100, 70, 60, 65}); }, true);

	suite.addTest(
		"9,8,7,6,5,4,3 -> true",
		[]() { return is_degenerate({9, 8, 7, 6, 5, 4, 3}); }, true);

	suite.addTest(
		"500,400,300,200,250,275,260 -> true",
		[]() { return is_degenerate({500, 400, 300, 200, 250, 275, 260}); },
		true);

	suite.addTest(
		"500,400,300,200,250,275,260,280 -> false",
		[]() {
			return is_degenerate({500, 400, 300, 200, 250, 275, 260, 280});
		},
		false);

	suite.run();
}
