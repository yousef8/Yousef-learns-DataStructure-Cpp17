#include "../../include/test_suite.hpp"
#include "../include/bst.hpp"
#include <iostream>

class DeleteSuccessorLocally : public BST<DeleteSuccessorLocally> {
  public:
	using BST<DeleteSuccessorLocally>::BST;

	void remove(int target) {
		if (target == data && !left && !right)
			return; // can't remove root in this structure
		delete_node(target, this);
	}

	DeleteSuccessorLocally *min() {
		auto cur = this;
		while (cur && cur->left)
			cur = cur->left;
		return cur;
	}

  private:
	void special_delete(DeleteSuccessorLocally *child) {
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
	DeleteSuccessorLocally *delete_node(int target,
										DeleteSuccessorLocally *node) {
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
				auto mn = node->right->min();
				node->data = mn->data; // copy & go delete
				// node->right = delete_node(node->data, node->right);
				// we know mn has no left child, so we can delete it locally
				// without recursion
				if (mn->right) {
					mn->data = mn->right->data;
					delete mn->right;
					mn->right = nullptr;
				} else {
					auto parent = node->get_node_parent(mn, node);
					if (parent == node) {
						node->right = nullptr;
					} else {
						parent->left = nullptr;
					}
					delete mn;
					mn = nullptr;
				}
			}
		}
		return node;
	}

	DeleteSuccessorLocally *get_node_parent(DeleteSuccessorLocally *target,
											DeleteSuccessorLocally *node) {
		if (!node)
			return nullptr;
		if (node->left == target || node->right == target)
			return node;
		if (target->data < node->data)
			return get_node_parent(target, node->left);
		else
			return get_node_parent(target, node->right);
	}
};

int main() {
	TestSuite<std::string> suite;

	suite.addTest(
		"Remove leaf node (left)",
		[]() {
			auto root = DeleteSuccessorLocally{10, 5, 15, 3, 7};
			std::string before = root.print_inorder();
			root.remove(3);
			return root.print_inorder();
		},
		"5 7 10 15 ");

	suite.addTest(
		"Remove leaf node (right)",
		[]() {
			auto root = DeleteSuccessorLocally{10, 5, 15, 3, 7, 12, 20};
			root.remove(20);
			return root.print_inorder();
		},
		"3 5 7 10 12 15 ");

	suite.addTest(
		"Remove node with only left child",
		[]() {
			auto root = DeleteSuccessorLocally{10, 5, 15, 3, 7, 6};
			root.remove(7);
			return root.print_inorder();
		},
		"3 5 6 10 15 ");

	suite.addTest(
		"Remove node with only right child",
		[]() {
			auto root = DeleteSuccessorLocally{10, 5, 15, 3, 7, 8};
			root.remove(7);
			return root.print_inorder();
		},
		"3 5 8 10 15 ");

	suite.addTest(
		"Remove node with two children",
		[]() {
			auto root = DeleteSuccessorLocally{10, 5, 15, 3, 7, 12, 20};
			root.remove(5);
			return root.print_inorder();
		},
		"3 7 10 12 15 20 ");

	suite.addTest(
		"Remove root with two children",
		[]() {
			auto root = DeleteSuccessorLocally{10, 5, 15, 3, 7, 12, 20};
			root.remove(10);
			return root.print_inorder();
		},
		"3 5 7 12 15 20 ");

	suite.addTest(
		"Root leaf cannot be removed",
		[]() {
			auto root = DeleteSuccessorLocally{10};
			root.remove(10);
			return root.print_inorder();
		},
		"10 ");

	suite.addTest(
		"Remove non-existent value (no effect)",
		[]() {
			auto root = DeleteSuccessorLocally{10, 5, 15};
			root.remove(999);
			return root.print_inorder();
		},
		"5 10 15 ");

	suite.addTest(
		"Multiple sequential removals",
		[]() {
			auto root = DeleteSuccessorLocally{10, 5, 15, 3, 7, 12, 20};
			root.remove(3);
			root.remove(12);
			root.remove(20);
			return root.print_inorder();
		},
		"5 7 10 15 ");

	suite.addTest(
		"Remove all leaf nodes",
		[]() {
			auto root = DeleteSuccessorLocally{10, 5, 15};
			root.remove(5);
			root.remove(15);
			return root.print_inorder();
		},
		"10 ");

	suite.addTest(
		"Remove from right subtree",
		[]() {
			auto root = DeleteSuccessorLocally{10, 5, 15, 12, 20};
			root.remove(15);
			return root.print_inorder();
		},
		"5 10 12 20 ");

	suite.addTest(
		"Remove node with complex right subtree",
		[]() {
			auto root = DeleteSuccessorLocally{10, 5, 20, 15, 25, 12, 17};
			root.remove(20);
			return root.print_inorder();
		},
		"5 10 12 15 17 25 ");

	suite.addTest(
		"Remove uses inorder successor correctly",
		[]() {
			auto root = DeleteSuccessorLocally{50, 30, 70, 20, 40, 60, 80};
			root.remove(30);
			return root.print_inorder();
		},
		"20 40 50 60 70 80 ");

	suite.addTest(
		"BST property maintained after removal",
		[]() {
			auto root = DeleteSuccessorLocally{50, 30, 70, 20, 40, 60,
											   80, 10, 25, 35, 45};
			root.remove(30);
			return root.print_inorder();
		},
		"10 20 25 35 40 45 50 60 70 80 ");

	suite.addTest(
		"Remove sequence leaves only root",
		[]() {
			auto root = DeleteSuccessorLocally{10, 5, 15, 3, 7, 12, 20};
			root.remove(3);
			root.remove(7);
			root.remove(5);
			root.remove(12);
			root.remove(20);
			root.remove(15);
			return root.print_inorder();
		},
		"10 ");

	suite.run();
	return 0;
}
