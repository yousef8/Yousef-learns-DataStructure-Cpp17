#include "../include/dll.hpp"

class DllExt : public Dll {
  public:
	DllExt() = default;
	DllExt(const std::initializer_list<int> &lst) : Dll(lst) {}

	void swapKthNode(int n) {
		if (n < 1) {
			return;
		}

		if (head.get() == tail) {
			return;
		}

		Node *first = this->head.get();
		Node *second = this->tail;
		int k = n;

		while (--k) {
			first = first->next.get();
			second = second->prev;
		}

		if (first == second) {
			return;
		}

		Node *front_of_first = first->next.get();
		Node *front_of_second = second->next.get();

		detach_node(first);
		detach_node(second);

		if (front_of_first == second) {
			attach_before(front_of_second, first);
			attach_before(first, second);
		} else {
			attach_before(front_of_first, second);
			attach_before(front_of_second, first);
		}

		debug_verify_data_integrity();
		return;
	}

	Node *detach_node(Node *node) {
		if (node == head.get()) {
			return detach_head();
		}

		if (node == tail) {
			return detach_tail();
		}

		return detach_middle(node);
	}

	Node *detach_head() {
		if (head.get() == tail && !head)
			return nullptr;

		delete_node(head.get());
		Node *detached_node = head.release();
		head.reset(detached_node->next.release());

		if (head)
			head->prev = nullptr;
		else
			tail = nullptr;

		reset_node_pointers(detached_node);
		debug_verify_data_integrity();

		return detached_node;
	}

	void reset_node_pointers(Node *node) {
		node->next.release();
		node->prev = nullptr;
		return;
	}

	Node *detach_tail() {
		if (head.get() == tail)
			return detach_head();

		tail = tail->prev;
		Node *detached_node = tail->next.release();

		delete_node(detached_node);

		reset_node_pointers(detached_node);
		debug_verify_data_integrity();

		return detached_node;
	}

	Node *detach_middle(Node *node) {
		Node *prev = node->prev;
		Node *detached_node = prev->next.release();

		link(prev, detached_node->next.release());
		delete_node(detached_node);

		reset_node_pointers(detached_node);
		debug_verify_data_integrity();
		return detached_node;
	}

	void attach_before(Node *cur_node, Node *new_node) {
		if (cur_node == head.get())
			return attach_head(new_node);

		if (!cur_node) {
			return attach_tail(new_node);
		}

		add_node(new_node);
		Node *prev = cur_node->prev;

		// new_node <-> cur
		link(new_node, prev->next.release());

		// prev <-> new_node <->cur
		link(prev, new_node);

		debug_verify_data_integrity();
		return;
	}

	void attach_head(Node *node) {
		add_node(node);
		link(node, head.release());
		head.reset(node);

		if (!tail)
			tail = head.get();

		debug_verify_data_integrity();
		return;
	}

	void attach_tail(Node *node) {
		add_node(node);
		link(tail, node);

		tail = node;

		if (!head) {
			head.reset(node);
		}

		debug_verify_data_integrity();
		return;
	}
};

void test_empty_dll(void);
void test_1_dll(void);
void test_odd_dll(void);
void test_even_dll(void);

int main() {
	test_empty_dll();
	test_1_dll();
	test_odd_dll();
	test_even_dll();

	return 0;
}

void test_empty_dll() {

	std::cout << "=================Empty DllExt Begin==================\n";

	DllExt dll{};
	std::cout << dll << std::endl;

	std::cout << "======swap 0 pair=======\n";
	dll.swapKthNode(0);
	std::cout << dll << std::endl;

	std::cout << "======swap 1 pair=======\n";
	dll.swapKthNode(1);
	std::cout << dll << std::endl;

	std::cout << "======swap 2 pair=======\n";
	dll.swapKthNode(2);
	std::cout << dll << std::endl;

	std::cout << "=================Empty DllExt Test End==================\n";
}

void test_1_dll() {

	std::cout
		<< "================= DllExt with 1 element Begin==================\n";

	DllExt dll{1};
	std::cout << dll << std::endl;

	std::cout << "======swap 0 pair=======\n";
	dll.swapKthNode(0);
	std::cout << dll << std::endl;

	std::cout << "======swap 1 pair=======\n";
	dll.swapKthNode(1);
	std::cout << dll << std::endl;

	std::cout << "======swap 2 pair=======\n";
	dll.swapKthNode(2);
	std::cout << dll << std::endl;

	std::cout
		<< "================= DllExt with 1 element End==================\n";
}

void test_odd_dll() {

	std::cout << "================= DllExt with odd element "
				 "Begin==================\n";

	DllExt dll{1, 2, 3};
	std::cout << dll << std::endl;

	std::cout << "======swap 0 pair=======\n";
	dll.swapKthNode(0);
	std::cout << dll << std::endl;

	std::cout << "======swap 1 pair=======\n";
	dll.swapKthNode(1);
	std::cout << dll << std::endl;

	std::cout << "======swap 2 pair=======\n";
	dll.swapKthNode(2);
	std::cout << dll << std::endl;

	std::cout
		<< "================= DllExt with odd element End==================\n";
}

void test_even_dll() {

	std::cout << "================= DllExt with even element "
				 "Begin==================\n";

	DllExt dll{6, 10, 8, 15};
	std::cout << dll << std::endl;

	std::cout << "======swap 0 pair=======\n";
	dll.swapKthNode(0);
	std::cout << dll << std::endl;

	std::cout << "======swap 1 pair=======\n";
	dll.swapKthNode(1);
	std::cout << dll << std::endl;

	std::cout << "======swap 2 pair=======\n";
	dll.swapKthNode(2);
	std::cout << dll << std::endl;

	std::cout
		<< "================= DllExt with even element End==================\n";
}
