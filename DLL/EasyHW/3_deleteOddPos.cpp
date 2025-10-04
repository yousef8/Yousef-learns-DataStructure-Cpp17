#include "../include/dll.hpp"
#include <initializer_list>

class DLLExt : public Dll {
  public:
	DLLExt() = default;

	DLLExt(const std::initializer_list<int> &lst) : Dll(lst) {}

	DLLExt(const DLLExt &another) = delete;
	DLLExt &operator=(const DLLExt &another) = delete;

	void delete_odd_pos() {
		for (Node *cur{head.get()}; cur;) {
			Node *to_be_deleted = cur;

			if ((cur = cur->next.get()))
				cur = cur->next.get();

			delete_a_node(to_be_deleted);
		}
		debug_verify_data_integrity();
	}
};

void test1() {
	std::cout << "\n\nTest 1\n";
	DLLExt ll{1};

	std::cout << ll << "\n";

	std::cout << "Delete Odd Postions\n";

	ll.delete_odd_pos();
	std::cout << ll << "\n";

	std::string expected = "";
	std::string result = ll.debug_to_string();
	if (expected != result) {
		std::cout << "no match:\nExpected: " << expected
				  << "\nResult : " << result << "\n";
		assert(false);
	}
	ll.debug_print_list("******************");
}

void test2() {
	std::cout << "\n\nTest 2\n";
	DLLExt ll{2, 1, 4, 3, 6, 5, 8, 7, 9};

	std::cout << ll << "\n";

	std::cout << "Delete Odd Positions\n";

	ll.delete_odd_pos();
	std::cout << ll << "\n";

	std::string expected = "1 3 5 7";
	std::string result = ll.debug_to_string();
	if (expected != result) {
		std::cout << "no match:\nExpected: " << expected
				  << "\nResult : " << result << "\n";
		assert(false);
	}
	ll.debug_print_list("******************");
}
int main() {
	test1();
	test2();
	std::cout << "\n\n NO RTE\n";
	return 0;
}
