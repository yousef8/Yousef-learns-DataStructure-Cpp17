#include "../../include/test_suite.hpp"
#include "../include/bst.hpp"
#include <deque>
#include <string>
#include <vector>

class QueryAncestorsBST : public BST<QueryAncestorsBST> {
  public:
	using BST<QueryAncestorsBST>::BST;
	void getSuccessorsOf(std::deque<int> &ancestors,
						 std::deque<int> &successors) const {
		std::vector<const QueryAncestorsBST *> traversal;
		getSuccessorsOf(ancestors, successors, traversal);
	};

  private:
	void
	getSuccessorsOf(std::deque<int> &ancestors, std::deque<int> &successors,
					std::vector<const QueryAncestorsBST *> &traversal) const {
		traversal.push_back(this);

		if (left && ancestors.front() < data) {
			left->getSuccessorsOf(ancestors, successors, traversal);
		}

		if (!ancestors.empty() && ancestors.front() == data) {
			if (right) {
				auto min = right->min();
				successors.push_back(min->data);
			} else {
				int res = -1;
				for (auto it = traversal.rbegin(); it != traversal.rend();
					 ++it) {
					if ((*it)->data > data) {
						res = (*it)->data;
						break;
					}
				}
				successors.push_back(res);
			}
			ancestors.pop_front();
		}

		if (ancestors.empty()) {
			traversal.pop_back();
			return;
		}

		if (right && ancestors.front() > data) {
			right->getSuccessorsOf(ancestors, successors, traversal);
		}

		traversal.pop_back();
	};
};

/*
 * Helper function to format deque output for test results
 */
std::string formatDeque(const std::deque<int> &d) {
	std::string result = "[";
	for (size_t i = 0; i < d.size(); ++i) {
		result += std::to_string(d[i]);
		if (i < d.size() - 1)
			result += ", ";
	}
	result += "]";
	return result;
}

