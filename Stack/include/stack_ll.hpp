#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>

template <typename T> class Stack {
  public:
	~Stack() {
		while (head) {
			auto next = std::move(head->nxt);
			head = std::move(next);
		}
	}

	void display() const {
		Node *current = head.get();

		while (current) {
			std::cout << current->data << " ";
			current = current->nxt.get();
		}
		std::cout << std::endl;
	}

	void push(T value) {
		head = std::unique_ptr<Node>(new Node{value, std::move(head)});
	}

	T pop() {
		if (isEmpty()) {
			throw std::underflow_error("Stack is empty");
		}
		auto element = head->data;
		auto next = std::move(head->nxt);
		head = std::move(next);
		return element;
	}

	T peek() const {
		if (isEmpty()) {
			throw std::underflow_error("Stack is empty");
		}
		auto element = head->data;
		return element;
	}

	int isEmpty() const { return !head; }

  private:
	struct Node {
		T data{};
		std::unique_ptr<Node> nxt;
		Node(T _data, std::unique_ptr<Node> _nxt = nullptr)
			: data{_data}, nxt{std::move(_nxt)} {}
	};

	std::unique_ptr<Node> head{};
};
