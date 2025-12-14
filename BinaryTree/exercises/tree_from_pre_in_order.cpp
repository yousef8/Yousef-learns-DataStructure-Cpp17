#include "../../include/test_suite.hpp"
#include "../include/binary_tree.hpp"
#include <deque>

class GenerateFromPreAndIn : public BinaryTree<GenerateFromPreAndIn> {
  public:
	using BinaryTree<GenerateFromPreAndIn>::BinaryTree;

	std::deque<int> preOrderDeque() const {
		std::deque<int> result{};

		result.push_back(data);

		if (left) {
			auto leftResult = left->preOrderDeque();
			result.insert(result.end(), leftResult.begin(), leftResult.end());
		}

		if (right) {
			auto rightResult = right->preOrderDeque();
			result.insert(result.end(), rightResult.begin(), rightResult.end());
		}

		return result;
	}

	std::deque<int> inOrderDeque() const {
		std::deque<int> result{};

		if (left) {
			auto leftResult = left->inOrderDeque();
			result.insert(result.end(), leftResult.begin(), leftResult.end());
		}

		result.push_back(data);

		if (right) {
			auto rightResult = right->inOrderDeque();
			result.insert(result.end(), rightResult.begin(), rightResult.end());
		}

		return result;
	}

	GenerateFromPreAndIn(std::deque<int> &preOrder, std::deque<int> &inOrder)
		: BinaryTree<GenerateFromPreAndIn>(0) {
		if (preOrder.empty() || inOrder.empty()) {
			throw std::invalid_argument("Invalid preorder or inorder sequence");
		}

		auto root = preOrder.front();
		this->data = root;
		preOrder.pop_front();

		std::deque<int> leftInOrder;
		std::deque<int> rightInOrder;

		while (inOrder.front() != root) {
			leftInOrder.push_back(inOrder.front());
			inOrder.pop_front();
		}

		inOrder.pop_front();

		while (!inOrder.empty()) {
			rightInOrder.push_back(inOrder.front());
			inOrder.pop_front();
		}

		if (!leftInOrder.empty()) {
			this->left = new GenerateFromPreAndIn(preOrder, leftInOrder);
		}

		if (!rightInOrder.empty()) {
			this->right = new GenerateFromPreAndIn(preOrder, rightInOrder);
		}
	};
};

