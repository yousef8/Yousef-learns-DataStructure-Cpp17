#include <cassert>
#include <cmath>
#include <string>

template <typename Derived> class BST {
  protected:
	int data{};
	Derived *left{};
	Derived *right{};

  public:
	BST(int data) : data(data) {}

	std::string print_inorder() {
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
			if (!left)
				left = new Derived(target);
			else
				left->insert(target);
		} else if (target > data) {
			if (!right)
				right = new Derived(target);
			else
				right->insert(target);
		} // else: exists already
	}

	bool search(int target) { // tail recursion
		if (target == data)
			return true;

		if (target < data)
			return left && left->search(target);

		return right && right->search(target);
	}

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

	~BST() { clear(); }
};
