#include "../../include/test_suite.hpp"
#include "../include/bst_with_parent.hpp"

class SuccessorBST : public ParentLinkBST<SuccessorBST> {
  public:
	using ParentLinkBST<SuccessorBST>::ParentLinkBST;
};

int main() {
	TestSuite<std::pair<bool, int>> ts;

	ts.addTest("Target doesn't exist in tree",
			   []() {
				   auto tree = new SuccessorBST(50);
				   tree->insert(30);
				   tree->insert(70);
				   return tree->getSuccessorOf(100);
			   },
			   {false, -1});

	ts.addTest("Single node tree - no successor",
			   []() {
				   SuccessorBST tree(50);
				   return tree.getSuccessorOf(50);
			   },
			   {false, -1});

	ts.addTest("Root with right subtree - successor is min of right",
			   []() {
				   SuccessorBST tree(50);
				   tree.insert(30);
				   tree.insert(70);
				   tree.insert(60);
				   tree.insert(80);
				   return tree.getSuccessorOf(50);
			   },
			   {true, 60});

	ts.addTest("Node without right subtree - successor is ancestor",
			   []() {
				   SuccessorBST tree(50);
				   tree.insert(30);
				   tree.insert(70);
				   tree.insert(20);
				   tree.insert(40);
				   return tree.getSuccessorOf(40);
			   },
			   {true, 50});

	ts.addTest("Maximum value - no successor",
			   []() {
				   SuccessorBST tree(50);
				   tree.insert(30);
				   tree.insert(70);
				   tree.insert(80);
				   return tree.getSuccessorOf(80);
			   },
			   {false, -1});

	ts.addTest("Minimum value - has successor",
			   []() {
				   SuccessorBST tree(50);
				   tree.insert(30);
				   tree.insert(70);
				   tree.insert(20);
				   return tree.getSuccessorOf(20);
			   },
			   {true, 30});

	ts.addTest("Left child with no right subtree",
			   []() {
				   SuccessorBST tree(50);
				   tree.insert(30);
				   tree.insert(20);
				   return tree.getSuccessorOf(30);
			   },
			   {true, 50});

	ts.addTest("Right child with no right subtree",
			   []() {
				   SuccessorBST tree(50);
				   tree.insert(70);
				   tree.insert(60);
				   return tree.getSuccessorOf(60);
			   },
			   {true, 70});

	ts.addTest("Leaf node - left position",
			   []() {
				   SuccessorBST tree(50);
				   tree.insert(30);
				   tree.insert(70);
				   tree.insert(20);
				   tree.insert(40);
				   tree.insert(60);
				   tree.insert(80);
				   return tree.getSuccessorOf(40);
			   },
			   {true, 50});

	ts.addTest("Leaf node - right position",
			   []() {
				   SuccessorBST tree(50);
				   tree.insert(30);
				   tree.insert(70);
				   tree.insert(20);
				   tree.insert(40);
				   tree.insert(60);
				   tree.insert(80);
				   return tree.getSuccessorOf(60);
			   },
			   {true, 70});

	ts.addTest("Right skewed tree",
			   []() {
				   SuccessorBST tree(10);
				   tree.insert(20);
				   tree.insert(30);
				   tree.insert(40);
				   return tree.getSuccessorOf(20);
			   },
			   {true, 30});

	ts.addTest("Left skewed tree",
			   []() {
				   SuccessorBST tree(40);
				   tree.insert(30);
				   tree.insert(20);
				   tree.insert(10);
				   return tree.getSuccessorOf(10);
			   },
			   {true, 20});

	ts.addTest("Node with both children",
			   []() {
				   SuccessorBST tree(50);
				   tree.insert(30);
				   tree.insert(70);
				   tree.insert(25);
				   tree.insert(40);
				   tree.insert(60);
				   tree.insert(80);
				   return tree.getSuccessorOf(30);
			   },
			   {true, 40});

	ts.addTest("Deep left descendant - successor is far ancestor",
			   []() {
				   SuccessorBST tree(50);
				   tree.insert(30);
				   tree.insert(70);
				   tree.insert(20);
				   tree.insert(40);
				   tree.insert(35);
				   tree.insert(45);
				   return tree.getSuccessorOf(45);
			   },
			   {true, 50});

	ts.addTest("Root with complex structure",
			   []() {
				   SuccessorBST tree(50);
				   tree.insert(30);
				   tree.insert(70);
				   tree.insert(20);
				   tree.insert(40);
				   tree.insert(60);
				   tree.insert(80);
				   tree.insert(55);
				   return tree.getSuccessorOf(50);
			   },
			   {true, 55});

	ts.addTest("Rightmost in left subtree",
			   []() {
				   SuccessorBST tree(50);
				   tree.insert(30);
				   tree.insert(70);
				   tree.insert(20);
				   tree.insert(40);
				   tree.insert(35);
				   tree.insert(45);
				   tree.insert(48);
				   return tree.getSuccessorOf(48);
			   },
			   {true, 50});

	ts.addTest("Leftmost in right subtree",
			   []() {
				   SuccessorBST tree(50);
				   tree.insert(30);
				   tree.insert(70);
				   tree.insert(60);
				   tree.insert(80);
				   tree.insert(55);
				   tree.insert(52);
				   return tree.getSuccessorOf(52);
			   },
			   {true, 55});

	ts.addTest("Sequential values",
			   []() {
				   SuccessorBST tree(5);
				   tree.insert(3);
				   tree.insert(7);
				   tree.insert(6);
				   tree.insert(8);
				   return tree.getSuccessorOf(6);
			   },
			   {true, 7});

	ts.addTest("Large gap in values",
			   []() {
				   SuccessorBST tree(100);
				   tree.insert(50);
				   tree.insert(200);
				   tree.insert(25);
				   tree.insert(75);
				   return tree.getSuccessorOf(75);
			   },
			   {true, 100});

	ts.addTest("Search in two-node tree",
			   []() {
				   SuccessorBST tree(50);
				   tree.insert(30);
				   return tree.getSuccessorOf(30);
			   },
			   {true, 50});

	ts.run();

	return 0;
}