int main() {
	TestSuite<bool> constructorTests;

	// Helper lambda to test constructor
	auto testConstruction = [](std::deque<int> preOrder,
							   std::deque<int> inOrder) -> bool {
		// Save copies before passing to constructor (which may mutate them)
		std::deque<int> expectedPre = preOrder;
		std::deque<int> expectedIn = inOrder;

		auto tree = new GenerateFromPreAndIn(preOrder, inOrder);
		auto resultPre = tree->preOrderDeque();

		auto resultIn = tree->inOrderDeque();
		delete tree;
		return resultPre == expectedPre && resultIn == expectedIn;
	};

	constructorTests.addTest(
		"Course Example",
		[&]() -> bool {
			return testConstruction(
				std::deque<int>{1, 2, 4, 7, 8, 5, 9, 3, 6, 10},
				std::deque<int>{7, 4, 8, 2, 5, 9, 1, 3, 10, 6});
		},
		true);

	constructorTests.addTest(
		"Single node tree",
		[&]() -> bool {
			return testConstruction(std::deque<int>{1}, std::deque<int>{1});
		},
		true);

	// Test 2: Left-skewed tree (1 -> 2 -> 3)
	//     1
	//    /
	//   2
	//  /
	// 3
	constructorTests.addTest(
		"Left-skewed tree",
		[&]() -> bool {
			return testConstruction(std::deque<int>{1, 2, 3},
									std::deque<int>{3, 2, 1});
		},
		true);

	// Test 3: Right-skewed tree
	// 1
	//  \
	//   2
	//    \
	//     3
	constructorTests.addTest(
		"Right-skewed tree",
		[&]() -> bool {
			return testConstruction(std::deque<int>{1, 2, 3},
									std::deque<int>{1, 2, 3});
		},
		true);

	// Test 4: Simple balanced tree
	//     2
	//    / \
	//   1   3
	constructorTests.addTest(
		"Simple balanced tree",
		[&]() -> bool {
			return testConstruction(std::deque<int>{2, 1, 3},
									std::deque<int>{1, 2, 3});
		},
		true);

	// Test 5: Complete binary tree
	//          1
	//        /   \
	//       2     3
	//      / \   / \
	//     4   5 6   7
	constructorTests.addTest(
		"Complete binary tree",
		[&]() -> bool {
			return testConstruction(std::deque<int>{1, 2, 4, 5, 3, 6, 7},
									std::deque<int>{4, 2, 5, 1, 6, 3, 7});
		},
		true);

	// Test 6: Tree with only left children at first level, then right
	//     1
	//    /
	//   2
	//    \
	//     3
	constructorTests.addTest(
		"Zigzag tree (left then right)",
		[&]() -> bool {
			return testConstruction(std::deque<int>{1, 2, 3},
									std::deque<int>{2, 3, 1});
		},
		true);

	// Test 7: Tree with only right child at first level, then left
	//   1
	//    \
	//     2
	//    /
	//   3
	constructorTests.addTest(
		"Zigzag tree (right then left)",
		[&]() -> bool {
			return testConstruction(std::deque<int>{1, 2, 3},
									std::deque<int>{1, 3, 2});
		},
		true);

	// Test 8: Tree with negative numbers
	//        -5
	//       /  \
	//      0    10
	//     /      \
	//   -2        15
	constructorTests.addTest(
		"Tree with negative numbers",
		[&]() -> bool {
			return testConstruction(std::deque<int>{-5, 0, -2, 10, 15},
									std::deque<int>{-2, 0, -5, 10, 15});
		},
		true);

	// Test 9: Larger balanced tree
	//            4
	//         /     \
	//        2       6
	//       / \     / \
	//      1   3   5   7
	constructorTests.addTest(
		"Larger balanced tree",
		[&]() -> bool {
			return testConstruction(std::deque<int>{4, 2, 1, 3, 6, 5, 7},
									std::deque<int>{1, 2, 3, 4, 5, 6, 7});
		},
		true);

	// Test 10: Tree with duplicate-like structure (all same except root)
	//      5
	//     / \
	//    3   8
	//   /
	//  1
	constructorTests.addTest(
		"Unbalanced tree with left-heavy subtree",
		[&]() -> bool {
			return testConstruction(std::deque<int>{5, 3, 1, 8},
									std::deque<int>{1, 3, 5, 8});
		},
		true);

	// Test 11: Tree with right-heavy subtree
	//    1
	//     \
	//      3
	//     / \
	//    2   4
	constructorTests.addTest(
		"Tree with right-heavy subtree",
		[&]() -> bool {
			return testConstruction(std::deque<int>{1, 3, 2, 4},
									std::deque<int>{1, 2, 3, 4});
		},
		true);

	// Test 12: Deep zigzag pattern
	//    1
	//   /
	//  2
	//   \
	//    3
	//   /
	//  4
	constructorTests.addTest(
		"Deep zigzag pattern",
		[&]() -> bool {
			return testConstruction(std::deque<int>{1, 2, 3, 4},
									std::deque<int>{2, 4, 3, 1});
		},
		true);

	// Test 13: Large values
	constructorTests.addTest(
		"Large values",
		[&]() -> bool {
			return testConstruction(std::deque<int>{1000, 500, 1500},
									std::deque<int>{500, 1000, 1500});
		},
		true);

	// Test 14: Two nodes - left child only
	//   2
	//  /
	// 1
	constructorTests.addTest(
		"Two nodes - left child only",
		[&]() -> bool {
			return testConstruction(std::deque<int>{2, 1},
									std::deque<int>{1, 2});
		},
		true);

	// Test 15: Two nodes - right child only
	// 1
	//  \
	//   2
	constructorTests.addTest(
		"Two nodes - right child only",
		[&]() -> bool {
			return testConstruction(std::deque<int>{1, 2},
									std::deque<int>{1, 2});
		},
		true);

	constructorTests.run();
	return 0;
}
