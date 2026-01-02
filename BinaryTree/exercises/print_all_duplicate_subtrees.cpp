#include "../../include/test_suite.hpp"
#include "../include/binary_tree.hpp"
#include <iostream>
#include <string>
#include <unordered_map>

class DuplicateSubtreeFinder : public BinaryTree<DuplicateSubtreeFinder> {
  public:
	using BinaryTree<DuplicateSubtreeFinder>::BinaryTree;

	/*
	 * This different from leetcode problem, we return any subtree that has at
	 * least 2 nodes and appeared at least twice
	 */
	std::vector<std::string> findDuplicateSubtrees() const {
		std::vector<std::string> duplicates;
		std::unordered_map<std::string, int> subtreeCount;

		serializeAndCount(const_cast<DuplicateSubtreeFinder *>(this),
						  subtreeCount);
		for (const auto &entry : subtreeCount) {
			if (entry.second > 1) {
				duplicates.push_back(entry.first);
			}
		}
		return duplicates;
	}

  private:
	static void
	serializeAndCount(DuplicateSubtreeFinder *root,
					  std::unordered_map<std::string, int> &subtreeCount) {
		if (!root)
			return;

		if (root->left) {
			serializeAndCount(root->left, subtreeCount);
		}

		if (root->right) {
			serializeAndCount(root->right, subtreeCount);
		}

		if (!root->left && !root->right) {
			return;
		}

		subtreeCount[serialize(root)]++;
	}

	static std::string serialize(DuplicateSubtreeFinder *root) {
		std::string repr = "(" + std::to_string(root->data);

		if (root->left) {
			repr += serialize(root->left);
		} else {
			repr += "()";
		}

		if (root->right) {
			repr += serialize(root->right);
		} else {
			repr += "()";
		}

		repr += ")";
		return repr;
	}
};

int main() {
	TestSuite<std::vector<std::string>> suite;

	// Custom formatter for vector<string>
	suite.setFormatter([](const std::vector<std::string> &v) {
		std::string result = "[";
		for (size_t i = 0; i < v.size(); ++i) {
			result += v[i];
			if (i < v.size() - 1)
				result += ", ";
		}
		result += "]";
		return result;
	});

	suite.addTest(
		"Single node tree - no duplicates",
		[]() {
			DuplicateSubtreeFinder tree(1);
			return tree.findDuplicateSubtrees();
		},
		std::vector<std::string>{});

	suite.addTest(
		"Tree with no duplicates",
		[]() {
			DuplicateSubtreeFinder tree(1);
			tree.add({2, 3, 4, 5}, {'L', 'R', 'L', 'R'});
			return tree.findDuplicateSubtrees();
		},
		std::vector<std::string>{});

	suite.addTest(
		"Mirror tree - identical left and right subtrees",
		[]() {
			DuplicateSubtreeFinder tree(1);
			// Left subtree: 1->L->2, 1->L->R->3
			tree.add({2, 3}, {'L', 'R'});
			// Right subtree: 1->R->2, 1->R->R->3 (same structure)
			tree.add({2, 3}, {'R', 'R'});
			return tree.findDuplicateSubtrees();
		},
		std::vector<std::string>{"(2()(3()()))"});

	suite.addTest(
		"Duplicate subtrees at different levels",
		[]() {
			DuplicateSubtreeFinder tree(1);
			//       1
			//      / \
			//     2   3
			//    /     \
			//   4       4
			//  / \     / \
			// 5   6   5   6
			tree.add({2, 4, 5}, {'L', 'L', 'L'});
			tree.add({2, 4, 6}, {'L', 'L', 'R'});
			tree.add({3, 4, 5}, {'R', 'R', 'L'});
			tree.add({3, 4, 6}, {'R', 'R', 'R'});
			return tree.findDuplicateSubtrees();
		},
		std::vector<std::string>{
			"(4(5()())(6()()))"}); // Nodes 5, 6, and subtree 4 are duplicated

	suite.addTest(
		"Multiple different duplicate subtrees",
		[]() {
			DuplicateSubtreeFinder tree(1);
			//       1
			//      / \
			//     2   2  (duplicate subtrees at depth 1)
			//    / \ / \
			//   3  4 3  4 (duplicate subtrees at depth 2)
			tree.add({2, 3}, {'L', 'L'});
			tree.add({2, 4}, {'L', 'R'});
			tree.add({2, 3}, {'R', 'L'});
			tree.add({2, 4}, {'R', 'R'});
			return tree.findDuplicateSubtrees();
		},
		std::vector<std::string>{"(2(3()())(4()()))"});

	suite.addTest(
		"Duplicate single nodes should not be counted",
		[]() {
			DuplicateSubtreeFinder tree(1);
			//     1
			//    / \
			//   2   2 (leaf nodes - only 1 node each, should NOT be counted)
			tree.add({2}, {'L'});
			tree.add({2}, {'R'});
			return tree.findDuplicateSubtrees();
		},
		std::vector<std::string>{});

	suite.addTest(
		"Complex tree with mixed duplicate patterns",
		[]() {
			DuplicateSubtreeFinder tree(1);
			//          1
			//        /   \
			//       2     2     (duplicate subtrees at depth 1)
			//      / \   / \
			//     3   4 3   5  (node 3 duplicated, node 4 and 5 unique)
			//    /     /
			//   6     6        (node 6 duplicated)
			tree.add({2, 3, 6}, {'L', 'L', 'L'});
			tree.add({2, 4}, {'L', 'R'});
			tree.add({2, 3, 6}, {'R', 'L', 'L'});
			tree.add({2, 5}, {'R', 'R'});
			return tree.findDuplicateSubtrees();
		},
		std::vector<std::string>{
			"(3(6()())())",
		});

	suite.addTest(
		"Course Example",
		[]() {
			DuplicateSubtreeFinder tree(1);
			//          1
			//        /   \
			//       2     4
			//      /    /  \
			//     3    2    5
			//         /   /  \
			//        3   6    6
			//           / \   / \
			//          7   8  7   8
			//               \      \
			//				  8	     8
			tree.add({2, 3}, {'L', 'L'});
			tree.add({4, 2, 3}, {'R', 'L', 'L'});
			tree.add({4, 5, 6, 7}, {'R', 'R', 'L', 'L'});
			tree.add({4, 5, 6, 8, 8}, {'R', 'R', 'L', 'R', 'R'});
			tree.add({4, 5, 6, 7}, {'R', 'R', 'R', 'L'});
			tree.add({4, 5, 6, 8, 8}, {'R', 'R', 'R', 'R', 'R'});
			return tree.findDuplicateSubtrees();
		},
		std::vector<std::string>{
			"(6(7()())(8()(8()())))",
			"(8()(8()()))",
			"(2(3()())())",
		});

	suite.run();
	return 0;
}