int main() {
	TestSuite<std::deque<int>> ts;
	ts.setFormatter([](const std::deque<int> &d) { return formatDeque(d); });

	ts.addTest("Single Node: No Successor",
			   []() {
				   QueryAncestorsBST tree{5};
				   auto targets = std::deque<int>{5};
				   auto successors = std::deque<int>{};
				   tree.getSuccessorsOf(targets, successors);
				   return successors;
			   },
			   {-1});

	ts.addTest("Two Nodes: Root has Successor",
			   []() {
				   QueryAncestorsBST tree{5, 10};
				   auto targets = std::deque<int>{5};
				   auto successors = std::deque<int>{};
				   tree.getSuccessorsOf(targets, successors);
				   return successors;
			   },
			   {10});

	ts.addTest("Two Nodes: Right Child has No Successor",
			   []() {
				   QueryAncestorsBST tree{5, 10};
				   auto targets = std::deque<int>{10};
				   auto successors = std::deque<int>{};
				   tree.getSuccessorsOf(targets, successors);
				   return successors;
			   },
			   {-1});

	// ============= EDGE CASE 3: Two Nodes (Root and Left Child)
	// =============
	ts.addTest("Two Nodes (Left): Child has Successor",
			   []() {
				   QueryAncestorsBST tree{10, 5};
				   auto targets = std::deque<int>{5};
				   auto successors = std::deque<int>{};
				   tree.getSuccessorsOf(targets, successors);
				   return successors;
			   },
			   {10});

	// ============= EDGE CASE 4: Balanced Tree with Multiple Levels
	// ============= Tree structure:
	//        10
	//       /  \
	//      5    15
	//     / \   / \
	//    3   7 12  20
	// Inorder: 3, 5, 7, 10, 12, 15, 20
	ts.addTest("Balanced Tree: Leftmost Node Successor",
			   []() {
				   QueryAncestorsBST tree{10, 5, 15, 3, 7, 12, 20};
				   auto targets = std::deque<int>{3};
				   auto successors = std::deque<int>{};
				   tree.getSuccessorsOf(targets, successors);
				   return successors;
			   },
			   {5});

	ts.addTest("Balanced Tree: Root Node Successor",
			   []() {
				   QueryAncestorsBST tree{10, 5, 15, 3, 7, 12, 20};
				   auto targets = std::deque<int>{10};
				   auto successors = std::deque<int>{};
				   tree.getSuccessorsOf(targets, successors);
				   return successors;
			   },
			   {12});

	ts.addTest("Balanced Tree: Rightmost Node (No Successor)",
			   []() {
				   QueryAncestorsBST tree{10, 5, 15, 3, 7, 12, 20};
				   auto targets = std::deque<int>{20};
				   auto successors = std::deque<int>{};
				   tree.getSuccessorsOf(targets, successors);
				   return successors;
			   },
			   {-1});

	ts.addTest("Balanced Tree: Node with Right Subtree",
			   []() {
				   QueryAncestorsBST tree{10, 5, 15, 3, 7, 12, 20};
				   auto targets = std::deque<int>{5};
				   auto successors = std::deque<int>{};
				   tree.getSuccessorsOf(targets, successors);
				   return successors;
			   },
			   {7});

	ts.addTest("Balanced Tree: Node with No Right Child (Left Ancestor)",
			   []() {
				   QueryAncestorsBST tree{10, 5, 15, 3, 7, 12, 20};
				   auto targets = std::deque<int>{7};
				   auto successors = std::deque<int>{};
				   tree.getSuccessorsOf(targets, successors);
				   return successors;
			   },
			   {10});

	ts.addTest("Balanced Tree: Node at Right Subtree with No Right Child",
			   []() {
				   QueryAncestorsBST tree{10, 5, 15, 3, 7, 12, 20};
				   auto targets = std::deque<int>{12};
				   auto successors = std::deque<int>{};
				   tree.getSuccessorsOf(targets, successors);
				   return successors;
			   },
			   {15});

	ts.addTest("Multiple Targets in Inorder: Ascending Sequence",
			   []() {
				   QueryAncestorsBST tree{10, 5, 15, 3, 7, 12, 20};
				   auto targets = std::deque<int>{3, 5, 7};
				   auto successors = std::deque<int>{};
				   tree.getSuccessorsOf(targets, successors);
				   return successors;
			   },
			   {5, 7, 10});

	ts.addTest("Multiple Targets: Ascending (Sorted)",
			   []() {
				   QueryAncestorsBST tree{10, 5, 15, 3, 7, 12, 20};
				   auto targets = std::deque<int>{10, 15, 20};
				   auto successors = std::deque<int>{};
				   tree.getSuccessorsOf(targets, successors);
				   return successors;
			   },
			   {12, 20, -1});

	ts.addTest("Multiple Targets: Sorted (Mixed Successors)",
			   []() {
				   QueryAncestorsBST tree{10, 5, 15, 3, 7, 12, 20};
				   auto targets = std::deque<int>{3, 5, 12, 20};
				   auto successors = std::deque<int>{};
				   tree.getSuccessorsOf(targets, successors);
				   return successors;
			   },
			   {5, 7, 15, -1});

	// ============= EDGE CASE 8: Skewed Tree (Right) =============
	// Tree structure:
	//    1
	//     \
	//      2
	//       \
	//        3
	//         \
	//          4
	// Inorder: 1, 2, 3, 4
	ts.addTest("Skewed Tree (Right): All have Successors except Last",
			   []() {
				   QueryAncestorsBST tree{1, 2, 3, 4};
				   auto targets = std::deque<int>{1, 2, 3};
				   auto successors = std::deque<int>{};
				   tree.getSuccessorsOf(targets, successors);
				   return successors;
			   },
			   {2, 3, 4});

	ts.addTest("Skewed Tree (Right): Last Node (No Successor)",
			   []() {
				   QueryAncestorsBST tree{1, 2, 3, 4};
				   auto targets = std::deque<int>{4};
				   auto successors = std::deque<int>{};
				   tree.getSuccessorsOf(targets, successors);
				   return successors;
			   },
			   {-1});

	// ============= EDGE CASE 9: Skewed Tree (Left) =============
	// Tree structure:
	//        4
	//       /
	//      3
	//     /
	//    2
	//   /
	//  1
	// Inorder: 1, 2, 3, 4
	ts.addTest("Skewed Tree (Left): Node with No Right Child (Ancestor)",
			   []() {
				   QueryAncestorsBST tree{4, 3, 2, 1};

				   auto targets = std::deque<int>{1, 2};
				   auto successors = std::deque<int>{};
				   tree.getSuccessorsOf(targets, successors);
				   return successors;
			   },
			   {2, 3});

	ts.addTest("Skewed Tree (Left): Root (No Successor)",
			   []() {
				   QueryAncestorsBST tree{4, 3, 2, 1};
				   auto targets = std::deque<int>{4};
				   auto successors = std::deque<int>{};
				   tree.getSuccessorsOf(targets, successors);
				   return successors;
			   },
			   {-1});

	// ============= EDGE CASE 10: Complex Tree - Multiple Levels
	// ============= Tree structure:
	//         50
	//        /  \
	//       30   70
	//      / \   / \
	//    20  40 60  80
	//   /         \
	//  10          75
	// Inorder: 10, 20, 30, 40, 50, 60, 70, 75, 80
	ts.addTest("Complex Tree: Deep Left Node",
			   []() {
				   QueryAncestorsBST tree{50, 30, 70, 20, 40, 60, 80, 10, 75};
				   auto targets = std::deque<int>{10};
				   auto successors = std::deque<int>{};
				   tree.getSuccessorsOf(targets, successors);
				   return successors;
			   },
			   {20});

	ts.addTest("Complex Tree: Middle Node",
			   []() {
				   QueryAncestorsBST tree{50, 30, 70, 20, 40, 60, 80, 10, 75};
				   auto targets = std::deque<int>{40};
				   auto successors = std::deque<int>{};
				   tree.getSuccessorsOf(targets, successors);
				   return successors;
			   },
			   {50});

	ts.addTest(
		"Complex Tree: Node with Right Subtree but No Direct Right Child",
		[]() {
			QueryAncestorsBST tree{50, 30, 70, 20, 40, 60, 80, 10, 75};
			auto targets = std::deque<int>{70};
			auto successors = std::deque<int>{};
			tree.getSuccessorsOf(targets, successors);
			return successors;
		},
		{75});

	ts.addTest("All Nodes as Targets: Complete Successor Chain",
			   []() {
				   QueryAncestorsBST tree{10, 5, 15, 3, 7, 12, 20};
				   auto targets = std::deque<int>{3, 5, 7, 10, 12, 15, 20};
				   auto successors = std::deque<int>{};
				   tree.getSuccessorsOf(targets, successors);
				   return successors;
			   },
			   {5, 7, 10, 12, 15, 20, -1});

	ts.addTest("Three Nodes: Left to Right Successors",
			   []() {
				   QueryAncestorsBST tree{10, 5, 15};
				   auto targets = std::deque<int>{5, 10, 15};
				   auto successors = std::deque<int>{};
				   tree.getSuccessorsOf(targets, successors);
				   return successors;
			   },
			   {10, 15, -1});

	ts.run();
	return 0;
}
