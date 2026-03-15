#include "../../include/test_suite.hpp"
#include "../include/bst.hpp"
#include <deque>
#include <limits>
#include <queue>
#include <string>
#include <utility>
#include <vector>

class FromPreV4 : public BST<FromPreV4> {
  public:
	using BST<FromPreV4>::BST;

	static FromPreV4 *fromBFS(const std::deque<int> &bfs) {
		if (bfs.empty()) {
			return nullptr;
		}

		std::queue<std::pair<FromPreV4 *, std::pair<int, int>>> q;

		auto root = new FromPreV4(bfs[0]);

		q.push({root,
				{std::numeric_limits<int>::min(),
				 std::numeric_limits<int>::max()}});

		auto size = bfs.size();

		for (int i{1}; i < size; ++i) {
			auto [node, bounds] = q.front();

			if (bfs[i] > bounds.first && bfs[i] < bounds.second) {
				if (bfs[i] < node->data) {
					if (node->left) {
						q.pop();
						--i;
						continue;
					};

					node->left = new FromPreV4(bfs[i]);
					q.push({node->left, {bounds.first, node->data}});
				} else {
					q.pop();
					node->right = new FromPreV4(bfs[i]);
					q.push({node->right, {node->data, bounds.second}});
				}
			} else {
				q.pop();
				--i;
			}
		}

		return root;
	}

	std::vector<int> inOrder() {
		std::vector<int> result;
		inOrderHelper(result);
		return result;
	}

	std::vector<int> levelOrder() {
		std::vector<int> result;
		std::queue<FromPreV4 *> q;
		q.push(this);

		while (!q.empty()) {
			auto *node = q.front();
			q.pop();
			result.push_back(node->data);

			if (node->left)
				q.push(node->left);
			if (node->right)
				q.push(node->right);
		}

		return result;
	}

  private:
	void inOrderHelper(std::vector<int> &result) {
		if (left)
			left->inOrderHelper(result);
		result.push_back(data);
		if (right)
			right->inOrderHelper(result);
	}
};

bool isSorted(const std::vector<int> &v) {
	for (size_t i = 1; i < v.size(); ++i) {
		if (v[i] < v[i - 1])
			return false;
	}
	return true;
}

bool vectorsEqual(const std::vector<int> &a, const std::vector<int> &b) {
	if (a.size() != b.size())
		return false;
	for (size_t i = 0; i < a.size(); ++i) {
		if (a[i] != b[i])
			return false;
	}
	return true;
}

bool validateTree(FromPreV4 *tree, const std::deque<int> &inputBFS) {
	if (inputBFS.empty()) {
		return tree == nullptr;
	}

	if (!tree)
		return false;

	auto inorder = tree->inOrder();
	if (!isSorted(inorder))
		return false;

	auto levelOrder = tree->levelOrder();
	std::vector<int> inputAsVector(inputBFS.begin(), inputBFS.end());
	if (!vectorsEqual(levelOrder, inputAsVector))
		return false;

	return true;
}

int main() {
	TestSuite<bool> suite;

	suite.addTest(
		"Empty input returns nullptr",
		[]() {
			auto tree = FromPreV4::fromBFS({});
			return tree == nullptr;
		},
		true);

	suite.addTest(
		"Single node: {5}",
		[]() {
			auto tree = FromPreV4::fromBFS({5});
			return validateTree(tree, {5});
		},
		true);

	suite.addTest(
		"Two nodes left: {5, 3}",
		[]() {
			auto tree = FromPreV4::fromBFS({5, 3});
			return validateTree(tree, {5, 3});
		},
		true);

	suite.addTest(
		"Two nodes right: {5, 7}",
		[]() {
			auto tree = FromPreV4::fromBFS({5, 7});
			return validateTree(tree, {5, 7});
		},
		true);

	suite.addTest(
		"Perfect BST: {5, 3, 7, 2, 4, 6, 8}",
		[]() {
			auto tree = FromPreV4::fromBFS({5, 3, 7, 2, 4, 6, 8});
			return validateTree(tree, {5, 3, 7, 2, 4, 6, 8});
		},
		true);

	suite.addTest(
		"Left-skewed: {10, 5, 3, 1}",
		[]() {
			auto tree = FromPreV4::fromBFS({10, 5, 3, 1});
			return validateTree(tree, {10, 5, 3, 1});
		},
		true);

	suite.addTest(
		"Right-skewed: {1, 5, 10, 15}",
		[]() {
			auto tree = FromPreV4::fromBFS({1, 5, 10, 15});
			return validateTree(tree, {1, 5, 10, 15});
		},
		true);

	suite.addTest(
		"Complex mixed: {50, 30, 70, 20, 40, 60, 80}",
		[]() {
			auto tree = FromPreV4::fromBFS({50, 30, 70, 20, 40, 60, 80});
			return validateTree(tree, {50, 30, 70, 20, 40, 60, 80});
		},
		true);

	suite.addTest(
		"With negatives: {0, -5, 5, -10, -2, 3, 7}",
		[]() {
			auto tree = FromPreV4::fromBFS({0, -5, 5, -10, -2, 3, 7});
			return validateTree(tree, {0, -5, 5, -10, -2, 3, 7});
		},
		true);

	suite.addTest(
		"Larger tree: {50, 25, 75, 12, 37, 62, 87, 6, 18, 31, 43}",
		[]() {
			auto tree =
				FromPreV4::fromBFS({50, 25, 75, 12, 37, 62, 87, 6, 18, 31, 43});
			return validateTree(tree,
								{50, 25, 75, 12, 37, 62, 87, 6, 18, 31, 43});
		},
		true);

	suite.addTest(
		"Only left subtree: {10, 5, 2, 1}",
		[]() {
			auto tree = FromPreV4::fromBFS({10, 5, 2, 1});
			return validateTree(tree, {10, 5, 2, 1});
		},
		true);

	suite.addTest(
		"Unbalanced: {7, 3, 11, 1, 5, 9, 15, 0, 2}",
		[]() {
			auto tree = FromPreV4::fromBFS({7, 3, 11, 1, 5, 9, 15, 0, 2});
			return validateTree(tree, {7, 3, 11, 1, 5, 9, 15, 0, 2});
		},
		true);

	suite.addTest(
		"Three nodes right: {1, 2, 3}",
		[]() {
			auto tree = FromPreV4::fromBFS({1, 2, 3});
			return validateTree(tree, {1, 2, 3});
		},
		true);

	suite.addTest(
		"Three nodes left: {3, 2, 1}",
		[]() {
			auto tree = FromPreV4::fromBFS({3, 2, 1});
			return validateTree(tree, {3, 2, 1});
		},
		true);

	suite.addTest(
		"Large value range: {1000, 500, 1500, 250, 750}",
		[]() {
			auto tree = FromPreV4::fromBFS({1000, 500, 1500, 250, 750});
			return validateTree(tree, {1000, 500, 1500, 250, 750});
		},
		true);

	suite.run();

	return 0;
}
