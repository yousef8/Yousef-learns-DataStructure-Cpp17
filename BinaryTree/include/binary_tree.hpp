#include <cassert>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

template <typename Derived, typename T = int> class BinaryTree {
  public:
	BinaryTree(T value) : data(value) {}

	void printInOrder() const {
		if (left) {
			left->printInOrder();
		}
		std::cout << data << " ";
		if (right) {
			right->printInOrder();
		}
	}

	void add(const std::vector<T> &values,
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

	std::string preOrder() const {
		std::string result{};
		result.append(std::to_string(data) + " ");
		if (left) {
			result += left->preOrder();
		}
		if (right) {
			result += right->preOrder();
		}
		return result;
	}

	std::string inOrder() const {
		std::string result;
		if (left) {
			result += left->inOrder();
		}
		result += std::to_string(data) + " ";
		if (right) {
			result += right->inOrder();
		}
		return result;
	}

	std::string postOrder() const {
		std::string result;
		if (left) {
			result += left->postOrder();
		}
		if (right) {
			result += right->postOrder();
		}
		result.append(std::to_string(data) + " ");
		return result;
	}

	std::string breadthFirst() const {
		std::string result;
		std::queue<const Derived *> q;
		q.push(static_cast<const Derived *>(this));

		while (!q.empty()) {
			const Derived *current = q.front();
			q.pop();

			result += std::to_string(current->data) + " ";

			if (current->left) {
				q.push(current->left);
			}
			if (current->right) {
				q.push(current->right);
			}
		}

		if (!result.empty()) {
			result.pop_back();
		}

		return result;
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
	T data{};
	Derived *left{nullptr};
	Derived *right{nullptr};
};
