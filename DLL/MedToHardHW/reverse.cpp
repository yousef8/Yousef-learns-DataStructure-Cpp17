#include "../include/dll.hpp"

class DllExt : public Dll {
  public:
	DllExt() = default;
	DllExt(const std::initializer_list<int> &lst) : Dll(lst) {}

	void reverse() {
		Node *current = head.get();
		Node *prev = nullptr;
		Node *next = nullptr;
		if (current) {
			prev = current->prev;
			next = current->next.get();
		}

		while (current) {
			current->next.release();
			current->next.reset(prev);
			current->prev = next;

			current = current->prev;
			if (current) {
				prev = current->prev;
				next = current->next.get();
			}
		}

		Node *temp = head.release();
		head.reset(tail);
		tail = temp;

		debug_verify_data_integrity();
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
	std::cout << "Current DllExt : " << dll << "\n";
	dll.reverse();
	std::cout << "Reversed DllExt : " << dll << "\n";

	std::cout << "=================Empty DllExt Test End==================\n";
}

void test_1_dll() {

	std::cout
		<< "================= DllExt with 1 element Begin==================\n";

	DllExt dll{1};
	std::cout << "Current DllExt : " << dll << "\n";
	dll.reverse();
	std::cout << "Reversed DllExt : " << dll << "\n";
	std::cout
		<< "================= DllExt with 1 element End==================\n";
}

void test_odd_dll() {

	std::cout << "================= DllExt with odd element "
				 "Begin==================\n";

	DllExt dll{1, 2, 3};

	std::cout << "Current DllExt : " << dll << "\n";
	dll.reverse();
	std::cout << "Reversed DllExt : " << dll << "\n";

	std::cout
		<< "================= DllExt with odd element End==================\n";
}

void test_even_dll() {

	std::cout << "================= DllExt with even element "
				 "Begin==================\n";

	DllExt dll{6, 10, 8, 15};

	std::cout << "Current DllExt : " << dll << "\n";
	dll.reverse();
	std::cout << "Reversed DllExt : " << dll << "\n";

	std::cout
		<< "================= DllExt with even element End==================\n";
}
