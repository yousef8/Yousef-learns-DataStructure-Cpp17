#include <cassert>
#include <iostream>
#include <vector>

template <typename Derived> class BinaryTree {
  public:
	BinaryTree(int value) : data(value) {}

	void printInOrder() const {
		if (left) {
			left->printInOrder();
		}
		std::cout << data << " ";
		if (right) {
			right->printInOrder();
		}
	}

	void add(const std::vector<int> &values,
			 const std::vector<char> &directions) {

		if (values.size() != directions.size()) {
			throw std::invalid_argument("Values and directions size mismatch");
		}

		auto current = static_cast<Derived *>(this);

		for (size_t i = 0; i < values.size(); ++i) {
			if (directions[i] == 'L') {
				if (!current->left) {
					current->left = new Derived(values[i]);
				} else {
					assert(current->left->data == values[i] &&
						   "Node already exists with different value");
				}
				current = current->left;
			} else if (directions[i] == 'R') {
				if (!current->right) {
					current->right = new Derived(values[i]);
				} else {
					assert(current->right->data == values[i] &&
						   "Node already exists with different value");
				}
				current = current->right;
			}
		}
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

	virtual ~BinaryTree() { clear(); }

  protected:
	int data{};
	Derived *left{nullptr};
	Derived *right{nullptr};
};
