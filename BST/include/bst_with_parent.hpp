#include "../../include/test_suite.hpp"
#include "../include/bst.hpp"

template <typename Derived> class ParentLinkBST {
  public:
	ParentLinkBST(int data, Derived *parent = nullptr)
		: data{data}, parent{parent} {}

	std::string print_inorder() const {
		std::string result;
		if (left)
			result += left->print_inorder();
		result += std::to_string(data) + " ";
		if (right)
			result += right->print_inorder();
		return result;
	}

	void insert(int target) {
		if (target < data) {
			if (!left) {
				left = new Derived(target, static_cast<Derived *>(this));
			} else {
				left->insert(target);
			}
		} else if (target > data) {
			if (!right) {
				right = new Derived(target, static_cast<Derived *>(this));
			} else {
				right->insert(target);
			}
		}
	}

	int minValue() const {
		auto current = static_cast<const Derived *>(this);
		while (current->left) {
			current = current->left;
		}
		return current->data;
	}

	const Derived *search(int target) const {
		if (target == data)
			return static_cast<const Derived *>(this);

		if (left && target < data)
			return left->search(target);

		if (right && target > data)
			return right->search(target);

		return nullptr;
	}

	std::pair<bool, int> getSuccessorOf(int target) const {
		auto node = this->search(target);
		if (!node) {
			return std::make_pair(false, -1);
		}

		if (node->right) {
			return std::make_pair(true, node->right->minValue());
		}

		auto parent = node->parent;
		auto child = node;
		while (parent && parent->right == child) {
			child = parent;
			parent = parent->parent;
		}

		if (parent)
			return std::make_pair(true, parent->data);

		return std::make_pair(false, -1);
	}

	int getData() const { return data; }

	void clear() {
		if (left) {
			delete left;
			left = nullptr;
		}
		if (right) {
			delete right;
			right = nullptr;
		}
	}

	~ParentLinkBST() { clear(); }

  protected:
	int data{};
	Derived *left{};
	Derived *right{};
	Derived *parent{};
};