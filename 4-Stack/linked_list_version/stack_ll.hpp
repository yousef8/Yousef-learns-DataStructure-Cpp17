#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>

template <typename T> class Stack {
  private:
	struct Node {
		T data{};
		std::unique_ptr<Node> nxt;
		Node(T _data, std::unique_ptr<Node> _nxt = nullptr)
			: data{_data}, nxt{std::move(_nxt)} {}
	};

	std::unique_ptr<Node> head{};

  public:
	~Stack() {
		while (head) {
			auto next = std::move(head->nxt);
			head = std::move(next);
		}
	}

	void display() {
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

	T peek() {
		if (isEmpty()) {
			throw std::underflow_error("Stack is empty");
		}
		auto element = head->data;
		return element;
	}

	int isEmpty() { return !head; }
};
