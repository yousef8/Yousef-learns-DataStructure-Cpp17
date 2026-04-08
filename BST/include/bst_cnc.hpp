#ifndef BST_CNC_HPP
#define BST_CNC_HPP

#include <queue>
#include <stdexcept>
#include <string>

class BST {
  public:
	BST() : root(nullptr) {}

	void insert(int val) { root = insert(root, val); }

	bool search(int val) const { return search(root, val); }

	int min() const {
		if (!root)
			throw std::runtime_error("Tree is empty");

		auto node = min_node(root);

		return node->data;
	}

	void remove(int val) { root = delete_node(root, val); }

	std::string inorder_traversal() const {
		std::string result;
		inorder_traversal(root, result);
		result.pop_back();
		return result;
	}

	std::string level_order_traversal() const {
		std::string res{};

		if (!root)
			return res;

		std::queue<BinaryNode *> q;
		q.push(root);

		while (!q.empty()) {
			auto node = q.front();
			q.pop();

			res += std::to_string(node->data) + " ";

			if (node->left)
				q.push(node->left);
			if (node->right)
				q.push(node->right);
		}

		res.pop_back();
		return res;
	}

	~BST() { delete root; }

  private:
	struct BinaryNode {
		int data;
		BinaryNode *left;
		BinaryNode *right;

		BinaryNode(int val) : data(val), left(nullptr), right(nullptr) {}
		~BinaryNode() {
			if (left) {
				delete left;
				left = nullptr;
			}
			if (right) {
				delete right;
				right = nullptr;
			}
		}
	};
	BinaryNode *root;

	BinaryNode *insert(BinaryNode *node, int val) {
		if (!node)
			return new BinaryNode(val);

		if (val < node->data)
			node->left = insert(node->left, val);
		else if (val > node->data)
			node->right = insert(node->right, val);

		return node;
	}

	const BinaryNode *min_node(const BinaryNode *node) const {
		if (!node)
			return nullptr;

		while (node->left)
			node = node->left;
		return node;
	}

	BinaryNode *delete_node(BinaryNode *root, int target) {
		if (!root)
			return nullptr;

		if (target < root->data)
			root->left = delete_node(root->left, target);

		if (target > root->data)
			root->right = delete_node(root->right, target);

		if (target != root->data)
			return root;

		if (!root->left && !root->right) {
			delete root;
			return nullptr;
		}

		if (!root->left) {
			auto temp = root->right;
			root->right = nullptr; // Detach the right child before deletion
			delete root;
			return temp;
		}

		if (!root->right) {
			auto temp = root->left;
			root->left = nullptr; // Detach the left child before deletion
			delete root;
			return temp;
		}

		auto mn = min_node(root->right);
		root->data = mn->data;
		root->right = delete_node(root->right, mn->data);
		return root;
	}

	bool search(BinaryNode *node, int val) const {
		if (!node)
			return false;

		if (val == node->data)
			return true;
		else if (val < node->data)
			return search(node->left, val);
		else
			return search(node->right, val);
	}

	void inorder_traversal(BinaryNode *root, std::string &res) const {
		if (!root)
			return;

		inorder_traversal(root->left, res);

		res += std::to_string(root->data) + " ";

		inorder_traversal(root->right, res);
	}
};

#endif
