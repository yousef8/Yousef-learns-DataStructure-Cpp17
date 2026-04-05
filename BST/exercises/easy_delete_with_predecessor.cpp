#include "../../include/test_suite.hpp"
#include "../include/bst.hpp"
#include <iostream>

class DeleteWithPredecessor : public BST<DeleteWithPredecessor> {
  public:
	using BST<DeleteWithPredecessor>::BST;

	void remove(int target) {
		if (target == data && !left && !right)
			return; // can't remove root in this structure
		delete_node(target, this);
	}

	const DeleteWithPredecessor *max() const {
		auto current = this;
		while (current->right)
			current = current->right;
		return current;
	}

  private:
	void special_delete(DeleteWithPredecessor *child) {
		// Instead of deleting node and return its child
		// copy child data and remove him
		// why? as sometimes node is actually the original this
		// Deleting it is RTE
		// This is another complication we pay for our coding style
		// to use only a single class instead of class + struct like linkedlist
		data = child->data;
		left = child->left;
		right = child->right;
		delete child;
	}

	// Delete the target node in the tree and return updated tree
	// Caller use updated tree to re-link with children!
	DeleteWithPredecessor *delete_node(int target,
									   DeleteWithPredecessor *node) {
		if (!node)
			return nullptr;

		if (target < node->data)
			node->left = delete_node(target, node->left);
		else if (target > node->data)
			node->right = delete_node(target, node->right);
		else {
			if (!node->left && !node->right) {
				delete node;
				node = nullptr;
			} else if (!node->right)
				node->special_delete(node->left);
			else if (!node->left)
				node->special_delete(node->right);
			else {
				auto mx = node->left->max(); // predecessor
				node->data = mx->data;
				node->left = delete_node(node->data, node->left);
			}
		}
		return node;
	}
};

DeleteWithPredecessor *createTestTree(const std::vector<int> &values) {
	if (values.empty())
		return nullptr;
	DeleteWithPredecessor *root = new DeleteWithPredecessor(values[0]);
	for (size_t i = 1; i < values.size(); ++i) {
		root->insert(values[i]);
	}
	return root;
}

int main() {
	TestSuite<std::string> suite;

	// ==================== EDGE CASE 1: Remove Leaf Node ====================
	suite.addTest(
		"Remove leaf node (left child)",
		[]() {
			auto tree = createTestTree({10, 5, 15});
			tree->remove(5);
			std::string result = tree->print_inorder();
			tree->clear();
			delete tree;
			return result;
		},
		"10 15 ");

	suite.addTest(
		"Remove leaf node (right child)",
		[]() {
			auto tree = createTestTree({10, 5, 15});
			tree->remove(15);
			std::string result = tree->print_inorder();
			tree->clear();
			delete tree;
			return result;
		},
		"5 10 ");

	// ==================== EDGE CASE 2: Remove Node with One Child
	// ====================
	suite.addTest(
		"Remove node with only left child",
		[]() {
			auto tree = createTestTree({10, 5, 15, 3});
			tree->remove(5);
			std::string result = tree->print_inorder();
			tree->clear();
			delete tree;
			return result;
		},
		"3 10 15 ");

	suite.addTest(
		"Remove node with only right child",
		[]() {
			auto tree = createTestTree({10, 5, 15, 7});
			tree->remove(5);
			std::string result = tree->print_inorder();
			tree->clear();
			delete tree;
			return result;
		},
		"7 10 15 ");

	// ==================== EDGE CASE 3: Remove Node with Two Children
	// (Predecessor) ====================
	suite.addTest(
		"Remove node with two children - predecessor simple",
		[]() {
			auto tree = createTestTree({10, 5, 15, 3, 7});
			tree->remove(5);
			std::string result = tree->print_inorder();
			tree->clear();
			delete tree;
			return result;
		},
		"3 7 10 15 ");

	suite.addTest(
		"Remove node with two children - predecessor complex",
		[]() {
			auto tree = createTestTree({50, 30, 70, 20, 40, 35, 45, 10});
			tree->remove(30);
			std::string result = tree->print_inorder();
			tree->clear();
			delete tree;
			return result;
		},
		"10 20 35 40 45 50 70 ");

	// ==================== EDGE CASE 4: Remove Root Node ====================
	suite.addTest(
		"Remove root node with one left child",
		[]() {
			auto tree = createTestTree({10, 5});
			tree->remove(10);
			std::string result = tree->print_inorder();
			tree->clear();
			delete tree;
			return result;
		},
		"5 ");

	suite.addTest(
		"Remove root node with one right child",
		[]() {
			auto tree = createTestTree({10, 15});
			tree->remove(10);
			std::string result = tree->print_inorder();
			tree->clear();
			delete tree;
			return result;
		},
		"15 ");

	suite.addTest(
		"Remove root node with two children",
		[]() {
			auto tree = createTestTree({10, 5, 15, 3, 7});
			tree->remove(10);
			std::string result = tree->print_inorder();
			tree->clear();
			delete tree;
			return result;
		},
		"3 5 7 15 ");

	// ==================== EDGE CASE 5: Remove Non-existent Value
	// ====================
	suite.addTest(
		"Remove non-existent value from single node tree",
		[]() {
			auto tree = createTestTree({10});
			tree->remove(5);
			std::string result = tree->print_inorder();
			tree->clear();
			delete tree;
			return result;
		},
		"10 ");

	suite.addTest(
		"Remove non-existent value from multi-node tree",
		[]() {
			auto tree = createTestTree({10, 5, 15});
			tree->remove(99);
			std::string result = tree->print_inorder();
			tree->clear();
			delete tree;
			return result;
		},
		"5 10 15 ");

	// ==================== EDGE CASE 6: Remove All Nodes Sequentially
	// ====================
	suite.addTest(
		"Remove all nodes from a tree (sequential removal)",
		[]() {
			auto tree = createTestTree({10, 5, 15});
			tree->remove(5);
			tree->remove(15);
			std::string result = tree->print_inorder();
			tree->clear();
			delete tree;
			return result;
		},
		"10 ");

	// ==================== EDGE CASE 7: Predecessor is Direct Parent
	// ====================
	suite.addTest(
		"Remove node where predecessor is direct parent",
		[]() {
			auto tree = createTestTree({20, 10, 30, 25, 35, 23});
			tree->remove(30);
			std::string result = tree->print_inorder();
			tree->clear();
			delete tree;
			return result;
		},
		"10 20 23 25 35 ");

	// ==================== EDGE CASE 8: Predecessor Has Left Subtree
	// ====================
	suite.addTest(
		"Remove node where predecessor has left subtree",
		[]() {
			auto tree = createTestTree({50, 30, 70, 20, 40, 10, 25});
			tree->remove(30);
			std::string result = tree->print_inorder();
			tree->clear();
			delete tree;
			return result;
		},
		"10 20 25 40 50 70 ");

	std::cout << "\n========== BST DELETE WITH PREDECESSOR - TEST SUITE "
				 "==========\n\n";
	suite.run();

	return 0;
}
