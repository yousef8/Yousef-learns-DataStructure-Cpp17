#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>

typedef char type;

class Stack {
  private:
	struct Node {
		type data{};
		std::unique_ptr<Node> nxt;
		Node(type _data, std::unique_ptr<Node> _nxt = nullptr)
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

	void push(type value) {
		head = std::unique_ptr<Node>(new Node{value, std::move(head)});
	}

	type pop() {
		if (isEmpty()) {
			throw std::underflow_error("Stack is empty");
		}
		int element = head->data;
		auto next = std::move(head->nxt);
		head = std::move(next);
		return element;
	}

	type peek() {
		if (isEmpty()) {
			throw std::underflow_error("Stack is empty");
		}
		int element = head->data;
		return element;
	}

	int isEmpty() { return !head; }
};
